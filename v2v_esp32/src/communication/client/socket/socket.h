#include <Arduino.h>
#include <WiFi.h>

namespace Client
{
    class Socket
    {
    private:
        WiFiClient client;
        static Socket *currentClient;
        String rcv; //kjsdhfksdjhfsd\naskdjhaskjdh
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
