#include <gtest/gtest.h>

#include "../src/temp_sensor.h"

#include <mutex>


TEST(SensorTest, BasicTest) {
  float temp_holder = 2.3;
  std::mutex mtx;
  TemperatureSensor sensor( & temp_holder, mtx);
  float set_temperature = sensor.get_temp();
  EXPECT_EQ(set_temperature, temp_holder);
}