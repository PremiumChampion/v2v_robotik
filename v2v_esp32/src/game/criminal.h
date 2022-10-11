#pragma once
namespace Game
{
    namespace Criminal
    {
        enum INIT_STATE
        {
            GENERATING_POSITION,
            WAITING_FOR_CRIMINAL_MOVEMENT,
            WAITING_FOR_POLICE_MOVEMENT,
        };
        void init();
        void run();
    } // namespace Criminal

} // namespace Game
