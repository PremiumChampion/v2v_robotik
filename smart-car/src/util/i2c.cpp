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

    void init(i2cDefinition *i2c)
    {
        if (i2c->state == i2cState::NONE)
        {
            SlowSoftI2CMaster master = SlowSoftI2CMaster(i2c->SDA_pin, i2c->SCL_pin, true);
            i2c->master = &master;
            i2c->master->i2c_init();
            i2c->state = i2cState::INITIALISED;
        }
    }

    void run(i2cDefinition *i2c)
    {
        switch (i2c->state)
        {
        case NONE:
            // do nothing
            break;
        case INITIALISED:
            // check for data and start connection
            if (i2c->read_data_internal != nullptr || i2c->write_data_internal != nullptr)
            {
                I2C::start_internal(i2c);
            }
            break;
        case START_ERROR:
            // start failed
            // retry starting connection
            I2C::start_internal(i2c);
            break;
        case STARTED:
            // start successfull
            // start reading or wrinting by checking read_data_internal or write_data_internal
            if (i2c->read_data_internal != nullptr)
            {
                // read data
                i2c->state = i2cState::READING;
            }
            if (i2c->write_data_internal != nullptr)
            {
                // write data
                i2c->state = i2cState::WRITING;
            }
            break;
        case WRITING:
            // write additional bytes until length
            write_internal(i2c);
            break;
        case READING:
            // read additional bytes until length
            read_internal(i2c);
            break;
        case CLOSING:
            // close connection
            close_internal(i2c);
            break;
        }
    }

    void read(i2cDefinition *i2c, byte *buffer, unsigned int length)
    {
        ReadData read_data_internal = {
            .buffer = buffer,
            .length = length,
            .position = 0,
        };

        i2c->read_data_internal = &read_data_internal;
    }

    void write(i2cDefinition *i2c, byte *buffer, unsigned int length)
    {
        WriteData write_data_internal = {
            .buffer = buffer,
            .length = length,
            .position = 0,
        };

        i2c->write_data_internal = &write_data_internal;
    }

    void start_internal(i2cDefinition *i2c)
    {
        bool startresult = i2c->master->i2c_start(i2c->address);

        i2c->state = startresult ? i2cState::STARTED : i2cState::START_ERROR;
    }

    void read_internal(i2cDefinition *i2c)
    {
        bool should_read = i2c->read_data_internal->position < i2c->read_data_internal->length;
        bool read_last_byte = i2c->read_data_internal->position == i2c->read_data_internal->length - 1;

        if (should_read)
        {
            i2c->read_data_internal->buffer[i2c->read_data_internal->position] = i2c->master->i2c_read(read_last_byte);
            i2c->read_data_internal->position++;
            if (read_last_byte)
            {
                i2c->state = i2cState::CLOSING;
            }
        }
    }

    void write_internal(i2cDefinition *i2c)
    {
        bool should_write = i2c->write_data_internal->position < i2c->write_data_internal->length;
        bool write_last_byte = i2c->write_data_internal->position == i2c->write_data_internal->length - 1;

        if (should_write)
        {
            i2c->master->i2c_write(i2c->write_data_internal->buffer[i2c->write_data_internal->position]);
            if (write_last_byte)
            {
                i2c->state = i2cState::CLOSING;
            }
        }
    }

    void close_internal(i2cDefinition *i2c)
    {
        i2c->master->i2c_stop();
        i2c->state = i2cState::INITIALISED;
    }

} // namespace I2C
