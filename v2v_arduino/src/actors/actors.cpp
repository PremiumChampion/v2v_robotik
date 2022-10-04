#include "broker/broker.h"
#include "actors.h"
#include "actors/motor/motor.h"

namespace Actors
{
    Broker::Broker<int> MESSAGE_BROKER(ACTOR_TYPE_COUNT);


    void run()
    {
        speed_l.run();
        speed_r.run();
        direction_l.run();
        direction_r.run();
    }
    void init()
    {
        enableMotors();
        speed_l.init();
        speed_r.init();
        direction_l.init();
        direction_r.init();
    }
} // namespace Actors
