// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdio>
#include <memory>
#include <vector>

struct bird {
    virtual void make_sound() = 0;
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

template <typename T>
void add_birds(std::vector<std::unique_ptr<bird>>& birds, size_t num) {
    for (auto i = 0uz; i < num; ++i) {
        birds.emplace_back(static_cast<bird*>(new T));
    }
}

void bird_symphony(const auto& birbs) {
    for (const auto& birb : birbs) birb->make_sound();
}

void __attribute__((noinline)) experiment() {
    std::vector<std::unique_ptr<bird>> birds;

    const auto num_of_each = 10;
    add_birds<crow>(birds, num_of_each);
    add_birds<duck>(birds, num_of_each);
    add_birds<owl>(birds, num_of_each);

    // enter repetition

    bird_symphony(birds);
}
