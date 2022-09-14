#include "broker/broker.h"
#include "actors.h"
#include "motor/motor.h"

namespace Actors
{
    Broker::Broker<int> MESSAGE_BROKER(ACTOR_TYPE_COUNT);

    void run()
    {
        motorL.run();
        motorR.run();
    }
} // namespace Actors
