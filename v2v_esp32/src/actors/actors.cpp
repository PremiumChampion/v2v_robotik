#include "broker/broker.h"
#include "actors.h"

namespace Actors
{
    Broker::Broker<int> MESSAGE_BROKER(ACTOR_TYPE_COUNT);
} // namespace Actors
