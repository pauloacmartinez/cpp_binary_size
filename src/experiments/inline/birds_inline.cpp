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

inline void add_crows(std::vector<std::unique_ptr<bird>>& birds, size_t num) {
    for (auto i = 0uz; i < num; ++i) {
        birds.emplace_back(static_cast<bird*>(new crow));
    }
}

inline void add_ducks(std::vector<std::unique_ptr<bird>>& birds, size_t num) {
    for (auto i = 0uz; i < num; ++i) {
        birds.emplace_back(static_cast<bird*>(new duck));
    }
}

inline void add_owls(std::vector<std::unique_ptr<bird>>& birds, size_t num) {
    for (auto i = 0uz; i < num; ++i) {
        birds.emplace_back(static_cast<bird*>(new owl));
    }
}

void bird_symphony(const auto& birbs) {
    for (const auto& birb : birbs) birb->make_sound();
}

void __attribute__((noinline)) experiment() {
    std::vector<std::unique_ptr<bird>> birds;

    const auto num_of_each = 10;
    add_crows(birds, num_of_each);
    add_ducks(birds, num_of_each);
    add_owls(birds, num_of_each);

    // enter repetition

    bird_symphony(birds);
}
