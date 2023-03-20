#pragma once

#include <iostream>

#include <unistd.h>

#include <thread>

#include <mutex>

#define ON true
#define OFF false
#define COOLER_POWER_C(1.5)
#define COOLER_POWER_S(1)

class Cooler {
  private: bool cooler_state = OFF;
  bool cooling_state = OFF;
  int _start_cooling(float & current_temp, std::mutex & temp_mtx);

  public: Cooler();
  int turn_cooler_on(float & current_temp, std::mutex & temp_mtx);
  int turn_cooler_off();
  int start_cooling();
  int stop_cooling();
  int get_cooling_state();
};