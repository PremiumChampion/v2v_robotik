#include <Arduino.h>
#include "sensors/sensors.h"
#include "actors/actors.h"
#include "serial/arduino_io_transferhandler.h"

void setup()
{
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
  Actors::init();
}

void loop()
{
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
  Sensors::run();
  Actors::run();
}