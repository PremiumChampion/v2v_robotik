#include "broker/broker.h"
#include "barcode/barcodescannermodule.h"
#include "line/line.h"

#pragma once

namespace Sensors
{
    static const int SENSOR_TYPE_COUNT = 2;
    enum Sensor
    {
        QR_CODE,
        LINE,
    };

    void run();

    // handles communicating changed sensor values
    extern Broker::Broker MESSAGE_BROKER;
    // pixi cam and its necesarry methods
    extern Sensors::HHN_V_BarcodeScannerModule BAR_CODE_SCANNER;
    extern Sensors::HHN_V_Line LINE_SENSOR;
} // namespace Sensors
