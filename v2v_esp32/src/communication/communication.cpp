#include <Arduino.h>

#include "client/socket/socket.h"
#include "server/connection.h"
#include "server/server.h"
#include "wlan/wlan.h"

// Communicaton setup file

#define CHASER 0
#define CHASED 1

#define ROLE CHASED

HHN_Client::Socket chaserClient;

void setupCommunication() // use setup instead setupCommunictaion. Need of a new Namspace because of collision mit setup in the main file.
{

#if ROLE == CHASED                                 // Chased-one
    WLAN::setupClient();                           // Setup connection to the accesspoint
    chaserClient = HHN_Client::createConnection(); // Initialize client on chaser site
#else                                              // Chaser
    WLAN::setupAP();                       // Create an accesspoint
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