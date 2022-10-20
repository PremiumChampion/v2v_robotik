#pragma once
namespace Game
{
    namespace Police
    {

        enum INIT_STATE{
            WAITING_FOR_CRIMINAL_READY,
            GENERATING_POSITION,
            WAITING_FOR_POLICE_MOVEMENT,
            WAITING_FOR_GAMESTART

        };

        void init();
        void run()
        {
#pragma check for win condition

#pragma endregion
        }
    } // namespace Police

} // namespace Game
