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

    void init()
    {
#pragma region wait for sync
#pragma endregion

#pragma region whoami police or criminal
        if (currentRole == CHASED)
        {
#pragma region wait for police to position
#pragma endregion
#pragma region position self
            Criminal::init();
#pragma endregion
#pragma region tell police to catch
#pragma endregion
        }
        if (currentRole == CHASER)
        {
#pragma region position self
            Police::init();
#pragma endregion
#pragma region wait for criminal to position
#pragma endregion
#pragma wait for catch signal
#pragma endregion
        }

#pragma endregion
    }
    void run()
    {
        if (currentGameState == INITIALISING)
        {
            
        }
        if (currentGameState == RUNNING)
        {
#pragma region should i run or chase the other one
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
