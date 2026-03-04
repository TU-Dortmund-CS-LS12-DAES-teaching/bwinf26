// GPIO pin definitions and BMA423 accelerometer setup for Watchy V2.0
#pragma once

#include <Wire.h>
#include "bma.h"

// Buttons
#define BTN_BOTTOM_LEFT  26
#define BTN_TOP_LEFT     25
#define BTN_BOTTOM_RIGHT  4
#define BTN_TOP_RIGHT    35

// E-paper display
#define DISPLAY_CS    5
#define DISPLAY_RES   9
#define DISPLAY_DC   10
#define DISPLAY_BUSY 19

extern BMA423 sensor;

// I2C read/write callbacks for the BMA423 library
uint16_t _readRegister(uint8_t address, uint8_t reg, uint8_t* data, uint16_t len) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)address, (uint8_t)len);
    uint8_t i = 0;
    while (Wire.available())
        data[i++] = Wire.read();
    return 0;
}

uint16_t _writeRegister(uint8_t address, uint8_t reg, uint8_t* data, uint16_t len) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data, len);
    return (0 != Wire.endTransmission());
}

// Init BMA423: 100Hz ODR, 2G range, continuous mode
void _bmaConfig() {
    Wire.begin(SDA, SCL);

    if (!sensor.begin(_readRegister, _writeRegister, delay))
        return;

    // Sampling config
    Acfg cfg;
    cfg.odr       = BMA4_OUTPUT_DATA_RATE_100HZ;
    cfg.range     = BMA4_ACCEL_RANGE_2G;
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;
    sensor.setAccelConfig(cfg);
    sensor.enableAccel();

    // Interrupt pin config
    struct bma4_int_pin_config pin_cfg;
    pin_cfg.edge_ctrl = BMA4_LEVEL_TRIGGER;
    pin_cfg.lvl       = BMA4_ACTIVE_HIGH;
    pin_cfg.od        = BMA4_PUSH_PULL;
    pin_cfg.output_en = BMA4_OUTPUT_ENABLE;
    pin_cfg.input_en  = BMA4_INPUT_DISABLE;
    sensor.setINTPinConfig(pin_cfg, BMA4_INTR1_MAP);

    // Remap axes to match Watchy V2.0 PCB orientation
    struct bma423_axes_remap remap;
    remap.x_axis      = 1;
    remap.x_axis_sign = 0xFF;
    remap.y_axis      = 0;
    remap.y_axis_sign = 0xFF;
    remap.z_axis      = 2;
    remap.z_axis_sign = 0xFF;
    sensor.setRemapAxes(&remap);

    // Enable motion features
    sensor.enableFeature(BMA423_STEP_CNTR, true);
    sensor.enableFeature(BMA423_TILT, true);
    sensor.enableFeature(BMA423_WAKEUP, true);
    sensor.resetStepCounter();
    sensor.enableStepCountInterrupt();
    sensor.enableTiltInterrupt();
    sensor.enableWakeupInterrupt();
}
