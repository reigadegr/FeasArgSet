#include <fstream>
#include <unistd.h>
#include <vector>

#include "include/function.h"

#if 0
    基于shadow3aaa的版本，微调
    使用说明：直接接收getTopApp()函数的返回值即可获取包名
    例如：std::string TopApp = getTopApp();
#endif
/*
std::string execCmdSync(const std::string &command, const std::vector<std::string> &args) {
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
*/
auto execCmdSync(std::string command, const std::vector<std::string> &args) -> std::string {
    // 将命令和参数拼接为一个字符串
    for (const auto &arg : args) {
        command += " ";
        command += arg;
    }
    // 执行命令并获取输出
    FILE *pipe = popen(command.c_str(), "r");
    if (pipe == nullptr) {
        return {};
    }
    char buffer[2];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

auto Testfile(const char *location) { return access(location, F_OK) == 0; }
auto getTopApp() -> std::string {
    if (Testfile("/sys/kernel/gbe/gbe2_fg_pid")) {
        std::string pid;
        std::string name;
        std::ifstream f_pid("/sys/kernel/gbe/gbe2_fg_pid");
        if (!f_pid.is_open()) {
            return getTopAppShell();
        }
        f_pid >> pid;
        f_pid.close();

        std::ifstream app("/proc/" + pid + "/cmdline");

        if (!app.is_open()) {
            return getTopAppShell();
        }

        std::getline(app, name, '\0');
        app.close();

        return checkSymbol(name);
    }
    // LOG("SHELL");
    return getTopAppShell();
}

auto getTopAppShell() -> std::string {
    std::string name;
    const std::string str = execCmdSync("/system/bin/dumpsys", {"window", "visible-apps"});

    const auto pkgPos = str.find("package=") + 8;

    name = str.substr(pkgPos, str.find(' ', pkgPos) - pkgPos - 0);

    const auto first = name.find_first_not_of(' ');
    const auto last = name.find_last_not_of(' ');
    name = name.substr(first, last - first + 1);

    return checkSymbol(name);
}

auto checkSymbol(std::string &name) -> std::string {
    if (auto colonPos = name.find(':'); colonPos != std::string::npos) {
        // 截取冒号前边的部分
        name = name.substr(0, colonPos);
    }
    return name;
}
