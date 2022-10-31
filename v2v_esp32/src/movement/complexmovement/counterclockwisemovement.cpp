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
        this->backwardsStartTime = 0;
    }
    void CounterClockWiseMovement::run()
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
        case CC_Starting:
            if (left && center && right)
            {
                Vehicle::ROVER.set(255, 180);
            }
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 0 - TURN_DELTA);
            }
            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 180 + TURN_DELTA);
            }
            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 180); // do this for at least 200ms ignoring sensor input
                this->state = CC_HalfWay_Pause;
                this->centerStartTime = millis();
            }
            break;
        case CC_HalfWay_Pause:
            if (this->centerStartTime + 200 < millis())
            {
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
                Vehicle::ROVER.set(255, 180 + TURN_DELTA);
            }

            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 180 - TURN_DELTA);
            }

            if (left && !center && right && this->backwardsStartTime == 0)
            {
                this->backwardsStartTime = millis();
            }

            if (!(left && !center && right))
            {
                this->backwardsStartTime = 0;
            }

            if (backwardsStartTime != 0)
            {
                if (backwardsStartTime + 100 < millis())
                {
                    Vehicle::ROVER.set(255, 270); // drive backwards for 0.1s
                }
                else if (backwardsStartTime + 250 < millis())
                {
                    Vehicle::ROVER.set(255, 90); // drive forwards until cross met
                }
                else
                {
                    digitalWrite(2, HIGH); // BUILTIN LED
                    Vehicle::ROVER.set(0, 270);
                }
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
