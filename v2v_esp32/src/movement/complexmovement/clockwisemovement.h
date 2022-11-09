#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum ClockWiseMovementState
    {
        TurningState,
        BackwardsState
    };
    class ClockWiseMovement : public BasicMovement
    {
    private:
        float startHeading;
        float targetHeading;
        ClockWiseMovementState state;

    public:
        ClockWiseMovement();
        void run();
    };

} // namespace Movement
