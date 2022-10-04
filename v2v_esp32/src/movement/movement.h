#include "basicmovement.h"
#include "movement/complexmovement/leftmovement.h"
#include "movement/complexmovement/rightmovement.h"
#include "movement/complexmovement/stopmovement.h"
#include "movement/complexmovement/straightmovement.h"
#pragma once

namespace Movement
{
    enum MovementKind
    {
        Straight,
        Left,
        Right,
        Stop
    };

    class MovementService : public Util::Pausable
    {
    private:
        // BasicMovement currentMovement;
        LeftMovement currentLeftMovements;
        RightMovement currentRightMovement;
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
    };

    extern MovementService MOVEMENTS;
} // namespace Movement
