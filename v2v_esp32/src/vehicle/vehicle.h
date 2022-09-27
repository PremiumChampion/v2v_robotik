#include "actors/motor/motor.h"

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
        // phaseDelta: degrees by which the cos function needs to be moved to archieve the correct encoding for the motor
        // motorL: 0
        // motorR: 90
        void calculateMotorValue(Actors::HHN_V_Motor *motor, int phaseDelta);

    public:
        Vehicle(Actors::HHN_V_Motor *motorL, Actors::HHN_V_Motor *motorR);
        ~Vehicle();
        float getSpeed();
        int getDirection();
        void set(float speed, int direction);
    };

    extern Vehicle ROVER;
} // namespace Vehicle
