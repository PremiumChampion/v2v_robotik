#include "positioning.h"

#pragma once

namespace Service
{
    class TurningEntry
    {
    private:
        Direction clockwise;
        Direction counterclockwise;
        int positiondelta;

    public:
        TurningEntry(Direction clockwise, Direction counterclockwise, int positiondelta);
        Direction getClockwise();
        Direction getCounterClockwise();
        int calculateNewPosition(int currentposition);
    };

    TurningEntry getForDirection(Direction direction);
} // namespace Service
