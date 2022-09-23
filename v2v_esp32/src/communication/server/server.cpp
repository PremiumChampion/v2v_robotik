#include <WiFi.h>

#include "server.h"
#include "communication/client/socket/socket.h"

namespace WLAN
{
    HHN_Client::Socket externalClient;
    HHN_Server::HHN_Server()
    {
        this->server = WiFiServer(80);
        this->server.begin();
        Serial.println("Server started!");
    }

    void HHN_Server::run()
    {
        do
        {
            WiFiClient client = this->server.available(); // Check if a new client connected
            // Check, if a client is connected to the server
            if (client)
            {
                Serial.println("New client successfully connected!");
                externalClient.setClient(client);
            }
        } while (1);
    }

} // namespace WLAN
