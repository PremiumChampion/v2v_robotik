#include <Arduino.h>

#include "client/socket/socket.h"
#include "server/connection.h"
#include "server/server.h"
#include "wlan/wlan.h"

// Communicaton setup file

#define CHASER 0
#define CHASED 1

#define ROLE CHASED

namespace COM
{
    HHN_Client::Socket externalClient;

    void setup()
    {
        Serial.println("Function: setup");
#if ROLE == CHASED       // Chased-one
        WLAN::setupAP(); // Create an accesspoint
        WLAN::HHN_Server server = WLAN::HHN_Server(); //
        server.run(); // Check for new clients. Initialize chased-one client.
#else                 // Chaser
        WLAN::setupClient();            // Setup WiFi connection to the accesspoint
        HHN_Client::createConnection(); // Initialize client on chaser site
#endif
    }
} // namespace COM
