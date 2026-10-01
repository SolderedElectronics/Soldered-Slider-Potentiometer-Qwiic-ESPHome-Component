/**
 * @file soldered_slider_potentiometer.h
 * @brief Public API for the soldered_slider_potentiometer ESPHome component
 * @author Soldered Electronics
 *
 * Driver for the Soldered Slider Potentiometer with Qwiic (10k linear slider + ATtiny404), ported from the Soldered
 * Slider Potentiometer with easyC Arduino library. The ATtiny samples the slider wiper with its 10-bit ADC whenever
 * register 0 is selected and read, and returns the value as two little-endian bytes. This component reads it on every
 * update and publishes the raw value (0 - 1023) and/or the slider position in percent.
 */

#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace soldered_slider_potentiometer {

class SolderedSliderPotentiometer : public PollingComponent, public i2c::I2CDevice {
 public:
  void set_position_sensor(sensor::Sensor *position_sensor) { this->position_sensor_ = position_sensor; }
  void set_raw_sensor(sensor::Sensor *raw_sensor) { this->raw_sensor_ = raw_sensor; }

  void setup() override;
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  /// Read the 10-bit ADC value, selecting the register on its own transaction like the easyC Arduino library does
  bool read_raw_(uint16_t *raw);

  sensor::Sensor *position_sensor_{nullptr};
  sensor::Sensor *raw_sensor_{nullptr};
};

}  // namespace soldered_slider_potentiometer
}  // namespace esphome
