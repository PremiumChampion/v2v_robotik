#include <Arduino.h>

//Change to 1 or 0, depending on which esp is being flashed (chaser or chased one)
#define IS_ACCESSPOINT 0
namespace WLAN 
{
    //Is called on its own
    void setup()
    {
        String pass = "lsdkjhfslk";
        String name = "lsdkfhslfjd";

        //TODO: Implement if clause to check, if current esp is the access point
        // or just the client

        // if (schoud_be_a_access_point)
        // {
        //     WiFi.softAP(name.c_str(), password.c_str());
        // } else{
        //     WiFi.begin(this->SSID, this->PASSPHRASE);
        //     WiFi.setAutoReconnect(true);
        // }

        // entweder AccessPoint oder Connection
    }
} // namespace WLAN
