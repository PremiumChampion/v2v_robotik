#include <WiFi.h>
#pragma once
namespace HHN
{
    class Server
    {
    private:
        WiFiServer server;
        Server(/* args */);
        static Server hhn_server;
    public:
        static Server *getServer();
        void run();
    };

} // namespace HHN
