#include "actors/motor/motor.h"

#define MIN_MOVEMENT_SPEED 30
#define MAX_STRAIGHT_MOVEMENT_SPEED 40
#define MAX_TURNING_MOVEMENT_SPEED 40

#pragma once

namespace Vehicle
{
    enum MotorDirection
    {
        FORWARD,
        BACKWARD,
        STOP
    };

    class Vehicle
    {
    private:
        Actors::HHN_V_Motor *motorL, *motorR;
        float currentSpeed;
        int currentDirection;
        int maxMovmementSpeed;
        // phaseDelta: degrees by which the cos function needs to be moved to archieve the correct encoding for the motor
        // motorL: 0
        // motorR: 90
        void calculateMotorValue(Actors::HHN_V_Motor *motor, bool rightMotor);

    public:
        Vehicle(Actors::HHN_V_Motor *motorL, Actors::HHN_V_Motor *motorR);
        ~Vehicle();
        float getSpeed();
        int getDirection();
        void set(float speed, int direction);
        void setMaxMovementSpeed(int newMovementSpeed);
    };

    extern Vehicle ROVER;
} // namespace Vehicle
