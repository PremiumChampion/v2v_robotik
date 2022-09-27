#include <Arduino.h>
#include <WiFi.h>

#include "socket.h"

namespace HHN_Client
{
    Socket::Socket()
    {
        this->rcvBuffer = "";
        // TODO: set static client
    }

    void Socket::setClient(WiFiClient& client)
    {
        this->client = client;
        Serial.println(this->client); //
    }

    Socket::~Socket() {}

    void Socket::send(String data)
    {
        this->client.println(data + "\n");
    }

    void Socket::run()
    {
        // Serial.println("Method: rcv"); //
        // Serial.print("Client: "); //
        while (this->client.available())
        {
            char c = this->client.read();
            // Serial.print(c); //
            this->rcvBuffer += c; 
        }
        
    }

        // recieve serial data strips newlines
    String Socket::recieve()
    {
        int nextNewlineLindex = this->rcvBuffer.indexOf('\n');
        if (nextNewlineLindex == -1)
            return "";

        String output = this->rcvBuffer.substring(0, nextNewlineLindex);
        this->rcvBuffer = this->rcvBuffer.substring(nextNewlineLindex + 1);
        return output;
    }
    // // send serial data
    // void Arduino2esp::send(String data)
    // {
    //     this->sndBuffer += data + '\n';
    // }

    void Socket::connectToIpAndPort(IPAddress ip, int port)
    {
        while (!this->client.connected()) // Try to reconnect if connection isn't possible.
        {
            this->client.connect(ip, port);
            delay(100); // Give the connection establishment time to connect to the server.
            Serial.println(client.connected());
        }
        Serial.println("Connected to server");
    }

    boolean Socket::isClientConnected(){
        return this->client.connected();
    }

} // namespace Client
