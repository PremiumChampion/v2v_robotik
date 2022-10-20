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
        INIT_STATE state = WAITING_FOR_CRIMINAL_READY;
        // function, that is called several times, until the whole initialization of the police is done
        // MUST NOT BLOCK THE FLOW
        void init()
        {
#pragma region wait for criminal ready
            //Über WiFi Broker auf Nachricht warten
            // Platzhalter im messages array für ready Nachricht definieren

            if(state == WAITING_FOR_CRIMINAL_READY){
                //Check, if the criminal is done with his movement initialization
                if(COM::broker.get(COM::CRIMINAL_INIT) == "Done"){
                state = GENERATING_POSITION;
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

                COM::broker.set(COM::POLICE_POSITION, String(nextTile));
                Service::Coordinator::setCurrentTarget(nextTile);
                Service::Coordinator::setRunWithCollisionAvoidance(true);
                Service::Coordinator::setStopBeforeTarget(false);
                state = WAITING_FOR_POLICE_MOVEMENT;
            }

            // Random number generator von 0-15
            // Wenn R.N. gleiche ist wie von Police -> workaround überlegen
#pragma endregion

#pragma region move to random position
            if (state == WAITING_FOR_POLICE_MOVEMENT)
            {
                int targetTile = COM::broker.get(COM::POLICE_POSITION).toInt();

                int nextTile = 0;
                Movement::MovementKind next_movement = Movement::Stop;

                Service::Coordinator::calculateRoute(&nextTile, &next_movement);
                // if nextTile equals to currenttarget and next movement is straight --> game won
                bool police_has_reached_starting_position = nextTile == targetTile && next_movement == Movement::Stop;

                if (police_has_reached_starting_position)
                {
                    COM::broker.set(COM::POLICE_INIT, String("Done"));
                    state = WAITING_FOR_GAMESTART;
                }
            }
            // Rufe die jeweiligen Methoden auf um zum Tile zu laufen
            // Wahrscheinlich im coordinator die Methode
#pragma endregion


#pragma region start game
if (state == WAITING_FOR_GAMESTART)
            {
                if (COM::broker.get(COM::SYNCPLAY).toInt() == COM::ACKNOWLEDGE)
                {
                    COM::broker.set(COM::SYNCPLAY, String(COM::ESTABLISHED));
                    setGameState(RUNNING);
                }
            }

#pragma endregion
        }
        
        void run()
        {
#pragma region check for win condition
            int nextTile = 0;
            int criminalPosition = Service::OTHER_ROBOT.getCurrentPositionTile();
            Movement::MovementKind next_movement = Movement::Stop;

            Service::Coordinator::calculateRoute(&nextTile, &next_movement);
            // if nextTile gleich currenttarget and next movement straight --> game won
            bool police_has_won = nextTile == criminalPosition && next_movement == Movement::Straight;
#pragma endregion

#pragma region if won
            if (police_has_won)
            {
#pragma region reset broker init vars
                // COM::broker.set(COM::POLICE_POSITION, String());
                // COM::broker.set(COM::CRIMINAL_POSITION, String());
                COM::broker.set(COM::SYNCPLAY, String(COM::CONNECTION));
                COM::broker.set(COM::POLICE_INIT, String(0));
                COM::broker.set(COM::CRIMINAL_INIT, String(0));
                // COM::broker.set(COM::CURRENT_CHASER_POSITON, String());
                // COM::broker.set(COM::CURRENT_CHASED_POSITION, String());
                COM::broker.set(COM::POLICE_WON, String(0));
#pragma endregion

                // Send Police has won flag
                COM::broker.set(COM::POLICE_WON, String(1));

#pragma region switch role (optional)

                Game::setCurrentRole(CHASED);
                // Switch own role in loop.cpp with set currentRole
                // Send switch role over the wifi broker to criminal
                // Criminal sets his own role according to the taken role from police
                // Check?
#pragma endregion

#pragma region reinit
                setGameState(INITIALISING);
#pragma endregion
            }
#pragma endregion

#pragma region not won
            if (!police_has_won)
            {
#pragma region navigate to OTHER_ROBOT
                Service::Coordinator::setStopBeforeTarget(true);
                Service::Coordinator::setRunWithCollisionAvoidance(false);
                Service::Coordinator::setCurrentTarget(criminalPosition);
#pragma endregion
            }
#pragma endregion
        }
    } // namespace Police

} // namespace Game
