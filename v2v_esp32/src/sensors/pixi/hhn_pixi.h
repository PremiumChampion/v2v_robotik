#include "sensors/pixi/pixy2/Pixy2.h"

#pragma once

namespace Sensors
{
    class HHN_V_Pixi
    {
    private:
        int current_code_value;

    public:
        HHN_V_Pixi();
        ~HHN_V_Pixi();
        void update_position();
    };

} // namespace Sensors
