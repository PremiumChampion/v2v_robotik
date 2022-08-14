#include <WiFi.h>
#pragma once
namespace HHN
{
    const int MAX_CONNECTIONS = 8;

    enum ConnectionType
    {
        AP,
        CLIENT,
    };

    class WiFi_Connection
    {
    private:
        ConnectionType type;
        char *SSID;
        char *PASSPHRASE;
        static WiFi_Connection connection;

    public:
        WiFi_Connection(ConnectionType type, char *SSID);
        ~WiFi_Connection();
        void connect();
        bool isConnected();
        void set_passphrase(char *PASSPHRASE);
        IPAddress get_IP();
        static WiFi_Connection *getConnection();
    };

} // namespace HHN
