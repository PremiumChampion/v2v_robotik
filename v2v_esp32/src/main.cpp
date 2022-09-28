#include <Arduino.h>
#include "serial/arduino2esp.h"
#include "serial/arduino_io_transferhandler.h"
#include "vehicle/vehicle.h"
#include "actors/actors.h"
#include "sensors/sensors.h"
#include "communication/communication.h"



void setup()
{
  
  // for debugging
  Serial.begin(9600);
  // delay(2000);
  // Serial.println("Function: main setup");
  COM::setup();

  // setup communication between both esps.
  // setup serial connection between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
}

void loop()
{
//   delay(1000);
//   Serial.println("Function: main loop");
//   Serial.println("Client connection status: ");

//   //Client connection ist auch nicht vorhanden
 

 
//  #if ROLE==CHASED
//   Serial.println(COM::server.getServer().available());
//    String received = COM::externalClient.rcv();
//   Serial.println(received);
//  #endif

//   #if ROLE==CHASER
//     Serial.println(COM::externalClient.isClientConnected());
//     Serial.println("---------------");
//     COM::externalClient.send("Hello Server");
//   #endif 
//   // Serial.println("Hello Server");


  // todo: run wifi transferhandler
 
  Sensors::run();
  // sync sensor and actor data between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
}