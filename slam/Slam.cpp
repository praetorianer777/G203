//
// Created by steve on 06.01.20.
//

#include "Slam.h"
Slam::Slam(std::string ip, int port, std::string vocabFile, std::string cameraFile)
: m_network(ip, port), m_slam(vocabFile, cameraFile, ORB_SLAM2::System::MONOCULAR, true)
{

}

Slam::~Slam()
{

}

void Slam::Run()
{
    cv::Point2f src_center(m_frame.cols/2.0F, m_frame.rows/2.0F);
    cv::Mat rot_mat = getRotationMatrix2D(src_center, 180, 1.0);
    cv::Mat dst;
    while(true)
    {
        //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::vector<u_char> buffer;
        uint8_t channel = m_network.GetNextMessage(buffer);

        if(channel != m_network.CAMERA_CHANNEL)
            continue;

        m_frame = cv::imdecode(buffer, 1);

        //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[µs]" << std::endl;

        // check if we succeeded
        if (m_frame.empty())
        {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        else
        {
            double tframe = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
            warpAffine(m_frame, dst, rot_mat, m_frame.size());

            m_slam.TrackMonocular(dst, tframe);
        }
    }
    m_slam.Shutdown();
}