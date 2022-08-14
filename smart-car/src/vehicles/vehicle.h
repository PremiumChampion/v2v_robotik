#include "actors/actors.h"
#include "actors/motor.h"
namespace Vehicle
{
    struct VehicleDefinition
    {
        Motor::MotorDefinition *left;
        Motor::MotorDefinition *right;
        //   0:right-inplace
        //  90:forward
        // 180:left-inplace
        // 270:backwards
        // 0 - 359
        int direction;
        double speed;
    };

    // void calculate_speed(Motor::MotorDirection *motor_direction, double *speed, int new_direction, double new_speed, int phase_delta);

    void set_direction(VehicleDefinition *vehicle, int direction, double speed);
    void init(VehicleDefinition *vehicle);
    void run(VehicleDefinition *vehicle);
} // namespace Vehicle
