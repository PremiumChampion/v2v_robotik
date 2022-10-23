#include "turningtable.h"
#include "positioning.h"

namespace Service
{
    TurningEntry _NORTH(EAST, WEST, -4);
    TurningEntry _EAST(SOUTH, NORTH, +1);
    TurningEntry _SOUTH(WEST, EAST, +4);
    TurningEntry _WEST(NORTH, SOUTH, -1);

    TurningEntry getTurningEntryForCompassDirection(Direction direction)
    {
        switch (direction)
        {
        case Direction::WEST:
            return _WEST;
        case Direction::NORTH:
            return _NORTH;
        case Direction::EAST:
            return _EAST;
        case Direction::SOUTH:
            return _SOUTH;
        default:
            return _NORTH;
        }
        return _NORTH;
    }

    TurningEntry::TurningEntry(Service::Direction clockwise, Service::Direction counterclockwise, int positiondelta)
    {
        this->clockwise = clockwise;
        this->counterclockwise = counterclockwise;
        this->positiondelta = positiondelta;
    }

    Service::Direction Service::TurningEntry::getClockwise()
    {
        return this->clockwise;
    }

    Service::Direction Service::TurningEntry::getCounterClockwise()
    {
        return this->counterclockwise;
    }

    int TurningEntry::calculateNewPosition(int currentPosition)
    {
        return currentPosition + this->positiondelta;
    }

} // namespace Service
