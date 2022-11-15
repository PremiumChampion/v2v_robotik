#include "communication/server/server.h"
#include "communication/client/socket.h"
#include "broker/broker.h"

#pragma once

#define CHASER 0
#define CHASED 1

#define ROLE CHASED
namespace COM
{
    static int WIFI_MESSAGE_SIZE = 8;

    enum WIFI_MESSAGE
    {
        // future police pos
        POLICE_POSITION,
        // future criminal po
        CRIMINAL_POSITION,
        // Syncplay - enum SYNCSTATE
        SYNCPLAY,
        // Police in the initialisation phase
        // Contains "Done", if the police is done with his initial moving
        POLICE_INIT,
        // Criminal in the initialisation phase
        // Contains "Done", if the police is done with his initial moving
        CRIMINAL_INIT,
        // Rename to robot1. Static position slot for first robot, due to context swich may not be syncronos.
        CURRENT_CHASER_POSITON,
        // Rename to robot2. Static position slot for second robot, due to context swich may not be syncronos.
        CURRENT_CHASED_POSITION,
        POLICE_WON,
    };

    enum SYNCSTATE
    {
        CONNECTION,
        ACKNOWLEDGE,
        ESTABLISHED,
    };

    WIFI_MESSAGE getThisPositionIndex();
    WIFI_MESSAGE getOtherPositionIndex();

#if ROLE == CHASED
    extern WLAN::HHN_Server server;
#endif

    void setup();
    void brokerInit();
    extern HHN_Client::Socket externalClient; // Socket externalClient = Socket();
    extern Broker::Broker<int> broker;
}
