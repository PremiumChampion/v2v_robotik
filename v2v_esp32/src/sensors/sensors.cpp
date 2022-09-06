#include "sensors.h"
#include "line/line.h"
#include "barcode/barcodescannermodule.h"

namespace Sensors
{
    Broker::Broker MESSAGE_BROKER = Broker::Broker(SENSOR_TYPE_COUNT);
    Sensors::HHN_V_BarcodeScannerModule BAR_CODE_SCANNER = Sensors::HHN_V_BarcodeScannerModule();
    Sensors::HHN_V_Line LINE_SENSOR = Sensors::HHN_V_Line();
    // TODO: add line sensor

    void run()
    {
        BAR_CODE_SCANNER.run();
        LINE_SENSOR.run();
        // TODO: update line sensor
    }

} // namespace Sensors
