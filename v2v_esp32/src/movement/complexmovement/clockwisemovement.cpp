#include <Arduino.h>
#include "communication/communication.h"
#include "clockwisemovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    ClockWiseMovement::ClockWiseMovement() : BasicMovement()
    {
#if ROLE == CHASED
        this->turningTime = 560;
        this->turningSpeed = 90;
        this->backupTime = 70;
#endif
#if ROLE == CHASER
        this->turningTime = 580;
        this->turningSpeed = 90;
        this->backupTime = 100;
#endif
        this->isDone = false;
        this->startTime = 0;
    }
    void ClockWiseMovement::run()
    {
        if (this->isDone)
        {
            return;
        }

        Vehicle::ROVER.setMaxMovementSpeed(this->turningSpeed);

        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        if (this->startTime == 0)
        {
            this->startTime = millis();
        }

        if (this->startTime + this->turningTime > millis())
        {
            Vehicle::ROVER.set(255, 0);
            return;
        }
        if (this->startTime + this->turningTime + this->backupTime > millis())
        {
            Vehicle::ROVER.set(255, 270);
            return;
        }

        if (this->startTime + this->turningTime + this->backupTime + 500 > millis())
        {
            Vehicle::ROVER.set(0, 0);
            return;
        }

        Serial.println("CLOCKWISE:Done");
        this->isDone = true;

        // switch (this->state)
        // {
        // case C_Starting:
        //     if (left && center && right)
        //     {
        //         Vehicle::ROVER.set(255, 0);
        //     }
        //     if (left && center && !right)
        //     {
        //         Vehicle::ROVER.set(255, 0 - TURN_DELTA);
        //     }
        //     if (left && !center && !right)
        //     {
        //         Vehicle::ROVER.set(255, 0 - TURN_DELTA);
        //     }
        //     if (!left && center && right)
        //     {
        //         Vehicle::ROVER.set(255, 180 + TURN_DELTA);
        //     }
        //     if (!left && !center && right)
        //     {
        //         Vehicle::ROVER.set(255, 180 + TURN_DELTA);
        //     }

        //     if (left && !center && right && this->backwardsStartTime == 0)
        //     {
        //         this->backwardsStartTime = millis();
        //     }

        //     if (!(left && !center && right))
        //     {
        //         this->backwardsStartTime = 0;
        //     }

        //     if (backwardsStartTime != 0)
        //     {
        //         if (backwardsStartTime + 100 < millis())
        //         {
        //             Vehicle::ROVER.set(255, 270); // drive backwards for 0.1s
        //         }
        //         else if (backwardsStartTime + 250 < millis())
        //         {
        //             Vehicle::ROVER.set(255, 90); // drive forwards until cross met
        //         }
        //         else
        //         {
        //             Vehicle::ROVER.set(0, 90);
        //             digitalWrite(2, HIGH); // BUILTIN LED
        //         }
        //     }

        //     if (!left && center && !right)
        //     {
        //         Vehicle::ROVER.set(255, 0); // do this for at least 200ms ignoring sensor input
        //         this->state = C_HalfWay;
        //         this->centerStartTime = millis();
        //     }

        //     if (!left && !center && !right)
        //     {
        //         Vehicle::ROVER.set(0, 0); // stop
        //         digitalWrite(2, HIGH);    // BUILTIN LED
        //         // Serial.println("Error");
        //     }

        //     break;
        // case C_HalfWay_Pause:
        //     if (this->centerStartTime + 200 < millis())
        //     {
        //         this->state = C_HalfWay;
        //     }
        //     break;
        // case C_HalfWay:
        //     if (left && center && right)
        //     {
        //         Vehicle::ROVER.set(255, 0);
        //     }
        //     if (left && center && !right)
        //     {
        //         Vehicle::ROVER.set(255, 0 - TURN_DELTA);
        //     }
        //     if (left && !center && !right)
        //     {
        //         Vehicle::ROVER.set(255, 0 - TURN_DELTA);
        //     }
        //     if (!left && center && right)
        //     {
        //         Vehicle::ROVER.set(255, 180 + TURN_DELTA);
        //     }
        //     if (!left && !center && right)
        //     {
        //         Vehicle::ROVER.set(255, 180 + TURN_DELTA);
        //     }

        //     if (left && !center && right && this->backwardsStartTime == 0)
        //     {
        //         this->backwardsStartTime = millis();
        //     }

        //     if (!(left && !center && right))
        //     {
        //         this->backwardsStartTime = 0;
        //     }

        //     if (backwardsStartTime != 0)
        //     {
        //         if (backwardsStartTime + 100 < millis())
        //         {
        //             Vehicle::ROVER.set(255, 270); // drive backwards for 0.1s
        //         }
        //         else if (backwardsStartTime + 250 < millis())
        //         {
        //             Vehicle::ROVER.set(255, 90); // drive forwards until cross met
        //         }
        //         else
        //         {
        //             Vehicle::ROVER.set(0, 90);
        //             digitalWrite(2, HIGH); // BUILTIN LED
        //         }
        //     }

        //     if (!left && !center && !right)
        //     {
        //         Vehicle::ROVER.set(0, 0); // stop
        //         digitalWrite(2, HIGH);    // BUILTIN LED
        //         // Serial.println("Error");
        //     }

        //     if (left && center && right)
        //     {
        //         this->state = C_Ending;
        //         Vehicle::ROVER.set(255, 0);
        //         this->centerStartTime = millis();
        //     }

        //     break;
        // case C_Ending:
        //     if (this->centerStartTime + 200 < millis())
        //     {
        //         this->isDone = true;
        //         Vehicle::ROVER.set(0, 0);
        //         Serial.println("DONE");
        //     }
        //     break;
        // default:

        //     break;
        // }
    }
} // namespace Movement
