#include "movement/basicmovement.h"
#pragma once
namespace Movement
{
    class LeftMovement : public BasicMovement
    {
    private:
        bool isComplete;
    public:
        LeftMovement();
        void run() override;
    };

} // namespace Movement
