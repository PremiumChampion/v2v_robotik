#pragma once

namespace Service
{
    namespace Routing
    {
        int calculateRoute(int from, int target);
        int calculateWithCollisionCheck(int from, int target, int blocked);
    } // namespace Routing

    // Chaser: Berechnet den nächsten Punkt zum Chased-one/ Array???
    // Chased-one: Berechnung zufällig?

}