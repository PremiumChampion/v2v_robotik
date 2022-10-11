#include "positionsyncservice.h"
#include "positioning.h"
#include "sensors/sensors.h"
#include "communication/communication.h"

namespace Service
{
    namespace PositionSync
    {
        void run()
        {
            int thisRobotPositionTile = Sensors::BAR_CODE_SCANNER.getCurrentCodeValue();
            THIS_ROBOT.setCurrentPositionTile(thisRobotPositionTile); // update position of this robot
            
            // TODO: update position of other robot
        }
    }
} // namespace Service
