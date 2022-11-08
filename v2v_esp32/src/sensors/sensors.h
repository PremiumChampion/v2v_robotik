#include "broker/broker.h"
#include "barcode/barcodescannermodule.h"
#include "line/line.h"
#include "mpu6050/mpu6050.h"

#pragma once

namespace Sensors
{
    static const int SENSOR_TYPE_COUNT = 3;
    enum Sensor
    {
        QR_CODE,
        LINE,
        GYRO
    };

    void run();

    // handles communicating changed sensor values
    extern Broker::Broker<int> MESSAGE_BROKER;
    // pixi cam and its necesarry methods
    extern Sensors::HHN_V_BarcodeScannerModule BAR_CODE_SCANNER;
    extern Sensors::HHN_V_Line LINE_SENSOR;
    extern Sensors::HHN_MPU6050 MPU;
} // namespace Sensors
