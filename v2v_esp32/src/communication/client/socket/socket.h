#include <Arduino.h>
#include <WiFi.h>

#pragma once

namespace HHN_Client
{
    class Socket
    {
    private:
        WiFiClient client;
        // static Socket *currentClient;
        String rcvData; //
        boolean hasData;

    public:
        Socket();
        ~Socket();
        void send(String data);
        String rcv();
        Socket getSocket();
        void setClient(WiFiClient& client);
        void connectToIpAndPort(IPAddress ip, int port);
        boolean isClientConnected();
    };

} // namespace Client
