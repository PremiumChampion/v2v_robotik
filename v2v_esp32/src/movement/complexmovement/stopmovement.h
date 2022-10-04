#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    class StopMovement : public BasicMovement
    {
    private:
        // bool isComplete;
    public:
        StopMovement();
        void run();
    };

} // namespace Movement
