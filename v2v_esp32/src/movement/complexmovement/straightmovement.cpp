#include <Arduino.h>
#include "straightmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    StraightMovement::StraightMovement() : BasicMovement()
    {
        this->state = StartCrossing;
        this->isDone = false;
        // this->isPaused = false;
    }
    void StraightMovement::run()
    {

        if (this->isDone)
        {
            Vehicle::ROVER.set(0, 90);
            return;
        }

        bool left = Sensors::LINE_SENSOR.left() == 1;
        bool center = Sensors::LINE_SENSOR.center() == 1;
        bool right = Sensors::LINE_SENSOR.right() == 1;


        switch (this->state)
        {
        case StartCrossing:
            if (left && right && center)
            {
                Vehicle::ROVER.set(255, 90);
            }
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 80);
            }
            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 100);
            }
            if (!left && center && !right)
            {
                this->state = Continuing;
                Vehicle::ROVER.set(255, 90);
            }
            if (!left && !center && right)
            {
                Vehicle::ROVER.set(255, 100);
            }
            if (left && !center && !right)
            {
                Vehicle::ROVER.set(255, 80);
            }
            if (!left && !right && !left)
            {
                Vehicle::ROVER.set(0, 90);
            }
            break;
        case Continuing:
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 80);
            }
            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 100);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 90);
            }
            if (left && center && right)
            {
                this->isDone = true;
                this->state = EndCrossing;
                Vehicle::ROVER.set(0, 90);
            }
            break;
        case EndCrossing:
            break;
        default:
            break;
        }
    }
} // namespace Movement
