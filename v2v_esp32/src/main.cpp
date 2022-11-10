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

void setup()
{
  Serial.begin(115200);

  randomSeed(42);

  Service::PositionSync::init();

  // setup serial connection between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
  unsigned long startSync = millis();
  while (startSync + 4000 > millis())
  {
    SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
    Sensors::run();
  }
  // Movement::MOVEMENTS.setNewDirections(Movement::Straight);
  // setup communication between both esps.
  // COM::WIFI_TRANSFER_HANDLER.init();
}
void loop()
{
  delay(1);

  Movement::MOVEMENTS.run();
  Sensors::run();

  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
  // COM::WIFI_TRANSFER_HANDLER.run();

  Service::PositionSync::run();
  Game::run();
  Service::Coordinator::run();
}