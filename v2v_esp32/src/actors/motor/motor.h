#include <Arduino.h>
#include "direction/direction.h"
#include "speed/speed.h"
#pragma once

namespace Actors
{
    class HHN_V_Motor
    {
    private:
        HHN_V_MotorSpeed *speed;
        HHN_V_MotorDirection *direction;

    public:
        HHN_V_Motor(HHN_V_MotorSpeed *speed, HHN_V_MotorDirection *direction);
        ~HHN_V_Motor();
        void set(int speed, int degrees);
    };

    extern HHN_V_MotorSpeed speed_l;
    extern HHN_V_MotorSpeed speed_r;
    extern HHN_V_MotorDirection direction_l;
    extern HHN_V_MotorDirection direction_r;
    extern HHN_V_Motor motorL;
    extern HHN_V_Motor motorR;

} // namespace Actors