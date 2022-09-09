#include "actors/actors.h";
namespace Actors
{
    class HHN_V_Actor
    {
    protected:
        int currentValue;
        Actor actor;

    public:
        HHN_V_Actor(Actor actor);
        ~HHN_V_Actor();
        void set(int value);
    };
} // namespace Actors
