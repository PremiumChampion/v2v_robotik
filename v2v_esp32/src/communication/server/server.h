#include <WiFi.h>

namespace WLAN
{
    class HHN_Server
    {
    private:
        WiFiServer server;
        HHN_Server(/* args */);

    public:
        void run();
    };

    extern HHN_Server server;
} // namespace WLAN
