#include <Arduino.h>
#include "services/positioning.h"
#pragma once

namespace Service{
    class Forwarding
    {
    private:
        /* data */
    public:
        Forwarding(/* args */);
        ~Forwarding();
        Movement calculateNextMovement(Positioning* posObject, int nextTile);
    };
    
  

}