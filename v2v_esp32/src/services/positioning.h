#pragma once

namespace Service{
        enum Direction{
            NORTH,
            SOUTH,
            EAST,
            WEST
        };

        enum Movement{
            COUNTERCLOCKWISE,
            FORWARD,
            CLOCKWISE
        };
    class Positioning
    {

    private:
        int OwnGridPos;
        int OtherGridPos;
        int MovementSteps[3];
        Direction facingDirection;

    public:
        Positioning(/* args */);
        int getOwnGridPos();
        int getOtherGridPos();
        int* getMovementSteps();
        Direction getDirection();
        void findStartingPos();
        int getCurrentGridPos();
        Direction getCurrentDirection();
        void setNewGridPos(int newPos);
        void setNewGridDirection(Direction newDirection);
        int getCurrentPositionTile();
        Direction getCurrentPositionDirection();
        // Interne Methoden die die neue Position bestimmen aus den Informationen des Forwarding Services.
        // Werden hier die Positionen von beiden Robotern festgehalten?
        
        void setOwnGridPos(int Pos); 
        void setOtherGridPos(int Pos);
        void setMovementSteps(Movement array[]);
        void setGridDirection(Direction newDirection);
    };
    
    extern Positioning THIS_ROBOT;
    extern Positioning OTHER_ROBOT;
    
}
