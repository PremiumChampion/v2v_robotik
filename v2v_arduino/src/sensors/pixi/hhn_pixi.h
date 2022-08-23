#include "sensors/pixi/pixy2/Pixy2.h"

#pragma once

namespace Sensors
{
    class HHN_Pixi
    {
    private:
        int current_code_value;
        unsigned long last_reading_time;
        int last_readings_count;
        int* last_readings;
        Pixy2 pixy;
        void add_value_to_last_readings(int value);
        int get_avg_reading();

    public:
        HHN_Pixi();
        ~HHN_Pixi();
        void update_position();
    };

} // namespace Sensors
