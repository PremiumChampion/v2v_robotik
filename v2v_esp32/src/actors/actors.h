#include "broker/broker.h"

#pragma once

namespace Actors
{
    static const int ACTOR_TYPE_COUNT = 4;

    enum Actor
    {
        motor_l_direction, // digital write 1/0
        motor_l_speed,     // analog write 0-255
        motor_r_direction, // digital write 1/0
        motor_r_speed,     // analog write 0-255
    };

    extern Broker::Broker<int> MESSAGE_BROKER;

    // void update();
} // namespace Actors
