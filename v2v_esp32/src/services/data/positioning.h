#pragma once

#define WORKING_WITH_QR_SENSOR true;

namespace Service
{
    enum Direction
    {
        NORTH,
        SOUTH,
        EAST,
        WEST,
    };

    class Positioning
    {
    private:
        int currentPositionTile;
        Direction direction;

    public:
        Positioning(/* args */);
        void setCurrentDirection(Direction direction);
        void setCurrentPositionTile(int currentPositionTile);
        Direction getCurrentDirection();
        int getCurrentPositionTile();
    };

    extern Positioning THIS_ROBOT;
    extern Positioning OTHER_ROBOT;
}
