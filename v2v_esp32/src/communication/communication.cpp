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
#if ROLE == CHASED
    WLAN::setupAP();             // Create an accesspoint
    WLAN::HHN_Server* server = new WLAN::HHN_Server(); // Initialize server instance
#endif

    HHN_Client::Socket* setup() // use setup instead setupCommunictaion. Need of a new Namspace because of collision mit setup in the main file.
    {

#if ROLE == CHASED                   // Chased-one
        return (*server).run();       // Check for new clients. Initialize chased-one client.
#else                                // Chaser
        WLAN::setupClient();                     // Setup connection to the accesspoint
        return HHN_Client::createConnection(); // Initialize client on chaser site
#endif
    }
} // namespace COM
