#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum RightMovementState
    {
        R_Starting,
        R_HalfWay,
        R_Ending
    };
    class RightMovement : public BasicMovement
    {
    private:
        // bool isComplete;
        RightMovementState state;

    public:
        RightMovement();
        void run();
    };

} // namespace Movement
