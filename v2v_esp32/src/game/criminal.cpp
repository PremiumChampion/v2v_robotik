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
        INIT_STATE DEFAULT_STATE = RESETTING_WON_STATE;
        INIT_STATE state = DEFAULT_STATE;
        // function, that is called several times, until the whole initialization of the criminal is done
        // MUST NOT BLOCK THE FLOW
        void init()
        {
            if (state == RESETTING_WON_STATE)
            {
                COM::broker.set(COM::POLICE_WON, 0);
                state = GENERATING_POSITION;
                Serial.println("CRIMINAL:GENERATING_POSITION");
            }

            // Serial.println("STATE:" + String(state));
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
                Service::Coordinator::setCurrentTarget(nextTile);
                Service::Coordinator::setRunWithCollisionAvoidance(true);
                Service::Coordinator::setStopBeforeTarget(false);
                // Serial.println("Pos:" + String(nextTile));
                // int generatedNextTile = 0;
                // Movement::MovementKind next_movement = Movement::Stop;

                // Service::Coordinator::setRunWithCollisionAvoidance(true);

                // Service::Coordinator::calculateRoute(&generatedNextTile, &next_movement);
                // Serial.println("generatedNextTile = " + String(generatedNextTile) + " next_movement = " + String(next_movement));
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
                    Service::Coordinator::setRunWithCollisionAvoidance(false);
                    Serial.println("CRIMINAL:RUNNING");
                    setGameState(RUNNING);
                }
            }

#pragma endregion
        }

        void run()
        {
#pragma region lost
#pragma region wait for police to tell you that you lost
            // Signal kommt von Police -> darauf hören
            if (COM::broker.get(COM::POLICE_WON) == 1)
            {
#pragma endregion

#pragma region switch role(optional)
                Game::setCurrentRole(CHASER);
#pragma endregion

#pragma region reinit
                setGameState(INITIALISING);
#pragma endregion
            }
#pragma endregion

// #pragma region not lost
//             if (COM::broker.get(COM::POLICE_WON) == 0)
//             {
//                 // criminal stays still when beeing chased
// #pragma region wait
//                 // do nothing
// #pragma endregion

// #pragma endregion
//             }
        }
    } // namespace Criminal

} // namespace Game
