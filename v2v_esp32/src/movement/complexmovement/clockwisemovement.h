#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum ClockWiseMovementState
    {
        C_Starting,
        C_HalfWay,
        C_HalfWay_Pause,
        C_Ending
    };
    class ClockWiseMovement : public BasicMovement
    {
    private:
        // bool isComplete;
        ClockWiseMovementState state;
        unsigned long centerStartTime;
        unsigned long backwardsStartTime;
    public:
        ClockWiseMovement();
        void run();
    };

} // namespace Movement
