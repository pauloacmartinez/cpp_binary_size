// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <iostream>
#include <memory>
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
    for (const auto& birb : birbs) birb->make_sound();
}

void __attribute__((noinline)) experiment() {
    std::vector<std::unique_ptr<bird>> birds;

    birds.emplace_back(new crow);
    birds.emplace_back(new duck);
    birds.emplace_back(new owl);

    bird_symphony(birds);
}
