#include "include/function.h"
#include <filesystem>
#include <fstream>
#include <iostream>

#define log(x) std::cout << x << std::endl;
// 参数分别为: 目录名，目标文件名，裁剪的字符串
std::string FindStr(std::string dir, std::string str, std::string reduceStr) {

    for (const auto &entry : std::filesystem::recursive_directory_iterator(dir)) {
        std::string path = entry.path().string();

        if (path.find(str) != std::string::npos) {

            //$1: 起始位置; $2: 裁剪的长度
            std::string moduleName = path.substr(dir.size() + 1, path.find(reduceStr) - dir.size() - 1);
            log(moduleName);
            return moduleName;
        }
    }
    return "UnSupport";
}

void mk_node(std::string name) {
    if (name == "UnSupport") {
        LOG("设备不支持Feas功能");
        exit(1);
    }
    std::vector<std::string> nodes = {"perfmgr_enable", "fixed_target_fps", "scaling_a", "scaling_b"};
    for (const auto &basename : nodes) {
        LOG("/sys/module/" + name + "/" + "parameters/" + basename);
    }
}

#if 0
    调用说明:
    mk_node(FindStr("/sys/module", "perfmgr_enable", "/parameters"));
#endif