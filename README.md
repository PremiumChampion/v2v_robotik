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

* [ ] [Broker](https://en.wikipedia.org/wiki/Broker_pattern)-Abstraction

    * [ ] Full-Sync Capabilities

* [ ] WiFi (Connection related)

    * [ ] Create Access-Point
    * [ ] Connect to Access-Point

* [ ] Serial Communication Arduino <-> ESP

    * [x] ESP
    * [ ] Arduino

* [ ] Virtual Sensors

    * [ ] Barcode-Sensor
    * [ ] Line-Sensor

* [ ] Virtual Actors

    * [x] Virtual Motor Speed
    * [x] Virtual Motor Direction

## Level C

* [ ] Server (maybe listen on multiple ports for additional differentiation)

    * [ ] Start Server (listen on port xxx)
    * [ ] Connect to Server (Initiate TCP-Connection)

* [x] Motor Abstraction (Speed + Direction)
* [x] Vehicle Abstraction (Motor-L + Motor-R)

## Level D

* [ ] Socket IO (in combination with server)

    * [ ] RCV Data
    * [ ] SND Data

* [ ] WiFi Broker

    * [ ] Figure out which state needs to be synced

* [ ] WiFi-Transmisstion-Handler (handles reading/publishing state changes syncing those to the ESP´s)

## Level E (Action-Level)

* [ ] Basic Movement (Sensor + Actor) (asynchronous)

    * [ ] Move Straight
    * [ ] Move Back
    * [ ] Turn Left
    * [ ] Turn Right

* [ ] Error Correction (asynchronous)

    * [ ] Out of Bounds
    * [ ] Off the Line

## Level F (Service-Level)

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