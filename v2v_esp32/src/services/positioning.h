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
        void turnClockwise();
        void turnCounterClockwise();
        void moveForward();
        // Interne Methoden die die neue Position bestimmen aus den Informationen des Forwarding Services.
        // Werden hier die Positionen von beiden Robotern festgehalten?

        // void setOwnGridPos(int Pos);
        // void setOtherGridPos(int Pos);
        // void setMovementSteps(Movement array[]);
        // void setGridDirection(Direction newDirection);
    };

    extern Positioning THIS_ROBOT;
    extern Positioning OTHER_ROBOT;
}
