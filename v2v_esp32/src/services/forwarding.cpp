#include "forwarding.h"
#include "movement/movement.h"

namespace Service
{
    Movement::MovementKind Forwarding::calculateNextMovement(int nextTile)
    {
        // Calculate from current tile pos current x and y
        // Calculate, if movement is either in x-axis or y-axis
        // direction(also either positive or negative direction)
        // Calculate, in which direction robot needs to turn, in relevance to its current facing direction
        int currentTile = THIS_ROBOT.getCurrentPositionTile();
        Direction currentDirection = THIS_ROBOT.getCurrentDirection();
        int nextTileX = nextTile % 4;
        int nextTileY = nextTile / 4;
        int currentX = currentTile % 4;
        int currentY = currentTile / 4;
        int deltaX = nextTileX - currentX;
        int deltaY = nextTileY - currentY;

        if (deltaX == 0 && deltaY == 0)
        {
            return Movement::MovementKind::Stop;
        }
        // Calculate movement if movement is in positive x-axis direction
        if (deltaX == 1)
        {

            if (currentDirection == Direction::EAST)
            {
                return Movement::MovementKind::Straight;
            }

            if (currentDirection == Direction::NORTH)
            {
                return Movement::MovementKind::Clockwise;
            }

            if (currentDirection == Direction::SOUTH)
            {
                return Movement::MovementKind::Counterclockwise;
            }

            return Movement::MovementKind::Clockwise;
        }
        // Calculate movement in negative x-axis direction
        if (deltaX == -1)
        {
            if (currentDirection == Direction::WEST)
            {
                return Movement::MovementKind::Straight;
            }

            if (currentDirection == Direction::NORTH)
            {
                return Movement::MovementKind::Counterclockwise;
            }

            if (currentDirection == Direction::SOUTH)
            {
                return Movement::MovementKind::Clockwise;
            }

            return Movement::MovementKind::Counterclockwise;
        }
        // Calculate movement in positive y-axis direction
        if (deltaY == 1)
        {
            if (currentDirection == Direction::NORTH)
            {
                return Movement::MovementKind::Straight;
            }

            if (currentDirection == Direction::EAST)
            {
                return Movement::MovementKind::Clockwise;
            }

            if (currentDirection == Direction::WEST)
            {
                return Movement::MovementKind::Counterclockwise;
            }

            return Movement::MovementKind::Clockwise;
        }
        // Calculate movement in negative y-axis direction
        if (deltaY == -1)
        {
            if (currentDirection == Direction::SOUTH)
            {
                return Movement::MovementKind::Straight;
            }

            if (currentDirection == Direction::WEST)
            {
                return Movement::MovementKind::Counterclockwise;
            }

            if (currentDirection == Direction::EAST)
            {
                return Movement::MovementKind::Clockwise;
            }

            return Movement::MovementKind::Counterclockwise;
        }
        return Movement::MovementKind::Stop;
    }

} // namespace Service
