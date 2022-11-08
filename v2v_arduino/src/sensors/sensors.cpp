#include "sensors.h"
#include "barcode/barcodescannermodule.h"
#include "line/line.h"
namespace Sensors
{
    Broker::Broker<int> MESSAGE_BROKER(SENSOR_TYPE_COUNT);
    SoftwareSerial SERIAL_SCANNER_CONNECTION(12, 13);
    QR::BarcodeScannerModule QR_CODE_SCANNER = QR::BarcodeScannerModule(&SERIAL_SCANNER_CONNECTION);
    Line::HHN_Line LINE_SENSOR = Line::HHN_Line(16, 15, 14);
    MPU6050::HHN_MPU6050 MPU = MPU6050::HHN_MPU6050();

    void run()
    {
        // QR_CODE_SCANNER.run();
        LINE_SENSOR.run();
        MPU.run();
    }
    void init()
    {
        // QR_CODE_SCANNER.init();
        LINE_SENSOR.init();
        MPU.init();
    }

} // namespace Sensors
