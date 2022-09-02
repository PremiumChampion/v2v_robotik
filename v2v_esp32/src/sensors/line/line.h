#include <Arduino.h>
#pragma once

namespace Sensors
{
    enum LineValue
    {
        None,
        L,
        C,
        R,
        LC,
        RC,
        RL,
        ALL
    };

    class HHN_V_Line
    {
    private:
        LineValue current_value;

    public:
        HHN_V_Line();
        ~HHN_V_Line();
        void update();
    };

} // namespace Sensors
