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
        void run();
    };

    extern HHN_Server server;
} // namespace WLAN
