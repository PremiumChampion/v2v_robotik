#include <Arduino.h>
#include "criminal.h"
#include "communication/communication.h"
#include "services/data/positioning.h"
#include "services/coordinator.h"
#include "game/loop.h"
namespace Game
{
    namespace Criminal
    {
        INIT_STATE DEFAULT_STATE = GENERATING_POSITION;
        INIT_STATE state = DEFAULT_STATE;

        unsigned long last_log_time = 0;
        unsigned long reset_pause_start = 0;

        // function, that is called several times, until the whole initialization of the criminal is done
        // MUST NOT BLOCK THE FLOW
        void init()
        {
            if (last_log_time + 500 < millis())
            {
                last_log_time = millis();
                switch (state)
                {
                case GENERATING_POSITION:
                    Serial.println("CRIMINAL:STATE:GENERATING_POSITION");
                    break;
                case WAITING_FOR_CRIMINAL_MOVEMENT:
                    Serial.println("CRIMINAL:STATE:WAITING_FOR_CRIMINAL_MOVEMENT");
                    break;
                case WAITING_FOR_POLICE_MOVEMENT:
                    Serial.println("CRIMINAL:STATE:WAITING_FOR_POLICE_MOVEMENT");
                    break;
                case WAITING_FOR_GAMESTART:
                    Serial.println("CRIMINAL:STATE:WAITING_FOR_GAMESTART");
                    break;
                default:
                    Serial.println("CRIMINAL:STATE:" + String(state));
                    break;
                }
            }

#pragma region generate random position
            if (state == GENERATING_POSITION)
            {
                int nextTile = -1;
                int currentOtherPosition = Service::OTHER_ROBOT.getCurrentPositionTile();

                do
                {
                    nextTile = random(16);
                } while (nextTile == currentOtherPosition);

                COM::broker.set(COM::CRIMINAL_POSITION, nextTile);

                state = WAITING_FOR_CRIMINAL_MOVEMENT;
                Serial.println("CRIMINAL:WAITING_FOR_CRIMINAL_MOVEMENT");
            }

            // Random number generator von 0-15
            // Wenn R.N. gleiche ist wie von Police -> workaround überlegen
#pragma endregion

#pragma region move to random position
            if (state == WAITING_FOR_CRIMINAL_MOVEMENT)
            {
                int targetTile = COM::broker.get(COM::CRIMINAL_POSITION);
                Service::Coordinator::setRunWithCollisionAvoidance(true);
                Service::Coordinator::setStopBeforeTarget(false);
                Service::Coordinator::setCurrentTarget(targetTile);

                int nextTile = 0;
                Movement::MovementKind next_movement = Movement::Stop;

                Service::Coordinator::calculateRoute(&nextTile, &next_movement);

                bool criminal_has_reached_starting_position = nextTile == targetTile && next_movement == Movement::Stop;

                if (criminal_has_reached_starting_position)
                {
                    // Set message in broker, that criminal is done moving
                    COM::broker.set(COM::CRIMINAL_INIT, 1);
                    state = WAITING_FOR_POLICE_MOVEMENT;
                    Serial.println("CRIMINAL:WAITING_FOR_POLICE_MOVEMENT");
                }
            }
            // Rufe die jeweiligen Methoden auf um zum Tile zu laufen
            // Wahrscheinlich im coordinator die Methode
#pragma endregion

#pragma region wait for police ready
            // Warte auf Signal, wenn der Barcode gelesen wurde, dass man an der Startposition angekommen ist
            // Arduino Broker
            if (state == WAITING_FOR_POLICE_MOVEMENT)
            {
                if (COM::broker.get(COM::POLICE_INIT) == 1)
                {
                    Serial.println("CRIMINAL:WAITING_FOR_GAMESTART");
                    state = WAITING_FOR_GAMESTART;
                }
            }
#pragma endregion

#pragma region start game

            // Start game -> setze ein FLag auf true
            if (state == WAITING_FOR_GAMESTART)
            {

                if (COM::broker.get(COM::SYNCPLAY) == COM::CONNECTION)
                {
                    COM::broker.set(COM::SYNCPLAY, COM::ACKNOWLEDGE);
                }

                if (COM::broker.get(COM::SYNCPLAY) == COM::ESTABLISHED)
                {
                    // state = next logical state
                    state = DEFAULT_STATE;
                    Serial.println("CRIMINAL:RUNNING");
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
                Serial.println("CRIMINAL:RUNNING");
            }

#pragma region wait for police to tell you that you lost
            // Signal kommt von Police -> darauf hören
            if (COM::broker.get(COM::POLICE_WON) == 1 && reset_pause_start == 0)
            {
                Serial.println("CRIMINAL:POLICE_WON");
                COM::broker.set(COM::CRIMINAL_INIT, 0);
                COM::broker.set(COM::POLICE_INIT, 0);
                COM::broker.set(COM::SYNCPLAY, COM::DISCARDED);
                reset_pause_start = millis();
            }
            if (reset_pause_start != 0 && reset_pause_start + 5000 < millis())
            {
                Game::setCurrentRole(CHASER);
                Game::setGameState(INITIALISING);
                reset_pause_start = 0;
            }
#pragma endregion
        }
    } // namespace Criminal

} // namespace Game
