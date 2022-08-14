#include <Arduino.h>
#include "actors/motor.h"

namespace Actors
{
    void set_left(Motor::MotorDirection direction, double speed);
    void set_right(Motor::MotorDirection direction, double speed);

    Motor::MotorDefinition *get_left();
    Motor::MotorDefinition *get_right();

    void init();

    void run();
} // namespace Actors
