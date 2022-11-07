#pragma once
namespace Game
{
    namespace Criminal
    {
        enum INIT_STATE
        {
            RESETTING_WON_STATE,
            GENERATING_POSITION,
            WAITING_FOR_CRIMINAL_MOVEMENT,
            WAITING_FOR_POLICE_MOVEMENT,
            WAITING_FOR_GAMESTART
        };
        void init();
        void run();
    } // namespace Criminal

} // namespace Game
