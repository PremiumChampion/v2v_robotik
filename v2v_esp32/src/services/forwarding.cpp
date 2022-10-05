#include "forwarding.h"

namespace Service
{
    Forwarding::Forwarding() {}

    Movement calculateNextMovement(int nextTile)
    {
        // Calculate from current tile pos current x and y
        // Calculate, if movement is either in x-axis or y-axis
        // direction(also either positive or negative direction)
        // Calculate, in which direction robot needs to turn, in relevance to its current facing direction
        int currentTile = THIS_ROBOT.getCurrentPositionTile();
        Direction currentDirection = THIS_ROBOT.getCurrentDirection();
        int nextTileX = nextTile % 4;
        int nextTileY = nextTile / 4;
        int currentX = currentTile % 4;
        int currentY = currentTile / 4;
        int deltaX = nextTileX - currentX;
        int deltaY = nextTileY - currentY;

        if (deltaX == 0 && deltaY == 0)
        {
            return; 
        }
        //Calculate movement if movement is in positive x-axis direction
        if(deltaX == 1){
            
            if(currentDirection == Direction::EAST){
                return Movement::FORWARD;
            }
            else if(currentDirection == Direction::NORTH){
                return Movement::CLOCKWISE;
            }
            else if(currentDirection == Direction::SOUTH){
                return Movement::COUNTERCLOCKWISE;
            }
            else{
                return Movement::CLOCKWISE;
            }
        }
        //Calculate movement in negative x-axis direction
        else if(deltaX == -1){
            if(currentDirection == Direction::WEST){
                return Movement::FORWARD;
            }
            else if(currentDirection == Direction::NORTH){
                return Movement::COUNTERCLOCKWISE;
            }
            else if(currentDirection == Direction::SOUTH){
                return Movement::CLOCKWISE;
            }
            else{
                return Movement::COUNTERCLOCKWISE;
            }

        }
        //Calculate movement in positive y-axis direction
        if(deltaY == 1){
            
            if(currentDirection == Direction::NORTH){
                return Movement::FORWARD;
            }
            else if(currentDirection == Direction::EAST){
                return Movement::CLOCKWISE;
            }
            else if(currentDirection == Direction::WEST){
                return Movement::COUNTERCLOCKWISE;
            }
            else{
                return Movement::CLOCKWISE;
            }
        }
        //Calculate movement in negative y-axis direction
        else if(deltaY == -1){
            if(currentDirection == Direction::SOUTH){
                return Movement::FORWARD;
            }
            else if(currentDirection == Direction::WEST){
                return Movement::COUNTERCLOCKWISE;
            }
            else if(currentDirection == Direction::EAST){
                return Movement::CLOCKWISE;
            }
            else{
                return Movement::COUNTERCLOCKWISE;
            }



        }

    }

} // namespace Service
