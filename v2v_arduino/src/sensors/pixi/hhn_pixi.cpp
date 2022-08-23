#include "sensors/pixi/hhn_pixi.h"
#include "sensors/sensors.h"

namespace Sensors
{
    HHN_Pixi::HHN_Pixi()
    {
        this->current_code_value = -1;
        this->pixy.init();
        this->last_reading = millis();
    }

    HHN_Pixi::~HHN_Pixi() {}

    void HHN_Pixi::update_position()
    {
        unsigned long current_time = millis();
        // check every 25 ms for new barcode ~40FPS
        if (last_reading + 25 < current_time)
        {
            this->pixy.line.getMainFeatures(4, false);
        }

        if (this->pixy.line.numBarcodes > 0)
        {
            // check if first detected barcode changed
            int new_code = this->pixy.line.barcodes[0].m_code;
            if (new_code != this->current_code_value)
            {
                this->current_code_value = new_code;
                SENSOR_MESSAGE_BROKER.set(Sensor::Pixi, new_code);
            }
        }
    }
} // namespace Sensors
