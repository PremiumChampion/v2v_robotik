#include <Arduino.h>

#include "client/socket.h"
#include "server/connection.h"
#include "server/server.h"
#include "wlan/wlan.h"
#include "communication/communication.h"

// Communicaton setup file

namespace COM
{
#if ROLE == CHASED
        WLAN::HHN_Server server = WLAN::HHN_Server();
#endif
        HHN_Client::Socket externalClient = HHN_Client::Socket();

        void setup()
        {
                Serial.println("Function: setup");
#if ROLE == CHASED               // Chased-one
                WLAN::setupAP(); // Create an accesspoint
                server.init();
                server.run(); // Check for new clients. Initialize chased-one client.
#else                         // Chaser
                WLAN::setupClient();            // Setup WiFi connection to the accesspoint
                HHN_Client::createConnection(); // Initialize client on chaser site
#endif
        }
} // namespace COM
