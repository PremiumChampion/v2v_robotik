#include "broker.h"

namespace Broker
{

    Broker::Broker(const int message_count)
    {
        this->message_count = message_count;

        this->messages = new int[message_count]{-1};
        this->pushed_message = new bool[message_count]{true};
        this->has_changes = false;
    }

    Broker::~Broker()
    {
    }

    int Broker::get(int vt)
    {
        return this->messages[vt];
    }

    void Broker::set(int vt, int value)
    {
        if (this->messages[vt] != value)
        {
            this->pushed_message[vt] = 0;
            this->messages[vt] = value;
            this->has_changes = true;
        }
    }

    String Broker::get_transmission_data()
    {
        String out_data = String("");
        for (int vt = 0; vt < this->message_count; vt++)
        {
            if (this->pushed_message[vt] == 0)
            {
                out_data += String(vt) + String(VALUE_DELIMITER) + String(this->messages[vt]) + String(ENTRY_DELIMITER);
                this->pushed_message[vt] = 1;
            }
        }
        this->has_changes = false;
        return out_data;
    }

    void Broker::rcv_transmission_data(String data)
    {
        unsigned int message_start_index = 0;
        while (message_start_index < data.length() - 1)
        {
            int message_end_index = data.indexOf(ENTRY_DELIMITER, message_start_index);
            String message = data.substring(message_start_index, message_end_index);

            message_start_index = message_end_index + 1;

            // type + VALUE_DELIMITER + value + ENTRY_DELIMITER

            unsigned int type_start_index = 0;
            unsigned int type_end_index = message.indexOf(VALUE_DELIMITER) - 1;

            unsigned int value_start_index = type_end_index + 1;
            unsigned int value_end_index = message.indexOf(ENTRY_DELIMITER) - 1;

            String type = message.substring(type_start_index, type_end_index);
            String value = message.substring(value_start_index, value_end_index);

            this->messages[type.toInt()] = value.toInt();
        }
    }

    bool Broker::get_has_changes()
    {
        return this->has_changes;
    }
} // namespace Broker
