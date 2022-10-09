#include "basicmovement.h"
#include "movement/complexmovement/counterclockwisemovement.h"
#include "movement/complexmovement/clockwisemovement.h"
#include "movement/complexmovement/stopmovement.h"
#include "movement/complexmovement/straightmovement.h"
#pragma once

namespace Movement
{
    enum MovementKind
    {
        Straight,
        Counterclockwise,
        Clockwise,
        Stop
    };

    class MovementService : public Util::Pausable
    {
    private:
        // BasicMovement currentMovement;
        CounterClockWiseMovement currentLeftMovements;
        ClockWiseMovement currentRightMovement;
        StraightMovement currentStraightMovement;
        StopMovement currentStopMovement;
        MovementKind currentMovementKind;

    public:
        MovementService(/* args */);
        void pause() override;
        void resume() override;
        void run();
        bool waitingForNewDirections();
        void setNewDirections(MovementKind newDirections);
        MovementKind getCurrentMovementKind();
    };

    extern MovementService MOVEMENTS;
} // namespace Movement
