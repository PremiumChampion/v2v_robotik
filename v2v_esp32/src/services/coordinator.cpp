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
        int currentTarget = 0;
        void setCurrentTarget(int nextTarget){
            currentTarget = nextTarget;
        }

        void run()
        {
            if (!Movement::MOVEMENTS.waitingForNewDirections())
            {
                return;
            }

            Direction currentDirection = THIS_ROBOT.getCurrentDirection();
            int currentPosition = THIS_ROBOT.getCurrentPositionTile();
            // todo: we need to set the target position from the outside
            // int targetPosition = OTHER_ROBOT.getCurrentPositionTile();
            int targetPosition = currentTarget;

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Clockwise)
            {
                Direction newDirectionClockwise = getForDirection(currentDirection).getClockwise();
                Service::THIS_ROBOT.setCurrentDirection(newDirectionClockwise);
                currentDirection = newDirectionClockwise;
            }

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Counterclockwise)
            {
                Direction newDirectionCounterClockwise = getForDirection(currentDirection).getCounterClockwise();
                Service::THIS_ROBOT.setCurrentDirection(newDirectionCounterClockwise);
                currentDirection = newDirectionCounterClockwise;
            }

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Stop)
            {
            }

            if (Movement::MOVEMENTS.getCurrentMovementKind() == Movement::MovementKind::Straight)
            {
                int newPosition = getForDirection(currentDirection).calculateNewPosition(currentPosition);
                Service::THIS_ROBOT.setCurrentPositionTile(newPosition); // comment when working with barcode scanner!!!
                currentPosition = newPosition;
            }

            int nextTile = Routing::calculateRoute(currentPosition, targetPosition);

            Movement::MovementKind next_movement = Forwarding::calculateNextMovement(&THIS_ROBOT, nextTile);

            Movement::MOVEMENTS.setNewDirections(next_movement);
        }
    } // namespace Coordinator
} // namespace Service
