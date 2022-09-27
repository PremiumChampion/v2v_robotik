#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    class StraightMovement : public BasicMovement
    {
    private:
        bool isCompleted;

    public:
        StraightMovement();
        void run() override;
    };

} // namespace Movement
