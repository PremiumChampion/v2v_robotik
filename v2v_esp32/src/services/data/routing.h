#pragma once

namespace Service
{
    namespace Routing
    {
        int calculateRouteWithCollisionAvoidance(int from, int target, int blocked);
        int calculateRoute(int from, int target);
    } // namespace Routing
}