#include "movement/basicmovement.h"
#pragma once

#define TURN_DELTA 40

namespace Movement
{
    enum StraightMovementState
    {
        Start,
        FirstNarrowSegment,
        WideSegment,
        SecondNarrowSegment,
        BackwardsSegment
    };

    class StraightMovement : public BasicMovement
    {
    private:
        // bool isCompleted;
        int state;
        unsigned long backupStartTime;
        unsigned int backupTime_ms;
        void startSegment();
        void narrowSegment();
        void wideSegment();
        void backwardsSegment();
    public:
        StraightMovement();
        void run();
    };

} // namespace Movement
