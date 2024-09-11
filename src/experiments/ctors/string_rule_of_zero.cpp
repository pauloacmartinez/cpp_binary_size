// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <string>

#include "random_inputs.h"

struct resource {
    std::string m_name;

    const char* operator()() { return m_name.c_str(); }
};

void __attribute__((noinline)) experiment() {
    resource res{random_string(32)};

    std::puts(res());
}
