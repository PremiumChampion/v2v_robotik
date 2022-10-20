#include "communication/server/server.h"
#include "communication/client/socket.h"
#include "broker/broker.h"

#pragma once

#define CHASER 0
#define CHASED 1

#define ROLE CHASED
namespace COM
{
    static int WIFI_MESSAGE_SIZE = 7;

    enum WIFI_MESSAGE
    {
        // future police pos
        POLICE_POSITION,
        // future criminal po
        CRIMINAL_POSITION,
        // Syncplay - Need more variables to have a handshake between criminal and police.
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
    };

    WIFI_MESSAGE getThisPositionIndex()
    {
#if ROLE == CHASED
        return CURRENT_CHASED_POSITION;
#endif

#if ROLE == CHASER
        return CURRENT_CHASER_POSITON;
#endif
    }

    WIFI_MESSAGE getOtherPositionIndex()
    {
#if ROLE == CHASED
        return CURRENT_CHASER_POSITON;
#endif

#if ROLE == CHASER
        return CURRENT_CHASED_POSITION;
#endif
    }

#if ROLE == CHASED
    extern WLAN::HHN_Server server;
#endif

    void setup();

    extern HHN_Client::Socket externalClient; // Socket externalClient = Socket();
    extern Broker::Broker<String> broker;
}
