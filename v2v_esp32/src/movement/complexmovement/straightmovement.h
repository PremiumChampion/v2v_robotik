#include "movement/basicmovement.h"
#pragma once

#define TURN_DELTA 30

namespace Movement
{
    enum StraightMovementState
    {
        Start,
        StraightSegment,
        BackwardsSegment
    };

    class StraightMovement : public BasicMovement
    {
    private:
        // bool isCompleted;
        int state;
        unsigned long log_time;
        unsigned long backupStartTime;
        unsigned int backupTime_ms;
        unsigned long debounce_start_ms;
        unsigned long start_ms;
        float heading;
        int debouncetime_ms;
        int straight_degrees;

        void startSegment();
        void straightSegment();
        void backwardsSegment();
        int calculateAngleOfAttak();

    public:
        StraightMovement();
        void run();
    };

} // namespace Movement
