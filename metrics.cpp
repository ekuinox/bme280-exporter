#include <M5Atom.h>
#include "metrics.hpp"

void Metric::write_metric(Stream & stream) const {
  // write help line
  stream.print("# HELP ");
  this->write_metric_name(stream);
  stream.print(' ');
  this->write_help_message(stream);
  stream.print('\n');

  // write type line
  stream.print("# TYPE ");
  this->write_metric_name(stream);
  stream.print(' ');
  this->write_type(stream);
  stream.print('\n');

  // write metric
  this->write_metric_name(stream);
  stream.print(' ');
  this->write_metric_value(stream);
  stream.print('\n');
}

void IncrementalMetric::update_metric() {
  this->count += 1;
}

void IncrementalMetric::write_metric_name(Stream & stream) const {
  stream.print("incremental");
}

void IncrementalMetric::write_help_message(Stream & stream) const {
  stream.print("Incremental Metric Example");
}

void IncrementalMetric::write_type(Stream & stream) const {
  stream.print("counter");
}

void IncrementalMetric::write_metric_value(Stream & stream) const {
  stream.print(this->count, DEC);
}
