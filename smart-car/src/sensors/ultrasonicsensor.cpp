#include "Arduino.h"

namespace Ultrasonic
{

    enum PingState
    {
        IDLE,
        WAIT_FOR_BURST,
        WAIT_FOR_ECHO
    };

    struct UltrasonicSensor
    {
        unsigned long ping_start_us;
        unsigned long ping_end_us;
        unsigned long next_ping_us;
        PingState ping_state;
        unsigned long measure_intervall_us;
        int distance_cm;
        int trigger_pin;
        uint8_t trigger_pin_state;
        int echo_pin;
        uint8_t echo_pin_state;
    };

    void init(Ultrasonic::UltrasonicSensor *sensor)
    {
        pinMode(sensor->trigger_pin, OUTPUT);
        digitalWrite(sensor->trigger_pin, HIGH);
        pinMode(sensor->echo_pin, INPUT);
        sensor->echo_pin_state = digitalRead(sensor->echo_pin);
    }

    void run_measure(Ultrasonic::UltrasonicSensor *sensor)
    {
        unsigned long time = micros();

        if (sensor->ping_state)
        {
            uint8_t current_sensor_value = digitalRead(sensor->echo_pin);
            // Serial.println("run_measure");

            if (sensor->ping_state == PingState::WAIT_FOR_BURST && sensor->echo_pin_state == LOW && current_sensor_value == HIGH)
            {
                // falling flank indicates start measurement
                sensor->ping_start_us = time;
                sensor->ping_state = PingState::WAIT_FOR_ECHO;
            }

            if (sensor->ping_state == PingState::WAIT_FOR_ECHO && sensor->echo_pin_state == HIGH && current_sensor_value == LOW)
            {
                // rising flank indicates ending measurement

                sensor->ping_end_us = time;
                sensor->ping_state = PingState::IDLE;
                if (sensor->ping_end_us > sensor->ping_start_us)
                {
                    unsigned long flight_time_us = sensor->ping_end_us - sensor->ping_start_us;

                    // 343 meter/s
                    // 343 * 10^-3 m/ms // 343 millimeter/ms
                    // 343 * 10^-6 m/us // 343000 mikrometer/ms // 343 mikrometer/mikrosekunden

                    sensor->distance_cm = (int)((unsigned long)343 * flight_time_us / (unsigned long)10000) / 2;

                    // set next trigger timepoint
                    sensor->next_ping_us = time + sensor->measure_intervall_us;
                }
            }

            sensor->echo_pin_state = current_sensor_value;
        }
    }

    void run_invoke_trigger(Ultrasonic::UltrasonicSensor *sensor)
    {
        // fallende Flanke am Triggereingang (trigger_pin) für mindestens 10µs.

        // current time
        unsigned long time = micros();

        // check if next trigger time slot is reached
        if (sensor->ping_state == PingState::IDLE && sensor->next_ping_us < time)
        {
            // Serial.println("invoke_trigger");
            // invoke trigger
            digitalWrite(sensor->trigger_pin, LOW);
            sensor->trigger_pin_state = LOW;

            sensor->ping_state = PingState::WAIT_FOR_BURST;
        }
    }

    void run_reset_trigger(Ultrasonic::UltrasonicSensor *sensor)
    {
        // fallende Flanke am Triggereingang (trigger_pin) für mindestens 10µs.
        unsigned long time = micros();

        // reset trigger after 1000µs
        if (sensor->ping_start_us + 1000 < time && sensor->trigger_pin_state == LOW)
        {
            // Serial.println("reset_trigger");

            digitalWrite(sensor->trigger_pin, HIGH);
            sensor->trigger_pin_state = HIGH;
        }
    }

    void run(Ultrasonic::UltrasonicSensor *sensor)
    {
        run_measure(sensor);
        run_reset_trigger(sensor);
        run_invoke_trigger(sensor);
    }

    int get_distance(Ultrasonic::UltrasonicSensor *sensor)
    {
        return sensor->distance_cm;
    }

    String toString(Ultrasonic::UltrasonicSensor *sensor)
    {
        return String("distance_cm: ") + String(sensor->distance_cm) + String("\n") +
               String("ping_start:") + String(sensor->ping_start_us) + String("\n") +
               String("ping_end_us:") + String(sensor->ping_end_us) + String("\n") +
               String("next_ping_us:") + String(sensor->next_ping_us) + String("\n") +
               String("ping_state:") + (sensor->ping_state ? String("true") : String("false")) + String("\n") +
               String("echo_pin_state:") + (sensor->echo_pin_state == HIGH ? String("HIGH") : String("LOW")) + String("\n") +
               String("trigger_pin_state:") + (sensor->trigger_pin_state == HIGH ? String("HIGH") : String("LOW")) + String("\n");
    }
} // namespace Ultrasonic
