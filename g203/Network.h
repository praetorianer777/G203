//
// Created by steve on 23.12.19.
//

#ifndef G203_NETWORK_H
#define G203_NETWORK_H

#include <enet/enet.h>
#include <vector>
#include <set>

class Network {
public:
    Network();
    ~Network();

    enum CHANNELS {NONE_CHANNEL = 255, CAMERA_CHANNEL = 0, COMMAND_CHANNEL = 1, INFO_CHANNEL = 2};

    /**
     * Get all network messages.
     * @param buffer The buffer as a reference (will be filled with the received data).
     * @return The channel on which the data are received.
     */
    uint8_t GetMessages(std::vector<u_char> &buffer);

    /**
     * Send a message to all peers on the given channel.
     * @param buffer The data to send.
     * @param channel The channel on which the data are sent.
     */
    void SendMessage(std::vector<u_char> &buffer, uint8_t channel);

    /**
     * Get the number of connected peers.
     * @return Number of connected peers.
     */
    uint8_t GetNumberOfPeers();
private:
    ENetAddress address;
    ENetHost * server;
    ENetEvent event;
    std::set<ENetPeer*> peers;
};


#endif //G203_NETWORK_H
