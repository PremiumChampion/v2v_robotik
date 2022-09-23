#include <WiFi.h>
namespace WLAN
{
    class HHN_Server
    {
    private:
        WiFiServer server;

    public:
        HHN_Server();
        void run();
    };

    extern HHN_Server server;
} // namespace WLAN
