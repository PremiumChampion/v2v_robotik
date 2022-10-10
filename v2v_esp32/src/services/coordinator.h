// Besitzt eine run Metode die nacheinander Routing, Positioning und den Forwardingservice aufruft.
#pragma once

namespace Service
{
    namespace Coordinator
    {
        void setCurrentTarget(int currentTarget);
        void run();
    };
} // namespace Service
