#include <gtest/gtest.h>
#include "../src/cooler.h"
#include <mutex>
#include <thread>

#define INIT_TEMP_VALUE (2.0)

TEST(CoolerTest, BasicTest)
{
    float starting_temperature = INIT_TEMP_VALUE;
    float temp_holder = INIT_TEMP_VALUE;
    float &temp_holder_r = temp_holder;
    std::mutex mtx;
    Cooler cooler;

    std::thread cooler_thread(&Cooler::turn_cooler_on, &cooler, std::ref(temp_holder_r), std::ref(mtx));
    sleep(1);
    EXPECT_EQ(starting_temperature, temp_holder);

    // Cooler decreases temperature for COOLER_POWER_C each COOLER_POWER_S
    cooler.start_cooling();
    sleep(COOLER_POWER_S);
    EXPECT_LT(temp_holder, starting_temperature);

    cooler.stop_cooling();
    cooler.turn_cooler_off();
    cooler_thread.join();
}
