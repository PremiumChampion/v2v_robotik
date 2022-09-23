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

HHN_Client::Socket externalClient = HHN_Client::Socket();

void setup()
{
  
  // for debugging
  Serial.begin(9600);
  delay(2000);
  Serial.println("Function: main setup");
  COM::setup();

  // setup communication between both esps.
  // setup serial connection between arduino and esp.
  // SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
}

void loop()
{
  delay(1000);
  Serial.println("Function: main loop");
  externalClient.send("Hello Server");
  // Serial.println("Hello Server");
  
  // String received = externalClient.rcv();
  // Serial.println(received);
  // Serial.println(".");
  // Serial.println(chased_oneClient.rcv());

  // sync sensor and actor data between arduino and esp.
  // SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
}