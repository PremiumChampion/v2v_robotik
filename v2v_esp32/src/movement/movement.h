#include "basicmovement.h"
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
        BasicMovement currentMovement;

    public:
        MovementService(/* args */);
        void pause() override;
        void resume() override;
        void run();
        bool waitingForNewDirections();
        void setNewDirections(MovementKind newDirections);
    };
} // namespace Movement
