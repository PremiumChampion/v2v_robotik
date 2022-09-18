#include <Arduino.h>
#include <WiFi.h>
#include "socket.h"

HHN_Client::Socket chaserClient;
HHN_Client::Socket chased_oneClient;
namespace HHN_Client
{

    Socket::Socket(WiFiClient client)
    {
        this->client = client;
        // TODO: set static client
    }
    Socket::~Socket() {}

    void Socket::send(String data)
    {
        this->client.println(data);
    }

    String Socket::rcv()
    {
        String data = "";
        while (this->client.available())
        {
            char c = this->client.read();
            data += c;
        }
        return data;
    }

    void Socket::run()
    {
    }
    // Socket Socket::getSocket()
    // {
    //     return NULL;
    // }

} // namespace Client
