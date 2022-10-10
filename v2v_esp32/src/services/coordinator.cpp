#include "movement/movement.h"
#include "coordinator.h"
#include "positioning.h"
#include "tunrningtable.h"
#include "routing.h"
#include "forwarding.h"

namespace Service
{
    namespace Coordinator
    {
        int currentTarget = 0; // target coordinate 0-15
        void setCurrentTarget(int nextTarget)
        {
            currentTarget = nextTarget;
        }

        void run()
        {
#pragma region check if new directions are needed
            if (!Movement::MOVEMENTS.waitingForNewDirections())
            {
                return;
            }
#pragma endregion

#pragma region variable section
            Direction currentDirection = THIS_ROBOT.getCurrentDirection();
            int currentPosition = THIS_ROBOT.getCurrentPositionTile();
            // todo: we need to set the target position from the outside
            // int targetPosition = OTHER_ROBOT.getCurrentPositionTile();
            int targetPosition = currentTarget;
#pragma endregion

#pragma region update position and turning value

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Clockwise)
            {
                Direction newDirectionClockwise = getTurningEntryForCompassDirection(currentDirection).getClockwise();
                Service::THIS_ROBOT.setCurrentDirection(newDirectionClockwise);
                currentDirection = newDirectionClockwise;
            }

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Counterclockwise)
            {
                Direction newDirectionCounterClockwise = getTurningEntryForCompassDirection(currentDirection).getCounterClockwise();
                Service::THIS_ROBOT.setCurrentDirection(newDirectionCounterClockwise);
                currentDirection = newDirectionCounterClockwise;
            }

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Stop)
            {
            }

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Straight)
            {
                int newPosition = getTurningEntryForCompassDirection(currentDirection).calculateNewPosition(currentPosition);
                Service::THIS_ROBOT.setCurrentPositionTile(newPosition); // comment when working with barcode scanner!!!
                currentPosition = newPosition;
            }
#pragma endregion

#pragma region calculate next tile
            int nextTile = Routing::calculateRoute(currentPosition, targetPosition);
#pragma endregion

#pragma region calculate next movement
            Movement::MovementKind next_movement = Forwarding::calculateNextMovement(&THIS_ROBOT, nextTile);
#pragma endregion

#pragma region set new directions
            Movement::MOVEMENTS.setNewDirections(next_movement);
#pragma endregion
        }
    } // namespace Coordinator
} // namespace Service
