#include <Arduino.h>
#include "communication/communication.h"
#include "counterclockwisemovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    CounterClockWiseMovement::CounterClockWiseMovement() : BasicMovement()
    {
        this->isDone = false;
        this->startHeading = Sensors::MPU.getValue();
        this->targetHeading = this->startHeading + 90;
        this->state = CC_TurningState;
    }
    void CounterClockWiseMovement::run()
    {
        if (this->isDone)
        {
            return;
        }

        Vehicle::ROVER.setMaxMovementSpeed(MAX_TURNING_MOVEMENT_SPEED);
        if (state == CC_TurningState)
        {

            float currentheading = Sensors::MPU.getValue();
            int speed = map(abs(targetHeading - currentheading), 0, 90, 50, 255);

            if (this->targetHeading > currentheading)
            {
                Vehicle::ROVER.set(speed, 180);
            }
            if (currentheading > this->targetHeading)
            {
                Vehicle::ROVER.set(speed, 0);
            }

            if (currentheading + 0.2 > targetHeading && currentheading - 0.2 < targetHeading)
            {
               state = CC_BackwardsState; 
            }
        }

        if (state == CC_BackwardsState)
        {
            bool left = Sensors::LINE_SENSOR.left();
            bool center = Sensors::LINE_SENSOR.center();
            bool right = Sensors::LINE_SENSOR.right();
            Vehicle::ROVER.set(255, 270);
            if (left && center && right)
            {
                Vehicle::ROVER.set(0, 0);
                this->isDone = true;
                Serial.println("COUNTERCLOCKWISE:Done");
            }
        }
    }

} // namespace Movement
