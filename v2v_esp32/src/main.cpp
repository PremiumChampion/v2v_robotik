#include <Arduino.h>
#include "serial/arduino2esp.h"
#include "serial/arduino_io_transferhandler.h"
#include "vehicle/vehicle.h"
#include "actors/actors.h"
#include "sensors/sensors.h"
#include "communication/communication.h"
#include "movement/movement.h"
#include "communication/server/server.h"
#include "communication/server/connection.h"
#include "communication/wlan/wlan.h"
#include "communication/shared/transfer.h"



unsigned long currentTime;
unsigned int currentNumber;
void setup()
{
  
  // for debugging
  Serial.begin(9600);
  delay(2000);
  Serial.println("Function: main setup");
  COM::WIFI_TRANSFER_HANDLER.init();
  // setup communication between both esps.
  // setup serial connection between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.init();
  Movement::MOVEMENTS.setNewDirections(Movement::Straight);
}
void loop()
{

  if(currentTime+1000<millis()){
     Serial.println("Function: main loop");
     Serial.println("Client connection status: ");
     currentTime = millis();
    //  currentNumber++;
    //  COM::broker.set(0,String(currentNumber));
    Serial.println(COM::broker.get(0));  
  }

//   //Client connection ist auch nicht vorhanden
 

  // WIFI_TRANSFER_HANDLER.run(); 
 
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
  Movement::MOVEMENTS.run();
  COM::WIFI_TRANSFER_HANDLER.run();
  
  
 

  // sync sensor and actor data between arduino and esp.
  SerialCommunication::SENSOR_ACTOR_TRANSFER_HANDLER.run();
}