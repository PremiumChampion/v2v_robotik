#include <Arduino.h>
#include "stopmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    StopMovement::StopMovement() : BasicMovement() {
        this->isDone = true;
        // this->isPaused = false;
    }
    void StopMovement::run()
    {
        // if (this->isPaused)
        // {
        //     Vehicle::ROVER.set(0, 90);
        //     return;
        // }
        this->isDone = true;
        Vehicle::ROVER.set(0, 90);

        if (this->isDone)
        {
            return;
        }
    }
} // namespace Movement
