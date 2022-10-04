#include "sensors/sensors.h"
#include "line.h"
#include "Arduino.h"

namespace Sensors
{
    HHN_V_Line::HHN_V_Line()
    {
        this->current_value = LineValue::None;
        this->extract_values();
    }

    void HHN_V_Line::extract_values()
    {
        this->leftValue = (this->current_value / 4) % 2 == 1;
        this->centerValue = (this->current_value / 2) % 2 == 1;
        this->rightValue = (this->current_value / 1) % 2 == 1;
    }

    void HHN_V_Line::run()
    {
        this->current_value = (LineValue)Sensors::MESSAGE_BROKER.get(Sensor::LINE);
        this->extract_values();
    }

    bool HHN_V_Line::right() { return this->rightValue; }
    bool HHN_V_Line::center() { return this->centerValue; }
    bool HHN_V_Line::left() { return this->leftValue; }
    LineValue HHN_V_Line::value() { return this->current_value; }
} // namespace Line
