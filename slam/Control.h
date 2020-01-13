//
// Created by steve on 06.01.20.
//

#ifndef SLAM_CONTROL_H
#define SLAM_CONTROL_H


#include <string>
#include "Network.h"
#include <SFML/Graphics.hpp>
#include "generated/TrackedMotorThrottle_generated.h"
#include "generated/Register_generated.h"
#include "generated/Data_generated.h"

class Control {
public:
    Control(std::string ip, int port, bool record, std::string recordPath);
    ~Control();
    void Run();
private:
    Network m_network;
    struct Moves
    {
        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;
    } m_moves;                  // registered pressed arrow keys
    struct MoveCommand
    {
        float left = 0;
        float right = 0;
    } m_moveCommand;            // data sent to the vehicle

    bool m_record;              // do we want to record data?
    std::string m_recordPath;   // path where the recorded files be saved
    uint8_t m_frameCounter;       // this is that we only save every x frame

    void InterpretMoves();
    void SendMoveCommands(flatbuffers::FlatBufferBuilder &builder);
};


#endif //SLAM_CONTROL_H
