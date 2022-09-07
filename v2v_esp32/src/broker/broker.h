#include <Arduino.h>

#pragma once

namespace Broker
{
    /**
     * @brief aggregates all messages from sensors and is able to communicates those in a serialised way
     * used for exchanging sensor and actor values between esp32 and arduino
     * if a value is changed with set the new value will be transmitted as soon as posibile
     */
    template <class T>
    class Broker
    {
    private:
        T* messages;
        bool* pushed_message;
        bool has_changes;
        int message_count;
        T parse(String input);
        String serialise(T input);
    public:
        Broker(int message_count);
        ~Broker();
        /**
         * @brief updates the value of a specific sensor 
         * 
         * @param type the type to update
         * @param value the new value
         */
        void set(int type, T value);
        T get(int type);
        bool get_has_changes();
        String get_transmission_data();
        void rcv_transmission_data(String data);
    };

    static const char VALUE_DELIMITER = '|';
    static const char ENTRY_DELIMITER = '#';

} // namespace Broker
