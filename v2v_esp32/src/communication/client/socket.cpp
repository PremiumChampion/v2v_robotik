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
        while (this->client.available())
        {
            char c = this->client.read();
            this->rcvBuffer += c; 
        }

        //Wo receive reinschreiben und daten an broker übergeben
        //Hier oder in transfer.cpp

    }

        // receive serial data strips newlines
    String Socket::receive()
    {
        int nextNewlineLindex = this->rcvBuffer.indexOf('\n'); // Check if rcvBuffer has one finished data frame
        if (nextNewlineLindex == -1)
            return ""; // Return with no data if there is no data or just a incomplete data frame.

        String output = this->rcvBuffer.substring(0, nextNewlineLindex);
        this->rcvBuffer = this->rcvBuffer.substring(nextNewlineLindex + 1);
        return output;
    }

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

    boolean Socket::hasClientData(){
        return this->rcvBuffer.indexOf("\n") + 1;
    }

} // namespace Client
