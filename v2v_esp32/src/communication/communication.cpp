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
        // Delete move broker to right place after everything is implemented correctly
        Broker::Broker<String> broker(WIFI_MESSAGE_SIZE);

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

#if ROLE == CHASED
        WIFI_MESSAGE getThisPositionIndex()
        {
                return CURRENT_CHASED_POSITION;
        }
        WIFI_MESSAGE getOtherPositionIndex()
        {
                return CURRENT_CHASER_POSITON;
        }
#endif

#if ROLE == CHASER
        WIFI_MESSAGE getThisPositionIndex()
        {
                return CURRENT_CHASER_POSITON;
        }
        WIFI_MESSAGE getOtherPositionIndex()
        {
                return CURRENT_CHASED_POSITION;
        }
#endif

} // namespace COM
