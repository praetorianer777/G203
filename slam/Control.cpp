//
// Created by steve on 06.01.20.
//

#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "Control.h"
#include "PID.h"

Control::Control(std::string ip, int port, bool record, std::string recordPath) : m_network(ip, port)
{
    m_record = record;
    m_recordPath = recordPath;
}

Control::~Control()
{

}

void Control::Run()
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 500;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "G203");
    window.setFramerateLimit(60);
    sf::Texture texture;
    sf::Sprite sprite;
    sprite.setPosition(sf::Vector2f(640.f, 480.f));
    sprite.setRotation(180.f);
    flatbuffers::FlatBufferBuilder builder;

    sf::Font font;
    if (!font.loadFromFile("8bitOperatorPlus8-Regular.ttf"))
    {
        perror("error loading font");
        exit(-1);
    }

    sf::Text text;
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setPosition(0.f, 470.f);

    PID pid;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Up)
                        m_moves.upPressed = true;
                    if (event.key.code == sf::Keyboard::Down)
                        m_moves.downPressed = true;
                    if (event.key.code == sf::Keyboard::Left)
                        m_moves.leftPressed = true;
                    if (event.key.code == sf::Keyboard::Right)
                        m_moves.rightPressed = true;
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Up)
                        m_moves.upPressed = false;
                    if (event.key.code == sf::Keyboard::Down)
                        m_moves.downPressed = false;
                    if (event.key.code == sf::Keyboard::Left)
                        m_moves.leftPressed = false;
                    if (event.key.code == sf::Keyboard::Right)
                        m_moves.rightPressed = false;
                    break;
                default:
                    break;
            }
        }
        if (sf::Joystick::isConnected(0))
        {
            // y and v for-/backward
            // x and u sideways
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            float v = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
            m_moveCommand.left = y / -100.f;
            m_moveCommand.right = v / -100.f;

        }
        else
        {
            InterpretMoves();
        }
        SendMoveCommands(builder);

        std::vector<u_char> buffer;
        uint8_t channel = m_network.GetNextMessage(buffer);
        if(channel == m_network.CAMERA_CHANNEL)
        {
            if(buffer.size() != 0)
            {

                /*
                float steering = pid.GetSteering(cv::imdecode(buffer, 1));
                if(steering < 0)
                {
                    m_moveCommand.right = 1;
                    m_moveCommand.left = 1 - abs(steering);
                }
                if(steering > 0)
                {
                    m_moveCommand.right = 1 - abs(steering);
                    m_moveCommand.left = 1;
                }
                std::cout << "left: " << m_moveCommand.left << "\t" << "right: " <<  m_moveCommand.right << std::endl;
                */
                //SendMoveCommands(builder);


                if(!texture.loadFromMemory(&buffer.at(0), buffer.size()))
                {
                    perror("texture loading failed...");
                    exit(-1);
                }
                sprite.setTexture(texture, true);
                if(m_record == true)
                {
                    m_frameCounter++;
                    if(m_frameCounter > 9)
                    {
                        // only if throttle of one motor is greater than 20%
                        if(m_moveCommand.left > 0.2f || m_moveCommand.right > 0.2f)
                        {
                            m_frameCounter = 0;
                            // get unique timestamp
                            auto timeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                            std::stringstream ss;
                            ss << m_recordPath << timeStamp << ".jpg";

                            // save image
                            texture.copyToImage().saveToFile(ss.str());

                            // save motor throttle
                            ss.str(std::string());
                            ss << m_recordPath << timeStamp << ".dat";
                            std::ofstream file;
                            file.open (ss.str());
                            file << "left=" << m_moveCommand.left << "\nright=" << m_moveCommand.right;
                            file.close();
                        }
                    }
                }
            }
        }
        std::stringstream ss;
        ss << "Ping: " << m_network.GetMeanPing();
        ss << "\tLost Packages: " << m_network.GetMeanLostPackages();
        //ss << "\tBandwidth: " << m_network.GetBandWidth();
        text.setString(ss.str());
        window.clear(sf::Color::Black);
        window.draw(text);
        window.draw(sprite);
        window.display();
    }
}

void Control::SendMoveCommands(flatbuffers::FlatBufferBuilder &builder)
{
    themachineeu::TrackedMotorThrottleBuilder tmtBuilder(builder);
    tmtBuilder.add_rightMotor(m_moveCommand.right);
    tmtBuilder.add_leftMotor(m_moveCommand.left);
    auto motorControl = tmtBuilder.Finish();
    builder.Finish(motorControl);
    uint8_t* dataBuffer = builder.GetBufferPointer();
    m_network.SendMessage(dataBuffer, builder.GetSize());
}

void Control::InterpretMoves()
{
    if(m_moves.downPressed == true && m_moves.leftPressed == true && m_moves.rightPressed == true && m_moves.upPressed ==true)
    {
        m_moveCommand.left = 0;
        m_moveCommand.right = 0;
    }
    else if (m_moves.downPressed == true && m_moves.leftPressed == true && m_moves.rightPressed == true && m_moves.upPressed == false)
    {
        m_moveCommand.left = -1;
        m_moveCommand.right = -1;
    }
    else if (m_moves.downPressed == true && m_moves.leftPressed == true && m_moves.rightPressed == false && m_moves.upPressed == true)
    {
        m_moveCommand.left = -1;
        m_moveCommand.right = 1;
    }
    else if (m_moves.downPressed == true && m_moves.leftPressed == true && m_moves.rightPressed == false && m_moves.upPressed == false)
    {
        m_moveCommand.left = -0.5;
        m_moveCommand.right = -1;
    }
    else if (m_moves.downPressed == true && m_moves.leftPressed == false && m_moves.rightPressed == true && m_moves.upPressed == true)
    {
        m_moveCommand.left = 1;
        m_moveCommand.right = -1;
    }
    else if (m_moves.downPressed == true && m_moves.leftPressed == false && m_moves.rightPressed == true && m_moves.upPressed == false)
    {
        m_moveCommand.left = -1;
        m_moveCommand.right = -0.5;
    }
    else if (m_moves.downPressed == true && m_moves.leftPressed == false && m_moves.rightPressed == false && m_moves.upPressed == true)
    {
        m_moveCommand.left = 0;
        m_moveCommand.right = 0;
    }
    else if (m_moves.downPressed == true && m_moves.leftPressed == false && m_moves.rightPressed == false && m_moves.upPressed == false)
    {
        m_moveCommand.left = -1;
        m_moveCommand.right = -1;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == true && m_moves.rightPressed == true && m_moves.upPressed == true)
    {
        m_moveCommand.left = 1;
        m_moveCommand.right = 1;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == true && m_moves.rightPressed == true && m_moves.upPressed == false)
    {
        m_moveCommand.left = 0;
        m_moveCommand.right = 0;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == true && m_moves.rightPressed == false && m_moves.upPressed == true)
    {
        m_moveCommand.left = 0.5;
        m_moveCommand.right = 1;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == true && m_moves.rightPressed == false && m_moves.upPressed == false)
    {
        m_moveCommand.left = -1;
        m_moveCommand.right = 1;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == false && m_moves.rightPressed == true && m_moves.upPressed == true)
    {
        m_moveCommand.left = 1;
        m_moveCommand.right = 0.5;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == false && m_moves.rightPressed == true && m_moves.upPressed == false)
    {
        m_moveCommand.left = 1;
        m_moveCommand.right = -1;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == false && m_moves.rightPressed == false && m_moves.upPressed == true)
    {
        m_moveCommand.left = 1;
        m_moveCommand.right = 1;
    }
    else if (m_moves.downPressed == false && m_moves.leftPressed == false && m_moves.rightPressed == false && m_moves.upPressed == false)
    {
        m_moveCommand.left = 0;
        m_moveCommand.right = 0;
    }
}