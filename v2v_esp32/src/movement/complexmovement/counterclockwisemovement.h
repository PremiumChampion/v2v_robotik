#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum CounterClockWiseMovementState
    {
        CC_Starting,
        CC_HalfWay_Pause,
        CC_HalfWay,
        CC_Ending
    };
    class CounterClockWiseMovement : public BasicMovement
    {
    private:
        CounterClockWiseMovementState state;
        unsigned long centerStartTime;
        unsigned long backwardsStartTime;

    public:
        CounterClockWiseMovement();
        void run();
    };
} // namespace Movement
