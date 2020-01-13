#include "Argparse.h"
#include "Control.h"
#include "Slam.h"

int main(int argc, const char* argv[]) {
    argparse::ArgumentParser parser("G203 frontend argument parser.");
    parser.add_argument()
            .name("--mode")
            .description("Which mode to run (1 = SLAM; 2 = Control).")
            .required(true);
    parser.add_argument()
            .name("--cameraConfig")
            .description("Total path to the camera config file (yaml).")
            .required(false);
    parser.add_argument()
            .name("--vocab")
            .description("Total path to the vocab file.")
            .required(false);
    parser.add_argument()
            .name("--ip")
            .description("IP adress or hostname to which to connect.")
            .required(false);
    parser.add_argument()
            .name("--port")
            .description("Port to connect to.")
            .required(false);
    parser.add_argument()
            .name("--recordPath")
            .description("If this is set the program will record images and steering.")
            .required(false);
    parser.enable_help();

    std::string ip = "141.32.21.181";
    int port = 5555;
    std::string cameraConfig = "/home/steve/CLionProjects/slam/files/camera.yaml";
    std::string vocabFile = "/home/steve/CLionProjects/slam/files/ORBvoc.txt";
    std::string recordPath = "";
    bool record = false;

    auto parserErr = parser.parse(argc, argv);
    if(parserErr)
    {
        perror("Error parsing arguments.");
        exit(-1);
    }

    if(parser.exists("help"))
    {
        parser.print_help();
        exit(0);
    }

    if(parser.exists("ip"))
        ip = parser.get<std::string>("ip");
    if(parser.exists("port"))
        port = parser.get<int>("port");
    if(parser.exists("cameraConfig"))
        cameraConfig = parser.get<std::string>("cameraConfig");
    if(parser.exists("vocab"))
        vocabFile = parser.get<std::string>("vocab");
    if(parser.exists("recordPath"))
    {
        recordPath = parser.get<std::string>("recordPath");
        record = true;
    }

    if (parser.get<int>("mode") == 1)
    {
        Slam slam(ip, port, vocabFile, cameraConfig);
        slam.Run();
    }
    else
    {
        Control control(ip, port, record, recordPath);
        control.Run();
    }
    return 0;
}