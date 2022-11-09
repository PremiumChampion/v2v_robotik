#include <MPU6050_light.h>
#pragma once

namespace HHN_MPU6050
{
    class HHN_MPU6050
    {
    private:
        unsigned long last_measurement_ms;

    public:
        HHN_MPU6050();
        void run();
        void init();
    };
} // namespace MPU6050
