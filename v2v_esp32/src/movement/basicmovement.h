#include "util/pausable.h"

#define TURN_DELTA 40

#pragma once

namespace Movement
{
    class BasicMovement
    {
    protected:
        bool isDone;

    public:
        BasicMovement();
        void run();
        bool isComplete();
    };
}

