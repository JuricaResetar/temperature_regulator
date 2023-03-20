#include "heater.h"

using namespace std;

Heater::Heater() {}

int Heater::turn_heater_on(float & global_temp_r, std::mutex & temp_mtx) {
  cout << "Heater device turned on." << endl;
  heater_state = ON;
  _start_heating(global_temp_r, temp_mtx);
  return 0;
}

int Heater::turn_heater_off() {
  cout << "Heater device turned off." << endl;
  heater_state = OFF;
  return 0;
}

int Heater::start_heating() {
  heating_state = ON;
  cout << "Heating started." << endl;
  return 0;
}

int Heater::stop_heating() {
  heating_state = OFF;
  cout << "Heating stoped!" << endl;
  return 0;
}

int Heater::get_heating_state() {
  // Returns true if heating is active, false otherwise
  return heating_state;
}

int Heater::_start_heating(float & global_temp_r, std::mutex & temp_mtx) {
  while (heater_state) {
    if (heating_state) {
      global_temp_r += HEATER_POWER_C;
    }
    sleep(HEATER_POWER_S);
  }
  return 0;
}