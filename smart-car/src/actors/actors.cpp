#include <Arduino.h>
#include "actors/motor.h"

namespace Actors
{
    Motor::MotorDefinition motor_left = {
        .pin_PWM = 5,
        .pin_PWM_value = 0,
        .pin_ENABLE = 8,
        .pin_ENABLE_value = LOW,
    };
    Motor::MotorDefinition motor_right = {
        .pin_PWM = 6,
        .pin_PWM_value = 0,
        .pin_ENABLE = 7,
        .pin_ENABLE_value = LOW,
    };

    void set_left(Motor::MotorDirection direction, double speed)
    {
        Motor::set_direction(&motor_left, direction, speed);
    }

    void set_right(Motor::MotorDirection direction, double speed)
    {
        Motor::set_direction(&motor_right, direction, speed);
    }

    Motor::MotorDefinition* get_left(){
        return &motor_left;
    }
    Motor::MotorDefinition* get_right(){
        return &motor_right;
    }

    void init()
    {
        Motor::init(&motor_left);
        Motor::init(&motor_right);
    }

    void run()
    {
        Motor::run(&motor_left);
        Motor::run(&motor_right);
    }
} // namespace Actors
