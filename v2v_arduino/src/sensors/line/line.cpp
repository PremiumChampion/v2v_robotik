#include "line.h"
#include "sensors/sensors.h"
#include "Arduino.h"

namespace Line
{

    HHN_Line::HHN_Line(int pinLeft, int pinCenter, int pinRight)
    {
        this->pinCenter = pinCenter;
        this->pinLeft = pinLeft;
        this->pinRight = pinRight;
        pinMode(this->pinCenter, INPUT);
        pinMode(this->pinLeft, INPUT);
        pinMode(this->pinRight, INPUT);
    }
    HHN_Line::~HHN_Line()
    {
    }

    bool HHN_Line::onLine(int pin)
    {
        int pinValue = analogRead(pin);
        return pinValue > 100 && pinValue < 600;
    }

    void HHN_Line::run()
    {
        int left = (int)this->onLine(this->pinLeft) << 2;
        int center = (int)this->onLine(this->pinCenter) << 1;
        int right = (int)this->onLine(this->pinRight);
        int result = left + center + right;
        Sensors::MESSAGE_BROKER.set(Sensors::Sensor::LINE, result);
    }
} // namespace Sensors
