#include <WiFi.h>
#pragma once
namespace WLAN
{
    class HHN_Server
    {
    private:
        WiFiServer server;

    public:
        HHN_Server();
        void run();
        void init();
       WiFiServer getServer();
    };
    extern HHN_Server server;
} // namespace WLAN
