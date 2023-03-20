#include <mutex>

#include "temp_regulator.h"

#include "temp_sensor.h"

#define REGULATOR_STEP_S(1)

using namespace std;

TemperatureRegulator::TemperatureRegulator(float * global_temp_pointer, float min_set_temp, float max_set_temp) {
  _global_temp_pointer = global_temp_pointer;
  _max_set_temp = max_set_temp;
  _min_set_temp = min_set_temp;
}
int TemperatureRegulator::run(std::mutex & temp_mtx) {
  float & global_temp_pointer_r = * _global_temp_pointer;
  std::thread cooler_thread( & Cooler::turn_cooler_on, & cooler, std::ref(global_temp_pointer_r), std::ref(temp_mtx));
  std::thread heater_thread( & Heater::turn_heater_on, & heater, std::ref(global_temp_pointer_r), std::ref(temp_mtx));
  regulator_state = ON;

  while (1) {
    if (sensor.get_temp() >= _max_set_temp) {
      // Temp is to high
      if (!cooler.get_cooling_state()) {
        cooler.start_cooling();
      }
      if (heater.get_heating_state()) {
        heater.stop_heating();
      }
    } else if (sensor.get_temp() <= _min_set_temp) {
      // Temp is to low
      if (cooler.get_cooling_state()) {
        cooler.stop_cooling();
      }
      if (!heater.get_heating_state()) {
        heater.start_heating();
      }
    }
    cout << "Current temperature: " << sensor.get_temp() << endl;
    sleep(REGULATOR_STEP_S);
  }
  return 0;
}