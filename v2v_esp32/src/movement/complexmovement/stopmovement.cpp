#include <Arduino.h>
#include "stopmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    StopMovement::StopMovement() : BasicMovement() {}
    void StopMovement::run()
    {
        if (this->isPaused)
        {
            Vehicle::ROVER.set(0, 90);
            return;
        }

        if (this->isDone)
        {
            return;
        }
        
        Vehicle::ROVER.set(0, 90);
    }
} // namespace Movement
