//
// Created by steve on 21.12.19.
//

#include <chrono>
#include <thread>
#include "G203.h"
#include <stdint.h>
#include <iostream>
#include "generated/TrackedMotorThrottle_generated.h"
#include "generated/Register_generated.h"
#include "generated/Data_generated.h"
#include <chrono>
#include <zconf.h>

namespace themachineeu
{
    G203::G203()
    {

    }

    G203::~G203()
    {

    }

    void G203::Run()
    {
        std::vector<u_char> receivedData;
        int numberOfClients = 0;

        while(m_isRunning)
        {
            // loop as long as there are network packets
            uint8_t channel = m_network.NONE_CHANNEL;
            do
            {
                channel = m_network.GetMessages(receivedData);
                if(channel == m_network.COMMAND_CHANNEL)
                    ExecuteCommands(receivedData);
            } while(channel != m_network.NONE_CHANNEL);

            // check if new clients connected or disconnected, if yes stop motors
            if(m_network.GetNumberOfPeers() != numberOfClients)
            {
                leftMotor.Stop();
                rightMotor.Stop();
                numberOfClients = m_network.GetNumberOfPeers();
            }

            // get the current frame from the camera
            std::vector<u_char> buffer = m_camera.GetFrame();
            // send the current camera frame to all peers
            m_network.SendMessage(buffer, m_network.CAMERA_CHANNEL);
            //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            //std::cout << "Time difference = " << chr << "[µs]" << std::endl;

            if(numberOfClients == 0)
            {
                sleep(0.25);
            }
        }
    }

    void G203::ExecuteCommands(std::vector<u_char> &data)
    {
        if(data.size() == 0)
        {
            return;
        }
        /*auto dataObject = GetDataObject(data.data());
        auto type = dataObject->dType();
        switch(type)
        {
            DataType_E_Register:
                break;
        }*/
        auto trackedMotorThrottle = GetTrackedMotorThrottle(data.data());

        leftMotor.SetTargetSpeed(trackedMotorThrottle->leftMotor());
        rightMotor.SetTargetSpeed(trackedMotorThrottle->rightMotor());
        //std::cout << "left " << trackedMotorThrottle->leftMotor() << "\t" << "right " << trackedMotorThrottle->rightMotor() << std::endl;
    }
}