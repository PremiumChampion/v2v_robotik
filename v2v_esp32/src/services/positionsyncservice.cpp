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

            int otherRobotPositionTile = COM::RCV_BROKER.get(COM::POSITION).toInt();
            OTHER_ROBOT.setCurrentPositionTile(otherRobotPositionTile); // update position of other robot
        }
    }
} // namespace Service
