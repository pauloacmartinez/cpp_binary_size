// Copyright (c) 2025 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <iostream>
#include <memory>
#include <variant>
#include <vector>

template <typename T>
concept bird_like = requires(T b) {
    { b.make_sound() } -> std::same_as<void>;
};

struct crow {
    void make_sound() { std::puts("caw"); }
};

struct duck {
    void make_sound() { std::puts("quack"); }
};

struct owl {
    void make_sound() { std::puts("hoot"); }
};

void bird_symphony(const auto& birbs) {
    for (const auto& birb : birbs) std::visit([](bird_like auto b) { b.make_sound(); }, birb);
}

void __attribute__((noinline)) experiment() {
    std::vector<std::variant<crow, duck, owl>> birds;

    birds.push_back(crow{});
    birds.push_back(duck{});
    birds.push_back(owl{});

    bird_symphony(birds);
}
