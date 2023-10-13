#ifndef CHECK_H
#define CHECK_H

#include <fstream>
#include <unistd.h>

#include "function.h"

template <typename T>
static void check_val(T value, const std::string &path) {

    if (access(path.c_str(), F_OK) == -1) {
        return;
    }

    // umount(path.c_str());

    // check value
    std::ifstream test(path);
    if (test.is_open()) {
        T temp;
        test >> temp;
        test.close();

        if (temp == value) {
            return;
        }
        LOG(path, ": 值不正确");
        LOG("正确值为: ", value, " 当前值为: ", temp);
    }
    // check done
}

#endif
