// Copyright (c) 2026 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

export module experiment_module;

import std;

export namespace experiment_module {
void __attribute__((noinline)) experiment() {
    const std::string str = "Hello World!";
    std::cout << str << std::endl;
}
}  // namespace experiment_module
