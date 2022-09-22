#include <Arduino.h>
#include <WiFi.h>

#include "communication/client/socket/socket.h"
#include "communication/communication.h"

// Creates the connection between server and client

namespace HHN_Client
{
        IPAddress server_ip(192, 168, 4, 1);
        int port = 80;
    void createConnection()
    {
        externalClient.connectToIpAndPort(server_ip, port);
    }
} // namespace Client
