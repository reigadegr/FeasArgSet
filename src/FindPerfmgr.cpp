#include "include/function.h"
#include <filesystem>
#include <fstream>
#include <iostream>

#define log(x) std::cout << x << std::endl;
// 参数分别为: 目录名，目标文件名，裁剪的字符串

std::string FindStr(std::string dir, std::string str, std::string reduceStr) {
    LOG("开始查找节点");

    for (const auto &entry : std::filesystem::recursive_directory_iterator(dir)) {
        std::string path = entry.path().string();

        if (path.find(str) != std::string::npos) {

            //$1: 起始位置; $2: 裁剪的长度
            std::string moduleName = path.substr(dir.size() + 1, path.find(reduceStr) - dir.size() - 1);
            log(moduleName);
            log("查找成功");
            return moduleName;
        }
    }
    log("查找失败");
    return "UnSupport";
}

#if 0
    struct FeasPath {
        std::string Feas_switch;
        std::string Fps;
        std::string scaling_a;
        std::string scaling_b;
    };
    调用说明:
    FeasPath feaspath;
    实例化后进行地址传递
    mk_node(FindStr("/sys/module", "perfmgr_enable", "/parameters"), &feaspath);
#endif

void mk_node(std::string name, struct FeasPath *p) {
    if (name == "UnSupport") {
        LOG("设备不支持Feas功能");
        exit(1);
    }
    p->Feas_switch = "/sys/module/" + name + "/parameters/perfmgr_enable";
    p->Fps = "/sys/module/" + name + "/parameters/fixed_target_fps";
    p->scaling_a = "/sys/module/" + name + "/parameters/scaling_a";
    p->scaling_b = "/sys/module/" + name + "/parameters/scaling_b";
    LOG("以下是你的节点: ");
    LOG(p->Feas_switch);
    LOG(p->Fps);
    LOG(p->scaling_a);
    LOG(p->scaling_b);
}
