#include <filesystem>

#include "include/function.h"

//  参数分别为: 目录名，目标文件名，裁剪的字符串
auto FindPerfmgrName(const std::string &dir, const std::string &str, const std::string &reduceStr) -> std::string {
    LOG("开始查找节点");
    for (const auto &entry : std::filesystem::recursive_directory_iterator(dir)) {
        std::string const path = entry.path().string();

        if (path.find(str) != std::string::npos) {
            //$1: 起始位置; $2: 裁剪的长度
            std::string PerfmgrName = path.substr(dir.size() + 1, path.find(reduceStr) - dir.size() - 1);
            LOG(PerfmgrName);
            LOG("查找成功");
            return PerfmgrName;
        }
    }
    LOG("查找失败");
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
    创建对象后进行地址传递以实例化
    参数说明:
    $1:搜索范围 $2:搜索的目标文件 $3:要开始裁剪字符串的标志(从第一个字符"/"开始裁剪)
    mk_node(FindPerfmgrName("/sys/module", "perfmgr_enable", "/parameters"), &feaspath);
#endif

void mk_node(const std::string &name, struct FeasPath *p) {
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
