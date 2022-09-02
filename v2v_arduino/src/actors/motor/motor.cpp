#include <Arduino.h>
#include "direction/direction.h"
#include "speed/speed.h"
#include "motor.h"

namespace Actors
{
    HHN_Motor::HHN_Motor(HHN_MotorSpeed *speed, HHN_MotorDirection *direction)
    {
        this->speed = speed;
        this->direction = direction;
    }

    HHN_Motor::~HHN_Motor()
    {
    }

    void HHN_Motor::update()
    {
        this->direction->update();
        this->speed->update();
    }

    HHN_MotorSpeed speed_l = HHN_MotorSpeed(Actors::MOTOR_LEFT_SPEED_PIN, Actor::motor_l_speed);
    HHN_MotorSpeed speed_r = HHN_MotorSpeed(Actors::MOTOR_RIGHT_SPEED_PIN, Actor::motor_r_speed);
    HHN_MotorDirection direction_l = HHN_MotorDirection(Actors::MOTOR_LEFT_DIRECTION_PIN, Actor::motor_l_direction);
    HHN_MotorDirection direction_r = HHN_MotorDirection(Actors::MOTOR_RIGHT_DIRECTION_PIN, Actor::motor_r_direction);
    HHN_Motor motorL = HHN_Motor(&speed_l, &direction_l);
    HHN_Motor motorR = HHN_Motor(&speed_r, &direction_r);
} // namespace Actors
