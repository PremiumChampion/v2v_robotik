#include "forwarding.h"
#include "movement/movement.h"

namespace Service
{

    Forwarding::ForwardingTable::ForwardingTable(Movement::MovementKind north, Movement::MovementKind east, Movement::MovementKind south, Movement::MovementKind west)
    {
        this->east = east;
        this->north = north;
        this->south = south;
        this->west = west;
    }
    Movement::MovementKind Forwarding::ForwardingTable::getNextMovementDirection(Direction currentDirection)
    {
        if (currentDirection == NORTH)
        {
            return this->north;
        }
        if (currentDirection == EAST)
        {
            return this->east;
        }
        if (currentDirection == SOUTH)
        {
            return this->south;
        }
        if (currentDirection == WEST)
        {
            return this->west;
        }

        return Movement::MovementKind::Stop;
    }

    // movement map in positive x-achsis direction
    Forwarding::ForwardingTable PositiveDeltaX(
        Movement::MovementKind::Clockwise,        // North
        Movement::MovementKind::Straight,         // East
        Movement::MovementKind::Counterclockwise, // South
        Movement::MovementKind::Clockwise);       // West
    // movement map in negative x-achsis direction
    Forwarding::ForwardingTable NegativeDeltaX(
        Movement::MovementKind::Counterclockwise, // North
        Movement::MovementKind::Counterclockwise, // East
        Movement::MovementKind::Clockwise,        // South
        Movement::MovementKind::Straight);        // West
    //  movement map in positive y-axis direction
    Forwarding::ForwardingTable PositiveDeltaY(
        Movement::MovementKind::Straight,          // North
        Movement::MovementKind::Clockwise,         // East
        Movement::MovementKind::Clockwise,         // South
        Movement::MovementKind::Counterclockwise); // West
    //  movement map in negative y-axis direction
    Forwarding::ForwardingTable NegativeDeltaY(
        Movement::MovementKind::Counterclockwise,  // North
        Movement::MovementKind::Clockwise,         // East
        Movement::MovementKind::Straight,          // South
        Movement::MovementKind::Counterclockwise); // West

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

        // if (deltaX == 0 && deltaY == 0)
        // {
        //     return Movement::MovementKind::Stop;
        // }
        // Calculate movement if movement is in positive x-axis direction

        if (deltaX == 1)
            return PositiveDeltaX.getNextMovementDirection(currentDirection);
        if (deltaX == -1)
            return NegativeDeltaX.getNextMovementDirection(currentDirection);
        if (deltaY == 1)
            return PositiveDeltaY.getNextMovementDirection(currentDirection);
        if (deltaY == -1)
            return NegativeDeltaY.getNextMovementDirection(currentDirection);

        return Movement::MovementKind::Stop;
        // if (deltaX == 1)
        // {

        //     if (currentDirection == Direction::EAST)
        //     {
        //         return Movement::MovementKind::Straight;
        //     }

        //     if (currentDirection == Direction::NORTH)
        //     {
        //         return Movement::MovementKind::Clockwise;
        //     }

        //     if (currentDirection == Direction::SOUTH)
        //     {
        //         return Movement::MovementKind::Counterclockwise;
        //     }

        //     return Movement::MovementKind::Clockwise;
        // }
        // // Calculate movement in negative x-axis direction
        // if (deltaX == -1)
        // {
        //     if (currentDirection == Direction::WEST)
        //     {
        //         return Movement::MovementKind::Straight;
        //     }

        //     if (currentDirection == Direction::NORTH)
        //     {
        //         return Movement::MovementKind::Counterclockwise;
        //     }

        //     if (currentDirection == Direction::SOUTH)
        //     {
        //         return Movement::MovementKind::Clockwise;
        //     }

        //     return Movement::MovementKind::Counterclockwise;
        // }
        // Calculate movement in positive y-axis direction
        // if (deltaY == 1)
        // {
        //     if (currentDirection == Direction::NORTH)
        //     {
        //         return Movement::MovementKind::Straight;
        //     }

        //     if (currentDirection == Direction::EAST)
        //     {
        //         return Movement::MovementKind::Clockwise;
        //     }

        //     if (currentDirection == Direction::WEST)
        //     {
        //         return Movement::MovementKind::Counterclockwise;
        //     }

        //     return Movement::MovementKind::Clockwise;
        // }
        // // Calculate movement in negative y-axis direction
        // if (deltaY == -1)
        // {
        //     if (currentDirection == Direction::SOUTH)
        //     {
        //         return Movement::MovementKind::Straight;
        //     }

        //     if (currentDirection == Direction::WEST)
        //     {
        //         return Movement::MovementKind::Counterclockwise;
        //     }

        //     if (currentDirection == Direction::EAST)
        //     {
        //         return Movement::MovementKind::Clockwise;
        //     }

        //     return Movement::MovementKind::Counterclockwise;
        // }
        // return Movement::MovementKind::Stop;
    }

} // namespace Service
