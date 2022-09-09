#include <Arduino.h>
#include "direction/direction.h"
#include "speed/speed.h"
#include "motor.h"

namespace Actors
{
    HHN_V_Motor::HHN_V_Motor(HHN_V_MotorSpeed *speed, HHN_V_MotorDirection *direction)
    {
        this->speed = speed;
        this->direction = direction;
    }

    HHN_V_Motor::~HHN_V_Motor()
    {
    }

    void HHN_V_Motor::set(int speed, MotorDirection direction)
    {
        this->direction->set(direction);
        this->speed->set(speed);
    }

    HHN_V_MotorSpeed speed_l(Actor::motor_l_speed);
    HHN_V_MotorSpeed speed_r(Actor::motor_r_speed);
    HHN_V_MotorDirection direction_l(Actor::motor_l_direction);
    HHN_V_MotorDirection direction_r(Actor::motor_r_direction);
    HHN_V_Motor motorL(&speed_l, &direction_l);
    HHN_V_Motor motorR(&speed_r, &direction_r);
} // namespace Actors
