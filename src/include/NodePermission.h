#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

static void Permission_unlock(const std::string &path) {

    if (access(path.c_str(), F_OK) == -1)
        return;

    chmod(path.c_str(), 0666);
    return;
}
