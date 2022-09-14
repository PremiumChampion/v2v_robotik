#include <Arduino.h>
#include "broker.h"

namespace Broker
{

    template <class T>
    Broker<T>::Broker(const int message_count)
    {
        this->message_count = message_count;

        this->messages = new T[message_count];
        this->pushed_message = new bool[message_count]{true};
        this->has_changes = false;
    }

    template <class T>
    Broker<T>::~Broker()
    {
    }

    template <class T>
    T Broker<T>::get(int type)
    {
        return this->messages[type];
    }

    template <class T>
    void Broker<T>::set(int type, T value)
    {
        if (this->messages[type] != value)
        {
            this->pushed_message[type] = 0;
            this->messages[type] = value;
            this->has_changes = true;
        }
    }
    template <class T>
    String Broker<T>::get_transmission_data()
    {
        String out_data = String("");
        for (int message = 0; message < this->message_count; message++)
        {
            if (this->pushed_message[message] == 0)
            {
                out_data += String(message) + String(VALUE_DELIMITER) + this->serialise(this->messages[message]) + String(ENTRY_DELIMITER);
                this->pushed_message[message] = 1;
            }
        }
        this->has_changes = false;
        return out_data;
    }

    template <class T>
    void Broker<T>::rcv_transmission_data(String data)
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
            this->messages[type.toInt()] = this->parse(message.substring(value_start_index, value_end_index));
        }
    }

    template <class T>
    bool Broker<T>::get_has_changes()
    {
        return this->has_changes;
    }

    template <>
    int Broker<int>::parse(String input)
    {
        return input.toInt();
    }

    template <>
    float Broker<float>::parse(String input)
    {
        return input.toFloat();
    }

    template <>
    String Broker<String>::parse(String input)
    {
        return input;
    }

    template <>
    String Broker<int>::serialise(int input)
    {
        return String(input);
    }

    template <>
    String Broker<float>::serialise(float input)
    {
        return String(input);
    }

    template <>
    String Broker<String>::serialise(String input)
    {
        return input;
    }

    template class Broker<int>;
    template class Broker<float>;
    template class Broker<String>;
} // namespace Broker
