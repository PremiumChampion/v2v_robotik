#include "movement/movement.h"

// Besitzt eine run Metode die nacheinander Routing, Positioning und den Forwardingservice aufruft.
#pragma once

namespace Service
{
    namespace Coordinator
    {
        void run();
        void calculateRoute(int *nextTile, Movement::MovementKind *nextMovement);

        void setStopBeforeTarget(bool nextStopBeforeTarget);
        bool getStopBeforeTarget();
        void setCurrentTarget(int currentTarget);
        int getCurrentTarget();
        void setRunWithCollisionAvoidance(bool collisionAvoidanceEnabled);
        bool getRunWithCollisionAvoidance();
    };
} // namespace Service
