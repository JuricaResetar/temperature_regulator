### README.md

## How to build the project
Run the following commands in the root directory:
`mkdir build`

`cmake -S . -B build`

`cd build`

`make`

## How to run the program
Navigate to the build folder and execute:
`./temperature_regulator_exe`

## How to execute unit test cases
Navigate to the `build/test` folder and execute:
`./unitTesting`

## How to use the program
Here is a list of parameters that could be modified:
- MIN_TEMP_FOR_REGULATOR
    - Defines lower temperature threshold for the regulator. The temperature should not go below that number (if the heater is powerful enough)
- MAX_TEMP_FOR_REGULATOR
    - Defines higher temperature threshold for the regulator. The temperature should not go above that number (if the cooler is powerful enough)
- MIN_TEMP_FOR_SIMULATOR
    - Defines the minimal temperature for the external temperature source simulator
- MAX_TEMP_FOR_SIMULATOR
    - Defines the maximum temperature for the external temperature source simulator
- RISING_DELTA_FOR_SIMULATOR
    - Defines rising increment of temperature for the external temperature source simulator
- FALLING_DELTA_FOR_SIMULATOR
    - Defines falling increment of temperature for the external temperature source simulator
- RISING_STEP_FOR_SIMULATOR_S
    - Defines delay between two rising increments of temperature for external temperature source simulator
- FALLING_STEP_FOR_SIMULATOR_S
    - Defines delay between two falling increments of temperature for external temperature source simulator
