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
        float targetHeading;
        unsigned long backupStartTime;
        ClockWiseMovementState state;

    public:
        ClockWiseMovement();
        void run();
    };

} // namespace Movement
