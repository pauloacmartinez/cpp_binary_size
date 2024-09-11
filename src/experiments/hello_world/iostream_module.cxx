// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

module;

#include <iostream>
// import std;

export module iostream_module;

export {
    void __attribute__((noinline)) experiment() {
        const std::string str = "Hello World!";
        std::cout << str << std::endl;
    }
}
