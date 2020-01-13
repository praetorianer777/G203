//
// Created by steve on 01.01.20.
//

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <thread>
#include "Network.h"

Network::Network(std::string hostname, int port)
{
    client = enet_host_create (nullptr /* create a client host */,
            1 /* only allow 1 outgoing connection */,
            3 /* allow up 2 channels to be used, 0 and 1 */,
            0 /* assume any amount of incoming bandwidth */,
            0 /* assume any amount of outgoing bandwidth */);
    if (client == nullptr)
    {
        perror("An error occurred while trying to create an ENet client host.\n");
        exit(-1);
    }
    enet_address_set_host (&address, hostname.c_str());
    address.port = port;
    Connect();
}

void Network::Connect()
{
    sleep(2);
    // initiate the connection, allocating the two channels 0 and 1
    peer = enet_host_connect(client, &address, 3, 0);
}

Network::~Network()
{
    enet_host_destroy(client);
}

void Network::SendMessage(uint8_t *buffer, int size)
{
    ENetPacket* packet = enet_packet_create (buffer, size, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(peer, 1, packet);
}

uint8_t Network::GetNextMessage(std::vector<u_char> & buffer)
{
    int eventStatus = enet_host_service (client, &event, 1000);
    if(eventStatus > 0)
    {
        switch (event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                printf ("A new client connected from %x:%u.\n",
                        event.peer->address.host,
                        event.peer->address.port);
                peer = event.peer;
                enet_peer_timeout(event.peer, 0, 0, 4096);
                std::cout << "connection successful" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                buffer.resize(event.packet->dataLength);
                std::copy(static_cast<u_char*>(event.packet->data), static_cast<u_char*>(event.packet->data) + event.packet->dataLength, buffer.begin());
                // clean up the packet
                enet_packet_destroy (event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "peer disconnected: " << event.peer->address.host << std::endl;
                /* Reset the peer's client information. */
                Connect();
        }
        return event.channelID;
    }
    return NONE_CHANNEL;
}

uint32_t Network::GetMeanPing()
{
    return peer->roundTripTime/2;
}

uint32_t Network::GetMeanLostPackages()
{
    return peer->packetLoss;
}