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

    void init(Ultrasonic::UltrasonicSensor *sensor);
    void run(Ultrasonic::UltrasonicSensor *sensor);
    String toString(Ultrasonic::UltrasonicSensor *sensor);
} // namespace Ultrasonic