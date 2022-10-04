#include <Arduino.h>
#include "basicmovement.h"

namespace Movement
{
    BasicMovement::BasicMovement() {
        this->isDone = false;
    }

    bool BasicMovement::isComplete()
    {
        return this->isDone;
    }

    void BasicMovement::run() {
        Serial.println("BasicMovement");
    }
} // namespace Movement
