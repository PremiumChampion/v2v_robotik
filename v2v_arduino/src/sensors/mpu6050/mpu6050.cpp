#include "mpu6050.h"
#include <MPU6050_light.h>
#include "sensors/sensors.h"
#include "Wire.h"

namespace HHN_MPU6050
{
    MPU6050 mpu(Wire);
    HHN_MPU6050::HHN_MPU6050()
    {
        this->last_measurement_ms = 0;
    }
    void HHN_MPU6050::run()
    {
        mpu.update();
        if (last_measurement_ms + 30 < millis())
        {
            Sensors::MESSAGE_BROKER.set(Sensors::GYRO, (int)(mpu.getAngleZ() * 10));
            last_measurement_ms = millis();
        }
    }
    void HHN_MPU6050::init()
    {
        Wire.begin();
        mpu.begin();
        delay(2000);
        mpu.calcOffsets();
        this->run();
    };
} // namespace MPU6050
