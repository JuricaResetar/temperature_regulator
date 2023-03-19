/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <unistd.h>
#include <thread>

#define ON true
#define OFF false

using namespace std;

class TemperatureSimulator{
    private:
        bool temp_is_rising = true;
        float *_simulated_temperature;
    public:
        TemperatureSimulator(float *temp)
        {
            _simulated_temperature = temp;
        }
        float start_temp_simulator(float min_temp, float max_temp, float rising_delta, float falling_delta, float rising_step_s, float falling_step_s)
        {
            while(1)
            {
                if (temp_is_rising)
                {
                    *_simulated_temperature += rising_delta;
                    sleep(rising_step_s);
                    if (*_simulated_temperature >= max_temp)
                    {
                        temp_is_rising = false;
                    }
                }
                else if (!temp_is_rising)
                {
                    *_simulated_temperature -= falling_delta;
                    sleep(falling_step_s);
                    if(*_simulated_temperature <= min_temp)
                    {
                        temp_is_rising = true;
                    }
                }
                std::cout << "Temp is: " << *_simulated_temperature << std::endl;
            }
        }
};

class TemperatureSensor{
    private:
        float current_temperture;

    public:
        TemperatureSensor(float initial_temperature) : current_temperture(initial_temperature)
        {}
        float get_temp(){
            return current_temperture;
        }
};

#define HEATER_POWER_C (0.5)
#define HEATER_POWER_S (1)
class Heater{
    private:
        bool heater_state = OFF;
        bool heating_state = OFF;
        int _start_heating(float &current_temp)
        {
            while(heater_state)
            {
                if(heating_state)
                {
                    current_temp  += HEATER_POWER_C;
                }
                sleep(HEATER_POWER_S);
            }
            return 0;
        }

    public:
        Heater(){};

        int turn_heater_on(float &current_temp)
        {
            cout << "Heater device turned on." << endl;
            heater_state = ON;
            _start_heating(current_temp);
            return 0;
        }

        int turn_heater_off()
        {
            cout << "Heater device turned off." << endl;
            return 0;
        }

        int start_heating()
        {
            heating_state = ON;
            cout << "Heating started." << endl;
            return 0;
        }

        int stop_heating()
        {
            heating_state = OFF;
            cout << "Heating stoped!" << endl;
            return 0;
        }
        
        int get_heating_state()
        {
            // Returns true if heating is active, false otherwise
            return heating_state;
        }
};

#define COOLER_POWER_C (1.0)
#define COOLER_POWER_S (1)
class Cooler{
    private:
        bool cooler_state = OFF;
        bool cooling_state = OFF;
        int _start_cooling(float &current_temp)
        {
            while(cooler_state)
            {
                if(cooling_state)
                {
                    current_temp  -= COOLER_POWER_C;
                }
                sleep(COOLER_POWER_S);
            }
            return 0;
        }

    public:
        Cooler(){};

        int turn_cooler_on(float &current_temp)
        {
            cout << "Cooler device turned on." << endl;
            cooler_state = ON;
            _start_cooling(current_temp);
            return 0;
        }

        int turn_cooler_off()
        {
            cout << "Cooler device turned off." << endl;
            return 0;
        }

        int start_cooling()
        {
            cooling_state = ON;
            cout << "Cooling started." << endl;
            return 0;
        }

        int stop_cooling()
        {
            cooling_state = OFF;
            cout << "Cooling stoped!" << endl;
            return 0;
        }
        
        int get_cooling_state()
        {
            // Returns true if cooling is active, false otherwise
            return cooling_state;
        }
};

class TemperatureRegulator{
    private:
        Heater heater;
        Cooler cooler;
        TemperatureSensor sensor{7}; // sensor bi se trebao predavati heateru i cooleru da oni znaju koja je temp
        float _max_set_temp;
        float _min_set_temp;
        float *_current_temp;

    public:
        TemperatureRegulator(float *current_temp, float min_set_temp, float max_set_temp){
             //current_temp_r = sensor.get_temp();
             _current_temp = current_temp;
             _max_set_temp = max_set_temp;
             _min_set_temp = min_set_temp;
            };
        int run()
        {
            float &current_temp_r = *_current_temp;
            std::thread cooler_thead(&Cooler::turn_cooler_on, &cooler, std::ref(current_temp_r));
            std::thread heater_thread(&Heater::turn_heater_on, &heater, std::ref(current_temp_r));
            while(1)
            {
                //cout << "Current:" << *_current_temp << ", min:" << _min_set_temp <<", max: " << _max_set_temp << endl;
                if (*_current_temp >= _max_set_temp)
                {
                    // Temp is to high
                    if(!cooler.get_cooling_state())
                    {
                        cooler.start_cooling();
                    }
                    if(heater.get_heating_state())
                    {
                        heater.stop_heating();
                    }
                }
                else if (*_current_temp <= _min_set_temp)
                {
                    // Temp is to low
                    if (cooler.get_cooling_state())
                    {
                        cooler.stop_cooling();
                    }
                    if (!heater.get_heating_state())
                    {
                        heater.start_heating();
                    }
                }
                cout << "Current temperature: " << *_current_temp << endl;
                sleep(1);
            }
        }
    
};


int main()
{
    float current_temp = 0;
    float &current_temp_r = current_temp;
    TemperatureSimulator simulator{&current_temp};
    TemperatureRegulator regulator{&current_temp, 0, 5};


    std::thread simulator_t(&TemperatureSimulator::start_temp_simulator, &simulator, 0, 5, 0.6, 0.6, 1, 1);
    regulator.run();
    return 0;
}
