#include <Arduino.h>
#pragma once

namespace Sensors
{
    // Binray encoded R-C-L
    enum LineValue
    {
        None = 0, // 000
        L = 1,    // 001
        C = 2,    // 010
        LC = 3,   // 011
        R = 4,    // 100
        RL = 5,   // 101
        RC = 6,   // 110
        ALL = 7   // 111
    };

    class HHN_V_Line
    {
    private:
        int nextLevelingIndex;
        int levelingArraySize;
        bool *leftLevelingValues;
        bool *centerLevelingValues;
        bool *rightLevelingValues;
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
