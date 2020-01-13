//
// Created by steve on 23.12.19.
//

#include <iostream>
#include "Network.h"
Network::Network()
{
    if (enet_initialize () != 0)
    {
        perror("An error occurred while initializing ENet.\n");
        exit(-1);
    }
    address.host = ENET_HOST_ANY;
    address.port = 5555;

    server = enet_host_create (& address /* the address to bind the server host to */,
                               32      /* allow up to 4 clients and/or outgoing connections */,
                               3      /* allow up to 3 channels to be used, 0, 1 and 2 */,
                               0      /* assume any amount of incoming bandwidth */,
                               0      /* assume any amount of outgoing bandwidth */);
    if (server == NULL)
    {
        perror("An error occurred while trying to create an ENet server host.\n");
        exit (-1);
    }
}

Network::~Network()
{
    enet_host_destroy(server);
}

void Network::SendMessage(std::vector<u_char> &buffer, uint8_t channel)
{
    ENetPacket* packet = enet_packet_create (&buffer.front(), buffer.size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_host_broadcast (server, channel, packet);
}

uint8_t Network::GetMessages(std::vector<u_char> &buffer)
{
    int eventStatus = enet_host_service (server, &event, 0);
    if(eventStatus > 0)
    {
        switch (event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "peer with address " << event.peer->host->address.host << "connected" << std::endl;
                peers.insert(event.peer);
                //enet_peer_timeout(event.peer, 0, 0, 4096);
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                buffer.resize(event.packet->dataLength);
                std::copy(static_cast<u_char*>(event.packet->data), static_cast<u_char*>(event.packet->data) + event.packet->dataLength, buffer.begin());
                // clean up the packet now that we're done using it
                enet_packet_destroy (event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "peer with address " << event.peer->host->address.host << "disconnected" << std::endl;
                // reset the peer's client information
                event.peer->data = nullptr;
                peers.erase(event.peer);
        }
        return event.channelID;
    }
    return NONE_CHANNEL;
}

uint8_t Network::GetNumberOfPeers()
{
    return peers.size();
}