#include "routing.h"

namespace Service
{
    class Routing
    {
    private:
        /* data */
    public:
        Routing(/* args */);
        ~Routing();
    };
    
    Routing::Routing(/* args */)
    {
    }
    
    Routing::~Routing()
    {
    }

    int calculateRoute(){
        // get own current position
        int OwnPosition = getCurrentGridPos();
        // get other current position 
        int OtherPosition = getOtherCurrentGridPos();
        // calculate delta Position
        int deltaX = OtherPosition % 4 - OwnPosition % 4;
        int deltaY = OtherPosition / 4 - OwnPosition / 4;
        int r[] = {deltaX, deltaY};
         
        return r;
    }
    
} // namespace Service
