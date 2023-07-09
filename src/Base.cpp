#include "include/LockValue.h"
#include "include/function.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include <vector>
// #include "include/GameList.h"

// 把第一个节点的值写到另一个节点
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

bool matching_start(std::vector<listGame> gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package) {
    std::string FgApp = getTopApp();
    // LOG("前台包名: ",FgApp);

    // 包名与上次相同则直接返回，降低开销
    if (FgApp == now_package) {
        return true;
    }

    now_package = FgApp;

    // 打印包名
    for (const auto &game : gamesaver) {
        if (FgApp.find(game.name) != std::string::npos) {
            LOG("检测到列表游戏  : ", game.name);
            // 成功后把结构体内各个对象的值写入到指定路径
            //...
            Feas_on(game.fixed_target_fps, game.scaling_a, game.scaling_b,
                    feaspath.Feas_switch, feaspath.Fps, feaspath.scaling_a,
                    feaspath.scaling_b);
            // LOG("目标fps\n",game.fixed_target_fps,"\nscaling
            // a:\n",game.scaling_a,"\nscal_b:
            // \n",game.scaling_b,"\n开关路径:\n",feaspath.Feas_switch,"\nfps路径\n",feaspath.Fps,"\n",feaspath.scaling_a,"\n",
            // feaspath.scaling_b);
            set_middle_big_gov(middle_big_core_in_game);
            return true;
        }
    }

    // LOG("失败匹配");
    LOG("检测到非列表应用: ", FgApp);
    Feas_off(feaspath.Feas_switch, feaspath.Fps, feaspath.scaling_a,
             feaspath.scaling_b);
    recover_freq();
    init_gov(gov);

    return true;
}

void matchingThread(std::vector<listGame> gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package) {
    while (true) {
        matching_start(gamesaver, middle_big_core_in_game, feaspath, gov,
                       now_package);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}