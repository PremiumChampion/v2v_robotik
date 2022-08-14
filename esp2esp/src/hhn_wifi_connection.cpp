#include <WiFi.h>
#include <hhn_wifi_connection.h>

namespace HHN
{
#pragma region static

    WiFi_Connection WiFi_Connection::connection = HHN::WiFi_Connection(HHN::ConnectionType::AP, "device2device");
    WiFi_Connection *WiFi_Connection::getConnection()
    {
        return &WiFi_Connection::connection;
    }

#pragma endregion

    WiFi_Connection::~WiFi_Connection()
    {
    }

    WiFi_Connection::WiFi_Connection(HHN::ConnectionType type, char *SSID)
    {
        this->type = type;
        this->SSID = SSID;
        this->PASSPHRASE = NULL;
    }

    void WiFi_Connection::set_passphrase(char *PASSPHRASE)
    {
        this->PASSPHRASE = PASSPHRASE;
    }

    void WiFi_Connection::connect()
    {
        if (this->type == ConnectionType::AP)
        {
            WiFi.softAP(this->SSID, this->PASSPHRASE, 1, 0, MAX_CONNECTIONS);
        }
        if (this->type == ConnectionType::CLIENT)
        {
            WiFi.begin(this->SSID, this->PASSPHRASE);
            WiFi.setAutoReconnect(true);
        }
    }
    IPAddress WiFi_Connection::get_IP()
    {
        return WiFi.softAPIP();
    }

    bool WiFi_Connection::isConnected()
    {
        if (this->type == ConnectionType::AP)
        {
            return true;
        }
        if (this->type == ConnectionType::CLIENT)
        {
            return WiFi.status() == WL_CONNECTED;
        }
        return false;
    }

} // namespace HHN
