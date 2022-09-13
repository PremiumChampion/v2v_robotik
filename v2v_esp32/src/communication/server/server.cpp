#include <WiFi.h>
#include "server.h"
#include "communication/client/socket/socket.h"

namespace WLAN
{
    HHN_Server::HHN_Server()
    {
        this->server = WiFiServer(80);
    }

    void HHN_Server::run()
    {
        WiFiClient client = this->server.available();

        if (client)
        {
            new HHN_Client::Socket(client);
        }
    }

} // namespace WLAN
