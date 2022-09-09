#include "actors/motor/motor.h"
#include "vehicle.h"

namespace Vehicle
{

    Vehicle::Vehicle(Actors::HHN_V_Motor *motorL, Actors::HHN_V_Motor *motorR)
    {
        this->motorL = motorL;
        this->motorR = motorR;
        this->set(0, STOP);
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
    void Vehicle::set(float speed, int direction)
    {
        this->currentSpeed = speed;
        this->currentDirection = direction;
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

        if (newDirection >= 90 && newDirection < 180 || newDirection >= 270 && newDirection < 360)
        {
            // see Rotation_Encoding.pdf
            // maps newDirection (0°+360°) and newSpeed to a speed -255 to 255 of a motor indicating the speed and direction of the motor
            graphedSpeed = newSpeed * cos(PI / 90 * (newDirection - 90));
        }
        outSpeed = abs(graphedSpeed);

#pragma endregion

#pragma region rotation direction

        // motor should move forwards
        if (graphedSpeed > 0)
            outDirection = Actors::FORWARD;

        // Motor should move backwards
        if (graphedSpeed < 0)
            outDirection = Actors::BACKWARD;

        // Motor should stop --> independent on what we set the motor will stop;
        if (graphedSpeed == 0)
            outDirection = Actors::FORWARD;
#pragma endregion
        // output value
        motor->set(outSpeed, outDirection);
    }

    Vehicle ROVER(&Actors::motorL, &Actors::motorR);

} // namespace Vehicle
