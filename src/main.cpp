#include <iostream>

#include <unistd.h>

#include <thread>

#include <mutex>

#include "heater.h"

#include "cooler.h"

#include "temp_simulator.h"

#include "temp_regulator.h"

#include "temp_sensor.h"

#define MIN_TEMP_FOR_REGULATOR(-10)
#define MAX_TEMP_FOR_REGULATOR(5)
#define MIN_TEMP_FOR_SIMULATOR(-11)
#define MAX_TEMP_FOR_SIMULATOR(10)
#define RISING_DELTA_FOR_SIMULATOR(1)
#define FALLING_DELTA_FOR_SIMULATOR(1)
#define RISING_STEP_FOR_SIMULATOR_S(1)
#define FALLING_STEP_FOR_SIMULATOR_S(1)

using namespace std;
std::mutex temperature_mtx;

int main() {
  float init_temp = 0;
  // Current temp is a shared variable that contains a current temperature value
  float current_temp = init_temp;
  TemperatureSensor sensor {
    & current_temp, std::ref(temperature_mtx)
  };
  TemperatureSimulator simulator {
    & current_temp, std::ref(temperature_mtx)
  };
  TemperatureRegulator regulator {
    & current_temp, MIN_TEMP_FOR_REGULATOR, MAX_TEMP_FOR_REGULATOR
  };

  std::thread simulator_t( & TemperatureSimulator::start_temp_simulator, & simulator,
    MIN_TEMP_FOR_SIMULATOR, MAX_TEMP_FOR_SIMULATOR, RISING_DELTA_FOR_SIMULATOR,
    FALLING_DELTA_FOR_SIMULATOR, RISING_STEP_FOR_SIMULATOR_S, FALLING_STEP_FOR_SIMULATOR_S,
    std::ref(temperature_mtx));
  regulator.run(std::ref(temperature_mtx));
  return 0;
}