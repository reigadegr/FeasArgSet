#pragma once
#include "function.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

template <typename T>
static void check_val(T value, const std::string &path) {

    if (access(path.c_str(), F_OK) == -1)
        return;

    // umount(path.c_str());

    // check value
    std::ifstream test(path);
    if (test.is_open()) {
        T temp;
        test >> temp;
        test.close();

        if (temp == value) {
            return;
        } else {
            LOG(path, ": 值不正确");
            LOG("正确值为: ", value, " 当前值为: ", temp);
        }
    }
    // check done
}
