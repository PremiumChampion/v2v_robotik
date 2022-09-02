#include <Arduino.h>
#include "broker/broker.h"
#include "sensors/sensors.h"
#include "actors/actors.h"

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop()
{
  // put your main code here, to run repeatedly:
  Sensors::update();
  Actors::update();

  // send sensor values
  if (Sensors::MESSAGE_BROKER.get_has_changes())
  {
    String transmission_data = Sensors::MESSAGE_BROKER.get_transmission_data();
    // Serial.println(transmission_data);

    for (int i = 0; i < transmission_data.length(); i++)
    {
      // Serial.write(transmission_data.charAt(i));
    }
    // Serial.write('\n');
    
    // Serial.available();
    // Sensors::MESSAGE_BROKER.rcv_transmission_data(Serial.readStringUntil('\n'));
  }

  // TODO: recieve actor values if available
  //  Actors::ACTOR_MESSAGE_BROKER.rcv_transmission_data(data);
}