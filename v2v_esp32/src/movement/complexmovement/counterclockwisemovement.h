#include "movement/basicmovement.h"
#pragma once
namespace Movement
{

    class CounterClockWiseMovement : public BasicMovement
    {
    private:
        int turningTime;
        int turningSpeed;
        int straightTime;
        unsigned long startTime;

    public:
        CounterClockWiseMovement();
        void run();
    };
} // namespace Movement
