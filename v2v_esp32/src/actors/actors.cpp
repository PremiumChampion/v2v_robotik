#include "actors.h"
#include "broker/broker.h"

namespace Actors
{
    Broker::Broker<int> MESSAGE_BROKER(ACTOR_TYPE_COUNT);
} // namespace Actors
