#ifndef PATH_H
#define PATH_H

#include "function.h"
struct FeasPath {
public:
    std::string Feas_switch;
    std::string Fps;
    std::string scaling_a;
    std::string scaling_b;
    std::string normal_frame_keep_count;
    std::string min_freq_limit_level;
    std::string max_freq_limit_level;
} __attribute__((aligned(128)));

#endif
