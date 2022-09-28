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
        String rcvBuffer; //
        boolean hasData;

    public:
        Socket();
        ~Socket();
        void send(String data);
        void run();
		String receive();
        Socket getSocket();
        void setClient(WiFiClient& client);
        void connectToIpAndPort(IPAddress ip, int port);
        boolean isClientConnected();
        boolean hasClientData();
    };

} // namespace Client


