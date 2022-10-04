namespace Service{
    class Positioning
    {
        
        enum Direction{
            NORTH,
            SOUTH,
            EAST,
            WEST
        };
    private:
        int currentGridPos;
        Direction currentDirection;
    public:
        Positioning(/* args */);
        void findStartingPos();
        int getCurrentGridPos();
        Direction getCurrentDirection();
        void setNewGridPos(int newPos);
        void setNewGridDirection(Direction newDirection);
        int getCurrentPositionTile();
        Direction getCurrentPositionDirection();
        // Interne Methoden die die neue Position bestimmen aus den Informationen des Forwarding Services.
        // Werden hier die Positionen von beiden Robotern festgehalten?
        
    };
    
    extern Positioning THIS_ROBOT;
    extern Positioning OTHER_ROBOT;
    
}