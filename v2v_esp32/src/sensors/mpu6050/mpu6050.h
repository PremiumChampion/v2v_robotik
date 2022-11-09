#pragma once

namespace Sensors
{
    class HHN_MPU6050
    {
    private:
        float value;
    public:
        HHN_MPU6050(/* args */);
        void run();
        float getValue();
    };
} // namespace MPU6050
