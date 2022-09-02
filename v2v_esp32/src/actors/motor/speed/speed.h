#include <Arduino.h>
#include "actors/actors.h"
#pragma once

namespace Actors
{
    class HHN_V_MotorSpeed
    {
    private:
        int pin;
        int currentValue;
        Actor actor;

    public:
        HHN_V_MotorSpeed(Actor actor);
        ~HHN_V_MotorSpeed();
        void set(int speed);
    };
} // namespace Actors
