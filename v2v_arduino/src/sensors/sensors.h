#include "broker/broker.h"
#include "barcode/barcodescannermodule.h"
#include "line/line.h"
#include "mpu6050/mpu6050.h"
#include <SoftwareSerial.h>

#pragma once

namespace Sensors
{
    static const int SENSOR_TYPE_COUNT = 3;
    enum Sensor
    {
        QR_CODE,
        LINE,
        GYRO,
    };

    void run();
    void init();

    // handles communicating changed sensor values
    extern Broker::Broker<int> MESSAGE_BROKER;
    // pixi cam and its necesarry methods
    extern QR::BarcodeScannerModule QR_CODE_SCANNER;
    extern Line::HHN_Line LINE_SENSOR;
    extern SoftwareSerial SERIAL_SCANNER_CONNECTION;
    extern HHN_MPU6050::HHN_MPU6050 MPU;
} // namespace Sensors
