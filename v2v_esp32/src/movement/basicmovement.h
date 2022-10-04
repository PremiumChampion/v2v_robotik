#include "util/pausable.h"

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

