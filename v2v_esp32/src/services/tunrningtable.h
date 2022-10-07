#include "positioning.h"

#pragma once

namespace Service
{
    class TurningTable
    {
    private:
        Direction clockwise;
        Direction counterclockwise;

    public:
        TurningEntry(Direction clockwise, Direction counterclockwise);
        Direction getClockwise();
        Direction getCounterclockwise();
    };

    
    TurningTable NORTH = TurningTable(EAST, WEST);
    TurningTable EAST = TurningTable(SOUTH, NORTH);
    TurningTable SOUTH = TurningTable(WEST, EAST);
    TurningTable WEST = TurningTable(NORTH, SOUTH);
} // namespace Service
