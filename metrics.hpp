#pragma once

class Stream;

struct Metric {
  /**
   * @brief 一行にメトリックを書き込む
   */
  void write_metric(Stream & stream) const;

  /**
   * @brief メトリックを更新する
   */
  virtual void update_metric() = 0;

protected:
  /**
   * @brief メトリック名を Stream に出力する
   */
  virtual void write_metric_name(Stream & stream) const = 0;

  /**
   * @brief HELP メッセージをStream に出力する
   */
  virtual void write_help_message(Stream & stream) const = 0;

  /**
   * @brief TYPE を Stream に出力する
   */
  virtual void write_type(Stream & stream) const = 0;

  /**
   * @brief 値を出力する
   */
  virtual void write_metric_value(Stream & stream) const = 0;
};

/**
 * @brief ただ加算されていくだけのメトリック(サンプル)
 */
struct IncrementalMetric : Metric {
  virtual void update_metric() override;
  virtual void write_metric_name(Stream & stream) const override;
  virtual void write_help_message(Stream & stream) const override;
  virtual void write_type(Stream & stream) const override;
  virtual void write_metric_value(Stream & stream) const override;

private:
  uint32_t count { 0 };
};
