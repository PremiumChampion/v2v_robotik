#include "barcodescannermodule.h"
#include "sensors/sensors.h"
#include "communication/communication.h"

namespace Sensors
{
    HHN_V_BarcodeScannerModule::HHN_V_BarcodeScannerModule()
    {
    }

    HHN_V_BarcodeScannerModule::~HHN_V_BarcodeScannerModule() {}

    void HHN_V_BarcodeScannerModule::run()
    {
        this->current_code_value = Sensors::MESSAGE_BROKER.get(Sensor::QR_CODE);
        COM::SND_BROKER.set(COM::position, String(this->current_code_value, BIN)); // Send current position to other robot
    }

    int HHN_V_BarcodeScannerModule::getCurrentCodeValue()
    {
        return this->current_code_value;
    }

} // namespace Sensors
