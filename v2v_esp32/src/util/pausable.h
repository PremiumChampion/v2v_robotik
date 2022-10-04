#pragma once
namespace Util
{
    class Pausable
    {
    private:
    protected:
        bool isPaused;

    public:
        Pausable();
        virtual void pause();
        virtual void resume();
    };
}