#include <Arduino.h>

#include "services/coordinator.h"
#include "movement/movement.h"
#include "services/data/positioning.h"
#include "police.h"
#include "communication/communication.h"
#include "criminal.h"
#include "game/loop.h"

namespace Game
{
    namespace Police
    {
        INIT_STATE DEFAULT_STATE = RESETTING_WON_STATE;
        INIT_STATE state = DEFAULT_STATE;
        // function, that is called several times, until the whole initialization of the police is done
        // MUST NOT BLOCK THE FLOW
        void init()
        {
            if (state == RESETTING_WON_STATE)
            {
                COM::broker.set(COM::POLICE_WON, 0);
                state = GENERATING_POSITION;
                Serial.println("CRIMINAL:GENERATING_POSITION");
            }
#pragma region wait for criminal ready
            //Über WiFi Broker auf Nachricht warten
            // Platzhalter im messages array für ready Nachricht definieren

            if (state == WAITING_FOR_CRIMINAL_READY)
            {
                // Check, if the criminal is done with his movement initialization
                if (COM::broker.get(COM::CRIMINAL_INIT) == 1)
                {
                    state = GENERATING_POSITION;
                    Serial.println("POLICE:GENERATING_POSITION");
                }
            }
#pragma endregion

#pragma region generate random starting position
            if (state == GENERATING_POSITION)
            {
                int nextTile = -1;
                int currentOtherPosition = Service::OTHER_ROBOT.getCurrentPositionTile();

                do
                {
                    nextTile = random(16);
                } while (nextTile == currentOtherPosition);

                COM::broker.set(COM::POLICE_POSITION, nextTile);
                Service::Coordinator::setCurrentTarget(nextTile);
                Service::Coordinator::setRunWithCollisionAvoidance(true);
                Service::Coordinator::setStopBeforeTarget(false);
                state = WAITING_FOR_POLICE_MOVEMENT;
                Serial.println("POLICE:WAITING_FOR_POLICE_MOVEMENT");
            }

            // Random number generator von 0-15
            // Wenn R.N. gleiche ist wie von Police -> workaround überlegen
#pragma endregion

#pragma region move to random position
            if (state == WAITING_FOR_POLICE_MOVEMENT)
            {
                int targetTile = COM::broker.get(COM::POLICE_POSITION);

                int nextTile = 0;
                Movement::MovementKind next_movement = Movement::Stop;

                Service::Coordinator::calculateRoute(&nextTile, &next_movement);

                bool police_has_reached_starting_position = nextTile == targetTile && next_movement == Movement::Stop;

                if (police_has_reached_starting_position)
                {
                    COM::broker.set(COM::POLICE_INIT, 1);
                    state = WAITING_FOR_GAMESTART;
                    Serial.println("POLICE:WAITING_FOR_GAMESTART");
                }
            }
            // Rufe die jeweiligen Methoden auf um zum Tile zu laufen
            // Wahrscheinlich im coordinator die Methode
#pragma endregion

#pragma region start game
            if (state == WAITING_FOR_GAMESTART)
            {
                COM::broker.set(COM::SYNCPLAY, COM::CONNECTION);

                if (COM::broker.get(COM::SYNCPLAY) == COM::ACKNOWLEDGE)
                {
                    COM::broker.set(COM::SYNCPLAY, COM::ESTABLISHED);
                    COM::broker.set(COM::POLICE_INIT, 0);
                    COM::broker.set(COM::CRIMINAL_INIT, 0);
                    state = DEFAULT_STATE;
                    Service::Coordinator::setStopBeforeTarget(true);
                    Service::Coordinator::setRunWithCollisionAvoidance(false);
                    Service::Coordinator::setCurrentTarget(Service::OTHER_ROBOT.getCurrentPositionTile());
                    setGameState(RUNNING);
                }
            }

#pragma endregion
        }

        void run()
        {
#pragma region check for win condition
            // if nextTile gleich currenttarget and next movement straight --> game won
            bool police_has_won = Service::Coordinator::hasReachedStraightBeforeTarget();
#pragma endregion

#pragma region if won
            if (police_has_won)
            {
                // Send Police has won flag
                COM::broker.set(COM::POLICE_WON, 1);
                COM::broker.set(COM::POLICE_INIT, 0);
                COM::broker.set(COM::CRIMINAL_INIT, 0);
                COM::broker.set(COM::SYNCPLAY, COM::CONNECTION);
                setGameState(INITIALISING);
                Game::setCurrentRole(CHASED);
            }
#pragma endregion
        }
    } // namespace Police

} // namespace Game
