// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdio>

#include "random_inputs.h"

void __attribute__((noinline)) experiment() {
    const auto str = random_string(256);
    std::putchar(str.at(random_number<uint8_t>()));
    std::putchar('\n');
}
