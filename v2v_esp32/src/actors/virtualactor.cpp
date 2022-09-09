#include "virtualactor.h"
#include "actors/actors.h"
#include <Arduino.h>

namespace Actors
{
    HHN_V_Actor::HHN_V_Actor(Actor actor)
    {
        this->actor = actor;
        this->currentValue = 0;
    }
    HHN_V_Actor::~HHN_V_Actor()
    {
    }
    void HHN_V_Actor::set(int value)
    {
        if (this->currentValue == value)
            return;
        this->currentValue = value;
        Actors::MESSAGE_BROKER.set(this->actor, this->currentValue);
    }
} // namespace Actors
