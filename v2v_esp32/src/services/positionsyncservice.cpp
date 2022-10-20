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

            
            // TODO: update position in broker
            COM::broker.set(COM::getThisPositionIndex(), String(thisRobotPositionTile));
            COM::broker.get(COM::getOtherPositionIndex());

            // update positions
            THIS_ROBOT.setCurrentPositionTile(thisRobotPositionTile); 
            OTHER_ROBOT.setCurrentPositionTile(COM::broker.get(COM::getOtherPositionIndex()).toInt());
        }
    }
} // namespace Service
