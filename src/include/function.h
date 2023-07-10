#pragma once
#include "GameList.h"
#include "Path.h"
#include <list>

// 记录时间
std::string printCurrentTime();
void set_middle_big_gov(std::string gov);

// readFile
bool readProfile(const char *profile, std::list<listGame> &profit,
                 std::string &middle_big_core_in_game,
                 std::string &little_core_gov);
bool readPathProfile(const char *pathProfile, std::string &Feas_switch,
                     std::string &Fps_path, std::string &scaling_a,
                     std::string &scaling_b);
auto Testfile(const char *location);
bool Get1To2(std::string input, std::string output);

// get fg APP name
std::string execCmdSync(const std::string &command,
                        const std::vector<std::string> &args);
std::string getTopApp();
std::string getTopAppShell();
std::string checkSymbol(std::string &name);
// running
bool matching_start(std::list<listGame> gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package);
void matchingThread(std::list<listGame> gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package);

void init_gov(std::string &gov);
void recover_freq();

void GetSecondArg(std::string &buf, std::string &secondArg);

void Feas_off(std::string Feas_switch, std::string fps_path,
              std::string scaling_a_path, std::string scaling_b_path);
void Feas_on(unsigned int fps, int scaling_a, int scaling_b,
             std::string Feas_switch, std::string fps_path,
             std::string scaling_a_path, std::string scaling_b_path);

template <typename... Args> static void LOG(const Args &...args);

template <typename... Args> static void LOG(const Args &...args) {
    const auto printArg = [&](const auto &arg) { std::cout << arg; };
    (printArg(args), ...);
    std::cout << std::endl;
}
// 备用打印函数，debug用
/*
template <typename... Args> static void LOG2(const Args &...args);
template <typename... Args> static void LOG2(const Args &...args) {
    const auto printArg = [&](const auto &arg) {
        std::cout << arg << std::endl;
    };
    (printArg(args), ...);
    std::cout << std::endl;
}
*/