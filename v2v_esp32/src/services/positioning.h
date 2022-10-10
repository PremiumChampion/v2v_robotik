#pragma once

namespace Service
{
    enum Direction
    {
        NORTH,
        SOUTH,
        EAST,
        WEST,
    };

    // enum Movement
    // {
    //     COUNTERCLOCKWISE,
    //     FORWARD,
    //     CLOCKWISE,
    // };

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
        // Interne Methoden die die neue Position bestimmen aus den Informationen des Forwarding Services.
        // Werden hier die Positionen von beiden Robotern festgehalten?
    };

    extern Positioning THIS_ROBOT;
    extern Positioning OTHER_ROBOT;
}
