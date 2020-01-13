//
// Created by steve on 23.12.19.
//

#ifndef G203_CAMERA_H
#define G203_CAMERA_H

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <stdint.h>

class Camera {
public:
    Camera();
    ~Camera();

    /**
     * Captures a frame and returns it as a jpeg in a buffer.
     * @return std::vector<uchar> - The buffer containing the jpg.
     */
    std::vector<u_char> &GetFrame();

private:
    cv::Mat m_frame;
    cv::VideoCapture m_cap;
    std::vector<u_char> m_buffer;
};


#endif //G203_CAMERA_H
