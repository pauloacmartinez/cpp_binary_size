// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdio>
#include <string>

void __attribute__((noinline)) experiment() {
    const std::string str = "Hello World!";

    std::puts(str.c_str());
}
