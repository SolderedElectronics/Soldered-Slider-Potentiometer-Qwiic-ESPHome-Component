/**
 * @file soldered_slider_potentiometer.cpp
 * @brief Implementation of the soldered_slider_potentiometer ESPHome component
 * @author Soldered Electronics
 */

#include "soldered_slider_potentiometer.h"

#include "esphome/core/log.h"

namespace esphome {
namespace soldered_slider_potentiometer {

static const char *const TAG = "soldered_slider_potentiometer";

static const uint8_t REG_ANALOG_READ = 0x00;

/// Full scale of the ATtiny's 10-bit analogRead()
static const uint16_t RAW_MAX = 1023;

void SolderedSliderPotentiometer::setup() {
  // There is no ID register; a plain reading checks the board answers
  uint16_t raw;
  if (!this->read_raw_(&raw)) {
    ESP_LOGE(TAG, "Board not responding");
    this->mark_failed();
  }
}

void SolderedSliderPotentiometer::update() {
  uint16_t raw;
  if (!this->read_raw_(&raw)) {
    ESP_LOGW(TAG, "Reading slider failed");
    this->status_set_warning();
    return;
  }
  this->status_clear_warning();

  if (raw > RAW_MAX)
    raw = RAW_MAX;
  float position = raw * 100.0f / RAW_MAX;
  ESP_LOGD(TAG, "raw=%u, position=%.1f%%", raw, position);

  if (this->raw_sensor_ != nullptr)
    this->raw_sensor_->publish_state(raw);
  if (this->position_sensor_ != nullptr)
    this->position_sensor_->publish_state(position);
}

void SolderedSliderPotentiometer::dump_config() {
  ESP_LOGCONFIG(TAG, "Soldered Slider Potentiometer:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
  }
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "Position", this->position_sensor_);
  LOG_SENSOR("  ", "Raw", this->raw_sensor_);
}

bool SolderedSliderPotentiometer::read_raw_(uint16_t *raw) {
  // Separate write and read transactions instead of a repeated start, matching the easyC Arduino library
  uint8_t reg = REG_ANALOG_READ;
  if (this->write(&reg, 1) != i2c::ERROR_OK)
    return false;
  uint8_t data[2];
  if (this->read(data, sizeof(data)) != i2c::ERROR_OK)
    return false;
  *raw = uint16_t(data[0]) | (uint16_t(data[1]) << 8);  // little-endian
  return true;
}

}  // namespace soldered_slider_potentiometer
}  // namespace esphome
