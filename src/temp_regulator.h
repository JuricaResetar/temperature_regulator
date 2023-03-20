#pragma once

#include <iostream>
#include <mutex>
#include "cooler.h"
#include "heater.h"
#include "temp_sensor.h"

#define ON true
#define OFF false

class TemperatureRegulator{
    private:
        Heater heater;
        Cooler cooler;
        TemperatureSensor sensor;
        float _max_set_temp;
        float _min_set_temp;
        float *_global_temp_pointer;
        int regulator_state = 0;

    public:
        TemperatureRegulator(float *global_temp_pointer, float min_set_temp, float max_set_temp);
        int run(std::mutex &temp_mtx);
};
