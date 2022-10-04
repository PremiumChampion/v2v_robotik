#include <Arduino.h>
#include "direction.h"
#include "actors/actors.h"
namespace Actors
{
    HHN_MotorDirection::HHN_MotorDirection(int pin, Actor actor)
    {
        this->pin = pin;
        this->actor = actor;
    }

    HHN_MotorDirection::~HHN_MotorDirection()
    {
    }

    void HHN_MotorDirection::init()
    {
        pinMode(this->pin, OUTPUT);
        this->run();
    }

    void HHN_MotorDirection::run()
    {
        this->currentValue = Actors::MESSAGE_BROKER.get(this->actor);
        digitalWrite(this->pin, this->currentValue);
    }
} // namespace Actors
