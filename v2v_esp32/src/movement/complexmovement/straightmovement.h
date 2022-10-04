#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum StraightMovementState
    {
        StartCrossing,
        Continuing,
        EndCrossing
    };

    class StraightMovement : public BasicMovement
    {
    private:
        // bool isCompleted;
        int state;
    public:
        StraightMovement();
        void run();
    };

} // namespace Movement
