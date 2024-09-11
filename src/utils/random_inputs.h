// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#pragma once

#include <functional>
#include <random>

extern uint32_t get_seed();

constexpr char s_chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

template <typename Dist>
auto get_random_gen(const int min, const int max) {
    return std::bind(Dist(min, max), std::mt19937(get_seed()));
}

std::string random_string(const size_t length) {
    auto random_gen = get_random_gen<std::uniform_int_distribution<>>(0, 61);

    std::string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += s_chars[random_gen()];
    }

    return random_string;
}

template <size_t length>
void randomize_char_array(std::array<char, length>& arr) {
    auto random_gen = get_random_gen<std::uniform_int_distribution<>>(0, 61);

    for (size_t i = 0; i < length; ++i) {
        arr[i] = s_chars[random_gen()];
    }
}

bool random_boolean() { return get_random_gen<std::uniform_int_distribution<>>(0, 1)(); }

template <typename Dist>
auto get_random_number(const auto& min, const auto& max) {
    return get_random_gen<Dist>(min, max)();
}

template <typename T>
T random_number() {
    return get_random_number<std::uniform_int_distribution<>>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <>
float random_number<float>() {
    return get_random_number<std::uniform_real_distribution<>>(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
}

template <>
double random_number<double>() {
    return get_random_number<std::uniform_real_distribution<>>(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
}
