#pragma once

#include "metrics.hpp"

class BME280;

/**
 * @brief 温度のメトリック
 */
struct TemperatureMetric : Metric {
  TemperatureMetric(BME280 * bme280);
  virtual void update_metric() override;
  virtual void write_metric_name(Stream & stream) const override;
  virtual void write_help_message(Stream & stream) const override;
  virtual void write_type(Stream & stream) const override;
  virtual void write_metric_value(Stream & stream) const override;

private:
  BME280 * bme280;
  float value;
};

/**
 * @brief 湿度のメトリック
 */
struct HumidityMetric : Metric {
  HumidityMetric(BME280 * bme280);
  virtual void update_metric() override;
  virtual void write_metric_name(Stream & stream) const override;
  virtual void write_help_message(Stream & stream) const override;
  virtual void write_type(Stream & stream) const override;
  virtual void write_metric_value(Stream & stream) const override;

private:
  BME280 * bme280;
  float value;
};

/**
 * @brief 温度のメトリック
 */
struct PressureMetric : Metric {
  PressureMetric(BME280 * bme280);
  virtual void update_metric() override;
  virtual void write_metric_name(Stream & stream) const override;
  virtual void write_help_message(Stream & stream) const override;
  virtual void write_type(Stream & stream) const override;
  virtual void write_metric_value(Stream & stream) const override;

private:
  BME280 * bme280;
  float value;
};
