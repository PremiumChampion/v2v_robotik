#include <WiFi.h>
namespace WLAN
{
    class HHN_Server
    {
    private:
        WiFiServer server;

    public:
        HHN_Client::Socket run();
    
    HHN_Server();
    };

    extern HHN_Server server;
} // namespace WLAN
