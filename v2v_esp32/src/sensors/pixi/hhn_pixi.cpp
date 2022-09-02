#include "sensors/pixi/hhn_pixi.h"
#include "sensors/sensors.h"

namespace Sensors
{
    HHN_V_Pixi::HHN_V_Pixi()
    {
        }

    HHN_V_Pixi::~HHN_V_Pixi() {}

    void HHN_V_Pixi::update_position()
    {
        this->current_code_value = Sensors::MESSAGE_BROKER.get(Sensor::Pixi);
    }

} // namespace Sensors
