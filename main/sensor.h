// Sensor data processing: receives car data via queue, updates map
#pragma once

#include "interface.h"

void sensor_init();
void sensor_task(void* pvParameters);
void get_sensor_data_from_isr(struct sensor_data* data);

// Defined in main.cpp
void set_car_position(int x, int y, int angle);
void add_barrier(int x, int y, int angle);
