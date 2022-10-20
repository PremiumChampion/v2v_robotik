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
        INIT_STATE state = GENERATING_POSITION;
        // function, that is called several times, until the whole initialization of the criminal is done
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
                Service::Coordinator::setRunWithCollisionAvoidance(true);
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
                bool criminal_has_reached_starting_position = nextTile == targetTile && next_movement == Movement::Stop;

                if (criminal_has_reached_starting_position)
                {
                    // Set message in broker, that criminal is done moving
                    COM::broker.set(COM::CRIMINAL_INIT, String("Done"));
                    Service::Coordinator::setRunWithCollisionAvoidance(false);
                    state = WAITING_FOR_POLICE_MOVEMENT;
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
                if (COM::broker.get(COM::POLICE_INIT).equals("Done"))
                {
                    state = WAITING_FOR_GAMESTART;
                }
            }
#pragma endregion

#pragma region start game

            // Start game -> setze ein FLag auf true
            if (state == WAITING_FOR_GAMESTART)
            {
                if (COM::broker.get(COM::SYNCPLAY).toInt() == COM::CONNECTION)
                {
                    COM::broker.set(COM::SYNCPLAY, String(COM::ACKNOWLEDGE));
                }

                if (COM::broker.get(COM::SYNCPLAY).toInt() == COM::ESTABLISHED)
                {
                    // state = next logical state
                    setGameState(RUNNING);
                }
            }

#pragma endregion
        }

        void run()
        {

#pragma region wait for police to tell you that you lost
            // Signal kommt von Police -> darauf hören
            if (COM::broker.get(COM::POLICE_WON).toInt()){
            // WiFi Broker
#pragma endregion

#pragma region if lost
#pragma region wait for reinit flag
#pragma endregion

#pragma region switch role (optional)
                Game::setCurrentRole(CHASER);

#pragma endregion

#pragma region reinit
                setGameState(INITIALISING);
#pragma endregion

            }
#pragma endregion

            if (!COM::broker.get(COM::POLICE_WON).toInt()){
#pragma region game ongoing

#pragma region wait
            }
#pragma endregion
        }
    } // namespace Criminal

} // namespace Game
