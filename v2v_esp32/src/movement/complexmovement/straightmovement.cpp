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
        this->backupTime_ms = 250;
        this->debouncetime_ms = 15;
        this->heading = Sensors::MPU.getValue();

#if (ROLE == CHASER)
        this->straight_degrees = 85;
#endif
#if (ROLE == CHASED)
        this->straight_degrees = 75;
#endif
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
        case FirstNarrowSegment:
        case SecondNarrowSegment:
            this->narrowSegment();
            break;
        case WideSegment:
            this->wideSegment();
            break;
        case BackwardsSegment:
            this->backwardsSegment();
            break;
        default:
            break;
        }
        // this->checkLine();
    }

    void StraightMovement::checkLine()
    {
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        if (!left && !center && !right)
        {
            Serial.println("DebounceStart");
            this->debounce_start_ms = millis();
        }
        else if (this->debounce_start_ms != 0)
        {
            Serial.println("DebounceReset");
            this->debounce_start_ms = 0;
        }

        if (debounce_start_ms + 100 < millis())
        {
            Vehicle::ROVER.set(0, this->straight_degrees);
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

        if (left && right && center)
        {
            Vehicle::ROVER.set(255, this->straight_degrees);
        }

        if (!(left && right && center) && this->start_ms + 200 < millis())
        {
            Serial.println("FirstNarrowSegment");
            this->state = FirstNarrowSegment;
        }
    }
    void StraightMovement::narrowSegment()
    {
        float currentHeading = Sensors::MPU.getValue();
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        int turnDelta = TURN_DELTA;

        if (left && !center && !right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees + turnDelta);
        }
        if (left && center && !right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees + turnDelta / 2);
        }

        if (!left && !center && right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees - turnDelta);
        }
        if (!left && center && right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees - turnDelta / 2);
        }

        if (this->state == FirstNarrowSegment)
        {
            if (left && center && right)
            {
                Serial.println("WideSegment");

                this->state = SecondNarrowSegment;
            }
        }

        if (this->state == SecondNarrowSegment)
        {
            if (left && center && right)
            {
                // Serial.println("BackwardsSegment");
                // this->state = BackwardsSegment;
                if (this->debounce_start_ms == 0)
                {
                    Serial.println("DebounceStart");
                    this->debounce_start_ms = millis();
                }
            }
            else
            {
                this->debounce_start_ms = 0;
            }

            if (this->debounce_start_ms != 0 && this->debounce_start_ms + this->debouncetime_ms < millis())
            {
                Serial.println("DebounceSuccess");
                Serial.println("BackwardsSegment");
                this->state = BackwardsSegment;
            }
        }
    }
    void StraightMovement::wideSegment()
    {
        float currentHeading = Sensors::MPU.getValue();
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        if (left && center && !right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees + TURN_DELTA / 4);
        }
        if (left && !center && !right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees + TURN_DELTA / 2);
        }

        if (!left && center && right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees - TURN_DELTA / 4);
        }
        if (!left && !center && right)
        {
            Vehicle::ROVER.set(255, this->straight_degrees - TURN_DELTA / 2);
        }

        if (!left && center && !right)
        {
            Serial.println("SecondNarrowSegment");

            this->state = SecondNarrowSegment;
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

        if (this->backupStartTime + this->backupTime_ms > millis())
        {
            Vehicle::ROVER.set(255, 270);
            return;
        }
        Vehicle::ROVER.set(0, 90);
        if (this->backupStartTime + this->backupTime_ms + 500 < millis())
        {
            Serial.println("Straight:Done");
            this->isDone = true;
        }
    }
} // namespace Movement
