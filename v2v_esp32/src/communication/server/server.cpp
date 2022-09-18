#include <WiFi.h>
#include "server.h"

#include "communication/client/socket/socket.h"

namespace WLAN
{
    HHN_Server::HHN_Server()
    {
        this->server = WiFiServer(80);
        server.begin();
        Serial.println("Server started!");
    }

    HHN_Client::Socket :run()
    {
        WiFiClient client = this->server.available(); // Check if a new client connected

        if (client)
        {   Serial.println("New client successfully connected!");
            return HHN_Client::Socket(client);
        }
    }

} // namespace WLAN
