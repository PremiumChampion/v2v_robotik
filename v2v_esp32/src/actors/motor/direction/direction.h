#include <Arduino.h>
#include "actors/actors.h"
#pragma once

namespace Actors
{
    class HHN_V_MotorDirection
    {
    private:
        int pin;
        int currentValue;
        Actor actor;

    public:
        HHN_V_MotorDirection( Actor actor);
        ~HHN_V_MotorDirection();
        void set(int direction);
    };
} // namespace Actors
