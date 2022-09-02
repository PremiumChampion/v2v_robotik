#include "sensors.h"

namespace Sensors
{
    Broker::Broker MESSAGE_BROKER = Broker::Broker(SENSOR_TYPE_COUNT);
    HHN_V_Pixi V_PIXI = HHN_V_Pixi();
    //TODO: add line sensor

    void update()
    {
        V_PIXI.update_position();
        //TODO: update line sensor
    }

} // namespace Sensors
