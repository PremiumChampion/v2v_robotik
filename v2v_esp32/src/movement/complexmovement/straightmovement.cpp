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
        Vehicle::ROVER.setMaxMovementSpeed(MAX_STRAIGHT_MOVEMENT_SPEED);

        if (this->isDone)
        {
            Vehicle::ROVER.set(0, 90);
            return;
        }
        digitalWrite(2, LOW); // BUILTIN LED

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
                Vehicle::ROVER.set(255, 90 - TURN_DELTA);
            }
            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 90 + TURN_DELTA);
            }
            if (!left && center && !right)
            {
                this->state = Continuing;
                Vehicle::ROVER.set(255, 90);
            }
            if (!left && !center && right)
            {
                Vehicle::ROVER.set(255, 90 + TURN_DELTA);
            }
            if (left && !center && !right)
            {
                Vehicle::ROVER.set(255, 90 - TURN_DELTA);
            }
            if (!left && !right && !left)
            {
                digitalWrite(2, HIGH); // BUILTIN LED
                Vehicle::ROVER.set(0, 90);
            }
            break;
        case Continuing:
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 90 - TURN_DELTA);
            }
            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 90 + TURN_DELTA);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 90);
            }
            if (!left && !right && !center)
            {
                digitalWrite(2, HIGH); // BUILTIN LED
                Vehicle::ROVER.set(0, 90);
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
