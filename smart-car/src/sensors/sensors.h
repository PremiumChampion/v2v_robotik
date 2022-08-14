#include "ultrasonicsensor.h"
#include "linetrackingsensor.h"
namespace Sensors
{
    // get the raw data of the ultrasonic sensor
    Ultrasonic::UltrasonicSensor* get_ultrasonic_sensor();
    // get the distance measured by the ultrasonic sensor
    int get_ultrasonic_distance_cm();

    // get the raw data measured by the line tracking sensor
    LineTracking::LineTrackingSensor* get_line_tracking_sensor();
    // get the direction of the line measured by the line tracking sensor
    LineTracking::LineDirection get_line_direction();
    void init();
    void run();
}
