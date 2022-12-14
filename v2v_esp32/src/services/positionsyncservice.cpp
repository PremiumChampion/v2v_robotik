#include "coordinator.h"
#include "positionsyncservice.h"
#include "services/data/positioning.h"
#include "sensors/sensors.h"
#include "communication/communication.h"

#if ROLE == CHASER
#define THIS_START_POSITION 15
#define OTHER_START_POSITION 12
#else
#define THIS_START_POSITION 12
#define OTHER_START_POSITION 15
#endif

namespace Service
{
    namespace PositionSync
    {

        void run()
        {
#if WORKING_WITH_QR_SENSOR
            int thisRobotPositionTile = Sensors::BAR_CODE_SCANNER.getCurrentCodeValue();

            // update position in broker otherwise done in coordinator.cpp
            COM::broker.set(COM::getThisPositionIndex(), String(thisRobotPositionTile));

            // update positions
            THIS_ROBOT.setCurrentPositionTile(thisRobotPositionTile); // comment out when not working w qr code scanner
#endif
            OTHER_ROBOT.setCurrentPositionTile(COM::broker.get(COM::getOtherPositionIndex())); // uncomment when working with relative positioning
        }

        void init()
        {
            COM::broker.set(COM::getThisPositionIndex(), THIS_START_POSITION);
            COM::broker.set(COM::getOtherPositionIndex(), OTHER_START_POSITION);
            COM::broker.set(COM::CRIMINAL_POSITION, ROLE == CHASED ? THIS_START_POSITION : OTHER_START_POSITION);
            COM::broker.set(COM::POLICE_POSITION, ROLE == CHASER ? THIS_START_POSITION : OTHER_START_POSITION);

            Coordinator::setCurrentTarget(THIS_START_POSITION);

            THIS_ROBOT.setCurrentPositionTile(THIS_START_POSITION);
            THIS_ROBOT.setCurrentDirection(NORTH);

            OTHER_ROBOT.setCurrentPositionTile(OTHER_START_POSITION);
            OTHER_ROBOT.setCurrentDirection(NORTH);
        }
    }
} // namespace Service
