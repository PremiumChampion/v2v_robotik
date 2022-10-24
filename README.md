# TODO

## Important Requirements

* [x] [__Cooperative multitasking__](https://en.wikipedia.org/wiki/Cooperative_multitasking)

## Level A (Arduino-IO)

* [x] Barcode-Sensor

    * [x] Configuration
    * [ ] Hardware-Positioning
    * [x] Reading

* [x] Line-Sensor
* [x] Motor Speed
* [x] Motor Direction

## Level B

* [x] [Broker](https://en.wikipedia.org/wiki/Broker_pattern)-Abstraction

    * [x] Full-Sync Capabilities

* [x] WiFi (Connection related)

    * [x] Create Access-Point
    * [x] Connect to Access-Point

* [x] Serial Communication Arduino <-> ESP

    * [x] ESP
    * [x] Arduino

* [x] Virtual Sensors

    * [x] Barcode-Sensor
    * [x] Line-Sensor

* [x] Virtual Actors

    * [x] Virtual Motor Speed
    * [x] Virtual Motor Direction

## Level C

* [x] Server (maybe listen on multiple ports for additional differentiation)

    * [x] Start Server (listen on port xxx)
    * [x] Connect to Server (Initiate TCP-Connection)

* [x] Motor Abstraction (Speed + Direction)
* [x] Vehicle Abstraction (Motor-L + Motor-R)

## Level D

* [x] Socket IO (in combination with server)

    * [x] RCV Data
    * [x] SND Data

* [x] WiFi Broker

    * [ ] Figure out which state needs to be synced
    * [ ] Sync positioning services

* [x] WiFi-Transmisstion-Handler (handles reading/publishing state changes syncing those to the ESP´s)

## Level E (Action-Level)

* [x] Basic Movement (Sensor + Actor) (asynchronous)

    * [x] Move Straight
    * [x] Move Back
    * [x] Turn Left
    * [x] Turn Right

## Level F (Service-Level) (Work in progress)

* [x] Positioning-Service

    * [x] Find starting postition (0-15) --> fixe starting points
    * [x] Find starting direction (east/south/west/north) --> fixe starting direction
    * [x] Keep track of current position (0-15)
    * [x] Keep track of current direction (east/south/west/north)
    * [ ] sync positions

* [x] Forwarding-Service

    * [x] Choose next Basic-Movement
    * [x] Move from pos/direction to adjacent post/direction

* [x] Routing-Service
    
    * [x] Find route from x to y
    * [x] Find forwarding points

* [x] Decide prisoner/police --> initial police/criminal set in code

## Level G (Game-Level)

* [x] Police move to prisoner
* [ ] Move away from police (deprecated)
* [x] Winner Logic
* [x] Criminal init
  * [x] generate random position
  * [x] move to random position
  * [x] wait for police ready
  * [x] start game
* [x] Police init
  * [x] wait for criminal ready
  * [x] generate random starting position
  * [x] move to random position
  * [x] start game
* [x] Police run
  * [x] check for win condition
  * [x] if won reset broker init vars
  * [x] if won switch role(optional)
  * [x] if won reinit
  * [x] if not won navigate to OTHER_ROBOT
* [x] Criminal run
  * [x] wait for police to tell you that you lost
  * [x] if lost switch role (optional)
  * [x] if lost reinit
  * [x] if not lost wait