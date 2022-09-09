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

    /**
     * 
     */
    void calculate_speed(Motor::MotorDirection *motor_direction, double *speed, int new_direction, double new_speed, int phase_delta)
    {
        new_direction += phase_delta;
        new_direction = new_direction % 360;

        double graphed_speed = 0;

        if (new_direction >= 0 && new_direction < 90)
        {
            graphed_speed = new_speed;
        }
        if (new_direction >= 180 && new_direction < 270)
        {
            graphed_speed = -new_speed;
        }

        if (new_direction >= 90 && new_direction < 180 || new_direction >= 270 && new_direction < 360)
        {
            // see Rotation_Encoding.pdf
            // maps new_direction (0°+360°) and new_speed to a speed -255 to 255 of a motor indicating the speed and direction of the motor
            graphed_speed = new_speed * cos(PI / 90 * (new_direction - 90));
        }

        if (graphed_speed > 0)
            *motor_direction = Motor::MotorDirection::FORWARD;

        if (graphed_speed < 0)
            *motor_direction = Motor::MotorDirection::BACKWARD;

        if (graphed_speed == 0)
            *motor_direction = Motor::MotorDirection::STOP;

        *speed = abs(graphed_speed);
    }

    void set_direction(VehicleDefinition *vehicle, int direction, double speed)
    {
        direction = direction % 360;

        vehicle->direction = direction;
        vehicle->speed = speed;
    }

    void init(VehicleDefinition *vehicle)
    {
    }

    void run(VehicleDefinition *vehicle)
    {
        Motor::MotorDirection left_direction;
        double left_speed;
        Motor::MotorDirection right_direction;
        double right_speed;

        calculate_speed(&left_direction, &left_speed, vehicle->direction, vehicle->speed, 0);
        calculate_speed(&right_direction, &right_speed, vehicle->direction, vehicle->speed, 0);
        
        Motor::set_direction(vehicle->left, left_direction, left_speed);
        Motor::set_direction(vehicle->right, right_direction, right_speed);
    }
} // namespace Vehicle
