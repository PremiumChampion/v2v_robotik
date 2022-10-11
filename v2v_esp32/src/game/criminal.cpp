namespace Game
{
    namespace Criminal
    {
        void init()
        {
#pragma region generate random position
    //Random number generator von 0-15
    //Wenn R.N. gleiche ist wie von Police -> workaround überlegen
#pragma endregion

#pragma region move to random position
    //Rufe die jeweiligen Methoden auf um zum Tile zu laufen
        //Wahrscheinlich im coordinator die Methode
#pragma endregion

#pragma region wait for police ready
    //Warte auf Signal, wenn der Barcode gelesen wurde, dass man an der Startposition angekommen ist
        //Arduino Broker
#pragma endregion

#pragma region start game
    //Start game -> setze ein FLag auf true
#pragma endregion
        }

        void run()
        {
#pragma region check for loss condition

#pragma region wait for police to tell you that you lost
    //Signal kommt von Police -> darauf hören
        //WiFi Broker
#pragma endregion
#pragma endregion

#pragma region if lost
    
#pragma region switch role
#pragma endregion
#pragma region set reinitgame flag
#pragma endregion

#pragma endregion

#pragma region game ongoing

#pragma region wait
#pragma endregion

#pragma endregion
        }
    } // namespace Criminal

} // namespace Game
