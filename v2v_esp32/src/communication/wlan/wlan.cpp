#include <Arduino.h>
namespace WLAN
{
    void setup()
    {
        String pass = "lsdkjhfslk";
        String name = "lsdkfhslfjd";

        if (schoud_be_a_access_point)
        {
            WiFi.softAP(name.c_str(), password.c_str());
        } else{
            WiFi.begin(this->SSID, this->PASSPHRASE);
            WiFi.setAutoReconnect(true);
        }

        // entweder AccessPoint oder Connection
    }
} // namespace WLAN
