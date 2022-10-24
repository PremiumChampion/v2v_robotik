#pragma once

namespace Service
{
    namespace Routing
    {
        int calculateRoute(int from, int target);
        int calculateWithCollisionCheck(int from, int target, int blocked);
    } // namespace Routing
}