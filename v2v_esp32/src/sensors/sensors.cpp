#include "sensors.h"
#include "line/line.h"
#include "barcode/barcodescannermodule.h"
#include "broker/broker.h"

namespace Sensors
{
    Broker::Broker<int> MESSAGE_BROKER(SENSOR_TYPE_COUNT);

    HHN_V_BarcodeScannerModule BAR_CODE_SCANNER = Sensors::HHN_V_BarcodeScannerModule();
    HHN_V_Line LINE_SENSOR = Sensors::HHN_V_Line();

    void run()
    {
        BAR_CODE_SCANNER.run();
        LINE_SENSOR.run();
    }

} // namespace Sensors
