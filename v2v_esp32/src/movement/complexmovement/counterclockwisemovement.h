#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum CounterClockWiseMovementState
    {
        CC_TurningState,
        CC_BackwardsState
    };
    class CounterClockWiseMovement : public BasicMovement
    {
    private:
        float targetHeading;
        unsigned long backupStartTime;
        unsigned long bdebounceStartTime;
        CounterClockWiseMovementState state;

    public:
        CounterClockWiseMovement();
        void run();
    };
} // namespace Movement
