#include <Arduino.h>
#include "actors/actors.h"
#pragma once

namespace Actors
{
    class HHN_MotorSpeed
    {
    private:
        int pin;
        int currentValue;
        Actor actor;

    public:
        HHN_MotorSpeed(int pin, Actor actor);
        ~HHN_MotorSpeed();
        void setup();
        void update();
    };
} // namespace Actors
