#include "temp_simulator.h"

#include "temp_sensor.h"

TemperatureSimulator::TemperatureSimulator(float * temp, std::mutex & temp_mtx) {
  temp_mtx.lock();
  global_temp_pointer = temp;
  temp_mtx.unlock();
}

float TemperatureSimulator::start_temp_simulator(float min_temp, float max_temp, float rising_delta,
  float falling_delta, float rising_step_s, float falling_step_s,
  std::mutex & temp_mtx) {
  while (1) {
    if (temp_is_rising) {
      temp_mtx.lock();
      * global_temp_pointer += rising_delta;
      temp_mtx.unlock();
      sleep(rising_step_s);
      if (sensor.get_temp() >= max_temp) {
        temp_is_rising = false;
      }
    } else if (!temp_is_rising) {
      temp_mtx.lock();
      * global_temp_pointer -= falling_delta;
      temp_mtx.unlock();
      sleep(falling_step_s);
      if (sensor.get_temp() <= min_temp) {
        temp_is_rising = true;
      }
    }
  }
}