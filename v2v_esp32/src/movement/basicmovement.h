#include "util/pausable.h"

#pragma once

namespace Movement
{
    class BasicMovement : public Util::Pausable
    {
    protected:
        bool isDone;

    public:
        virtual void run();
        virtual bool isComplete();
    };
}

