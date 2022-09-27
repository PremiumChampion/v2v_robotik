#include <Arduino.h>
#include "leftmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    LeftMovement::LeftMovement() : BasicMovement() {}
    void LeftMovement::run() {

        // if(this->isPaused) 
        // Vehicle::ROVER.set(0,90);
        // return

        // Sensors::LINE_SENSOR.value();
        // Vehicle::ROVER.set(255,90);

        // Sensors::LINE_SENSOR.left()
        // Vehicle::ROVER.set(255,80);

        // Sensors::LINE_SENSOR.rigth()
        // Vehicle::ROVER.set(255,100);

        // Sensors::LINE_SENSOR auf kreuzung
        // this->isDone = true;
    }

} // namespace Movement
