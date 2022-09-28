#include <Arduino.h>
#include "leftmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    LeftMovement::LeftMovement() : BasicMovement()
    {
        this->state = Starting;
    }
    void LeftMovement::run()
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

        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        switch (this->state)
        {
        case Starting:
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
                this->state = HalfWay;
            }
            break;
        case HalfWay:
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
                this->state = Ending;
                Vehicle::ROVER.set(0, 180);
            }

            break;
        case Ending:
            break;
        default:
            break;
        }
    }

} // namespace Movement
