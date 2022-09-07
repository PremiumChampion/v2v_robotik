#include "barcodescannermodule.h"
#include "sensors/sensors.h"

namespace Sensors
{
    HHN_V_BarcodeScannerModule::HHN_V_BarcodeScannerModule()
    {
    }

    HHN_V_BarcodeScannerModule::~HHN_V_BarcodeScannerModule() {}

    void HHN_V_BarcodeScannerModule::run()
    {
        this->current_code_value = Sensors::MESSAGE_BROKER.get(Sensor::QR_CODE);
    }

} // namespace Sensors
