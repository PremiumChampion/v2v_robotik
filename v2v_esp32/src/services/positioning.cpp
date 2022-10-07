#include "services/positioning.h"

namespace Service
{

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
