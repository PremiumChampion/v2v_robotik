

#pragma once

namespace Sensors
{
    class HHN_V_BarcodeScannerModule
    {
    private:
        int current_code_value;

    public:
        HHN_V_BarcodeScannerModule();
        ~HHN_V_BarcodeScannerModule();
        void run();
        int getCurrentCodeValue();
    };

} // namespace Sensors
