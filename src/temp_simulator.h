#pragma once

#include <unistd.h>

#include <iostream>

#include <mutex>

#include "temp_sensor.h"

using namespace std;

class TemperatureSimulator {
  private: bool temp_is_rising = true;
  float * global_temp_pointer;
  TemperatureSensor sensor;
  public: TemperatureSimulator(float * temp, std::mutex & temp_mtx);
  float start_temp_simulator(float min_temp, float max_temp, float rising_delta, float falling_delta,
    float rising_step_s, float falling_step_s, std::mutex & temp_mtx);
};