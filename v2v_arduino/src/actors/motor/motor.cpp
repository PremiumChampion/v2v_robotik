#include <Arduino.h>
#include "direction/direction.h"
#include "speed/speed.h"
#include "motor.h"
#include "actors/actors.h"

namespace Actors
{
    HHN_MotorSpeed speed_l = HHN_MotorSpeed(Actors::MOTOR_LEFT_SPEED_PIN, Actor::motor_l_speed);
    HHN_MotorSpeed speed_r = HHN_MotorSpeed(Actors::MOTOR_RIGHT_SPEED_PIN, Actor::motor_r_speed);
    HHN_MotorDirection direction_l = HHN_MotorDirection(Actors::MOTOR_LEFT_DIRECTION_PIN, Actor::motor_l_direction);
    HHN_MotorDirection direction_r = HHN_MotorDirection(Actors::MOTOR_RIGHT_DIRECTION_PIN, Actor::motor_r_direction);

    void enableMotors()
    {
        pinMode(ENABLE_MOTOR_CONTROL_PIN, OUTPUT);
        digitalWrite(ENABLE_MOTOR_CONTROL_PIN, HIGH);
    }
    void disableMotors()
    {
        pinMode(ENABLE_MOTOR_CONTROL_PIN, OUTPUT);
        digitalWrite(ENABLE_MOTOR_CONTROL_PIN, LOW);
    }

} // namespace Actors
