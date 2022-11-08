#include "sensors/sensors.h"
#include "line.h"
#include "Arduino.h"

namespace Sensors
{
    HHN_V_Line::HHN_V_Line()
    {
        this->nextLevelingIndex = 0;
        this->levelingArraySize = 3;
        this->leftLevelingValues = new bool[this->levelingArraySize];
        this->centerLevelingValues = new bool[this->levelingArraySize];
        this->rightLevelingValues = new bool[this->levelingArraySize];

        this->current_value = LineValue::ALL;
        this->extract_values();
    }

    void HHN_V_Line::extract_values()
    {
        this->leftLevelingValues[this->nextLevelingIndex] = (this->current_value / 4) % 2 == 1;
        this->centerLevelingValues[this->nextLevelingIndex] = (this->current_value / 2) % 2 == 1;
        this->rightLevelingValues[this->nextLevelingIndex] = (this->current_value / 1) % 2 == 1;
        this->nextLevelingIndex = (this->nextLevelingIndex + 1) % this->levelingArraySize;

        int leftPosCount = 0;
        int centerPosCount = 0;
        int rightPosCount = 0;

        for (int i = 0; i < this->levelingArraySize; i++)
        {
            if(this->leftLevelingValues[i]== true){
                leftPosCount++;
            }
            if(this->centerLevelingValues[i]== true){
                centerPosCount++;
            }
            if(this->rightLevelingValues[i]== true){
                rightPosCount++;
            }
        }
        
        this->leftValue = leftPosCount >= this->levelingArraySize / 2;
        this->centerValue = centerPosCount >= this->levelingArraySize / 2;
        this->rightValue = rightPosCount >= this->levelingArraySize / 2;
    }

    void HHN_V_Line::run()
    {
        this->current_value = (LineValue)Sensors::MESSAGE_BROKER.get(Sensor::LINE);
        this->extract_values();
    }

    bool HHN_V_Line::right() { return this->leftValue; }
    bool HHN_V_Line::center() { return this->centerValue; }
    bool HHN_V_Line::left() { return this->rightValue; }
    LineValue HHN_V_Line::value() { return this->current_value; }
} // namespace Line
