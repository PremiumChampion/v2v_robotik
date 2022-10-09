#include <Arduino.h>
#include "services/positioning.h"
#include "movement/movement.h"

#pragma once

namespace Service
{
    namespace Forwarding
    {
        Movement::MovementKind calculateNextMovement(Positioning *posObject, int nextTile);
    }

}