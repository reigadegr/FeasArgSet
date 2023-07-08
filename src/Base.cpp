#include <iostream>
#include <fstream>
#include <sstream>
#include "include/function.h"

bool Get1To2(std::string input,std::string output)
{
    std::ifstream input_path(input);
    
    if (!input_path.is_open())
        return false;
        
    std::string value;
    std::getline(input_path, value);
    input_path.close();
    
    lock_val(value,output);

    return true;
    
}

void GetSecondArg(std::string &buf,std::string& secondArg){
    std::istringstream iss(buf);
    std::string tmp;
    iss >> tmp >> secondArg;
    //LOG(tmp," : ",secondArg);
}