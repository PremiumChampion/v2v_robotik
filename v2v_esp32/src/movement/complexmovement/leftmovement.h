#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum LeftMovementState
    {
        L_Starting,
        L_HalfWay,
        L_Ending
    };
    class LeftMovement : public BasicMovement
    {
    private:
        // bool isComplete;
        LeftMovementState state;

    public:
        LeftMovement();
        void run();
    };

} // namespace Movement
