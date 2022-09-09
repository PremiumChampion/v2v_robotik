#include <Arduino.h>
#include "actors/actors.h"
#include "actors/virtualactor.h"
#pragma once

namespace Actors
{
    class HHN_V_MotorSpeed : public HHN_V_Actor
    {
    public:
        HHN_V_MotorSpeed(Actor actor);
    };
} // namespace Actors
