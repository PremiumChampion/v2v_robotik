#include <Arduino.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

namespace SerialCommunication
{
    enum SerialMode
    {
        IDLE,
        SENDING,
        RECIEVING,
    };

    enum SerialImplementation
    {
        Software,
        Hardware
    };

    class Arduino2esp
    {
    private:
        Stream *serial;

        // buffers serial input until a whole fragment is ready
        String rcvBuffer;
        // the time the serial communication recieved some data (millis)
        unsigned long lastRecieveTime;
        // buffers serial output until it is ready to be sent
        String sndBuffer;

        // SoftwareSerial can not recieve and send data at the same time
        SerialMode mode;
        SerialImplementation implementation;
        // method for sending serial data
        void snd_data();
        // method for recieving serial data
        void rcv_data();

    public:
        Arduino2esp(Stream *serialConnection, SerialImplementation implementation);
        ~Arduino2esp();
        void init();
        void run();
        // recieve serial data
        // strips newlines
        String recieve();
        // send serial data
        void send(String data);
        bool hasData();
    };

    extern Arduino2esp ArduinoConnection;

} // namespace SerialCommunication
