#include "vehicles/vehicle.h"
#include "actors/actors.h"
namespace Vehicles
{
    Vehicle::VehicleDefinition rover = {
        .left = Actors::get_left(),
        .right = Actors::get_right(),
        .direction = 90,
        .speed = 0,
    };

    Vehicle::VehicleDefinition *get_rover()
    {
        return &rover;
    }

    void init()
    {
        Vehicle::init(get_rover());
    }

    void run()
    {
        Vehicle::run(get_rover());  
    }
} // namespace Vehicles
