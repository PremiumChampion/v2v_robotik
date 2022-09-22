#include <Arduino.h>
#include <WiFi.h>
#include "socket.h"

namespace HHN_Client
{

    Socket::Socket()
    {
        // TODO: set static client
    }

    void Socket::setClient(WiFiClient client)
    {
        this->client = client;
    }

    // Socket::Socket(WiFiClient client)
    // {
    //     this->client = client;
    //     // TODO: set static client
    // }

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

    void Socket::connectToIpAndPort(IPAddress ip, int port)
    {
        while (!this->client.connected()) // Try to reconnect if connection isn't possible.
        {
            this->client.connect(ip, port);
            delay(200); // Give the connection establishment time to connect to the server.
        }
        Serial.println("Connected to server");
    }

    void Socket::run()
    {
    }
    // Socket Socket::getSocket()
    // {
    //     return NULL;
    // }

} // namespace Client
