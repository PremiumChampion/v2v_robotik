#include "services/positioning.h"

namespace Service
{
    Positioning::Positioning(){
        // Set robot starting position to 0 facing NORTH
        this->direction = Direction::NORTH;
        this->currentPositionTile = 0;
    }

    void Positioning::setCurrentDirection(Direction direction)
    {
        this->direction = direction;
    }

    void Positioning::setCurrentPositionTile(int currentPositionTile)
    {
        this->currentPositionTile = currentPositionTile;
    }

    Direction Positioning::getCurrentDirection()
    {
        return this->direction;
    }

    int Positioning::getCurrentPositionTile()
    {
        return this->currentPositionTile;
    }

}
