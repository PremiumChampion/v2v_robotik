#include <Arduino.h>
#include "communication/communication.h"
#include "clockwisemovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    ClockWiseMovement::ClockWiseMovement() : BasicMovement()
    {
        this->isDone = false;
        int currentHeading = Sensors::MPU.getValue();
        int result = currentHeading + (currentHeading < 0 ? -1 : 1) * 90 / 2;
        this->targetHeading = (result - result % 90) - 180;
        this->backupStartTime = 0;
        this->state = TurningState;
    }
    void ClockWiseMovement::run()
    {
        if (this->isDone)
        {
            return;
        }

        Vehicle::ROVER.setMaxMovementSpeed(MAX_TURNING_MOVEMENT_SPEED);
        if (state == TurningState)
        {

            float currentheading = Sensors::MPU.getValue();
            int speed = map(abs(currentheading - targetHeading), 0, 180, 30, 200);

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
                Vehicle::ROVER.set(0, 90);
                state = BackwardsState;
            }
        }

        if (state == BackwardsState)
        {
            bool left = Sensors::LINE_SENSOR.left();
            bool center = Sensors::LINE_SENSOR.center();
            bool right = Sensors::LINE_SENSOR.right();

            if (backupStartTime == 0)
            {
                if (!(left && center && right))
                {
                    Vehicle::ROVER.set(40, 270);
                }

                if (left && center && right)
                {
                    Vehicle::ROVER.set(0, 90);
                    if (this->backupStartTime == 0)
                    {
                        this->backupStartTime = millis();
                    }
                }
            }

            if (this->backupStartTime != 0 && this->backupStartTime + 1000 < millis())
            {
                this->isDone = true;
            }
        }
    }
} // namespace Movement
