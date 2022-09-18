#include <Arduino.h>
#include <WiFi.h>

#include "communication/client/socket/socket.h"

// Creates the connection between server and client

WiFiClient client;
IPAddress server_ip(192, 168, 4, 1);
int port = 80;

namespace HHN_Client
{
    Socket createConnection()
    {
        client.connect(server_ip, port);
        while (!client.connected())
        {
        }
        Serial.println("Connected to server");
        HHN_Client::Socket smthing = Socket(client);

        return smthing;
    }
} // namespace Client
