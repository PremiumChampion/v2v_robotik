#include <Arduino.h>
#include "criminal.h"
#include "communication/communication.h"
#include "services/positioning.h"
#include "services/coordinator.h"
namespace Game
{
    namespace Criminal
    {
        INIT_STATE state = GENERATING_POSITION;
        // MUST NOT BLOCK THE FLOW
        void init()
        {
            
#pragma region generate random position
            if (state == GENERATING_POSITION)
            {
                int nextTile = -1;
                int currentOtherPosition = Service::OTHER_ROBOT.getCurrentPositionTile();

                do
                {
                    nextTile = random(16);
                } while (nextTile == currentOtherPosition);

                COM::broker.set(COM::CRIMINAL_POSITION, String(nextTile));
                Service::Coordinator::setCurrentTarget(nextTile);
                Service::Coordinator::setStopBeforeTarget(false);
                state = WAITING_FOR_CRIMINAL_MOVEMENT;
            }

            // Random number generator von 0-15
            // Wenn R.N. gleiche ist wie von Police -> workaround überlegen
#pragma endregion

#pragma region move to random position
            if (state == WAITING_FOR_CRIMINAL_MOVEMENT)
            {
                int targetTile = COM::broker.get(COM::CRIMINAL_POSITION).toInt();

                int nextTile = 0;
                Movement::MovementKind next_movement = Movement::Stop;

                Service::Coordinator::calculateRoute(&nextTile, &next_movement);
                // if nextTile gleich currenttarget and next movement straight --> game won
                bool criminal_has_reached_starting_position = nextTile == targetTile && next_movement == Movement::Stop;

                if (criminal_has_reached_starting_position)
                {
                    COM::broker.set(COM::CRIMINAL_INIT, String());
                    state = WAITING_FOR_POLICE_MOVEMENT;
                }
            }
            // Rufe die jeweiligen Methoden auf um zum Tile zu laufen
            // Wahrscheinlich im coordinator die Methode
#pragma endregion

#pragma region wait for police ready
            // Warte auf Signal, wenn der Barcode gelesen wurde, dass man an der Startposition angekommen ist
            // Arduino Broker
#pragma endregion

#pragma region start game
            // Start game -> setze ein FLag auf true
#pragma endregion
        }

        void run()
        {
#pragma region check for loss condition

#pragma region wait for police to tell you that you lost
            // Signal kommt von Police -> darauf hören
            // WiFi Broker
#pragma endregion
#pragma endregion

#pragma region if lost

#pragma region switch role
#pragma endregion
#pragma region set reinitgame flag
#pragma endregion

#pragma endregion

#pragma region game ongoing

#pragma region wait
#pragma endregion

#pragma endregion
        }
    } // namespace Criminal

} // namespace Game
