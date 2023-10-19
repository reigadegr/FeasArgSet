#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

#include "GameList.h"
#include "Path.h"

auto CheckArg(int &argc) -> bool;
auto AutoNode(FeasPath &feaspath) -> bool;
auto FindPerfmgrName(const std::string &dir, const std::string &str,
                     const std::string &reduceStr) -> std::string;
void mk_node(const std::string &name, struct FeasPath *p);
void init_FeasNode();
// 记录时间
auto printCurrentTime() -> std::string;
void set_middle_big_gov(std::string &gov);
// 内置节点
auto write_struct(std::string switch_ctrl, struct FeasPath *p,
                  const char *pathProfile) -> bool;
auto auto_define() -> std::string;

// readFile
auto readProfile(const char *profile, std::vector<listGame> &profit,
                 std::string &middle_big_core_in_game,
                 std::string &little_core_gov) -> bool;
auto readPathProfile(const char *pathProfile, struct FeasPath *p) -> bool;
auto Testfile(const char *location);
auto Get1To2(const std::string &input, const std::string &output) -> bool;
// 检查
auto check_path(const struct FeasPath *p) -> bool;
// get
// TaAPP
// name
auto execCmdSync(std::string command, const std::vector<std::string> &args)
    -> std::string;
auto getTopApp() -> std::string;
auto getTopAppShell() -> std::string;
auto checkSymbol(std::string &name) -> std::string;
// running
auto matching_start(std::vector<listGame> &gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package) -> bool;
void matchingThread(std::vector<listGame> &gamesaver,
                    std::string &middle_big_core_in_game, FeasPath &feaspath,
                    std::string &gov, std::string &now_package);

void set_gov(std::string &gov);
void recover_freq();

void GetSecondArg(std::string &buf, std::string &secondArg);

void Feas_off(const struct FeasPath *p);
// void
// Feas_on(unsigned
// int
// fps,
// int
// scaling_a,
// int
// scaling_b,
// struct
// FeasPath
// *p);
void Feas_on(const struct listGame *o, const struct FeasPath *p);
void Allow_system_operation();
template <typename... Args>
static void LOG(const Args &...args);

template <typename... Args>
static void LOG(const Args &...args) {
    const auto printArg = [&](const auto &arg) { std::cout << arg; };
    (printArg(args), ...);
    std::cout << std::endl;
}
// 备用打印函数，debug用
/*
template
<typename...
Args>
static
void
LOG2(const
Args
&...args);
template
<typename...
Args>
static
void
LOG2(const
Args
&...args)
{ const
auto
printArg =
[&](const
auto &arg)
{
        std::cout
<< arg <<
std::endl;
    };
    (printArg(args),
...);
    std::cout
<<
std::endl;
}
*/

#endif
