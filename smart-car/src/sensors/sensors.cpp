#include <Arduino.h>
#include "sensors/ultrasonicsensor.h"
#include "jobs/jobs.h"
#include "sensors/linetrackingsensor.h"

namespace Sensors
{

#pragma region ultrasonic_sensor

    Ultrasonic::UltrasonicSensor ultrasonic_sensor = {
        .ping_start_us = 0,
        .ping_end_us = 0,
        .next_ping_us = 0,
        .ping_state = Ultrasonic::PingState::IDLE,
        .measure_intervall_us = 50000,
        .distance_cm = 0,
        .trigger_pin = 13,
        .trigger_pin_state = HIGH,
        .echo_pin = 12,
        .echo_pin_state = LOW,
    };

    Ultrasonic::UltrasonicSensor* get_ultrasonic_sensor()
    {
        return &ultrasonic_sensor;
    }
    
    int get_ultrasonic_distance_cm(){
        return ultrasonic_sensor.distance_cm;
    }
    void log_ultrasonic_sensor()
    {
        Serial.print("Ultrasonic-Sensor-Distance (cm): ");
        Serial.println(ultrasonic_sensor.distance_cm);
    }

#pragma endregion

#pragma region line_tracking_sensor

    LineTracking::LineTrackingSensor line_tracking_sensor = {
        .pin_left = 16,
        .pin_left_state = 0,
        .pin_center = 15,
        .pin_center_state = 0,
        .pin_right = 14,
        .pin_right_state = 0,
        .last_meassurement_time_ms = 0,
        .measurement_interval_ms = 50,
        .direction = LineTracking::LineDirection::NO_LINE,
    };

    void log_line_tracking_sensor()
    {
        Serial.print("Line Direction:");
        Serial.println(LineTracking::getDirectionString(line_tracking_sensor.direction));
    }

    LineTracking::LineTrackingSensor* get_line_tracking_sensor()
    {
        return &line_tracking_sensor;
    }

    LineTracking::LineDirection get_line_direction(){
        return line_tracking_sensor.direction;
    }

#pragma endregion

#pragma region logging
 
    void log_sensor_init()
    {
        Serial.begin(9600);
    }

    unsigned long last_execution_ms = 0;
    bool log_sensor_should_run()
    {
        unsigned long time = millis();
        bool should_run = last_execution_ms + 500 < time;
        if (should_run)
        {
            last_execution_ms = time;
        }
        return should_run;
    }

    void log_sensor_run()
    {
        // log_ultrasonic_sensor();
        log_line_tracking_sensor();
    }

    Jobs::JobDefinition sensor_log_action = {
        log_sensor_run,
        log_sensor_init,
        log_sensor_should_run,
    };

#pragma endregion
   
    void init()
    {
        Jobs::register_action(sensor_log_action);
        Ultrasonic::init(&ultrasonic_sensor);
        LineTracking::init(&line_tracking_sensor);
    }

    void run()
    {
        Ultrasonic::run(&ultrasonic_sensor);
        LineTracking::run(&line_tracking_sensor);
    }

}
