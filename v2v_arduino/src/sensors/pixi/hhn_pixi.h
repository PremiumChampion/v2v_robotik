#include "sensors/pixi/pixy2/Pixy2.h"

#pragma once

namespace Sensors
{
    class HHN_Pixi
    {
    private:
        int current_code_value;
        unsigned long last_reading;
        Pixy2 pixy;

    public:
        HHN_Pixi();
        ~HHN_Pixi();
        void update_position();
    };

} // namespace Sensors
