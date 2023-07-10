#include "include/function.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

std::string execCmdSync(const std::string &command,
                        const std::vector<std::string> &args) {
    // 将命令和参数拼接为一个字符串
    std::string cmdStr = command;
    for (const auto &arg : args) {
        cmdStr += " ";
        cmdStr += arg;
    }
    // 执行命令并获取输出
    FILE *pipe = popen(cmdStr.c_str(), "r");
    if (!pipe)
        return {};
    char buffer[256];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

std::string getTopApp() {
    auto Testfile = [](const char *location) {
        return access(location, F_OK) == 0;
    };
    std::string name;
    if (Testfile("/sys/kernel/gbe/gbe2_fg_pid")) {
        std::string pid;
        std::ifstream f_pid, app;
        f_pid.open("/sys/kernel/gbe/gbe2_fg_pid");
        if (!f_pid) {
            return getTopAppShell();
        }
        f_pid >> pid;
        f_pid.close();

        app.open("/proc/" + pid + "/cmdline");

        if (!app) {

            return getTopAppShell();
        }

        std::getline(app, name, '\0');
        app.close();

        if (name.find(":") != std::string::npos) {
            // 获取冒号的位置
            unsigned int colonPos = name.find(':');
            // 截取冒号前边的部分
            name = name.substr(0, colonPos);
        }
        return name;
    } else {
        return getTopAppShell();
    }
}
std::string getTopAppShell() {
    std::string name;
    const std::string str =
        execCmdSync("/system/bin/dumpsys", {"window", "visible-apps"});

    const auto pkgPos = str.find("package=") + 8;

    name = str.substr(pkgPos, str.find(' ', pkgPos) - pkgPos - 0);

    const auto first = name.find_first_not_of(" ");
    const auto last = name.find_last_not_of(" ");
    name = name.substr(first, last - first + 1);

    if (name.find(":") != std::string::npos) {
        // 获取冒号的位置
        unsigned int colonPos = name.find(':');
        // 截取冒号前边的部分
        name = name.substr(0, colonPos);
    }

    return name;
}