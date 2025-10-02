// Copyright (c) 2025 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <iostream>
#include <string>

void __attribute__((noinline)) experiment() {
    const std::string str = "Hello World!";
    std::cout << str << std::endl;
}
