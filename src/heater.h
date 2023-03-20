#pragma once

#include <iostream>

#include <unistd.h>

#include <thread>

#include <mutex>

#define ON true
#define OFF false
#define HEATER_POWER_C(0.5)
#define HEATER_POWER_S(1)

class Heater {
  private: bool heater_state = OFF;
  bool heating_state = OFF;
  int _start_heating(float & current_temp, std::mutex & temp_mtx);

  public: Heater();
  int turn_heater_on(float & current_temp, std::mutex & temp_mtx);
  int turn_heater_off();
  int start_heating();
  int stop_heating();
  int get_heating_state();
};