// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include "random_inputs.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "fmt/compile.h"
#pragma GCC diagnostic pop
#include "fmt/core.h"

using namespace fmt::literals;

void __attribute__((noinline)) experiment() {
    std::puts(fmt::format("string: {}"_cf, random_string(16)).c_str());

    std::puts(fmt::format("int: {}"_cf, random_number<int>()).c_str());

    std::puts(fmt::format("float: {}"_cf, random_number<float>()).c_str());

    std::puts(fmt::format("double: {}"_cf, random_number<double>()).c_str());

    // enter repetition
}
