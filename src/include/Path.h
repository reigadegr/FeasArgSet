#ifndef PATH_H
#define PATH_H

#pragma once
#include "function.h"
struct FeasPath {
public:
    std::string Feas_switch;
    std::string Fps;
    std::string scaling_a;
    std::string scaling_b;
} __attribute__((aligned(128)));

#endif
