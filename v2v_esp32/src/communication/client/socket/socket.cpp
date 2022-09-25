#include <Arduino.h>
#include <WiFi.h>

#include "socket.h"

namespace HHN_Client
{
    Socket::Socket()
    {
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
        this->client.println(data);
    }

    String Socket::rcv()
    {
        Serial.println("Method: rcv"); //
        String data = "";
        Serial.print("Client: "); //
        while (this->client.available())
        {
            char c = this->client.read();
            Serial.print(c); //
            data += c;
        }
        Serial.println(); //
        return data;
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

} // namespace Client
