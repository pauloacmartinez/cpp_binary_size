// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include "random_inputs.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wpedantic"
#include "fmt/format.h"
#pragma GCC diagnostic pop

void __attribute__((noinline)) experiment() {
    std::puts(fmt::format("string: {}", random_string(16)).c_str());

    std::puts(fmt::format("int: {}", random_number<int>()).c_str());

    std::puts(fmt::format("float: {}", random_number<float>()).c_str());

    std::puts(fmt::format("double: {}", random_number<double>()).c_str());

    // enter repetition
}
