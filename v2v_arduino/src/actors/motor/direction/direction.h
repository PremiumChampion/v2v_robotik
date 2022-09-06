#include <Arduino.h>
#include "actors/actors.h"
#pragma once

namespace Actors
{
    class HHN_MotorDirection
    {
    private:
        int pin;
        int currentValue;
        Actor actor;

    public:
        HHN_MotorDirection(int pin, Actor actor);
        ~HHN_MotorDirection();
        void run();
    };
} // namespace Actors
