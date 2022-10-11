#include "communication/server/server.h"
#include "communication/client/socket.h"
#include "broker/broker.h"

#pragma once

#define CHASER 0
#define CHASED 1

#define ROLE CHASED
namespace COM
{
    static const int SYSTEM_INFORMATION_TYPE_COUNT = 3;

    static int WIFI_MESSAGE_SIZE = 7;
    
    enum WIFI_MESSAGE{
        POLICE_POSITION,
        CRIMINAL_POSITION,
        SYNCPLAY,
        POLICE_INIT,
        CRIMINAL_INIT,
        CURRENT_CHASER_POSITON,
        CURRENT_CHASED_POSITION,
    };
    enum SystemInformation
    {
        POSITION,
        READY,
        WON,
    };

#if ROLE == CHASED
    extern WLAN::HHN_Server server;
#endif

    void setup();

    extern HHN_Client::Socket externalClient; // Socket externalClient = Socket();
    extern Broker::Broker<String> RCV_BROKER;
    extern Broker::Broker<String> SND_BROKER;
}
