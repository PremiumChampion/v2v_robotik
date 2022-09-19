#include <Arduino.h>
#include "server/server.h"

// Communicaton setup file

void setup()
{
    WLAN::setup();

    // setup wifi
    // create server
    // connect to server
}

void run()
{
    WLAN::server.run();
}