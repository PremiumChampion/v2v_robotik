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

    class HHN_Line
    {
    private:
        LineValue current_value;
        int pinLeft;
        int pinCenter;
        int pinRight;
        void update_reading();

    public:
        HHN_Line();
        ~HHN_Line();
        void init();
        void update();
    };

} // namespace Sensors
