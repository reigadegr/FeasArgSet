#include <iostream>
#include <fstream>
//#include "include/LockValue.h"
#include "include/function.h"
//recover scaling_max_freq from cpu_infoax_freq
void recover_freq(){
    for(int i = 0 ; i <= 7  ; i++)
    {
        Get1To2("/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/cpuinfo_max_freq","/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_max_freq");
    }
}
