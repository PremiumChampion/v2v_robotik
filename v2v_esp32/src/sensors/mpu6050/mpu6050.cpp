#include "mpu6050.h"
#include "sensors/sensors.h"
#include "communication/communication.h"
namespace Sensors
{
    HHN_MPU6050::HHN_MPU6050(/* args */)
    {
        this->value = 0;
    }

    void HHN_MPU6050::run()
    {
// #if ROLE == CHASED
//         this->value = (MESSAGE_BROKER.get(GYRO) - (millis() / 5000)) / 10;
// #endif
// #if ROLE == CHASER
        this->value = MESSAGE_BROKER.get(GYRO) / 10;
// #endif
    }

    float HHN_MPU6050::getValue()
    {
        return this->value;
    }
} // namespace MPU6050
