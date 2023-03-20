#include <gtest/gtest.h>
#include "../src/heater.h"
#include <mutex>
#include <thread>

#define INIT_TEMP_VALUE (2.0)

TEST(HeaterTest, BasicTest)
{
    float starting_temperature = INIT_TEMP_VALUE;
    float temp_holder = INIT_TEMP_VALUE;
    float &temp_holder_r = temp_holder;
    std::mutex mtx;
    Heater heater;

    std::thread heater_thread(&Heater::turn_heater_on, &heater, std::ref(temp_holder_r), std::ref(mtx));
    sleep(1);
    EXPECT_EQ(starting_temperature, temp_holder);

    // Heater increases temperature for HEATER_POWER_C each HEATER_POWER_S
    heater.start_heating();
    sleep(HEATER_POWER_S);
    EXPECT_GT(temp_holder, starting_temperature);

    heater.stop_heating();
    heater.turn_heater_off();
    heater_thread.join();
}
