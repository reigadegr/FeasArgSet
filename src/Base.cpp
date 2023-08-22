#include "include/LockValue.h"
#include "include/function.h"
#include <fstream>
#include <sstream>
#include <thread>
// 把第一个节点的值写到另一个节点(lock_val方法)
bool Get1To2(std::string input, std::string output) {
    std::ifstream input_path(input);

    if (!input_path.is_open())
        return false;

    std::string value;
    // std::getline(input_path, value);
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
    // LOG(tmp," : ",secondArg);
}
void debugnode() {
    system("cat /sys/module/perfmgr_mtk/parameters/perfmgr_enable");
    system("echo -n \"pandora_fps: \" && cat /sys/module/perfmgr_mtk/parameters/fixed_target_fps");

    system("cat /sys/module/perfmgr_mtk/parameters/scaling_a");
    system("cat /sys/module/perfmgr_mtk/parameters/scaling_b");

    system("echo \"---------------------------------\"");

    system("cat /sys/module/mtk_fpsgo/parameters/perfmgr_enable");
    system("echo -n \"xiaomiFeas_fps: \" && cat /sys/module/mtk_fpsgo/parameters/fixed_target_fps");

    system("cat /sys/module/mtk_fpsgo/parameters/scaling_a");
    system("cat /sys/module/mtk_fpsgo/parameters/scaling_b");

    system("cat /sys/devices/system/cpu/cpufreq/policy0/scaling_governor");
    system("cat /sys/devices/system/cpu/cpufreq/policy4/scaling_governor");
    system("cat /sys/devices/system/cpu/cpufreq/policy7/scaling_governor");
}
bool matching_start(std::vector<listGame> gamesaver, std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package) {
    std::string TopApp = getTopApp();
    // LOG("前台包名: ",TopApp);

    // 包名与上次相同则直接返回，降低开销
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
            Allow_system_operation();
            // 调试debug
            // debugnode();
            return true;
        }
    }

    // LOG("失败匹配");

    LOG("检测到非列表应用: ", TopApp, "\n");
    Feas_off(&feaspath);

    recover_freq();
    set_gov(gov);
    // 调试debug
    // debugnode();
    return true;
}

void matchingThread(std::vector<listGame> gamesaver, std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package) {
    while (true) {
        matching_start(gamesaver, middle_big_core_in_game, feaspath, gov, now_package);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
void check_path(const struct FeasPath *p) {
    // check path
    std::vector<std::string> nodes = {p->Feas_switch, p->Fps, p->scaling_a, p->scaling_b};
    bool check = false;
    for (const auto &node : nodes) {
        if (access(node.c_str(), F_OK) == -1) {
            check = true;
            LOG("节点: ", node, "不存在");
            // return -1;
        }
    }
    if (check) {
        LOG("设置了不存在的节点");
        LOG("请检查: ");
        LOG("1,设备是否支持Feas功能");
        LOG("2,节点是否设置正确");
        LOG("进程已结束");
        exit(1);
    }
    // check down
}

std::string auto_define() {
    std::vector<std::string> nodes = {"/sys/module/perfmgr_mtk/parameters/perfmgr_enable",
                                      "/sys/module/bocchi_perfmgr/parameters/perfmgr_enable",
                                      "/sys/module/mtk_fpsgo/parameters/perfmgr_enable"};

    for (const auto &node : nodes) {
        if (access(node.c_str(), F_OK) == 0) {
            LOG("检测到节点: ", node, " 存在\n");
            return node;
        }
    }
    return "ReadFile";
}

bool write_struct(std::string switch_ctrl, struct FeasPath *p, const char *pathProfile) {

    if (switch_ctrl == "/sys/module/mtk_fpsgo/parameters/perfmgr_enable") {
        p->Feas_switch = "/sys/module/mtk_fpsgo/parameters/perfmgr_enable";
        p->Fps = "/sys/module/mtk_fpsgo/parameters/fixed_target_fps";
        p->scaling_a = "/sys/module/mtk_fpsgo/parameters/scaling_a";
        p->scaling_b = "/sys/module/mtk_fpsgo/parameters/scaling_b";
        return true;
    }

    if (switch_ctrl == "/sys/module/perfmgr_mtk/parameters/perfmgr_enable") {
        p->Feas_switch = "/sys/module/perfmgr_mtk/parameters/perfmgr_enable";
        p->Fps = "/sys/module/perfmgr_mtk/parameters/fixed_target_fps";
        p->scaling_a = "/sys/module/perfmgr_mtk/parameters/scaling_a";
        p->scaling_b = "/sys/module/perfmgr_mtk/parameters/scaling_b";
        return true;
    }

    if (switch_ctrl == "/sys/module/bocchi_perfmgr/parameters/perfmgr_enable") {
        p->Feas_switch = "/sys/module/bocchi_perfmgr/parameters/perfmgr_enable";
        p->Fps = "/sys/module/bocchi_perfmgr/parameters/fixed_target_fps";
        p->scaling_a = "/sys/module/bocchi_perfmgr/parameters/scaling_a";
        p->scaling_b = "/sys/module/bocchi_perfmgr/parameters/scaling_b";
        return true;
    }

    if (switch_ctrl == "ReadFile") {
        LOG("内置节点不存在，读取文件\n");
        // 实例化FeasPath的对象feaspath
        FeasPath feaspath;
        readPathProfile(pathProfile, &feaspath);
        check_path(&feaspath);
        return true;
    }

    return false;
}
