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
    std::getline(input_path, value);
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
            /*
            system("cat /sys/module/perfmgr_mtk/parameters/perfmgr_enable");
            system("cat /sys/module/perfmgr_mtk/parameters/fixed_target_fps");
            system("cat /sys/module/perfmgr_mtk/parameters/scaling_a");
            system("cat /sys/module/perfmgr_mtk/parameters/scaling_b");
*/
            set_middle_big_gov(middle_big_core_in_game);
            Allow_system_operation();
            return true;
        }
    }

    // LOG("失败匹配");

    LOG("检测到非列表应用: ", TopApp, "\n");
    Feas_off(&feaspath);
    /*
        system("cat /sys/module/perfmgr_mtk/parameters/perfmgr_enable");
        system("cat /sys/module/perfmgr_mtk/parameters/fixed_target_fps");
        system("cat /sys/module/perfmgr_mtk/parameters/scaling_a");
        system("cat /sys/module/perfmgr_mtk/parameters/scaling_b");
    */
    recover_freq();
    set_gov(gov);

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
        LOG("设置了不存在的节点，请检查设备是否支持Feas功能，节点是否设置正确");
        LOG("进程已结束");
        exit(1);
    }
    // check down
}