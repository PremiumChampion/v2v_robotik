#include "sensors.h"

namespace Sensors
{
    Broker::Broker SENSOR_MESSAGE_BROKER = Broker::Broker(SENSOR_TYPE_COUNT);
    HHN_Pixi PIXI = HHN_Pixi();

    void update()
    {
        PIXI.update_position();
    }

} // namespace Sensors
