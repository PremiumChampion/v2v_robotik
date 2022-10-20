#include "positionsyncservice.h"
#include "positioning.h"
#include "sensors/sensors.h"
#include "communication/communication.h"

#if ROLE == CHASER
#define THIS_START_POSITION 15
#endif

#if ROLE == CHASED
#define THIS_START_POSITION 12
#endif

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
            OTHER_ROBOT.setCurrentPositionTile(COM::broker.get(COM::getOtherPositionIndex()).toInt()); // uncomment when working with relative positioning
        }

        void init(){
            COM::broker.set(COM::getThisPositionIndex(), String(THIS_START_POSITION));
        }
    }
} // namespace Service
