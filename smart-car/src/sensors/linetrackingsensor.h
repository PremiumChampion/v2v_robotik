#include <Arduino.h>

namespace LineTracking
{
    enum LineDirection
    {
        TURNING_LEFT = 0,
        TURNING_RIGHT = 1,
        STRAIGHT = 2,
        NO_LINE = 3,
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

    void init(LineTrackingSensor *sensor);
    void run(LineTrackingSensor *sensor);
    String getDirectionString(LineTracking::LineDirection direction);
    String toString(LineTrackingSensor *sensor);
} // namespace LineTracking
