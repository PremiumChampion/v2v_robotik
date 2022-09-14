#include <Arduino.h>
#include "stopmovement.h"
#include "sensors/sensors.h"
#include "vehicle/vehicle.h"

namespace Movement
{
    StopMovement::StopMovement() : BasicMovement() {}
    void StopMovement::run() {}
} // namespace Movement
