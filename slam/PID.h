//
// Created by steve on 09.01.20.
//

#ifndef SLAM_PID_H
#define SLAM_PID_H

#include <opencv2/core/mat.hpp>

class PID {
public:
    PID();
    ~PID();
    float GetSteering(cv::Mat frame);
private:
    float kp = 1;
    float ki = 1;
    float kd = 1;
    int MID = 320;

    float CalcP(int lastWhiteIndex, int firstWhiteIndex);
    float CalcI();
    float CalcD();
};


#endif //SLAM_PID_H
