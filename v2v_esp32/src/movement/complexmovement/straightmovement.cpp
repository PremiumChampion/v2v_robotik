#include <Arduino.h>
#include "straightmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"
#include "communication/communication.h"

namespace Movement
{
    StraightMovement::StraightMovement() : BasicMovement()
    {
        this->state = Start;
        this->isDone = false;
        this->backupStartTime = 0;
        this->start_ms = 0;
        this->backupTime_ms = 0;
        this->debouncetime_ms = 0;
        int currentHeading = Sensors::MPU.getValue();
        int result = currentHeading + (currentHeading < 0 ? -1 : 1) * 90 / 2;
        this->heading = result - result % 90;
        this->straight_degrees = 90;
    }

    void StraightMovement::run()
    {
        Vehicle::ROVER.setMaxMovementSpeed(MAX_STRAIGHT_MOVEMENT_SPEED);

        if (this->isDone)
        {
            Vehicle::ROVER.set(0, this->straight_degrees);
            return;
        }

        switch (this->state)
        {
        case Start:
            this->startSegment();
            break;
        case StraightSegment:
            this->straightSegment();
            break;
        case BackwardsSegment:
            this->backwardsSegment();
            break;
        default:
            break;
        }
    }

    void StraightMovement::startSegment()
    {
        float currentHeading = Sensors::MPU.getValue();
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        if (this->start_ms == 0)
        {
            this->start_ms = millis();
        }

        Vehicle::ROVER.set(255, this->calculateAngleOfAttak());

        if (!(left && center && right) && this->start_ms + 1000 < millis())
        {
            this->state = StraightSegment;
        }
    }

    int StraightMovement::calculateAngleOfAttak()
    {
        float currentHeading = Sensors::MPU.getValue();
        return this->straight_degrees - ((int)(this->heading - currentHeading) * 6);
    }

    void StraightMovement::straightSegment()
    {
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        Vehicle::ROVER.set(255, this->calculateAngleOfAttak());

        if (left && center && right)
        {
            if (this->debounce_start_ms == 0)
            {
                this->debounce_start_ms = millis();
            }
            if (this->debounce_start_ms + this->debouncetime_ms < millis())
            {
                this->state = BackwardsSegment;
            }
        }
        else
        {
            this->debounce_start_ms = 0;
        }
    }
    void StraightMovement::backwardsSegment()
    {
        float currentHeading = Sensors::MPU.getValue();
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        if (this->backupStartTime == 0)
        {
            this->backupStartTime = millis();
        }

        // if (this->backupStartTime + this->backupTime_ms > millis())
        // {
        //     Vehicle::ROVER.set(255, 270);
        //     return;
        // }
        Vehicle::ROVER.set(0, 90);
        if (this->backupStartTime + 500 < millis())
        {
            this->isDone = true;
        }
    }
} // namespace Movement
