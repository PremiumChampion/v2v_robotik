#include <Arduino.h>
#include "movement.h"
#include "complexmovement/leftmovement.h"
#include "complexmovement/rightmovement.h"
#include "complexmovement/straightmovement.h"
#include "complexmovement/stopmovement.h"

namespace Movement
{
    MovementService::MovementService(/* args */)
    {
        this->currentMovement = StopMovement();
    }

    void MovementService::pause()
    {
        Util::Pausable::pause();
        this->currentMovement.pause();
    }

    void MovementService::resume()
    {
        Util::Pausable::resume();
        this->currentMovement.resume();
    }

    void MovementService::run()
    {
        this->currentMovement.run();
    }

    bool MovementService::waitingForNewDirections()
    {
        return this->currentMovement.isComplete();
    }
    
    void MovementService::setNewDirections(MovementKind newDirections)
    {
        if (this->waitingForNewDirections())
        {
            switch (newDirections)
            {
            case Straight:
                this->currentMovement = StraightMovement();
                break;
            case Left:
                this->currentMovement = LeftMovement();
                break;
            case Right:
                this->currentMovement = RightMovement();
                break;
            case Stop:
                this->currentMovement = StopMovement();
                break;
            default:
                this->currentMovement = StopMovement();
                break;
            }
        }
    }
} // namespace Movement
