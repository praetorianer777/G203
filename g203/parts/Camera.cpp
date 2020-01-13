//
// Created by steve on 23.12.19.
//

#include "Camera.h"
Camera::Camera()
{
    // open camera device (here the first and default camera will be opened)
    m_cap = cv::VideoCapture(0);
    m_cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    m_cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    m_cap.set(cv::CAP_PROP_FPS, 60);
}

Camera::~Camera()
{
    // close the camera access
    m_cap.release();
}

std::vector<u_char>& Camera::GetFrame()
{
    m_buffer.clear();
    if (!m_cap.isOpened()) {
        perror("ERROR! Unable to open camera\n");
        exit(-1);
    }

    // read next frame from camera
    m_cap.read(m_frame);
    cv::imencode(".jpg", m_frame, m_buffer);

    return m_buffer;
}