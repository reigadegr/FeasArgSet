#include <chrono>
#include <iomanip>
#include <sstream>

#include "include/function.h"

auto printCurrentTime() -> std::string {

    // 获取当前时间点
    std::chrono::system_clock::time_point const currentTime =
        std::chrono::system_clock::now();

    // 将时间点转换为时间结构体
    std::time_t const currentTimeT =
        std::chrono::system_clock::to_time_t(currentTime);

    // 将时间结构体转换为本地时间
    std::tm *currentTimeInfo = std::localtime(&currentTimeT);

    // 打印当前时间

    std::ostringstream oss;
    oss << std::put_time(currentTimeInfo,
                         "%Y 年 %m 月 %d 日 %H 时 %M 分 %S 秒");
    return oss.str();
}
