#include <Arduino.h>
#include <WiFi.h>

char ssid[] = "ESP32";
char password[] = "12345678";

namespace WLAN
{
    void setup_AP()
    {
        WiFi.softAP(ssid, password); // Create accesspoint
    }

    void setup_Client()
    {
        WiFi.begin(ssid, password); // Connect to the accesspoint
        Serial.println("Connecting to WiFi:");
        while (WiFi.status() != WL_CONNECTED) // Is the WiFi connection successful
        {
            delay(500); // Waiting for changeing connection state
            Serial.println(".");
        }
        Serial.println("\nWiFi connected!");
        WiFi.setAutoReconnect(true);
    }
} // namespace WLAN
