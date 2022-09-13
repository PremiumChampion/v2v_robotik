#include <Arduino.h>
#include <WiFi.h>
#include "socket.h"

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
    }
    String Socket::rcv()
    {
        return "";
    }
    void Socket::run()
    {
    }
    Socket Socket::getSocket()
    {
        return NULL;
    }

} // namespace Client
