#include "pausable.h"

namespace Util
{
    Pausable::Pausable()
    {
        this->isPaused = false;
    }
    void Pausable::pause()
    {
        this->isPaused = true;
    }
    void Pausable::resume()
    {
        this->isPaused = false;
    }
} // namespace Util
