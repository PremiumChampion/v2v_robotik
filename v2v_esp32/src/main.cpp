#include <Arduino.h>
#include "serial/arduino2esp.h"
#include "serial/arduino_io_transferhandler.h"
#include "vehicle/vehicle.h"
#include "actors/actors.h"
#include "sensors/sensors.h"
#include "services/coordinator.h"
#include "services/positionsyncservice.h"
#include "communication/communication.h"
#include "movement/movement.h"
#include "game/loop.h"
#include "communication/server/server.h"
#include "communication/server/connection.h"
#include "communication/wlan/wlan.h"
#include "communication/shared/transfer.h"



unsigned long currentTime;
unsigned int currentNumber;
void setup()
{
  
  // for debugging
  Serial.begin(115200);
  delay(2000);
  Serial.println("Function: main setup");
  COM::WIFI_TRANSFER_HANDLER.init();

  // setup communication between both esps.
  // setup serial connection between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
  Service::PositionSync::init();

  Movement::MOVEMENTS.setNewDirections(Movement::Straight);
}
void loop()
{

  // todo: run wifi transferhandler
  
  Movement::MOVEMENTS.run();
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
  Sensors::run();

  COM::WIFI_TRANSFER_HANDLER.run();
    
  Service::Coordinator::run();
  Service::PositionSync::run();
  Game::run();

  // sync sensor and actor data between arduino and esp.
}