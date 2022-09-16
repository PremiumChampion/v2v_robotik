#include <Arduino.h>
#include <WiFi.h>

//Change to 1 or 0, depending on which esp is being flashed (chaser or chased one)
#define IS_ACCESSPOINT 0

char ssid[] = "ESP32";
char password[] = "12345678";

namespace WLAN 
{
    //Is called on its own
    void setup()
    {

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

        if (IS_ACCESSPOINT) {
            WiFi.softAP(ssid, password); // Create accesspoint
        } else {
            WiFi.begin(ssid, password); // Connect to the accesspoint on chased-one
            Serial.println("Connecting to WiFi:");
            while (WiFi.status() != WL_CONNECTED) // Is the WiFi connection successful
            {
                delay(500); // Waiting for changeing connection state
                Serial.println(".");
            }
            Serial.println("\nWiFi connected!");
            WiFi.setAutoReconnect(true);
        }
    }
} // namespace WLAN
