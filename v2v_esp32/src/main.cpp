#include <Arduino.h>
#include "communication/wlan/wlan.h"
void setup() {
  // put your setup code here, to run once:
  WLAN::setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Server.run();

  // socket.run(); // sind daten von der transportschicht vorhanden
  // String data = socket.rcv(); // sind neue komplette anwendungsdaten vorhanden. // dlkfksjdhfk\n

}