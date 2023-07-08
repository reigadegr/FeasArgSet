#pragma once
#include "GameList.h"
#include "Path.h"
void set_middle_big_gov(std::string gov);
//bool Shell(const char *sh, std::string &result);
//readFile
bool readProfile(const char *profile, std::vector<listGame> &profit,std::string &middle_big_core_in_game, std::string &little_core_gov);
bool readPathProfile(const char *pathProfile,std::string &Fps_path, std::string &Feas_switch, std::string & scaling_a, std::string & scaling_b);

bool Get1To2(std::string input,std::string output);
std::string execCmdSync(const std::string &command, const std::vector<std::string> &args);
std::string getTopApp();

void GetSecondArg(std::string &buf,std::string& secondArg);
bool matching_start(std::vector<listGame> gamesaver, std::string &middle_big_core_in_game,FeasPath &feaspath,std::string &gov);


//std::string getSoc(std::string &gov);
void init_gov(std::string &gov);
void recover_freq();
bool Get1To2(std::string input,std::string output);



void Feas_off(std::string Feas_switch,std::string fps_path,std::string scaling_a_path,std::string scaling_b_path);
void Feas_on(unsigned int fps,int scaling_a,int scaling_b,std::string Feas_switch,std::string fps_path,std::string scaling_a_path, std::string scaling_b_path);
template <typename T>
void lock_val(T value, const std::string &path);

template<typename... Args>
static inline void LOG(const Args&... args);

template<typename... Args>
static void LOG(const Args&... args) {
    const auto printArg = [&](const auto& arg) {
        std::cout << arg;
    };
    (printArg(args), ...);
    std::cout << std::endl;
}