#include "actors/actors.h"

#pragma once

namespace Actors
{
    class HHN_V_Actor
    {
    protected:
        int currentValue;
        Actor actor;

    public:
        HHN_V_Actor(Actor actor);
        void set(int value);
    };
} // namespace Actors
