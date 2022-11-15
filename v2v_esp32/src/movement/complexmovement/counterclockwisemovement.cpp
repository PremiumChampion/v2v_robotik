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
        // this->startHeading = Sensors::MPU.getValue();
        int currentHeading = Sensors::MPU.getValue();
        int result = currentHeading + (currentHeading < 0 ? -1 : 1) * 90 / 2;
        this->targetHeading = (result - result % 90) + 180;
        // this->targetHeading = this->startHeading + 180;
        this->state = CC_TurningState;
        this->backupStartTime = 0;
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
            int speed = map(abs(currentheading - targetHeading), 0, 180, 35, 200);

            if (this->targetHeading > currentheading)
            {
                Vehicle::ROVER.set(speed, 180);
            }
            if (currentheading > this->targetHeading)
            {
                Vehicle::ROVER.set(speed, 0);
            }

            if (currentheading == targetHeading)
            {
                state = CC_BackwardsState;
            }
        }

        if (state == CC_BackwardsState)
        {
            bool left = Sensors::LINE_SENSOR.left();
            bool center = Sensors::LINE_SENSOR.center();
            bool right = Sensors::LINE_SENSOR.right();

            if (backupStartTime == 0)
            {
                if (left && !right)
                {
                    Vehicle::ROVER.set(40, 240);
                }
                else if (!left && right)
                {
                    Vehicle::ROVER.set(40, 300);
                }
                else if (!(left && center && right))
                {
                    Vehicle::ROVER.set(40, 270);
                }
                else if (left && center && right)
                {
                    Vehicle::ROVER.set(0, 90);
                    if (this->backupStartTime == 0)
                    {
                        this->backupStartTime = millis();
                    }
                }
            }
            if (this->backupStartTime != 0 && this->backupStartTime + 500 < millis())
            {
                this->isDone = true;
            }
        }
    }

} // namespace Movement
