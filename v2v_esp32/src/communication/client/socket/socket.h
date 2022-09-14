#include <Arduino.h>
#include <WiFi.h>

#pragma once

namespace HHN_Client
{
    class Socket
    {
    private:
        WiFiClient client;
        static Socket *currentClient;
        String rcvData; // kjsdhfksdjhfsd\naskdjhaskjdh
        boolean hasData;

    public:
        Socket(WiFiClient client);
        ~Socket();
        void send(String data);
        String rcv();
        void run();
        Socket getSocket();
    };

} // namespace Client
