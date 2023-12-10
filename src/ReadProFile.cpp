#include <fstream>
#include <sstream>
#include <vector>

#include "include/GameList.h"
#include "include/function.h"
template <typename T>
const T &clamp(const T &v, const T &lo, const T &hi) {
    return v < lo ? lo : v > hi ? hi : v;
}
auto readProfile(const char *profile, std::vector<listGame> &profit,
                 std::string &middle_big_core_in_game, std::string &global_gov)
    -> bool {
    std::ifstream file(profile);

    if (!file.is_open()) {
        return false;
    }

    std::string buf;

    while (std::getline(file, buf)) {
        if (buf.empty()) {
            continue;
        }
        if (buf[0] == '$') {
            std::istringstream iss1(buf.substr(1)); // 去掉$符号
            iss1 >> middle_big_core_in_game;
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
            int fps = 60;
            int scaling_a = 0;
            int scaling_b = 0;
            int normal_frame_keep_count = 8;
            int min_freq_limit_level = 0;
            int max_freq_limit_level = 41;

            iss >> name >> fps >> scaling_a >> scaling_b >>
                normal_frame_keep_count >> min_freq_limit_level >>
                max_freq_limit_level;
            // 错误值处理

            if (fps != 60 && fps != 90 && fps != 120) {
                int closest = std::min(
                    {std::abs(fps - 60), std::abs(fps - 90), abs(fps - 120)});
                if (closest == std::abs(fps - 60)) {
                    closest = 60;
                } else if (closest == std::abs(fps - 90)) {
                    closest = 90;
                } else if (closest == std::abs(fps - 120)) {
                    closest = 120;
                }
                fps = closest;
            }

            scaling_a = clamp(scaling_a, -1000, 1000);
            scaling_b = clamp(scaling_b, -1000, 1000);

            profit.insert(profit.begin(),
                          {name, fps, scaling_a, scaling_b,
                           normal_frame_keep_count, min_freq_limit_level,
                           max_freq_limit_level});

            LOG("成功添加: ", name, "\n目标帧率: ", fps,
                "\nscaling_a: ", scaling_a, "\nscaling_b: ", scaling_b, "\n",
                "normal_frame_keep_count: ", normal_frame_keep_count, "\n",
                "max_freq_limit_level: ", max_freq_limit_level, "\n",
                "min_freq_limit_level: ", min_freq_limit_level, "\n");
        }
    }
    file.close();
    return true;
}

auto readPathProfile(const char *pathProfile, struct FeasPath *p) -> bool {
    std::ifstream file(pathProfile);

    if (!file.is_open()) {
        return false;
    }

    std::string buf;
    // 定义结构体
    struct Config {
        std::string key;
        std::string *value;
        std::string description;
    } __attribute__((aligned(32)));

    Config const configs[] = {
        {"Feas_switch_path", &p->Feas_switch, "Feas开关节点"},
        {"Fps_Path", &p->Fps, "目标fps节点"},
        {"Scaling_a_path", &p->scaling_a, "scaling_a节点"},
        {"Scaling_b_path", &p->scaling_b, "scaling_b节点"},
        {"normal_frame_keep_count", &p->normal_frame_keep_count,
         "normal_frame_keep_count节点"},
        {"min_freq_limit_level", &p->min_freq_limit_level, "最小频率等级"},
        {"max_freq_limit_level", &p->max_freq_limit_level, "最大频率等级"}};

    while (std::getline(file, buf)) {
        if (!buf.empty() && buf[0] != '#') {
            for (const auto &config : configs) {
                if (buf.find(config.key) != std::string::npos) {
                    GetSecondArg(buf, *config.value);
                    LOG(config.description, ": ", *config.value, "\n");
                    break;
                }
            }
        }
    }

    file.close();
    return true;
}
