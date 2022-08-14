#include <WiFi.h>
#define MAX_SOCKETS 8
#pragma once
namespace HHN
{

    class Socket
    {
    private:
        WiFiClient client;
        String payload;

    public:
        // create a dummy element for use in arrays
        Socket();
        Socket(WiFiClient client);
        boolean isConnected();
        void run();
        String getPayload();
        String remoteIP();
        void close();
        void send(String data);
        void sendln(String data);


        static Socket sockets[];
        static int NEXT_SOCKET_CLEAN_MS;
        static int ACTIVE_SOCKET_COUNT;

        static void run_sockets();
        static int getSocketCount();
        static void addSocket(WiFiClient client);
        static void cleanSockets();
    };

} // namespace HHNServer
