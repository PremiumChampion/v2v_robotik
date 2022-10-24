#pragma once
namespace Game
{
    enum GameState {
        INITIALISING,
        RUNNING,
    };
    // CHASED or CHASER !
    void setCurrentRole(int newRole);
    int getCurrentRole();
    void setGameState(GameState newGameState);
    GameState getGameState();


    void run();
} // namespace Game
