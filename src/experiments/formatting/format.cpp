// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdio>
#include <format>

#include "random_inputs.h"

void __attribute__((noinline)) experiment() {
    std::puts(std::format("string: {}", random_string(16)).c_str());

    std::puts(std::format("int: {}", random_number<int>()).c_str());

    std::puts(std::format("float: {}", random_number<float>()).c_str());

    std::puts(std::format("double: {}", random_number<double>()).c_str());

    // enter repetition
}
