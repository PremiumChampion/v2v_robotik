#include <Arduino.h>
#include <WiFi.h>

#define CHASER 0
#define CHASED 1

#define ROLE CHASED

char ssid[] = "ESP32";
char password[] = "12345678";

namespace WLAN
{
    // Is called on its own
    void setup()
    {
#if ROLE == CHASED
        WiFi.softAP(ssid, password); // Create accesspoint
#else
        WiFi.begin(ssid, password); // Connect to the accesspoint on chased-one
        Serial.println("Connecting to WiFi:");
        while (WiFi.status() != WL_CONNECTED) // Is the WiFi connection successful
        {
            delay(500); // Waiting for changeing connection state
            Serial.println(".");
        }
        Serial.println("\nWiFi connected!");
        WiFi.setAutoReconnect(true);
#endif
    }
} // namespace WLAN
