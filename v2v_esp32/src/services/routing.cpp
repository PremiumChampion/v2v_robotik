#include <Arduino.h>
#include "routing.h"
#include "positioning.h"

namespace Service
{
    int getRelativeRegion(int deltaX, int deltaY);
    int getRelativeRegion(int deltaX, int deltaY)
    {
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

    int Routing::calculateRouteWithCollisionAvoidance(int from, int target, int blocked)
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

        int deltaTargetX = targetX - fromX;
        int deltaTargetY = targetY - fromY;

        int deltaBlockedX = blockedX - fromX;
        int deltaBlockedY = blockedY - fromY;

        int nextX = fromX;
        int nextY = fromY;

        int moveX = 0;
        if (deltaTargetX > 0)
        {
            moveX = 1;
        }
        if (deltaTargetX < 0)
        {
            moveX = -1;
        }

        int moveY = 0;
        if (deltaTargetY > 0)
        {
            moveY = 1;
        }
        if (deltaTargetY < 0)
        {
            moveY = -1;
        }

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

        int blockedRegion = getRelativeRegion(deltaBlockedX, deltaBlockedY);
        int targetRegion = getRelativeRegion(deltaTargetX, deltaTargetY);

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

        if (regionConflict)
        {

            int absDeltaBlockedX = abs(deltaBlockedX);
            int absDeltaBlockedY = abs(deltaBlockedY);

            if (absDeltaBlockedX == 1 && absDeltaBlockedY == 1)
            {
                // on cross point -> if deltay == 0 move in direction deltay t
                // on cross point -> if deltax == 0 move in direction deltax t

                if (absDeltaX > absDeltaY)
                {
                    nextX = nextX + moveX;
                }
                else
                {
                    nextY = nextY + moveY;
                }

                return nextY * 4 + nextX;
            }
            else if (absDeltaBlockedX == 1 && absDeltaBlockedY == 0)
            {
                // blocked on x achse -> move on y where no border

                bool borderTop = fromY == 0;
                bool borderBottom = fromY == 3;

                if (borderTop)
                {
                    nextY = fromY + (moveY == 0 ? +1 : moveY);
                }
                else if (borderBottom)
                {
                    nextY = fromY + (moveY == 0 ? -1 : moveY);
                }
                else
                {
                    nextY = fromY + (moveY == 0 ? -1 : moveY);
                }

                return nextY * 4 + nextX;
            }
            else if (absDeltaBlockedX == 0 && absDeltaBlockedY == 1)
            {
                // blocked on y achse -> move on x where no border

                bool borderLeft = fromX == 0;
                bool borderRight = fromX == 3;

                if (borderLeft)
                {
                    nextX = fromX + (moveX == 0 ? +1 : moveX);
                }
                else if (borderRight)
                {
                    nextX = fromX + (moveX == 0 ? -1 : moveX);
                }
                else
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
            nextY = nextY + moveY;
            return nextY * 4 + nextX;
        }

        nextX = nextX + moveX;
        return nextY * 4 + nextX;
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
