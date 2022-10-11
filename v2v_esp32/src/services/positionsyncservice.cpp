#include "positionsyncservice.h"
#include "positioning.h"
#include "sensors/sensors.h"

namespace Service
{
    namespace PositionSync
    {
        // call run function in main in the service section

        void run()
        {
            int thisRobotPositionTile = Sensors::BAR_CODE_SCANNER.getCurrentCodeValue();
            THIS_ROBOT.setCurrentPositionTile(thisRobotPositionTile); // update position of this robot

            // int otherRobotPositionTile = 0; // how to get the other robot's qr code.

            // OTHER_ROBOT.setCurrentPositionTile(otherRobotPositionTile); // update position of other robot
        }
    }
} // namespace Service
