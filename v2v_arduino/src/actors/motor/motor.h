#include <Arduino.h>
#include "direction/direction.h"
#include "speed/speed.h"
#pragma once

namespace Actors
{
    class HHN_Motor
    {
    private:
        HHN_MotorSpeed *speed;
        HHN_MotorDirection *direction;

    public:
        HHN_Motor(HHN_MotorSpeed *speed, HHN_MotorDirection *direction);
        ~HHN_Motor();
        void run();
    };

    static const int MOTOR_LEFT_SPEED_PIN = 5;
    static const int MOTOR_RIGHT_SPEED_PIN = 6;
    static const int MOTOR_RIGHT_DIRECTION_PIN = 7;
    static const int MOTOR_LEFT_DIRECTION_PIN = 8;

    extern HHN_MotorSpeed speed_l;
    extern HHN_MotorSpeed speed_r;
    extern HHN_MotorDirection direction_l;
    extern HHN_MotorDirection direction_r;
    extern HHN_Motor motorL;
    extern HHN_Motor motorR;

} // namespace Actors
