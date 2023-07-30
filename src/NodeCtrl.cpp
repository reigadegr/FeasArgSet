#include "include/LockValue.h"
#include "include/NodePermission.h"
#include "include/function.h"
void Feas_on(unsigned int fps, int scaling_a, int scaling_b, std::string Feas_switch, std::string fps_path,
             std::string scaling_a_path, std::string scaling_b_path) {
    lock_val(1, Feas_switch);
    lock_val(fps, fps_path);
    lock_val(scaling_a, scaling_a_path);
    lock_val(scaling_b, scaling_b_path);
}

void Feas_off(std::string Feas_switch, std::string fps_path, std::string scaling_a_path, std::string scaling_b_path) {
    lock_val(0, Feas_switch);
    lock_val(0, fps_path);
    lock_val(0, scaling_a_path);
    lock_val(0, scaling_b_path);
}

void init_gov(std::string &gov) {
    for (int i = 0; i <= 7; i++) {
        lock_val(gov, "/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_governor");
    }
}
void set_middle_big_gov(std::string gov) {
    for (int i = 3; i <= 7; i++) {
        lock_val(gov, "/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_governor");
    }
}
void Allow_system_operation() {
    for (int i = 0; i <= 7; i++) {
        Permission_unlock("/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_max_freq");
    }
}
// Recover the scaling_max_freq and scaling_min_freq from cpu_info_max_freq and cpu_info_min_freq
void recover_freq() {
    for (int i = 0; i <= 7; i++) {
        Get1To2("/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/cpuinfo_max_freq",
                "/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_max_freq");
        Get1To2("/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/cpuinfo_min_freq",
                "/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_min_freq");
    }
}
