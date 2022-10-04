#include <Arduino.h>
#include "direction/direction.h"
#include "speed/speed.h"
#pragma once

namespace Actors
{

    static const int MOTOR_LEFT_SPEED_PIN = 5;
    static const int MOTOR_RIGHT_SPEED_PIN = 6;
    static const int MOTOR_RIGHT_DIRECTION_PIN = 7;
    static const int MOTOR_LEFT_DIRECTION_PIN = 8;
    static const int ENABLE_MOTOR_CONTROL_PIN = 3;

    extern HHN_MotorSpeed speed_l;
    extern HHN_MotorSpeed speed_r;
    extern HHN_MotorDirection direction_l;
    extern HHN_MotorDirection direction_r;

    void enableMotors();
    void disableMotors();

} // namespace Actors
