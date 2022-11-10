#include "movement/movement.h"
#include "coordinator.h"
#include "services/data/positioning.h"
#include "services/data/turningtable.h"
#include "services/data/routing.h"
#include "services/data/forwarding.h"
#include "communication/communication.h"

namespace Service
{
    namespace Coordinator
    {
        // target coordinate 0-15
        int currentTarget = 0;
        bool stopBeforeTarget = false;
        void setCurrentTarget(int nextTarget)
        {
            Serial.println("target:" + String(currentTarget) + "->" + String(nextTarget));
            currentTarget = nextTarget;
        }
        int getCurrentTarget()
        {
            return currentTarget;
        }
        void setStopBeforeTarget(bool nextStopBeforeTarget)
        {
            Serial.println("stopBeforeTarget:" + String(stopBeforeTarget) + "->" + String(nextStopBeforeTarget));
            stopBeforeTarget = nextStopBeforeTarget;
        }
        bool getStopBeforeTarget()
        {
            return stopBeforeTarget;
        }

        bool runWithCollisionAvoidance = true;
        void setRunWithCollisionAvoidance(bool collisionAvoidanceEnabled)
        {
            Serial.println("runWithCollisionAvoidance:" + String(collisionAvoidanceEnabled) + "->" + String(runWithCollisionAvoidance));
            runWithCollisionAvoidance = collisionAvoidanceEnabled;
        }
        bool getRunWithCollisionAvoidance()
        {
            return runWithCollisionAvoidance;
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
            int targetPosition = currentTarget;
#pragma endregion

#pragma region update position and turning value after moving
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
#if !WORKING_WITH_QR_SENSOR
                COM::broker.set(COM::getThisPositionIndex(), newPosition);
                Service::THIS_ROBOT.setCurrentPositionTile(newPosition);
#endif
                currentPosition = newPosition;
            }
#pragma endregion

            int nextTile = 0;
            Movement::MovementKind next_movement = Movement::Stop;

            calculateRoute(&nextTile, &next_movement);

            // if nextTile gleich currenttarget and next movement straight --> game won
            if (hasReachedStraightBeforeTarget())
            {
                Movement::MOVEMENTS.setNewDirections(Movement::Stop);
                return;
            }

#pragma region set new directions
            Movement::MOVEMENTS.setNewDirections(next_movement);
#pragma endregion
        }

        void calculateRoute(int *nextTile, Movement::MovementKind *next_movement)
        {

#pragma region variable section
            Direction currentDirection = THIS_ROBOT.getCurrentDirection();
            int currentPosition = THIS_ROBOT.getCurrentPositionTile();
            int blockedPosition = OTHER_ROBOT.getCurrentPositionTile();
            int targetPosition = currentTarget;
#pragma endregion

#pragma region calculate next tile
            if (runWithCollisionAvoidance)
            {
                // enables the robot to drive around a specified position
                *nextTile = Routing::calculateRouteWithCollisionAvoidance(currentPosition, targetPosition, blockedPosition);
            }
            if (!runWithCollisionAvoidance)
            {
                // enables the robot to drive straight to the other robot
                *nextTile = Routing::calculateRoute(currentPosition, targetPosition);
            }
#pragma endregion

#pragma region calculate next movement
            *next_movement = Forwarding::calculateNextMovement(&THIS_ROBOT, *nextTile);
#pragma endregion
        }

        bool hasReachedStraightBeforeTarget()
        {
            int nextTile = 0;
            Movement::MovementKind next_movement = Movement::Stop;

            calculateRoute(&nextTile, &next_movement);

            // if nextTile gleich currenttarget and next movement straight --> game won
            return (nextTile == currentTarget && next_movement == Movement::Straight && stopBeforeTarget);
        }
    } // namespace Coordinator
} // namespace Service
