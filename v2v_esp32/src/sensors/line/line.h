#include <Arduino.h>
#pragma once

namespace Sensors
{
    // Binray encoded L-C-R
    enum LineValue
    {
        None = 0,
        R = 1,
        C = 2,
        RC = 3,
        L = 4,
        RL = 5,
        LC = 6,
        ALL = 7
    };

    class HHN_V_Line
    {
    private:
        LineValue current_value;
        bool leftValue;
        bool centerValue;
        bool rightValue;
        void extract_values();

    public:
        HHN_V_Line();
        void run();
        bool left();
        bool center();
        bool right();
        LineValue value();
    };

} // namespace Sensors
