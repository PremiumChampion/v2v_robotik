#include <Arduino.h>
#include <SlowSoftI2CMaster.h>

namespace I2C
{
    enum i2cState
    {
        NONE,
        INITIALISED,
        STARTED,
        START_ERROR,
        WRITING,
        READING,
        CLOSING,
    };

    struct ReadData
    {
        byte *buffer;
        unsigned int length;
        unsigned int position;
    };

    struct WriteData
    {
        byte *buffer;
        unsigned int length;
        unsigned int position;
    };

    struct i2cDefinition
    {
        uint8_t SDA_pin;
        uint8_t SCL_pin;
        // set to NONE
        i2cState state;
        // address of the i2c device
        uint8_t address;
        // set to nullptr
        SlowSoftI2CMaster *master;
        // set to nullptr
        ReadData *read_data_internal;
        // set to nullptr
        WriteData *write_data_internal;
    };

    void init(i2cDefinition *i2c);

    void run(i2cDefinition *i2c);

    void read(i2cDefinition *i2c, byte *buffer, unsigned int length);

    void write(i2cDefinition *i2c, byte *buffer, unsigned int length);

} // namespace I2C
