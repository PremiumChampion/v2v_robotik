#include <Arduino.h>
#include "movement.h"
#include "movement/basicmovement.h"
#include "complexmovement/counterclockwisemovement.h"
#include "complexmovement/clockwisemovement.h"
#include "complexmovement/straightmovement.h"
#include "complexmovement/stopmovement.h"

namespace Movement
{
    MovementService::MovementService(/* args */)
    {
        this->currentMovementKind = MovementKind::Stop;
        this->currentStopMovement = StopMovement();
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
        case Counterclockwise:
            this->currentLeftMovements.run();
            break;
        case Clockwise:
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
        bool isComplete = false;
        switch (this->currentMovementKind)
        {
        case Straight:
            isComplete = this->currentStraightMovement.isComplete();
            break;
        case Counterclockwise:
            isComplete = this->currentLeftMovements.isComplete();
            break;
        case Clockwise:
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
            Serial.print("Setting new directions:");
            Serial.println(newDirections);
            this->currentMovementKind = newDirections;
            switch (newDirections)
            {
            case Straight:
                this->currentStraightMovement = StraightMovement();
                break;
            case Counterclockwise:
                this->currentLeftMovements = CounterClockWiseMovement();
                break;
            case Clockwise:
                this->currentRightMovement = ClockWiseMovement();
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

    MovementKind MovementService::getCurrentMovementKind()
    {
        return this->currentMovementKind;
    }

    MovementService MOVEMENTS = MovementService();
} // namespace Movement
