#include <Arduino.h>

namespace LineTracking
{

    enum LineDirection
    {
        TURNING_LEFT = 0,
        TURNING_RIGHT = 1,
        STRAIGHT = 2,
        NO_LINE = 3
    };

    struct LineTrackingSensor
    {
        uint8_t pin_left;
        float pin_left_state;
        uint8_t pin_center;
        float pin_center_state;
        uint8_t pin_right;
        float pin_right_state;
        unsigned long last_meassurement_time_ms;
        unsigned long measurement_interval_ms;
        LineDirection direction;
    };

    void set_direction(LineTrackingSensor *sensor)
    {
        bool left = sensor->pin_left_state > 100 && sensor->pin_left_state < 600;
        bool center = sensor->pin_center_state > 100 && sensor->pin_center_state < 600;
        bool right = sensor->pin_right_state > 100 && sensor->pin_right_state < 600;

        if (left && !right)
        {
            sensor->direction = LineTracking::LineDirection::TURNING_LEFT;
            return;
        }

        if (!left && right)
        {
            sensor->direction = LineTracking::LineDirection::TURNING_RIGHT;
            return;
        }

        if (center)
        {
            sensor->direction = LineTracking::LineDirection::STRAIGHT;
            return;
        }

        sensor->direction = LineTracking::LineDirection::NO_LINE;
    }

    void init(LineTrackingSensor *sensor)
    {
        pinMode(sensor->pin_left, INPUT);
        pinMode(sensor->pin_center, INPUT);
        pinMode(sensor->pin_right, INPUT);
        sensor->pin_left_state = analogRead(sensor->pin_left);
        sensor->pin_center_state = analogRead(sensor->pin_center);
        sensor->pin_right_state = analogRead(sensor->pin_right);

        set_direction(sensor);
    }

    void run(LineTrackingSensor *sensor)
    {
        unsigned long time = millis();

        if (sensor->last_meassurement_time_ms + sensor->measurement_interval_ms < time)
        {
            // Serial.println("Reading analog");
            // Serial.println(analogRead(sensor->pin_left));

            sensor->pin_left_state = analogRead(sensor->pin_left);
            sensor->pin_center_state = analogRead(sensor->pin_center);
            sensor->pin_right_state = analogRead(sensor->pin_right);
            set_direction(sensor);
        }
    }

    String getDirectionString(LineTracking::LineDirection direction)
    {
        String result = String("");

        if (direction == LineTracking::LineDirection::TURNING_LEFT)
            result = String("TURNING_LEFT");
        if (direction == LineTracking::LineDirection::TURNING_RIGHT)
            result = String("TURNING_RIGHT");
        if (direction == LineTracking::LineDirection::STRAIGHT)
            result = String("STRAIGHT");
        if (direction == LineTracking::LineDirection::NO_LINE)
            result = String("NO_LINE");
        return result;
    }

    String toString(LineTrackingSensor *sensor)
    {
        String direction = String("");

        if (sensor->direction == LineTracking::LineDirection::TURNING_LEFT)
            direction = String("TURNING_LEFT");
        if (sensor->direction == LineTracking::LineDirection::TURNING_RIGHT)
            direction = String("TURNING_RIGHT");
        if (sensor->direction == LineTracking::LineDirection::STRAIGHT)
            direction = String("STRAIGHT");
        if (sensor->direction == LineTracking::LineDirection::NO_LINE)
            direction = String("NO_LINE");

        return String("direction: ") + direction + String("\n") +
               String("pin_left_state:") + String(sensor->pin_left_state) + String("\n") +
               String("pin_center_state:") + String(sensor->pin_center_state) + String("\n") +
               String("pin_right_state:") + String(sensor->pin_right_state) + String("\n");
    }

} // namespace LineTracking
