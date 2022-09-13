#include <Arduino.h>
#include "broker/broker.h"
#include "sensors/sensors.h"
#include "actors/actors.h"

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String rcv = "";
unsigned long last_rcv_time = millis();

void loop()
{
  if (Serial.available())
  {
    while (Serial.available())
    {
      rcv += (char)Serial.read();
    }
    last_rcv_time = millis();
  }

  if (last_rcv_time + 250 < millis())
  {
    Serial.print(rcv);
    rcv = "";
  }

  // put your main code here, to run repeatedly:
  // Sensors::run();
  // Actors::run();

  // send sensor values
  // if (Sensors::MESSAGE_BROKER.get_has_changes())
  // {
  //   String transmission_data = Sensors::MESSAGE_BROKER.get_transmission_data();
  //   // Serial.println(transmission_data);

  //   for (int i = 0; i < transmission_data.length(); i++)
  //   {
  //     // Serial.write(transmission_data.charAt(i));
  //   }
  //   // Serial.write('\n');

  //   // Serial.available();
  //   // Sensors::MESSAGE_BROKER.rcv_transmission_data(Serial.readStringUntil('\n'));
  // }

  // TODO: recieve actor values if available
  //  Actors::ACTOR_MESSAGE_BROKER.rcv_transmission_data(data);
}