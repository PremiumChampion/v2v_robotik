#pragma once

namespace Service{
    class Positioning
    {
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
        
        void setOwnGridPos(int Pos); 
        void setOtherGridPos(int Pos);
        void setMovementSteps(Movement array[]);
        void setGridDirection(Direction newDirection);
    };
}
