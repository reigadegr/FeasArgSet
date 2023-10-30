#pragma once

#include "function.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
template <typename T>
static void lock_val(T value, const std::string &path) {
    const char *TmpPath = path.c_str();
    /*
    if (access(TmpPath, F_OK) == -1) {
        return;
    }
    */
    if (!std::filesystem::exists(path)) {
        LOG("Warning: ", path, " 不存在");
        return;
    }

    std::system(("umount " + path).c_str());
    // check
    // value
    std::ifstream test(path);
    if (test.is_open()) {
        T temp;
        test >> temp;
        test.close();

        if (temp == value) {
            return;
        }
    }
    // check
    // done

    // chown(TmpPath,0,0);
    chmod(TmpPath, 0666);
    // target_file:path
    // 对象

    std::ofstream target_file(path, std::ios::out | std::ios::trunc);
    if (!target_file.is_open()) {
        std::cerr << "无法打开文件进行写操作: " << path << std::endl;
        return;
    }

    target_file << value;
    target_file.close();

    chmod(TmpPath, 0555);
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
