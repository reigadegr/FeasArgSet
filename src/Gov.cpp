#include <iostream>
#include "include/LockValue.h"
//#include "include/function.h"
/*
bool Shell(const char *sh, std::string &result);

std::string getSoc(std::string &gov){
    std::string model;
    Shell("getprop ro.hardware",model);
    if( model != "qcom" )
    {
        gov = "schedutil";
    }
    else
    {
        gov = "walt";
    }
    return model;
}
*/

void init_gov(std::string &gov){
    for(int i = 0; i <= 7; i++){
        lock_val(gov,"/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_governor");
    }
}
void set_middle_big_gov(std::string gov){
    for(int i = 3; i <= 7; i++){
        lock_val(gov,"/sys/devices/system/cpu/cpufreq/policy" + std::to_string(i) + "/scaling_governor");
    }
}
