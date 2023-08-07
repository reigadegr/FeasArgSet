#include "include/GameList.h"
#include "include/function.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
bool readProfile(const char *profile, std::vector<listGame> &profit, std::string &middle_big_core_in_game,
                 std::string &global_gov) {
    std::ifstream file(profile);

    if (!file.is_open())
        return false;

    std::string buf;

    while (std::getline(file, buf)) {
        if (!buf.empty()) {
            if (buf[0] == '$') {
                std::istringstream iss(buf.substr(1)); // 去掉$符号
                iss >> middle_big_core_in_game;
                LOG("游戏内中大核调速器为: ", middle_big_core_in_game);
                continue;
            }

            if (buf[0] == '&') {
                std::istringstream iss2(buf.substr(1));
                iss2 >> global_gov;
                LOG("普通APP全局调速器为: ", global_gov);
                continue;
            }

            if (buf[0] != '#' && buf[0] != '$' && buf[0] != '&') {
                std::istringstream iss(buf);

                std::string name;
                unsigned int fps = 60;
                int scaling_a = 0;
                int scaling_b = 0;

                iss >> name >> fps >> scaling_a >> scaling_b;
                // 错误值处理
                // fps
                int fps_int = fps;
                if (fps_int != 60 && fps_int != 90 && fps_int != 120) {
                    int closest = std::min({std::abs(fps_int - 60), std::abs(fps_int - 90), abs(fps_int - 120)});
                    if (closest == std::abs(fps_int - 60)) {
                        closest = 60;
                    } else if (closest == std::abs(fps_int - 90)) {
                        closest = 90;
                    } else if (closest == std::abs(fps_int - 120)) {
                        closest = 120;
                    }

                    fps = closest;
                }

                scaling_a = std::clamp(scaling_a, -1000, 1000);
                scaling_b = std::clamp(scaling_b, -1000, 1000);

                profit.insert(profit.begin(), {name, fps, scaling_a, scaling_b});

                LOG("成功添加: ", name, "\n目标帧率: ", fps, "\nscaling_a: ", scaling_a, "\nscaling_b: ", scaling_b,
                    "\n");
            }
        }
    }
    file.close();
    return true;
}

bool readPathProfile(const char *pathProfile, struct FeasPath *p) {
    std::ifstream file(pathProfile);

    if (!file.is_open())
        return false;

    std::string buf;
    while (std::getline(file, buf)) {
        if (!buf.empty() && buf[0] != '#') {
            if (buf.find("Feas_switch_path") != std::string::npos) {
                GetSecondArg(buf, p->Feas_switch);
                LOG("Feas开关节点: ", p->Feas_switch, "\n");
                continue;
            }

            if (buf.find("Fps_Path") != std::string::npos) {
                GetSecondArg(buf, p->Fps);
                LOG("目标fps节点: ", p->Fps, "\n");
                continue;
            }
            if (buf.find("Scaling_a_path") != std::string::npos) {
                GetSecondArg(buf, p->scaling_a);
                LOG("scaling_a节点: ", p->scaling_a, "\n");
                continue;
            }

            if (buf.find("Scaling_b_path") != std::string::npos) {
                GetSecondArg(buf, p->scaling_b);
                LOG("scaling_b节点: ", p->scaling_b, "\n");
                continue;
            }
        }
    }
    file.close();
    return true;
}