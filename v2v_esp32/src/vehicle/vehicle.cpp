#include "actors/motor/motor.h"
#include "vehicle.h"

namespace Vehicle
{

    Vehicle::Vehicle(Actors::HHN_V_Motor *motorL, Actors::HHN_V_Motor *motorR)
    {
        this->motorL = motorL;
        this->motorR = motorR;
        this->currentSpeed = 0;
        this->currentDirection = 90;
    }
    Vehicle::~Vehicle()
    {
    }
    float Vehicle::getSpeed()
    {
        return this->currentSpeed;
    }
    int Vehicle::getDirection()
    {
        return this->currentDirection;
    }
    void Vehicle::set(float speed, int degree)
    {
        this->currentSpeed = speed;
        this->currentDirection = degree;
        calculateMotorValue(this->motorL, 0);
        calculateMotorValue(this->motorR, 90);
    }

    // phaseDelta: degrees by which the cos function needs to be moved to archieve the correct encoding for the motor
    // motorL: 0
    // motorR: 90
    void Vehicle::calculateMotorValue(Actors::HHN_V_Motor *motor, int phaseDelta)
    {

        int newDirection = this->currentDirection;
        float newSpeed = this->currentSpeed;
        float graphedSpeed = 0;
        int outSpeed;
        Actors::MotorDirection outDirection;

#pragma region rotation speed
        // adjust graph for dirrerent motors
        newDirection += phaseDelta;
        newDirection = newDirection % 360;

        if (newDirection >= 0 && newDirection < 90)
        {
            graphedSpeed = newSpeed;
        }
        if (newDirection >= 180 && newDirection < 270)
        {
            graphedSpeed = -newSpeed;
        }

        // see Rotation_Encoding.pdf
        // maps newDirection (0°+360°) and newSpeed to a speed -255 to 255 of a motor indicating the speed and direction of the motor
        if (newDirection >= 90 && newDirection < 180)
        {
            graphedSpeed = -newSpeed * cos(PI / 90 * (newDirection * DEG_TO_RAD));
        }
        if (newDirection >= 270 && newDirection < 360)
        {
            graphedSpeed = newSpeed * cos(PI / 90 * (newDirection * DEG_TO_RAD));
        }

        // rad = deg x PI / 180
        // deg = rad x 180 / PI

        outSpeed = abs(graphedSpeed);

        // we only want movable speeds from 30...60 only
        // non movable speeds are 0

        outSpeed = map(outSpeed, 0, 255,29,50);
        if(outSpeed < 30){
            outSpeed = 0;
        }

#pragma endregion

#pragma region rotation direction

        // motor should move forwards
        if (graphedSpeed > 0)
            outDirection = Actors::MotorDirection::FORWARD;

        // Motor should move backwards
        if (graphedSpeed < 0)
            outDirection = Actors::MotorDirection::BACKWARD;

        // Motor should stop --> independent on what we set the motor will stop;
        if (graphedSpeed == 0)
            outDirection = Actors::MotorDirection::FORWARD;
#pragma endregion
        // output value




        motor->set(outSpeed, outDirection);
    }

    Vehicle ROVER = Vehicle(&Actors::motorL, &Actors::motorR);

} // namespace Vehicle
