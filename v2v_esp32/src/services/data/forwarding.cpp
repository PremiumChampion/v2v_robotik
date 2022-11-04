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

    // nach rechts fahren
    Forwarding::ForwardingTable PositiveDeltaX(
        Movement::MovementKind::Clockwise,        // North
        Movement::MovementKind::Straight,         // East
        Movement::MovementKind::Counterclockwise, // South
        Movement::MovementKind::Clockwise);       // West
    // nach links fahren
    Forwarding::ForwardingTable NegativeDeltaX(
        Movement::MovementKind::Counterclockwise, // North
        Movement::MovementKind::Clockwise,        // East
        Movement::MovementKind::Clockwise,        // South
        Movement::MovementKind::Straight);        // West
    //  nach unten fahren
    Forwarding::ForwardingTable PositiveDeltaY(
        Movement::MovementKind::Clockwise,         // North
        Movement::MovementKind::Clockwise,         // East
        Movement::MovementKind::Straight,          // South
        Movement::MovementKind::Counterclockwise); // West
    //  nach oben fahren
    Forwarding::ForwardingTable NegativeDeltaY(
        Movement::MovementKind::Straight,         // North
        Movement::MovementKind::Counterclockwise, // East
        Movement::MovementKind::Clockwise,        // South
        Movement::MovementKind::Clockwise);       // West

    Movement::MovementKind Forwarding::calculateNextMovement(Positioning *posObject, int nextTile)
    {
        // Calculate from current tile pos current x and y
        // Calculate, if movement is either in x-axis or y-axis
        // direction(also either positive or negative direction)
        // Calculate, in which direction robot needs to turn, in relevance to its current facing direction
        int currentTile = posObject->getCurrentPositionTile();         // 12
        Direction currentDirection = posObject->getCurrentDirection(); // NORTH
        // nextTile == 8
        int nextTileX = nextTile % 4;      // 0
        int nextTileY = nextTile / 4;      // 2
        int currentX = currentTile % 4;    // 0
        int currentY = currentTile / 4;    // 3
        int deltaX = nextTileX - currentX; // 0
        int deltaY = nextTileY - currentY; // -1

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
    }

} // namespace Service
