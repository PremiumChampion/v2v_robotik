#include <Arduino.h>
#include "server/server.h"

// Communicaton setup file

#define CHASER 0
#define CHASED 1

#define ROLE CHASED

void setup()
{

#if ROLE == CHASED        // Chased-one
    WLAN::setup_Client(); // Setup connection to the accesspoint
#else                     // Chaser
    WLAN::setup_AP(); // Create an accesspoint
#endif

    // create server
    // connect to server
}

void run()
{
    WLAN::server.run();
}