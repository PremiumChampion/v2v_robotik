#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum ClockWiseMovementState
    {
        C_Starting,
        C_HalfWay,
        C_Ending
    };
    class ClockWiseMovement : public BasicMovement
    {
    private:
        // bool isComplete;
        ClockWiseMovementState state;

    public:
        ClockWiseMovement();
        void run();
    };

} // namespace Movement
