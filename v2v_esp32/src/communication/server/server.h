#include <WiFi.h>
#include "communication/client/socket/socket.h"
namespace WLAN
{
    class HHN_Server
    {
    private:
        WiFiServer server;

    public:
        HHN_Server();
        HHN_Client::Socket run();
    };

    extern HHN_Server server;
} // namespace WLAN
