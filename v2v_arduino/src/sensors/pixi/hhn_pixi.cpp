#include "sensors/pixi/hhn_pixi.h"
#include "sensors/sensors.h"

namespace Sensors
{
    HHN_Pixi::HHN_Pixi()
    {
        this->current_code_value = -1;
        this->pixy.init();
        this->last_reading_time = millis();
        // used for error correction when detecting single incorrect barcode
        this->last_readings_count = 16;
        this->last_readings = new int[this->last_readings_count];
    }

    HHN_Pixi::~HHN_Pixi() {}

    void HHN_Pixi::update_position()
    {
        unsigned long current_time = millis();
        // check every 25 ms for new barcode ~40FPS
        if (last_reading_time + 25 < current_time)
        {
            this->pixy.line.getMainFeatures(4, false);
        }

        if (this->pixy.line.numBarcodes > 0)
        {
            // check if first detected barcode changed
            int new_code = this->pixy.line.barcodes[0].m_code;
            this->add_value_to_last_readings(new_code);
        }

        if (this->pixy.line.numBarcodes == 0 && last_reading_time + 25 < current_time)
        {
            // each barcode gets reported only once --> it is necesarry for the error correction to report a value with each frame
            // adding the last value if no new barcode has been detected
            int last_recognised_code = this->last_readings[0];
            this->add_value_to_last_readings(last_recognised_code);
        }

        int avg_code = this->get_avg_reading();
        if (avg_code != this->current_code_value)
        {
            this->current_code_value = avg_code;
            SENSOR_MESSAGE_BROKER.set(Sensor::Pixi, avg_code);
        }

        // update time after new feature request
        if (last_reading_time + 25 < current_time)
        {
            last_reading_time = current_time;
        }
    }

    void HHN_Pixi::add_value_to_last_readings(int value)
    {
        for (int i = this->last_readings_count - 1; i > 0; i--)
        {
            this->last_readings[i] = this->last_readings[i - 1];
        }
        this->last_readings[0] = value;
    }

    int HHN_Pixi::get_avg_reading()
    {
        for (int i = 0; i < this->last_readings_count - 1; i++)
        {
            if (this->last_readings[i] != this->last_readings[i + 1])
            {
                return this->current_code_value;
            }
        }
        return this->last_readings[0];
    }
} // namespace Sensors
