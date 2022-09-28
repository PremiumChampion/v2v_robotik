#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    enum LeftMovementState
    {
        Starting,
        HalfWay,
        Ending
    };
    class LeftMovement : public BasicMovement
    {
    private:
        bool isComplete;
        LeftMovementState state;

    public:
        LeftMovement();
        void run() override;
    };

} // namespace Movement
