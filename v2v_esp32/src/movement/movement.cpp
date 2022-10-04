#include <Arduino.h>
#include "movement.h"
#include "movement/basicmovement.h"
#include "complexmovement/leftmovement.h"
#include "complexmovement/rightmovement.h"
#include "complexmovement/straightmovement.h"
#include "complexmovement/stopmovement.h"

namespace Movement
{
    MovementService::MovementService(/* args */)
    {
        this->currentMovementKind = MovementKind::Stop;
    }

    void MovementService::pause()
    {
        Util::Pausable::pause();
    }

    void MovementService::resume()
    {
        Util::Pausable::resume();
    }

    void MovementService::run()
    {
        switch (this->currentMovementKind)
        {
        case Straight:
            this->currentStraightMovement.run();
            break;
        case Left:
            this->currentLeftMovements.run();
            break;
        case Right:
            this->currentRightMovement.run();
            break;
        case Stop:
            this->currentStopMovement.run();
            break;
        default:
            this->currentStopMovement.run();
            break;
        }
    }

    bool MovementService::waitingForNewDirections()
    {
        bool isComplete = true;
        switch (this->currentMovementKind)
        {
        case Straight:
            isComplete = this->currentStraightMovement.isComplete();
            break;
        case Left:
            isComplete = this->currentLeftMovements.isComplete();
            break;
        case Right:
            isComplete = this->currentRightMovement.isComplete();
            break;
        case Stop:
            isComplete = this->currentStopMovement.isComplete();
            break;
        default:
            isComplete = this->currentStopMovement.isComplete();
            break;
        }
        return isComplete;
    }

    void MovementService::setNewDirections(MovementKind newDirections)
    {
        if (this->waitingForNewDirections())
        {
            Serial.println("Setting new directions");
            this->currentMovementKind = newDirections;
            switch (newDirections)
            {
            case Straight:
                this->currentStraightMovement = StraightMovement();
                break;
            case Left:
                this->currentLeftMovements = LeftMovement();
                break;
            case Right:
                this->currentRightMovement = RightMovement();
                break;
            case Stop:
                this->currentStopMovement = StopMovement();
                break;
            default:
                this->currentStopMovement = StopMovement();
                break;
            }
        }
    }

    MovementService MOVEMENTS = MovementService();
} // namespace Movement
