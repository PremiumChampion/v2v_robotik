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
        this->startHeading = Sensors::MPU.getValue();
        this->targetHeading = this->startHeading - 180;
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
            int speed = map(abs(currentheading - targetHeading), 0, 90, 40, 255);

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
                state = BackwardsState;
            }
        }

        if (state == BackwardsState)
        {
            bool left = Sensors::LINE_SENSOR.left();
            bool center = Sensors::LINE_SENSOR.center();
            bool right = Sensors::LINE_SENSOR.right();
            Vehicle::ROVER.set(128, 270);
            if (left && center && right)
            {
                Vehicle::ROVER.set(0, 0);
                this->isDone = true;
                Serial.println("CLOCKWISE:Done");
            }
        }
    }
} // namespace Movement
