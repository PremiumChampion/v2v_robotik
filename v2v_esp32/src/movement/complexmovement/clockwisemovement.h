#include "movement/basicmovement.h"
#pragma once
namespace Movement
{

    class ClockWiseMovement : public BasicMovement
    {
    private:
        int turningTime;
        int turningSpeed;
        int backupTime;
        unsigned long startTime;
    public:
        ClockWiseMovement();
        void run();
    };

} // namespace Movement
