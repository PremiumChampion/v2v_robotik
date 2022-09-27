#include "communication/server/server.h"
#include "communication/client/socket.h"

#pragma once

#define CHASER 0
#define CHASED 1

#define ROLE CHASER
namespace COM
{
    #if ROLE==CHASED
        extern WLAN::HHN_Server server;
    #endif


    void setup();
    extern HHN_Client::Socket externalClient; // Socket externalClient = Socket();

}