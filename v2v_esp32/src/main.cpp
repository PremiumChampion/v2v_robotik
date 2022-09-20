#include <Arduino.h>
// #include "serial/arduino2esp.h"
// #include "serial/arduino_io_transferhandler.h"
// #include "vehicle/vehicle.h"
// #include "actors/actors.h"
// #include "sensors/sensors.h"
#include "communication/client/socket/socket.h"
#include "communication/communication.h"
#include "communication/server/server.h"
#include "communication/server/connection.h"
#include "communication/wlan/wlan.h"

WLAN::HHN_Server server;
HHN_Client::Socket externalClient;

void setup()
{
  // for debugging
  Serial.begin(9600);
  COM::setup(externalClient);

  // setup communication between both esps.
  // setup serial connection between arduino and esp.
  // SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
}

void loop()
{
  // chaserClient.send("Hello server, I'm cooler than you!");
  // Serial.println(chased_oneClient.rcv());

  // sync sensor and actor data between arduino and esp.
  // SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
}