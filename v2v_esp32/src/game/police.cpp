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
        unsigned long last_log_time = 0;
        unsigned long reset_pause_start = 0;
        unsigned long game_start_delay_start = 0;
        // function, that is called several times, until the whole initialization of the police is done
        // MUST NOT BLOCK THE FLOW
        void init()
        {
            if (last_log_time + 500 < millis())
            {
                last_log_time = millis();
                switch (state)
                {
                case RESETTING_WON_STATE:
                    Serial.println("POLICE:STATE:RESETTING_WON_STATE");
                    break;
                case WAITING_FOR_CRIMINAL_READY:
                    Serial.println("POLICE:STATE:WAITING_FOR_CRIMINAL_READY");
                    break;
                case GENERATING_POSITION:
                    Serial.println("POLICE:STATE:GENERATING_POSITION");
                    break;
                case WAITING_FOR_POLICE_MOVEMENT:
                    Serial.println("POLICE:STATE:WAITING_FOR_POLICE_MOVEMENT");
                    break;
                case WAITING_FOR_GAMESTART:
                    Serial.println("POLICE:STATE:WAITING_FOR_GAMESTART");
                    break;
                default:
                    Serial.println("POLICE:STATE:" + String(state));
                    break;
                }
            }

            if (state == RESETTING_WON_STATE)
            {
                COM::broker.set(COM::POLICE_WON, 0);
                state = WAITING_FOR_CRIMINAL_READY;
                Serial.println("POLICE:WAITING_FOR_CRIMINAL_READY");
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

                if (game_start_delay_start == 0 && police_has_reached_starting_position)
                {
                    COM::broker.set(COM::POLICE_INIT, 1);
                    game_start_delay_start = millis();
                }
                if (game_start_delay_start != 0 && game_start_delay_start + 5000 < millis())
                {
                    game_start_delay_start = 0;
                    state = WAITING_FOR_GAMESTART;
                    Serial.println("POLICE:WAITING_FOR_GAMESTART");
                }
            }
#pragma endregion

#pragma region start game
            if (state == WAITING_FOR_GAMESTART)
            {
                if (COM::broker.get(COM::SYNCPLAY) == COM::DISCARDED)
                {
                    COM::broker.set(COM::SYNCPLAY, COM::CONNECTION);
                }

                if (COM::broker.get(COM::SYNCPLAY) == COM::ACKNOWLEDGE)
                {
                    COM::broker.set(COM::SYNCPLAY, COM::ESTABLISHED);
                    state = DEFAULT_STATE;
                    Service::Coordinator::setStopBeforeTarget(true);
                    Service::Coordinator::setRunWithCollisionAvoidance(false);
                    Service::Coordinator::setCurrentTarget(Service::OTHER_ROBOT.getCurrentPositionTile());
                    Game::setGameState(RUNNING);
                }
            }

#pragma endregion
        }

        void run()
        {
            if (last_log_time + 500 < millis())
            {
                last_log_time = millis();
                Serial.println("POLICE:RUNNING");
            }

#pragma region check for win condition
            // if nextTile gleich currenttarget and next movement straight --> game won
            bool police_has_won = Service::Coordinator::hasReachedStraightBeforeTarget();
#pragma endregion

#pragma region if won
            if (police_has_won && reset_pause_start == 0)
            {
                // Send Police has won flag
                Serial.println("POLICE:POLICE_WON");
                COM::broker.set(COM::POLICE_WON, 1);
                COM::broker.set(COM::CRIMINAL_INIT, 0);
                COM::broker.set(COM::POLICE_INIT, 0);
                COM::broker.set(COM::SYNCPLAY, COM::DISCARDED);
                reset_pause_start = millis();
            }

            if (reset_pause_start != 0 && reset_pause_start + 5000 < millis())
            {
                Game::setCurrentRole(CHASED);
                Game::setGameState(INITIALISING);
                reset_pause_start = 0;
            }
#pragma endregion
        }
    } // namespace Police

} // namespace Game
