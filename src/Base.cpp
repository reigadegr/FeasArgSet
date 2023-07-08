#include <iostream>
#include <fstream>
#include "include/function.h"
/*
bool Shell(const char *sh, std::string &result)
{
    FILE *pp = popen(sh, "r");
    if (pp == NULL)
    {
        perror("Failed");
        return false;
    }
    char buffer[1024];
    //std::string buffer;
    // collect result
    fgets(buffer, sizeof(buffer), pp);
    result = buffer;
    result.pop_back();
    pclose(pp);
    return true;
}

*/
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

