// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <vector>

void add(std::vector<int> &v, unsigned int a) {
    auto b = static_cast<bool>(a);
    for (auto i = 0uz; i < v.size() * b; ++i) {
        v[i] += a;
    }
}

void __attribute__((noinline)) experiment() {
    std::vector<int> v{0, 1, 2, 3};
    add(v, 0);
}
