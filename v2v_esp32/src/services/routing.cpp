#include "routing.h"
#include "positioning.h"

namespace Service
{
    int calculateWithCollisionCheck(int from, int target, int blocked)
    {
        if (target == blocked)
        {
            return from;
        }

        int targetX = target % 4;
        int targetY = target / 4;

        int fromX = from % 4;
        int fromY = from / 4;

        int blockedX = blocked % 4;
        int blockedY = blocked / 4;

        int deltaX = targetX - fromX;
        int deltaY = targetY - fromY;

        int nextX = fromX;
        int nextY = fromY;

        if (deltaX <= deltaY || deltaY == 0)
        {
            nextX = nextX + (deltaX > 0 ? 1 : -1);
        }
        else
        {
            nextY = nextY + (deltaY > 0 ? 1 : -1);
        }

        if (nextX == blockedX && nextY == blockedY)
        {
            nextX = fromX;
            nextY = fromY;

            if (deltaX > deltaY)
            {
                nextX = nextX + (deltaX > 0 ? 1 : -1);
            }
            else
            {
                nextY = nextY + (deltaY > 0 ? 1 : -1);
            }

            // edge cases
            if (nextX == 5)
            {
                nextX = 3;
            }
            if (nextY == 5)
            {
                nextY = 3;
            }
            if (nextX == -1)
            {
                nextX = 1;
            }
            if (nextY == -1)
            {
                nextY = 1;
            }
        }

        int nextPos = nextY * 4 + nextX;

        return nextPos;
    }

    int Routing::calculateRoute(int from, int target)
    {
        int currentPos = from;

        int targetX = target % 4;
        int targetY = target / 4;

        int currentX = currentPos % 4;
        int currentY = currentPos / 4;

        int deltaX = targetX - currentX;
        int deltaY = targetY - currentY;

        int nextX = currentX;
        int nextY = currentY;

        if (deltaX == 0 && deltaY == 0)
        {
            return currentPos;
        }

        if (deltaX <= deltaY || deltaY == 0)
        {
            nextX = nextX + (deltaX > 0 ? 1 : -1);
        }
        else
        {
            nextY = nextY + (deltaY > 0 ? 1 : -1);
        }

        int nextPos = nextY * 4 + nextX;

        return nextPos;
    }
} // namespace Services
