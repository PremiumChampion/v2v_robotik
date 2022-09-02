#include "broker/broker.h"
#include "actors.h"

namespace Actors
{
    Broker::Broker ACTOR_MESSAGE_BROKER = Broker::Broker(ACTOR_TYPE_COUNT);

    void update()
    {
    }
} // namespace Actors
