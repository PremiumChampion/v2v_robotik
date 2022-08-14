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

    void set_direction(Motor::MotorDefinition *motor, Motor::MotorDirection direction, double speed)
    {
        int _speed = (int)(speed * 100);
        _speed = _speed % 101;
        speed = (double)_speed / 100;
        int speed_PWM = 255 * speed;

        switch (direction)
        {
        case MotorDirection::FORWARD:
            motor->pin_PWM_value = speed_PWM;
            motor->pin_ENABLE_value = LOW;
            break;
        case MotorDirection::BACKWARD:
            motor->pin_PWM_value = speed_PWM;
            motor->pin_ENABLE_value = HIGH;
            break;
        case MotorDirection::STOP:
            motor->pin_PWM_value = 0;
            motor->pin_ENABLE_value = LOW;
            break;
        default:
            break;
        }
    }

    void init(Motor::MotorDefinition *motor)
    {
        pinMode(motor->pin_PWM, OUTPUT);
        pinMode(motor->pin_ENABLE, OUTPUT);
        analogWrite(motor->pin_PWM, motor->pin_PWM_value);
        analogWrite(motor->pin_ENABLE, motor->pin_ENABLE_value);
    }

    void run(Motor::MotorDefinition *motor)
    {
        analogWrite(motor->pin_PWM, motor->pin_PWM_value);
        analogWrite(motor->pin_ENABLE, motor->pin_ENABLE_value);
    }

} // namespace Motor
