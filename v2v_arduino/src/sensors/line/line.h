#include <Arduino.h>
#pragma once

namespace Line
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

    class HHN_Line
    {
    private:
        LineValue current_value;
        int pinLeft;
        int pinCenter;
        int pinRight;
        bool onLine(int pin);

    public:
        HHN_Line(int pinLeft, int pinCenter, int pinRight);
        ~HHN_Line();
        void run();
        void init();
    };

} // namespace Sensors
