#pragma once

#define INTERFACE_MAGIC 0xDEADBEEF

// Maximum speed (units/s) and steering angle (degrees) for drive commands
#define MAX_SPEED 5
#define MAX_ANGLE 90

// Sensor data sent from car to watch
struct sensor_data {
    unsigned int magic;
    double lidar_distance;
    double pos_X;
    double pos_Y;
    double gyr_X;
    double gyr_Y;
    double gyr_Z;
    double ang_X;
    double ang_Y;
    double ang_Z;
};

// Drive command sent from watch to car
struct drive_data {
    unsigned int magic;
    double speed;   // [-MAX_SPEED, MAX_SPEED]
    double angle;   // [-MAX_ANGLE, MAX_ANGLE] degrees
};
