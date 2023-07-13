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
static void lock_val(T value, const std::string &path) {

    if (access(path.c_str(), F_OK) == -1)
        return;

    umount(path.c_str());

    // check value
    std::ifstream test(path);
    if (test.is_open()) {
        T temp;
        test >> temp;
        test.close();

        if (temp == value) {
            return;
        }
    }
    // check done

    // chown(path.c_str(), 0, 0);
    chmod(path.c_str(), 0666);
    // target_file:path 对象

    std::ofstream target_file(path, std::ios::out | std::ios::trunc);
    if (!target_file.is_open()) {
        std::cerr << "Error opening file for writing: " << path << std::endl;
        return;
    }

    target_file << value;
    target_file.close();

    chmod(path.c_str(), 0444);

    // mask value
    /*
    const std::string mask_dir = "/data/local/tmp";
    const std::string mount_mask_file = mask_dir + "/mount_mask_" +
    std::to_string(value);

    std::ofstream maskfile(mount_mask_file);
    maskfile << value;
    maskfile.close();


    mount(mount_mask_file.c_str(), path.c_str(), "", MS_BIND, "");

    remove(mount_mask_file.c_str());

    */
}
