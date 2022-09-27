#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    class RightMovement : public BasicMovement
    {
    private:
        bool isComplete;
    public:
        RightMovement();
        void run() override;
    };

} // namespace Movement
