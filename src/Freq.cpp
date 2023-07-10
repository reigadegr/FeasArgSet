#include "include/function.h"
#include <fstream>
#include <iostream>
// Recover the scaling_max_freq from cpu_info_max_freq
void recover_freq() {
    for (int i = 0; i <= 7; i++) {
        Get1To2("/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) +
                    "/cpuinfo_max_freq",
                "/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) +
                    "/scaling_max_freq");
    }
}
