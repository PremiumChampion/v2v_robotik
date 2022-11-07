#include <Arduino.h>
#include "straightmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    StraightMovement::StraightMovement() : BasicMovement()
    {
        this->state = Start;
        this->isDone = false;
        this->backupStartTime = 0;
        this->backupTime_ms = 100;
    }
    void StraightMovement::run()
    {
        Vehicle::ROVER.setMaxMovementSpeed(MAX_STRAIGHT_MOVEMENT_SPEED);

        if (this->isDone)
        {
            Vehicle::ROVER.set(0, 90);
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
            this->debounce_start_ms = millis();
        }
        else
        {
            this->debounce_start_ms = 0;
        }

        if (debounce_start_ms + 100 < millis())
        {
            Vehicle::ROVER.set(0, 90);
        }
    }

    void StraightMovement::startSegment()
    {
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();
        if (left && right && center)
        {
            Vehicle::ROVER.set(255, 90);
        }

        if (!(left && right && center))
        {
            Serial.println("FirstNarrowSegment");
            this->state = FirstNarrowSegment;
        }
    }
    void StraightMovement::narrowSegment()
    {
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        int turnDelta = this->state == FirstNarrowSegment ? TURN_DELTA : TURN_DELTA / 2;

        if (left && !center && !right)
        {
            Vehicle::ROVER.set(255, 90 - turnDelta);
        }
        if (left && center && !right)
        {
            Vehicle::ROVER.set(255, 90 - turnDelta / 2);
        }

        if (!left && !center && right)
        {
            Vehicle::ROVER.set(255, 90 + turnDelta);
        }
        if (!left && center && right)
        {
            Vehicle::ROVER.set(255, 90 + turnDelta / 2);
        }

        if (left && center && right)
        {
            Serial.println(this->state == FirstNarrowSegment ? "WideSegment" : "BackwardsSegment");

            this->state = this->state == FirstNarrowSegment ? WideSegment : BackwardsSegment;
        }
    }
    void StraightMovement::wideSegment()
    {
        bool left = Sensors::LINE_SENSOR.left();
        bool center = Sensors::LINE_SENSOR.center();
        bool right = Sensors::LINE_SENSOR.right();

        if (left && center && !right)
        {
            Vehicle::ROVER.set(255, 90 - TURN_DELTA / 2);
        }
        if (!left && center && right)
        {
            Vehicle::ROVER.set(255, 90 + TURN_DELTA / 4);
        }

        if (!left && !center && right)
        {
            Vehicle::ROVER.set(255, 90 + TURN_DELTA / 2);
        }

        if (left && !center && !right)
        {
            Vehicle::ROVER.set(255, 90 - TURN_DELTA / 4);
        }

        if (!left && center && !right)
        {
            Serial.println("SecondNarrowSegment");

            this->state = SecondNarrowSegment;
        }
    }
    void StraightMovement::backwardsSegment()
    {
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
