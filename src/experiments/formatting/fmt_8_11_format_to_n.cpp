// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include "random_inputs.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "fmt/core.h"
#pragma GCC diagnostic pop

constexpr auto buffer_size = 32;

void print(const auto buf, const auto& size) {
    if (size >= buffer_size) return;
    buf[size] = '\0';
    std::puts(buf);
}

void __attribute__((noinline)) experiment() {
    std::array<char, buffer_size> format_buffer;
    std::array<char, 16> random_c_arr;

    randomize_char_array(random_c_arr);
    auto format_size =
        fmt::format_to_n(format_buffer.begin(), format_buffer.size(), "string: {}", std::string_view{random_c_arr.data(), 16}).size;
    print(format_buffer.data(), format_size);

    format_size = fmt::format_to_n(format_buffer.begin(), format_buffer.size(), "int: {}", random_number<int>()).size;
    print(format_buffer.data(), format_size);

    format_size = fmt::format_to_n(format_buffer.begin(), format_buffer.size(), "float: {}", random_number<float>()).size;
    print(format_buffer.data(), format_size);

    format_size = fmt::format_to_n(format_buffer.begin(), format_buffer.size(), "double: {}", random_number<double>()).size;
    print(format_buffer.data(), format_size);

    // enter repetition
}
