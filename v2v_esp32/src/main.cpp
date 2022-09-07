#include <Arduino.h>
// #include "communication/wlan/wlan.h"
#include "serial/arduino2esp.h"

void setup()
{
  // put your setup code here, to run once:
  // WLAN::setup();
  Serial.begin(9600);
  SerialCommunication::ArduinoConnection.init();
}

void loop()
{
  SerialCommunication::ArduinoConnection.run();
  if (SerialCommunication::ArduinoConnection.hasData())
    Serial.println(SerialCommunication::ArduinoConnection.recieve());
  // put your main code here, to run repeatedly:
  // Server.run();

  // socket.run(); // sind daten von der transportschicht vorhanden
  // String data = socket.rcv(); // sind neue komplette anwendungsdaten vorhanden. // dlkfksjdhfk\n
}