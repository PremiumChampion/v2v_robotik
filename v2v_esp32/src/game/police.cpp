#include "services/coordinator.h"
#include "movement/movement.h"
#include "services/positioning.h"
namespace Game
{
    namespace Police
    {
        // MUST NOT BLOCK THE FLOW
        void init()
        {
#pragma region wait for criminal ready
            //Über WiFi Broker auf Nachricht warten
            // Platzhalter im messages array für ready Nachricht definieren
#pragma endregion

#pragma region start game
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
