#pragma once

#include <mutex>

class TemperatureSensor {
  public: inline static float * _global_temp_pointer;
  TemperatureSensor(float * current_temp, std::mutex & temp_mtx);
  TemperatureSensor();
  float get_temp();
};