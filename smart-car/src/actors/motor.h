#include <Arduino.h>
namespace Motor
{
    struct MotorDefinition
    {
        uint8_t pin_PWM;
        int pin_PWM_value;
        uint8_t pin_ENABLE;
        uint8_t pin_ENABLE_value;
    };

    enum MotorDirection
    {
        FORWARD,
        BACKWARD,
        STOP
    };

    void set_direction(Motor::MotorDefinition *motor, Motor::MotorDirection direction, double speed);

    void init(Motor::MotorDefinition *motor);
    void run(Motor::MotorDefinition *motor);

} // namespace Motor
