
cmake_minimum_required(VERSION 3.22.1)

set(This temperature_regulator)

project(${This})

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/28219b169c62f110f7b85810b60bfdd4eedea9ef.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Sources
    src/main.cpp
    src/cooler.cpp
    src/heater.cpp
    src/temp_simulator.cpp
    src/temp_regulator.cpp
    src/temp_sensor.cpp
)

set(Headers
    ${PROJECT_SOURCE_DIR}/src/cooler.h
    ${PROJECT_SOURCE_DIR}/src/heater.h
    ${PROJECT_SOURCE_DIR}/src/temp_simulator.h
    ${PROJECT_SOURCE_DIR}/src/temp_regulator.h
    ${PROJECT_SOURCE_DIR}/src/temp_sensor.h
)

add_executable(${PROJECT_NAME}_exe ${Sources} ${Headers})
add_library(${This} STATIC ${Sources} ${Headers})
add_subdirectory(test)
