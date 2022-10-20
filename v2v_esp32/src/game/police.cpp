#include <Arduino.h>

#include "services/coordinator.h"
#include "movement/movement.h"
#include "services/positioning.h"
#include "police.h"
#include "communication/communication.h"
#include "criminal.h"
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
            if(state==WAITING_FOR_GAMESTART){
                
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
#pragma region switch role
#pragma endregion
#pragma region set reinitgame flag
#pragma endregion
            }
#pragma endregion

#pragma region not won
            if (!police_has_won)
            {
#pragma region navigate to OTHER_ROBOT
                Service::Coordinator::setStopBeforeTarget(true);
                Service::Coordinator::setCurrentTarget(criminalPosition);
#pragma endregion
            }
#pragma endregion
        }
    } // namespace Police

} // namespace Game
