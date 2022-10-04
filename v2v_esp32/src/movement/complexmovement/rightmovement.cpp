#include <Arduino.h>
#include "rightmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    RightMovement::RightMovement() : BasicMovement()
    {
        this->state = R_Starting;
        // this->isPaused = false;
        this->isDone = false;
    }
    void RightMovement::run()
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
        case R_Starting:
            if (left && center && right)
            {
                Vehicle::ROVER.set(255, 0);
            }
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 350);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 10);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 0);
                this->state = R_HalfWay;
            }
            break;
        case R_HalfWay:
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 0);
            }

            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 350);
            }

            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 10);
            }

            if (left && center && right)
            {
                this->isDone = true;
                this->state = R_Ending;
                Vehicle::ROVER.set(0, 0);
            }

            break;
        case R_Ending:
            break;
        default:
            break;
        }
    }
} // namespace Movement
