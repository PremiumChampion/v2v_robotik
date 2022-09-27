#include <WiFi.h>

#include "server.h"
#include "communication/client/socket.h"
#include "communication/communication.h"
namespace WLAN
{
    HHN_Server::HHN_Server()
    {
        this->server = WiFiServer(80);
       
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
                COM::externalClient.setClient(client);
                return;
            }
        } while (1);
    }

    WiFiServer HHN_Server::getServer(){
        return this->server;
    }

    void HHN_Server::init(){
        this->server.begin();
        Serial.println("Server started!");
    }

} // namespace WLAN
