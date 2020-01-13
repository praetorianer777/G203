//
// Created by steve on 09.01.20.
//

#include "PID.h"

#include <array>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cv.hpp>

PID::PID()
{

}

PID::~PID()
{

}

float PID::GetSteering(cv::Mat frame)
{
    cv::Mat row = frame.row(0);
    //frame *= 2;
    // convert to grey
    cv::Mat rowGray;
    cv::cvtColor(frame, rowGray, CV_BGR2GRAY);
    cv::Mat rowBlackWhite;
    cv::threshold(rowGray, rowBlackWhite, 180, 255, CV_THRESH_BINARY);

    cv::bilateralFilter(rowBlackWhite, rowGray, 7, 50, 50);
    cv::Canny(rowGray, rowBlackWhite, 100, 180);
/*
    int firstWhiteIndex = 0;
    int lastWhiteIndex = 639;
    for(int i = 0; i < rowBlackWhite.cols; i++)
    {
        if(rowBlackWhite.at<uint8_t>(i)==255)
        {
            firstWhiteIndex = i;
            break;
        }
    }

    for(int i = rowBlackWhite.cols; i > 0; i--)
    {
        if(rowBlackWhite.at<uint8_t>(i)==255)
        {
            lastWhiteIndex = i;
            break;
        }
    }*/

    //float p = CalcP(lastWhiteIndex, firstWhiteIndex);
    cv::imshow("bw", rowBlackWhite);
    cv::waitKey(1);
    return 0;
}

float PID::CalcP(int lastWhiteIndex, int firstWhiteIndex)
{
    int currentMidPos = lastWhiteIndex - firstWhiteIndex;

    // if currentMidPos == 320, then error is 0, because we drive with line in mid
    // if currentMidPos == 0, then error is -320, which means full left steering
    int error = currentMidPos - 320;

    error = firstWhiteIndex - 320;

    return (1.f / 320.f * static_cast<float>(error)) * kp;
}

float PID::CalcI()
{
    return 0;
}

float PID::CalcD()
{
    return 0;
}