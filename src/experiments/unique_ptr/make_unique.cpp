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

    birds.push_back(std::make_unique<crow>());
    birds.push_back(std::make_unique<duck>());
    birds.push_back(std::make_unique<owl>());

    bird_symphony(birds);
}
