#include <Arduino.h>
#include <WiFi.h>

#include "communication/client/socket/socket.h"

// Creates the connection between server and client

WiFiClient client;
IPAddress server_ip(192, 168, 4, 1);
int port = 80;

namespace HHN_Client
{
    Socket* createConnection()
    {
        while (!client.connected()) // Try to reconnect if connection isn't possible.
        {
            client.connect(server_ip, port);
            delay(200); // Give the connection establishment time to connect to the server.
        }
        Serial.println("Connected to server");

        return new Socket(client);
    }
} // namespace Client
