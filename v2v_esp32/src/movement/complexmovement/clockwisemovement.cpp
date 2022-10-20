#include <Arduino.h>
#include "clockwisemovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    ClockWiseMovement::ClockWiseMovement() : BasicMovement()
    {
        this->state = C_Starting;
        this->isDone = false;
    }
    void ClockWiseMovement::run()
    {
        if (this->isDone)
        {
            return;
        }

        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        switch (this->state)
        {
        case C_Starting:
            if (left && center && right)
            {
                Vehicle::ROVER.set(255, 0);
            }
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 360 - TURN_DELTA);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 0 + TURN_DELTA);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 0);
                this->state = C_HalfWay;
            }
            break;
        case C_HalfWay:
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 0);
            }

            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 360 - TURN_DELTA);
            }

            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 0 + TURN_DELTA);
            }

            if (left && center && right)
            {
                this->isDone = true;
                this->state = C_Ending;
                Vehicle::ROVER.set(0, 0);
            }

            break;
        case C_Ending:
            break;
        default:
            break;
        }
    }
} // namespace Movement
