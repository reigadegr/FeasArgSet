#pragma once
#include <fstream>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>
template <typename T>
static void lock_val(const T &value, const char *path) {
    if (access(path, F_OK) != 0) [[unlikely]] {
        // LOG("Warning: ", path, " 不存在");
        return;
    }
    umount(path);

    // chown(TmpPath,0,0);
    chmod(path, 0666);

    std::ofstream target_file(path, std::ios::out | std::ios::trunc);
    if (!target_file.is_open()) {
        // std::cerr << "无法打开文件进行写操作: " << path << std::endl;
        return;
    }

    chmod(path, 0555);
}
