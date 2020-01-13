//
// Created by steve on 21.12.19.
//

#ifndef G203_G203_H
#define G203_G203_H


#include <cstdint>
#include "parts/Motor.h"
#include "parts/Camera.h"
#include "Network.h"
namespace themachineeu
{
    class G203 {
    public:
        G203();
        ~G203();

        /**
         * Starts the vehicle with all its components.
         */
        void Run();

    private:
        static constexpr int64_t ONE_MILLI_SECOND = 1000000;
        static constexpr int64_t UPDATE_TIME = ONE_MILLI_SECOND * 14; // = ~60 FPS

        bool m_isRunning    = true;
        int m_port          = 8887;
        Motor leftMotor     {28, 27, 26, 0.4};
        Motor rightMotor    {21, 22, 23, 0.4};
        Network m_network;
        Camera m_camera;

        /**
         * Takes the buffer which contains commands.
         * @param data The buffer with the data.
         */
        void ExecuteCommands(std::vector<u_char> &data);
    };
}
#endif //G203_G203_H
