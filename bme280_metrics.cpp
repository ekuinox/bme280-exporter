#include <BME280.h>
#include "bme280_metrics.hpp"

constexpr auto TEMPERATURE_UNIT = BME280::TempUnit_Celsius;
constexpr auto PRESSURE_UNIT = BME280::PresUnit_hPa;

/// START TemperatureMetric
TemperatureMetric::TemperatureMetric(BME280 * bme280): bme280(bme280), value(NAN) {
}

void TemperatureMetric::update_metric() {
  const auto value = this->bme280->temp(TEMPERATURE_UNIT);
  this->value = value;
}

void TemperatureMetric::write_metric_name(Stream & stream) const {
  stream.print("temperature");
}

void TemperatureMetric::write_help_message(Stream & stream) const {
  stream.print("temperature by bme280");
}

void TemperatureMetric::write_type(Stream & stream) const {
  stream.print("gauge");
}

void TemperatureMetric::write_metric_value(Stream & stream) const {
  stream.print(this->value, DEC);
}

/// START HumidityMetric
HumidityMetric::HumidityMetric(BME280 * bme280): bme280(bme280), value(NAN) {
}

void HumidityMetric::update_metric() {
  const auto value = this->bme280->hum();
  this->value = value;
}

void HumidityMetric::write_metric_name(Stream & stream) const {
  stream.print("humidity");
}

void HumidityMetric::write_help_message(Stream & stream) const {
  stream.print("humidity by bme280");
}

void HumidityMetric::write_type(Stream & stream) const {
  stream.print("gauge");
}

void HumidityMetric::write_metric_value(Stream & stream) const {
  stream.print(this->value, DEC);
}

/// START PressureMetric
PressureMetric::PressureMetric(BME280 * bme280): bme280(bme280), value(NAN) {
}

void PressureMetric::update_metric() {
  const auto value = this->bme280->pres(PRESSURE_UNIT);
  this->value = value;
}

void PressureMetric::write_metric_name(Stream & stream) const {
  stream.print("pressure");
}

void PressureMetric::write_help_message(Stream & stream) const {
  stream.print("pressure by bme280");
}

void PressureMetric::write_type(Stream & stream) const {
  stream.print("gauge");
}

void PressureMetric::write_metric_value(Stream & stream) const {
  stream.print(this->value, DEC);
}
