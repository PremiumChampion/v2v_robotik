#include "mpu6050.h"
#include "sensors/sensors.h"
namespace Sensors
{
    HHN_MPU6050::HHN_MPU6050(/* args */)
    {
        this->value = 0;
    }

    void HHN_MPU6050::run()
    {
        this->value = MESSAGE_BROKER.get(GYRO) / 10;
    }

    float HHN_MPU6050::getValue()
    {
        return this->value;
    }
} // namespace MPU6050
