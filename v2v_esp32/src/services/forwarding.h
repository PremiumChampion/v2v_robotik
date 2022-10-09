#include <Arduino.h>
#include "services/positioning.h"
#include "movement/movement.h"

#pragma once

namespace Service
{
    namespace Forwarding
    {
        Movement::MovementKind calculateNextMovement(Positioning *posObject, int nextTile);

        class ForwardingTable
        {

        private:
            Movement::MovementKind north;
            Movement::MovementKind east;
            Movement::MovementKind south;
            Movement::MovementKind west;

        public:
            ForwardingTable(Movement::MovementKind north, Movement::MovementKind east, Movement::MovementKind south, Movement::MovementKind west);
            Movement::MovementKind getNextMovementDirection(Direction currentDirection);
        };
    }
}