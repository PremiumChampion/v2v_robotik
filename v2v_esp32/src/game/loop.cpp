#include "loop.h"
#include "criminal.h"
#include "police.h"
#include "communication/communication.h"

namespace Game
{
    int currentRole = ROLE;

    void setCurrentRole(int newRole)
    {
        currentRole = newRole;
    }
    int getCurrentRole()
    {
        return currentRole;
    }

    GameState currentGameState = INITIALISING;

    void setGameState(GameState newGameState)
    {
        currentGameState = newGameState;
    }
    GameState getGameState()
    {
        return currentGameState;
    }

    void run()
    {
        if (currentGameState == INITIALISING)
        {
#pragma region whoami police or criminal
            if (currentRole == CHASED)
            {
                Criminal::init();
            }
            if (currentRole == CHASER)
            {
                Police::init();
            }
#pragma endregion
        }

        if (currentGameState == RUNNING)
        {
#pragma region whoami police or criminal
            if (currentRole == CHASED)
            {
                Criminal::run();
            }
            if (currentRole == CHASER)
            {
                Police::run();
            }
#pragma endregion
        }
    }

} // namespace Game
