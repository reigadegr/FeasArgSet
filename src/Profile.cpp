#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "include/GameList.h"
#include "include/function.h"


bool readProfile(const char *profile, std::vector<listGame> &profit,std::string &middle_big_core_in_game, std::string &little_core_gov) {
    std::ifstream file(profile);
    
    if (!file.is_open())
        return false;
    
    std::string buf;
  
    while (std::getline(file, buf))
    {
        if(!buf.empty())
        {
            if (buf[0] == '$')
            {
                std::istringstream iss(buf.substr(1)); // 去掉$符号
                iss >> middle_big_core_in_game;
                LOG("调速器为: ",middle_big_core_in_game);
            }
            
            if(buf[0] == '&')
            {
                std::istringstream iss2(buf.substr(1));
                iss2 >> little_core_gov;
            }
            
            if (buf[0] != '#' && buf[0] != '$' && buf[0] != '&')
            {
                std::istringstream iss(buf);
                listGame tmpmsg;
                std::string name = tmpmsg.name;
                unsigned int fps = tmpmsg.fixed_target_fps;
                int scaling_a = tmpmsg.scaling_a;
                int scaling_b = tmpmsg.scaling_b;
                                
                if (iss >> name >> fps >> scaling_a >> scaling_b)
                {
                    
                    if(scaling_a > 1000)
                        scaling_a = 1000;
                    else if(scaling_a < -1000)
                        scaling_a = -1000;
                        
                    if(scaling_b > 1000)
                        scaling_b = 1000;
                    else if(scaling_b < -1000)
                        scaling_b = -1000;
                        
                    profit.push_back({name,fps,scaling_a,scaling_b});
                }
            }
        }
    }
    file.close();
    
    return true;
}



bool readPathProfile(const char *pathProfile,std::string &Fps_path, std::string &Feas_switch, std::string & scaling_a, std::string & scaling_b)
{
    std::ifstream file(pathProfile);
    
    if (!file.is_open())
        return false;        
    std::string buf;
  
    while (std::getline(file, buf))
    {            
        if(!buf.empty() && buf[0] != '#')
        {
            if(buf.find("Feas_switch_path") != std::string::npos)
            {
                GetSecondArg(buf,Feas_switch);
            }
        
            if(buf.find("Fps_Path") != std::string::npos)
            {
                GetSecondArg(buf,Fps_path);
            }
            
            if(buf.find("Scaling_a_path") != std::string::npos)
            {
                GetSecondArg(buf,scaling_a);
            }
            
            if(buf.find("Scaling_b_path") != std::string::npos)
            {
                GetSecondArg(buf,scaling_b);
            }
            
        }
    }
    return true;
}