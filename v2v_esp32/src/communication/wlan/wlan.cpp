#include <Arduino.h>
#include <WiFi.h>

char ssid[] = "ESP32";
char password[] = "12345678";

namespace WLAN
{
    void setupAP()
    {
        WiFi.softAP(ssid, password); // Create accesspoint
    }

    void setupClient()
    {
        Serial.println("setupClient");
        WiFi.begin(ssid, password); // Connect to the accesspoint
        Serial.println("Connecting to WiFi:");
        while (WiFi.status() != WL_CONNECTED) // Is the WiFi connection successful
        {
            delay(100); // Waiting for changeing connection state
            Serial.println(".");
        }
        Serial.println("\nWiFi connected!");
        WiFi.setAutoReconnect(true);
    }
} // namespace WLAN
