#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum CounterClockWiseMovementState
    {
        CC_Starting,
        CC_HalfWay,
        CC_Ending
    };
    class CounterClockWiseMovement : public BasicMovement
    {
    private:
        // bool isComplete;
        CounterClockWiseMovementState state;

    public:
        CounterClockWiseMovement();
        void run();
    };

} // namespace Movement
