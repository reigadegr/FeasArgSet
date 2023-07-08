#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "include/LockValue.h"
#include "include/function.h"
#include "include/GameList.h"
#include "include/Path.h"

bool matching_start(std::vector<listGame> gamesaver, std::string &middle_big_core_in_game,FeasPath &feaspath,std::string &gov)
{
    std::string FgApp = getTopApp();
    LOG("前台包名: ",FgApp);
    int tmp_i = 0;
    //打印包名
    for (const auto& game : gamesaver)
    {        
        if(FgApp == game.name){
            LOG("成功匹配");
            //成功后把结构体内各个对象的值写入到指定路径
            //...
            Feas_on(game.fixed_target_fps,game.scaling_a,game.scaling_b,feaspath.Feas_switch,feaspath.Fps,feaspath.scaling_a, feaspath.scaling_b);
            
            set_middle_big_gov(middle_big_core_in_game);
            tmp_i = 1;
            break;
        }
        else{
            continue;
        }
    }
    
    if(!tmp_i){
        Feas_off(feaspath.Feas_switch,feaspath.Fps,feaspath.scaling_a,feaspath.scaling_b);
        recover_freq();
        init_gov(gov);
    }
    return true;
}

int main(int argc, char * argv[])
{
    const char * profile = argv[1];
    const char * pathProfile = argv[2];
    //创建FeasPath的对象feaspath
    FeasPath feaspath;
    //获取feas节点
    //实例化FeasPath的对象feaspath
    readPathProfile(pathProfile, feaspath.Fps, feaspath.Feas_switch, feaspath.scaling_a, feaspath.scaling_b);
    //设置游戏默认中大核调速器(默认值)
    std::string middle_big_core_in_game = "performance";
    //设置非游戏全局调速器(默认值)
    std::string gov = "schedutil";

    
    std::vector<listGame> gamesaver;
    //读取包名列表
    bool ReadProfile = readProfile(profile, gamesaver, middle_big_core_in_game,gov);
    
    if(!ReadProfile)
    {
        LOG("读取文件失败");
        return 1;
    }
    
    //初始化governor和scaling_max freq
    init_gov(gov);
    recover_freq();
    
    
    while(true){
        matching_start(gamesaver, middle_big_core_in_game, feaspath,gov);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

