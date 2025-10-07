// Copyright (c) 2025 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <iostream>
#include <memory>
#include <variant>
#include <vector>

struct bird {
    virtual void make_sound() = 0;
    virtual ~bird() = default;
};

struct crow : bird {
    void make_sound() override { std::puts("caw"); }
};

struct duck : bird {
    void make_sound() override { std::puts("quack"); }
};

struct owl : bird {
    void make_sound() override { std::puts("hoot"); }
};

void bird_symphony(const auto& birbs) {
    for (const auto& birb : birbs) std::visit([](auto b) { b.make_sound(); }, birb);
}

void __attribute__((noinline)) experiment() {
    std::vector<std::variant<crow, duck, owl>> birds;

    birds.push_back(crow{});
    birds.push_back(duck{});
    birds.push_back(owl{});

    bird_symphony(birds);
}
