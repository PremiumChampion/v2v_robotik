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
        this->backwardsStartTime = 0;
    }
    void ClockWiseMovement::run()
    {
        Vehicle::ROVER.setMaxMovementSpeed(MAX_TURNING_MOVEMENT_SPEED);
        if (this->isDone)
        {
            return;
        }
        digitalWrite(2, LOW); // BUILTIN LED

        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();
        Serial.print("L:" + String(left));
        Serial.print("C:" + String(center));
        Serial.println("R:" + String(right));
        switch (this->state)
        {
        case C_Starting:
            if (left && center && right)
            {
                Vehicle::ROVER.set(255, 0);
            }
            if (left && center && !right)
            {
                Vehicle::ROVER.set(255, 0 - TURN_DELTA);
            }
            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 180 + TURN_DELTA);
            }

            if (left && !center && right && this->backwardsStartTime == 0)
            {
                this->backwardsStartTime = millis();
            }

            if (!(left && !center && right))
            {
                this->backwardsStartTime = 0;
            }

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
                Vehicle::ROVER.set(0, 90);
                digitalWrite(2, HIGH); // BUILTIN LED
            }

            if (!left && center && !right)
            {
                Vehicle::ROVER.set(255, 0); // do this for at least 200ms ignoring sensor input
                this->state = C_HalfWay_Pause;
                this->centerStartTime = millis();
            }

            break;
        case C_HalfWay_Pause:
            if (this->centerStartTime + 200 < millis())
            {
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
                Vehicle::ROVER.set(255, 0 + TURN_DELTA);
            }

            if (!left && center && right)
            {
                Vehicle::ROVER.set(255, 0 - TURN_DELTA);
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
                else
                {
                    Vehicle::ROVER.set(255, 90); // drive forwards until cross met
                }
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
