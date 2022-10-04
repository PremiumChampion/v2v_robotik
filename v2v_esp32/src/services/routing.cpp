#include "routing.h"
#include "positioning.h"

namespace Service
{
    Routing::Routing(){

    }

    int Routing::calculateRoute(int target){
        int currentPos = THIS_ROBOT.getCurrentPositionTile();

        int targetX = target % 4;
        int targetY = target / 4;

        int currentX = currentPos % 4;
        int currentY = currentPos / 4;

        int deltaX = targetX - currentX;
        int deltaY = targetY - currentY;

        int nextX = currentX;
        int nextY = currentY;

        if(deltaX == 0 && deltaY == 0){
            return currentPos;
        }
        
        if(deltaX <= deltaY || deltaY == 0){
            nextX = nextX + (deltaX > 0 ? 1 : -1);
        }else{
            nextY = nextY + (deltaY > 0 ? 1 : -1);
        }

        int nextPos = nextY * 16 + nextX;

        return nextPos;
    }
} // namespace Services
