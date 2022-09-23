#include <Arduino.h>
#include <WiFi.h>

#include "communication/client/socket/socket.h"

// Creates the connection between server and client

namespace HHN_Client
{
    HHN_Client::Socket externalClient;
    WiFiClient client;
    IPAddress server_ip(192, 168, 4, 1);
    int port = 80;
    void createConnection()
    {
        externalClient.setClient(client);
        externalClient.connectToIpAndPort(server_ip, port);
    }
} // namespace Client
