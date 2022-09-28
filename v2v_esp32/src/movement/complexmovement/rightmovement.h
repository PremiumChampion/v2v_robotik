#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum RightMovementState
    {
        Starting,
        HalfWay,
        Ending
    };
    class RightMovement : public BasicMovement
    {
    private:
        bool isComplete;
        RightMovementState state;

    public:
        RightMovement();
        void run() override;
    };

} // namespace Movement
