#include <Arduino.h>
#include <WiFi.h>
#include "socket.h"

namespace Client
{
    
        Socket::Socket(WiFiClient client){
           this->client = client;
           //TODO: set static client
        }
    
} // namespace Client
