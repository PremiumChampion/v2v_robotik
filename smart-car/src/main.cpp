#include <Arduino.h>
#include "sensors/sensors.h"
#include "jobs/jobs.h"
#include "actors/actors.h"
#include "vehicles/vehicles.h"

void setup()
{
  Sensors::init();
  // initialise actors before vehicle
  Actors::init();
  Vehicles::init();
  // initialise jobs last, these define the behaviour of the car
  Jobs::init();
}

void loop()
{
  // principle follows a programmable logic controller, PLC (speicherprogrammierbare Steuerung)
  // no blocking calls should be performred in loop (sleep, pulseIn,...)
  // this reduces the pulling rate of the sensors/actors
  
  // Eingabe
  Sensors::run();

  // Verarbeitung
  // do not modify values directly (digitalWrite/analogWrite/analogRead/digitalRead) in a job.
  // use provided values in the single entities from sensors / actors... to perform or update tasks
  Jobs::run();
  
  // Ausgabe
  Vehicles::run();
  Actors::run();
}