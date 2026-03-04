// Watchy-specific tunable constants
#pragma once

// MAC addresses of the two rover cars
#define CAR1_MAC {0x7c, 0x2c, 0x67, 0x45, 0x46, 0x00}
#define CAR2_MAC {0x98, 0xa3, 0x16, 0x7e, 0x6f, 0x44}

// ESP-NOW WiFi channel (must match the car)
#define ESPNOW_CHANNEL 7

// Raw BMA423 value at 90-degree tilt (2G range)
#define ACCEL_FULL_TILT 1000

// Converts rover position units to map coords (0-100)
#define IMU_SCALING_FACTOR 0.03

// LiDAR obstacles closer than this (in map coords) are drawn
#define OBSTACLE_DISTANCE_THRESHOLD 20
#define MAX_OBSTACLES 50

// Map coords 0-100 → 200x200 pixel display
#define MAP_TO_DISPLAY_SCALE 2
#define CAR_TRIANGLE_SIZE    5
#define OBSTACLE_DOT_RADIUS  2

// Full e-paper refresh every N partial refreshes (avoids ghosting)
#define PARTIAL_REFRESH_LIMIT 60

#define ACCEL_TASK_INTERVAL_MS   100
#define MAP_REFRESH_INTERVAL_MS 1000

#define PRIORITY_ACCEL  4
#define PRIORITY_MAP    3
#define PRIORITY_SENSOR 2
#define TASK_STACK_SIZE 4096
