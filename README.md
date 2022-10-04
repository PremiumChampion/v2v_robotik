# TODO

## Important Requirements

* [ ] [__Cooperative multitasking__](https://en.wikipedia.org/wiki/Cooperative_multitasking)

## Level A (Arduino-IO)

* [ ] Barcode-Sensor

    * [ ] Configuration
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

* [x] WiFi-Transmisstion-Handler (handles reading/publishing state changes syncing those to the ESP´s)

## Level E (Action-Level)

* [x] Basic Movement (Sensor + Actor) (asynchronous)

    * [x] Move Straight
    * [x] Move Back
    * [x] Turn Left
    * [x] Turn Right

## Level F (Service-Level) (Work in progress)

* [ ] Positioning-Service

    * [ ] Find starting postition (0-15)
    * [ ] Find starting direction (east/south/west/north)

        * [ ] !Entscheidung!: initial immer norden oder dynamische berechnung?

    * [ ] Keep track of current position (0-15)
    * [ ] Keep track of current direction (east/south/west/north)

* [ ] Forwarding-Service

    * [ ] Choose next Basic-Movement
    * [ ] Move from pos/direction to adjacent post/direction

* [ ] Routing-Service
    
    * [ ] Find route from x to y
    * [ ] Find forwarding points

* [ ] Decide prisoner/police

## Level G (Game-Level)

* [ ] Move to prisoner
* [ ] Move away from police
* [ ] Winner Logic