#include "actors/motor/motor.h"
#include "vehicle.h"



namespace Vehicle
{
    double mapDouble(double x, double in_min, double in_max, double out_min, double out_max){
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    Vehicle::Vehicle(Actors::HHN_V_Motor *motorL, Actors::HHN_V_Motor *motorR)
    {
        this->motorL = motorL;
        this->motorR = motorR;
        this->currentSpeed = 0;
        this->currentDirection = 90;
        this->maxMovmementSpeed = MAX_STRAIGHT_MOVEMENT_SPEED;
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
        calculateMotorValue(this->motorL, false);
        calculateMotorValue(this->motorR, true);
    }

    // phaseDelta: degrees by which the cos function needs to be moved to archieve the correct encoding for the motor
    // motorL: 0
    // motorR: 90
    void Vehicle::calculateMotorValue(Actors::HHN_V_Motor *motor, bool rightMotor)
    {

        int newDirection = this->currentDirection;
        float newSpeed = this->currentSpeed;
        float graphedSpeed = 0;
        int outSpeed;
        Actors::MotorDirection outDirection;

#pragma region rotation speed
        // adjust graph for dirrerent motors
        newDirection += 360;
        newDirection = abs(newDirection) % 360;
        if (!rightMotor)
        {
            if (newDirection >= 0 && newDirection <= 90)
            {
                graphedSpeed = 255;
            }
            else if (newDirection > 90 && newDirection <= 180)
            {

                double dx = 180 - 90;
                double dy = -255 - 255;

                double dNewDirection = newDirection - 90;
                double steigung = dy / dx;

                graphedSpeed = 255 + steigung * dNewDirection;
            }
            else if (newDirection > 180 && newDirection <= 270)
            {
                graphedSpeed = -255;
            }
            else if (newDirection > 270 && newDirection <= 360)
            {
                double dx = 360 - 270;
                double dy = 255 - (-255);

                double dNewDirection = newDirection - 270;
                double steigung = dy / dx;

                graphedSpeed = -255 + steigung * dNewDirection;
            }
        }
        if (rightMotor)
        {
            if (newDirection >= 0 && newDirection <= 90)
            {
                double dx = 90 - 0;
                double dy = 255 - (-255);

                double dNewDirection = newDirection - 0;
                double steigung = dy / dx;

                graphedSpeed = -255 + steigung * dNewDirection;
            }
            else if (newDirection > 90 && newDirection <= 180)
            {
                graphedSpeed = 255;
            }
            else if (newDirection > 180 && newDirection <= 270)
            {
                double dx = 270 - 180;
                double dy = -255 - 255;

                double dNewDirection = newDirection - 180;
                double steigung = dy / dx;

                graphedSpeed = 255 + steigung * dNewDirection;
            }
            else if (newDirection > 270 && newDirection <= 360)
            {
                graphedSpeed = -255;
            }
        }

        graphedSpeed = mapDouble(newSpeed, 0, 255, 0, 1) * graphedSpeed * (-1);

        outSpeed = abs(graphedSpeed);

        // we only want movable speeds from MIN_MOVEMENT_SPEED...MAX_MOVEMENT_SPEED only
        // non movable speeds below MIN_MOVEMENT_SPEED are maped to 0

        outSpeed = map(outSpeed, 0, 255, MIN_MOVEMENT_SPEED - 1, this->maxMovmementSpeed);
        if (outSpeed < 30)
        {
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

    void Vehicle::setMaxMovementSpeed(int newMovementSpeed){
        this->maxMovmementSpeed = newMovementSpeed;
    }

    Vehicle ROVER = Vehicle(&Actors::motorL, &Actors::motorR);

} // namespace Vehicle
