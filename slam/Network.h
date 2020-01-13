//
// Created by steve on 01.01.20.
//

#ifndef SLAM_NETWORK_H
#define SLAM_NETWORK_H

#include <enet/enet.h>
#include <vector>

class Network {
public:
    /**
     * Constructor of the network class.
     * @param hostname The hostname or IP address of the server.
     * @param port The port to which to connect.
     */
    Network(std::string hostname, int port);
    ~Network();

    /**
     * This function returns the last received message.
     * @param channel Overwrites the given integer with the channel ID on which the data arrived.
     * @return The data as vector of u_char.
     */
    u_int8_t GetNextMessage(std::vector<u_char> &buffer);

    /**
     * Sends the data to the connected peer.
     * @param buffer The data to be sent.
     * @param size The size of the buffer.
     */
    void SendMessage(uint8_t* buffer, int size);

    uint32_t GetMeanPing();

    uint32_t GetMeanLostPackages();

    enum CHANNELS {NONE_CHANNEL = 255, CAMERA_CHANNEL = 0, COMMAND_CHANNEL = 1, INFO_CHANNEL = 2};
private:
    ENetHost * client;
    ENetAddress address;
    ENetEvent event;
    ENetPeer *peer;

    void Connect();
};


#endif //SLAM_NETWORK_H
