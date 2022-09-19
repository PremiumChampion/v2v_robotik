#include <Arduino.h>
#include "server/server.h"

// Communicaton setup file

#define CHASER 0
#define CHASED 1

#define ROLE CHASED

void setup()
{

#if ROLE == CHASED                                 // Chased-one
    WLAN::setup_Client();                          // Setup connection to the accesspoint
    chaserClient = HHN_Client::createConnection(); // Initialize client on chaser site
#else                                              // Chaser
    WLAN::setup_AP();                      // Create an accesspoint
    WLAN::HHN_Server();                    // Create server instance. TODO: Check correct implementaion.
    server = WLAN::HHN_Server();           // Initialize server instance
#endif
}

void run()
{
#if ROLE == CHASED
#else
    chased_oneClient = WLAN::server.run(); // Check for new clients. Initialize chased-one client.
#endif
}