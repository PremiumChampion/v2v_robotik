#include <Arduino.h>
// #include "communication/wlan/wlan.h"
#include "serial/arduino2esp.h"
#include "serial/arduino_io_transferhandler.h"
#include "vehicle/vehicle.h"
#include "actors/actors.h"
#include "sensors/sensors.h"

void setup()
{
  // for debugging
  Serial.begin(9600);

  // put your setup code here, to run once:
  WLAN::WLAN.setup();

  // setup serial connection between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
}

void loop()
{
  // sync sensor and actor data between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();


  // put your main code here, to run repeatedly:
  // Server.run();

  // socket.run(); // sind daten von der transportschicht vorhanden
  // String data = socket.rcv(); // sind neue komplette anwendungsdaten vorhanden. // dlkfksjdhfk\n
}