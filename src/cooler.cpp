#include <mutex>
#include "cooler.h"

using namespace std;

Cooler::Cooler(){
}

int Cooler::turn_cooler_on(float &global_temp_r, std::mutex &temp_mtx)
{
    cout << "Cooler device turned on." << endl;
    cooler_state = ON;
    _start_cooling(global_temp_r, temp_mtx);
    return 0;
}

int Cooler::turn_cooler_off()
{
    cooler_state = OFF;
    cout << "Cooler device turned off." << endl;
    return 0;
}

int Cooler::start_cooling()
{
    cooling_state = ON;
    cout << "Cooling started." << endl;
    return 0;
}

int Cooler::stop_cooling()
{
    cooling_state = OFF;
    cout << "Cooling stoped!" << endl;
    return 0;
}

int Cooler::get_cooling_state()
{
    // Returns true if cooling is active, false otherwise
    return cooling_state;
}

int Cooler::_start_cooling(float &global_temp_r, std::mutex &temp_mtx)
{
    while(cooler_state)
    {
        if(cooling_state)
        {
            temp_mtx.lock();
            global_temp_r -= COOLER_POWER_C;
            temp_mtx.unlock();
        }
        sleep(COOLER_POWER_S);
    }
    return 0;
}
