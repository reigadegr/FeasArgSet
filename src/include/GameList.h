#pragma once

#include <string>

struct listGame {
    std::string name;
    int fixed_target_fps;
    int scaling_a;
    int scaling_b;
    int normal_frame_keep_count;
    int min_freq_limit_level;
    int max_freq_limit_level;
} __attribute__((aligned(64)));
