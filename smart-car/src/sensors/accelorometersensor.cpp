#include "util/i2c.h"

namespace Accelorometer
{

#define GY521_WAKEUP 0x00

#define RAD2DEGREES (180.0 / PI)
#define RAW2DPS_FACTOR (1.0 / 131.0)
#define RAW2G_FACTOR (1.0 / 16384.0)

    enum AccelorometerState
    {
        NONE,
        REQEST_START,

        WAITING,
    };

    struct AccelorometerDefinition
    {
        I2C::i2cDefinition i2c;
        // set to NONE
        AccelorometerState state;
    };

    void init(AccelorometerDefinition *sensor)
    {
        if (sensor->state == NONE)
        {
            I2C::init(&sensor->i2c);
            sensor->state = REQEST_START;
        }
    }
    void run(AccelorometerDefinition *sensor)
    {
        switch (sensor->state)
        {
        case NONE:
            // do nothing
            break;
        case REQEST_START:
            // start measurements
            break;
        case WAITING:
            // do nothing as callback will handle unsetting of state
            break;
        }
    }

    void write_callback(I2C::WriteData data)
    {
    }

    void start_request_internal(AccelorometerDefinition *sensor)
    {
    }
} // namespace Accelorometer
