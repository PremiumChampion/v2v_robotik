#include <Arduino.h>
#include <WiFi.h>

#pragma once

namespace HHN_Client
{
    class Socket
    {
    private:
        WiFiClient client;
        static Socket *currentClient; //???
        String rcvData; // 
        boolean hasData;

    public:
        Socket(WiFiClient client);
        ~Socket();
        void send(String data);
        String rcv();
        void run();
        Socket getSocket();
};
extern HHN_Client::Socket chaserClient;
extern HHN_Client::Socket chased_oneClient;
} // namespace Client
