// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdio>
#include <string>

void __attribute__((noinline)) experiment() {
    const std::string str = "Hello World!";

    constexpr auto eol = '\n';
    std::fwrite(str.c_str(), sizeof(char), str.length(), stdout);
    std::fwrite(&eol, sizeof(char), 1, stdout);
}
