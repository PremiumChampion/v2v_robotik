#include <Arduino.h>
#include "routing.h"
#include "positioning.h"

namespace Service
{
    int getRelativeRegion(int deltaX, int deltaY);

    int Routing::calculateWithCollisionCheck(int from, int target, int blocked)
    {
        // dont move if the target tile is equal to the blocked tile
        if (target == blocked)
        {
            return from;
        }

        // x coordinate of the target tile
        int targetX = target % 4;
        // y coordinate of the target tile
        int targetY = target / 4;

        // x coordinate of the current tile
        int fromX = from % 4;
        // y coordinate of the current tile
        int fromY = from / 4;
        // x coordinate of the blocked tile
        int blockedX = blocked % 4;
        // y coordinate of the blocked tile
        int blockedY = blocked / 4;

        // the distance on the x axis to the target tile
        int deltaTargetX = targetX - fromX;
        // the distance on the y axis to the target tile
        int deltaTargetY = targetY - fromY;

        // the distance on the x axis to the blocked tile
        int deltaBlockedX = blockedX - fromX;
        // the distance on the y axis to the blocked tile
        int deltaBlockedY = blockedY - fromY;

        // the next x coordinate
        int nextX = fromX;
        // the next y coordinate
        int nextY = fromY;

        // value for calculating the next tile in the x direction
        // -1 or 0 or +1
        int moveX = 0;
        if (deltaTargetX > 0)
        {
            moveX = 1;
        }
        if (deltaTargetX < 0)
        {
            moveX = -1;
        }

        // value for calculating the next tile in the y direction
        // -1 or 0 or +1
        int moveY = 0;
        if (deltaTargetY > 0)
        {
            moveY = 1;
        }
        if (deltaTargetY < 0)
        {
            moveY = -1;
        }

#pragma region target one step away on x or y axis
        int absDeltaX = abs(deltaTargetX);
        if (absDeltaX == 1 && deltaTargetY == 0)
        {
            // move x -> target one step ahead
            nextX = nextX + deltaTargetX;
            return nextY * 4 + nextX;
        }

        int absDeltaY = abs(deltaTargetY);
        if (absDeltaY == 1 && deltaTargetX == 0)
        {
            // move y -> target one step around
            nextY = nextY + deltaTargetY;
            return nextY * 4 + nextX;
        }
#pragma endregion

#pragma region check if the blocked tile is able to interfere with the normal routing algorithm
        // regions:
        //  0   0   1   2   2
        //  0   0   1   2   2
        //  7   7   x   3   3
        //  6   6   5   4   4
        //  6   6   5   4   4

        int blockedRegion = getRelativeRegion(deltaBlockedX, deltaBlockedY);
        int targetRegion = getRelativeRegion(deltaTargetX, deltaTargetY);

        // true if the current blocked tile is able to interfere with the normal routing algorithm
        bool regionConflict = false;

        if (targetRegion == 0 && (blockedRegion == 0 || blockedRegion == 1 || blockedRegion == 7))
        {
            regionConflict = true;
        }
        if (targetRegion == 1 && (blockedRegion == 1))
        {
            regionConflict = true;
        }
        if (targetRegion == 2 && (blockedRegion == 1 || blockedRegion == 2 || blockedRegion == 3))
        {
            regionConflict = true;
        }
        if (targetRegion == 3 && (blockedRegion == 3))
        {
            regionConflict = true;
        }
        if (targetRegion == 4 && (blockedRegion == 3 || blockedRegion == 4 || blockedRegion == 5))
        {
            regionConflict = true;
        }
        if (targetRegion == 5 && (blockedRegion == 5))
        {
            regionConflict = true;
        }
        if (targetRegion == 6 && (blockedRegion == 5 || blockedRegion == 6 || blockedRegion == 7))
        {
            regionConflict = true;
        }
        if (targetRegion == 7 && (blockedRegion == 7))
        {
            regionConflict = true;
        }
#pragma endregion

        if (regionConflict)
        {
            // the absolute distance on the x axis to the blocked tile
            int absDeltaBlockedX = abs(deltaBlockedX);
            // the absolute distance on the y axis to the blocked tile
            int absDeltaBlockedY = abs(deltaBlockedY);

            if (absDeltaBlockedX == 1 && absDeltaBlockedY == 1)
            {
                // on diagonal tile -> if deltay == 0 move in y direction
                // on diagonal tile -> if deltax == 0 move in x direction

                if (absDeltaX > absDeltaY)
                {
                    nextX = fromX + moveX;
                }
                else
                {
                    nextY = fromY + moveY;
                }

                return nextY * 4 + nextX;
            }

            else if (absDeltaBlockedX == 1 && absDeltaBlockedY == 0)
            {
                // blocked on x achse -> move on y where no border present

                // has border above the current tile
                bool borderTop = fromY == 0;
                // has border below the current tile
                bool borderBottom = fromY == 3;

                if (!borderTop && !borderBottom)
                {
                    nextY = fromY + (moveY == 0 ? -1 : moveY);
                }
                if (borderTop && !borderBottom)
                {
                    nextY = fromY + (moveY == 0 ? +1 : moveY);
                }
                if (!borderTop && borderBottom)
                {
                    nextY = fromY + (moveY == 0 ? -1 : moveY);
                }

                return nextY * 4 + nextX;
            }
            else if (absDeltaBlockedX == 0 && absDeltaBlockedY == 1)
            {
                // blocked on y achse -> move on x where no border

                // has border on the left of the current tile
                bool borderLeft = fromX == 0;
                // has border on the right of the current tile
                bool borderRight = fromX == 3;

                if (!borderLeft && !borderRight)
                {
                    nextX = fromX + (moveX == 0 ? -1 : moveX);
                }
                if (borderLeft && !borderRight)
                {
                    nextX = fromX + (moveX == 0 ? +1 : moveX);
                }
                if (!borderLeft && borderRight)
                {
                    nextX = fromX + (moveX == 0 ? -1 : moveX);
                }

                return nextY * 4 + nextX;
            }
        }

        // minimise one delta coordinate and then minimise the other
        if (deltaTargetX != 0 && deltaTargetY != 0)
        {
            if (absDeltaX <= absDeltaY)
            {
                nextX = nextX + moveX;
            }
            else
            {
                nextY = nextY + moveY;
            }
            return nextY * 4 + nextX;
        }

        if (deltaTargetX == 0)
        {
            // target x coordinate reached -> move only on y coordinate
            nextY = nextY + moveY;
            return nextY * 4 + nextX;
        }

        // target y coordinate reached -> move only on x coordinate
        nextX = nextX + moveX;
        return nextY * 4 + nextX;
    }

    int getRelativeRegion(int deltaX, int deltaY)
    {   
        // regions:
        //  0   0   1   2   2
        //  0   0   1   2   2
        //  7   7   x   3   3
        //  6   6   5   4   4
        //  6   6   5   4   4

        int region = 0;
        if (deltaX < 0 && deltaY < 0)
        {
            region = 0;
        }
        if (deltaX == 0 && deltaY < 0)
        {
            region = 1;
        }
        if (deltaX > 0 && deltaY < 0)
        {
            region = 2;
        }
        if (deltaX > 0 && deltaY == 0)
        {
            region = 3;
        }
        if (deltaX > 0 && deltaY > 0)
        {
            region = 4;
        }
        if (deltaX == 0 && deltaY > 0)
        {
            region = 5;
        }
        if (deltaX < 0 && deltaY > 0)
        {
            region = 6;
        }
        if (deltaX < 0 && deltaY == 0)
        {
            region = 7;
        }
        return region;
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
