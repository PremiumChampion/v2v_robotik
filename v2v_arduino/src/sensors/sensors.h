#include "broker/broker.h"
#include "sensors/pixi/hhn_pixi.h"

#pragma once

namespace Sensors
{
    static const int SENSOR_TYPE_COUNT = 2;
    enum Sensor
    {
        Pixi,
        Line,
    };

    void update();

    // handles communicating changed sensor values
    extern Broker::Broker MESSAGE_BROKER;
    // pixi cam and its necesarry methods
    extern HHN_Pixi PIXI;
} // namespace Sensors
