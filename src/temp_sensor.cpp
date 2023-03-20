#include "temp_sensor.h"

TemperatureSensor::TemperatureSensor(float * current_temp, std::mutex & temp_mtx) {
  temp_mtx.lock();
  _global_temp_pointer = current_temp;
  temp_mtx.unlock();
}

TemperatureSensor::TemperatureSensor() {}

float TemperatureSensor::get_temp() {
  return * _global_temp_pointer;
}