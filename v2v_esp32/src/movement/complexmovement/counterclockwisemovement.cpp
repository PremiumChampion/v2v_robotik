#include <Arduino.h>
#include "counterclockwisemovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    CounterClockWiseMovement::CounterClockWiseMovement() : BasicMovement()
    {
        this->state = CC_Starting;
        this->isDone = false;
    }
    void CounterClockWiseMovement::run()
    {

        // if (this->isPaused)
        // {
        //     Vehicle::ROVER.set(0, 90);
        //     return;
        // }

        if (this->isDone)
        {
            return;
        }

        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        switch (this->state)
        {
        case CC_Starting:
            if (left && center && right)
            {
                Vehicle::ROVER.set(255, 180);
            }
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 190);
            }
            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 170);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 180);
                this->state = CC_HalfWay;
            }
            break;
        case CC_HalfWay:
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 180);
            }

            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 190);
            }

            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 170);
            }

            if (left && center && right)
            {
                this->isDone = true;
                this->state = CC_Ending;
                Vehicle::ROVER.set(0, 180);
            }

            break;
        case CC_Ending:
            break;
        default:
            break;
        }
    }

} // namespace Movement
