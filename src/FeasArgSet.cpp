#include "include/function.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>

int main(int argc, char *argv[]) {
    const char *profile = argv[1];
    const char *pathProfile = argv[2];
    // 创建FeasPath的对象feaspath
    FeasPath feaspath;
    // 获取feas节点

    // 实例化FeasPath的对象feaspath
    readPathProfile(pathProfile, feaspath.Feas_switch, feaspath.Fps, feaspath.scaling_a, feaspath.scaling_b);

    if (access(feaspath.Feas_switch.c_str(), F_OK) == -1) {
        LOG("节点不存在。请检查设备是否支持Feas功能，节点是否设置正确");
        LOG("进程已结束");
        return -1;
    }

    // 设置游戏默认中大核调速器(默认值)
    std::string middle_big_core_in_game = "performance";

    // 设置非游戏全局调速器(默认值)
    std::string gov = "schedutil";

    std::vector<listGame> gamesaver;

    // 读取包名列表
    bool ReadProfile = readProfile(profile, gamesaver, middle_big_core_in_game, gov);

    if (!ReadProfile) {
        LOG("读取文件失败，进程结束");
        return 1;
    }

    // 初始化governor和scaling_max freq
    init_gov(gov);
    recover_freq();
    LOG("运行中...");
    // 记录当前包名
    std::string now_package = "";
    /*
        std::thread t(matchingThread, gamesaver, std::ref(middle_big_core_in_game), std::ref(feaspath), std::ref(gov),
                      std::ref(now_package));

        t.join();
        */
    matchingThread(gamesaver, middle_big_core_in_game, feaspath, gov, now_package);
}
