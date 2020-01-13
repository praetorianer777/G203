//
// Created by steve on 06.01.20.
//

#ifndef SLAM_SLAM_H
#define SLAM_SLAM_H

#include <System.h>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include "Network.h"

class Slam {
public:
    Slam(std::string ip, int port, std::string vocabFile, std::string cameraFile);
    ~Slam();
    void Run();
private:
    ORB_SLAM2::System m_slam;
    cv::Mat m_frame{480, 640, 16};
    Network m_network;
};


#endif //SLAM_SLAM_H
