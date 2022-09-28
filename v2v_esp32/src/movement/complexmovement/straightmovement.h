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
        bool isCompleted;
        StraightMovementState state;
    public:
        StraightMovement();
        void run() override;
    };

} // namespace Movement
