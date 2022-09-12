#include <Arduino.h>
// #include "communication/wlan/wlan.h"
#include "serial/arduino2esp.h"
#include "vehicle/vehicle.h"
#include "actors/actors.h"
#include "sensors/sensors.h"

void setup()
{
  Serial.begin(115200); // for debugging

  // put your setup code here, to run once:
  // WLAN::setup();
  SerialCommunication::ArduinoConnection.init();
}
// for echo demo
// unsigned long lastSentTime = 0;

void loop()
{
#pragma region echo demo
  // SerialCommunication::ArduinoConnection.run();

  // if (SerialCommunication::ArduinoConnection.hasData())
  // {
  //   Serial.println(SerialCommunication::ArduinoConnection.recieve());
  // }

  // if (lastSentTime + 1000 < millis())
  // {
  //   SerialCommunication::ArduinoConnection.send("Hello World");
  //   lastSentTime = millis();
  // }
#pragma endregion
  // put your main code here, to run repeatedly:
  // Server.run();

  // socket.run(); // sind daten von der transportschicht vorhanden
  // String data = socket.rcv(); // sind neue komplette anwendungsdaten vorhanden. // dlkfksjdhfk\n
}