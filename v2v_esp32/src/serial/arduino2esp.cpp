#include <Arduino.h>
#include <SoftwareSerial.h>
#include "arduino2esp.h"

namespace SerialCommunication
{

#pragma region private

    // method for sending serial data
    void Arduino2esp::snd_data()
    {
        unsigned long startTime = millis();
        while (startTime + 10 < millis() && this->sndBuffer.length() > 0)
        {
            this->serial->write(this->sndBuffer.charAt(0));
            this->sndBuffer = sndBuffer.substring(1);
        }
    }

    // method for recieving serial data
    void Arduino2esp::rcv_data()
    {
        while (this->serial->available())
        {
            this->rcvBuffer += (char)this->serial->read();
        }
        this->lastRecieveTime = millis();
    }

#pragma endregion
#pragma region public
    Arduino2esp::Arduino2esp(Stream *serialConnection, SerialImplementation implementation)
    {
        // SoftwareSerial connection(this->RX_PIN, this->TX_PIN);
        this->serial = serialConnection;
        this->implementation = implementation;
        // only do this on software serial

        this->rcvBuffer = "";
        this->sndBuffer = "";
        this->lastRecieveTime = 0;
        this->mode = IDLE;
    }

    Arduino2esp::~Arduino2esp()
    {
    }

    void Arduino2esp::init()
    {
        if (this->implementation == Software)
            ((SoftwareSerial *)this->serial)->begin(9600);

        if (this->implementation == Hardware)
            ((HardwareSerial *)this->serial)->begin(9600);
    }
    
    void Arduino2esp::run()
    {
        switch (this->mode)
        {
        case IDLE:

            if (this->serial->available())
            {
                this->mode = RECIEVING;
                this->rcv_data();
            }
            else if (this->serial->availableForWrite() > 0 && this->sndBuffer.length() > 0)
            {
                this->mode = SENDING;
                this->snd_data();
            }

            break;
        case SENDING:

            if (this->serial->availableForWrite() > 0 && this->sndBuffer.length() > 0)
                this->snd_data();
            else
                this->mode = IDLE;

            break;
        case RECIEVING:

            unsigned long currentTime = millis();

            if (this->lastRecieveTime + 10 < currentTime)
                this->rcv_data();
            else
                this->mode = IDLE;

            break;
        }
    }
    // recieve serial data strips newlines
    String Arduino2esp::recieve()
    {
        int nextNewlineLindex = this->rcvBuffer.indexOf('\n');
        if (nextNewlineLindex == -1)
            return "";

        String output = this->rcvBuffer.substring(0, nextNewlineLindex);
        this->rcvBuffer = this->rcvBuffer.substring(nextNewlineLindex + 1);
        return output;
    }
    // send serial data
    void Arduino2esp::send(String data)
    {
        this->rcvBuffer += data + '\n';
    }

    bool Arduino2esp::hasData()
    {
        return this->rcvBuffer.indexOf('\n') != -1;
    }

    SoftwareSerial ArduinoSerial(GPIO_NUM_33, GPIO_NUM_4);

    Arduino2esp ArduinoConnection = Arduino2esp(&ArduinoSerial, Software);

#pragma endregion
} // namespace SerialCommunication
