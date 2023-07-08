#include "include/function.h"
#include "include/LockValue.h"
void Feas_on(unsigned int fps,int scaling_a,int scaling_b,std::string Feas_switch,std::string fps_path,std::string scaling_a_path, std::string scaling_b_path){
    lock_val(1,Feas_switch);
    lock_val(fps,fps_path);
    lock_val(scaling_a,scaling_a_path);
    lock_val(scaling_b,scaling_b_path);
}

void Feas_off(std::string Feas_switch,std::string fps_path,std::string scaling_a_path, std::string scaling_b_path){
    lock_val(0,Feas_switch);
    lock_val(0,fps_path);
    lock_val(0,scaling_a_path);
    lock_val(0,scaling_b_path);
}