#include <Arduino.h>
#include "communication/communication.h"
#include "counterclockwisemovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    CounterClockWiseMovement::CounterClockWiseMovement() : BasicMovement()
    {
#if ROLE == CHASED
        this->turningTime = 570;
        this->turningSpeed = 90;
        this->straightTime = 80;
#endif
#if ROLE == CHASER
        this->turningTime = 650;
        this->turningSpeed = 90;
        this->straightTime = 50;
#endif
        this->isDone = false;
        this->startTime = 0;
    }

    void CounterClockWiseMovement::run()
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
            Vehicle::ROVER.set(255, 180);
            return;
        }
        if (this->startTime + this->turningTime + this->straightTime > millis())
        {
            Vehicle::ROVER.set(255, 270);
            return;
        }

        if (this->startTime + this->turningTime + this->straightTime + 500 > millis())
        {
            Vehicle::ROVER.set(0, 0);
            return;
        }
        Serial.println("COUNTERCLOCKWISE:Done");
        this->isDone = true;
    }

} // namespace Movement
