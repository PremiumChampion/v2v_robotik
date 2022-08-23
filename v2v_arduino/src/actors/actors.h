#include "broker/broker.h"

#pragma once

namespace Actors
{
    static const int ACTOR_TYPE_COUNT = 4;

    enum Actor
    {
        motor_l_direction,
        motor_l_speed,
        motor_r_direction,
        motor_r_speed,
    };

    extern Broker::Broker ACTOR_MESSAGE_BROKER;

    void update();
} // namespace Actors
