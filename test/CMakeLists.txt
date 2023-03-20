

cmake_minimum_required(VERSION 3.22.1)

set(This unitTesting)

set(Sources
    sensor_test.cpp
    heater_test.cpp
    cooler_test.cpp
    )

add_executable(
  ${This} ${Sources}
)

target_link_libraries(${This} PUBLIC
  GTest::gtest_main
  temperature_regulator
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
