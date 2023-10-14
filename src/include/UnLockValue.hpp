#pragma once
#include "LockValue.h"
#include "NodePermission.h"
template <typename T>
auto UnLock_val(T &value,const std::string &path){
    lock_val(value,path);
    Permission_unlock(value,path);
}