#include "speed.h"
#include "actors/actors.h"

namespace Actors
{
    HHN_MotorSpeed::HHN_MotorSpeed(int pin, Actor actor)
    {
        this->pin = pin;
        this->actor = actor;
    }

    HHN_MotorSpeed::~HHN_MotorSpeed()
    {
    }

    void HHN_MotorSpeed::init()
    {
        pinMode(this->pin, OUTPUT);
        this->run();
    }

    void HHN_MotorSpeed::run()
    {
        this->currentValue = Actors::MESSAGE_BROKER.get(this->actor);
        analogWrite(this->pin, this->currentValue);
    }
} // namespace Actors
