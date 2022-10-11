#pragma once
namespace Game
{
    enum GameState {
        INITIALISING,
        RUNNING,
    };
    
    void setCurrentRole(int newRole);
    int getCurrentRole();
    void setGameState(GameState newGameState);
    GameState getGameState();


    void run();
    void init();
} // namespace Game
