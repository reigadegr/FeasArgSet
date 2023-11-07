#include <sstream>
#include <thread>
#include <vector>

#include "include/LockValue.h"
#include "include/function.h"

// 把第一个节点的值写到另一个节点(lock_val方法)
auto Get1To2(const std::string &input, const std::string &output) -> bool {
    std::ifstream input_path(input);

    if (!input_path.is_open()) {
        return false;
    }

    std::string value;
    input_path >> value;
    input_path.close();

    lock_val(value, output);

    return true;
}
// 获取第二个参数
void GetSecondArg(std::string &buf, std::string &secondArg) {
    std::istringstream iss(buf);
    std::string tmp;
    iss >> tmp >> secondArg;
    // LOG(tmp,"
    // :
    // ",secondArg);
}
void debugnode() {
    system("cat /sys/module/mtk_fpsgo/parameters/perfmgr_enable");
    system("echo -n \"xiaomiFeas_fps: \" && cat "
           "/sys/module/mtk_fpsgo/parameters/fixed_target_fps");

    system("cat /sys/module/mtk_fpsgo/parameters/scaling_a");
    system("cat /sys/module/mtk_fpsgo/parameters/scaling_b");
    system("cat /sys/module/mtk_fpsgo/parameters/normal_frame_keep_count");
    system("cat /sys/module/mtk_fpsgo/parameters/min_freq_limit_level");
    system("cat /sys/module/mtk_fpsgo/parameters/max_freq_limit_level");
    system("ls -al /sys/devices/system/cpu/cpufreq/policy*/scaling_max_freq");
    // gov
    system("cat /sys/devices/system/cpu/cpufreq/policy0/scaling_governor");
    system("cat /sys/devices/system/cpu/cpufreq/policy4/scaling_governor");
    system("cat /sys/devices/system/cpu/cpufreq/policy7/scaling_governor");
    system("echo \"---------------------------------\"");
}
auto matching_start(std::vector<listGame> &gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package) -> bool {
    // 获取TopApp name
    std::string const TopApp = getTopApp();

    // 包名与上次相同则直接返回
    if (TopApp == now_package) {
        return true;
    }

    now_package = TopApp;

    LOG("时间: ", printCurrentTime());
    // 打印包名
    for (const auto &game : gamesaver) {
        if (TopApp.find(game.name) != std::string::npos) {
            LOG("检测到列表应用:   ", game.name, "\n");
            // 成功后把结构体内各个对象的值写入到指定路径
            //...
            Feas_on(&game, &feaspath);
            set_middle_big_gov(middle_big_core_in_game);
            // 解锁scaling_max_freq权限
            Allow_system_operation();
            // 调试debug
            // debugnode();
            return true;
        }
    }

    // LOG("失败匹配");

    LOG("检测到非列表应用: ", TopApp, "\n");
    Feas_off(&feaspath);

    set_gov(gov);
    recover_freq();

    // 调试debug
    // debugnode();
    return true;
}

void matchingThread(std::vector<listGame> &gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package) {
    while (true) {
        matching_start(gamesaver, middle_big_core_in_game, feaspath, gov,
                       now_package);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

auto check_path(const struct FeasPath *p) -> bool {
    // check
    // path
    std::vector<std::string> const nodes = {p->Feas_switch, p->Fps};
    for (const auto &node : nodes) {
        if (access(node.c_str(), F_OK) == -1) {
            LOG("你设置的节点: ", node, "不存在");
            return false;
        }
    }
    // check
    // down
    return true;
}

auto CheckArg(int &argc) -> bool {
    if (argc == 3) {
        return true;
    }
    if (argc < 3) {
        LOG("命令行参数个数有误，需要有", 3, "个\n", "当前为: ", argc, "个");
        return false;
    } else if (argc > 3) {
        LOG("Warning: 命令行参数过多，当前有", argc, "个");
    }
    return true;
}
