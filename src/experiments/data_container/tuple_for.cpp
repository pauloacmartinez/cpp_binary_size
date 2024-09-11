// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdint>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

#include "random_inputs.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "fmt/compile.h"
#pragma GCC diagnostic pop
#include "fmt/core.h"

using namespace fmt::literals;

auto my_format(auto&&... args) { return fmt::format(std::forward<decltype(args)>(args)...); }

using value_t = std::variant<std::monostate, bool, float, uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t, std::string>;

struct data_printer {
    void operator()(const std::monostate&) { std::puts("value not found"); }
    void operator()(const bool& v) { std::puts(my_format("boolean: {}"_cf, v).c_str()); }
    void operator()(const float& v) { std::puts(my_format("float: {}"_cf, v).c_str()); }
    void operator()(const uint32_t& v) { std::puts(my_format("uint32_t: {}"_cf, v).c_str()); }
    void operator()(const int32_t& v) { std::puts(my_format("int32_t: {}"_cf, v).c_str()); }
    void operator()(const uint16_t& v) { std::puts(my_format("uint16_t: {}"_cf, v).c_str()); }
    void operator()(const int16_t& v) { std::puts(my_format("int16_t: {}"_cf, v).c_str()); }
    void operator()(const uint8_t& v) { std::puts(my_format("uint8_t: {}"_cf, v).c_str()); }
    void operator()(const int8_t& v) { std::puts(my_format("int8_t: {}"_cf, v).c_str()); }
    void operator()(const std::string& v) { std::puts(my_format("string: {}"_cf, v).c_str()); }

    void out(const value_t& v) { std::visit(*this, v); }
};

template <typename T>
using data_points_from_type = std::vector<std::tuple<uint32_t, std::string, T>>;

template <typename... T>
using all_supported_data_points = std::tuple<data_points_from_type<T>...>;

using all_data_points = all_supported_data_points<bool, float, uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t, std::string>;

value_t get_value(all_data_points& dps, uint32_t id) {
    value_t value{std::monostate{}};

    auto get_dp_for_t = [&id, &value](const auto& dps_for_t) {
        for (auto& dp : dps_for_t) {
            if (std::get<0>(dp) == id) {
                value = std::get<2>(dp);
                return true;
            }
        }
        return false;
    };

    std::apply([&get_dp_for_t](auto&&... dps_for_t) { (get_dp_for_t(dps_for_t) || ...); }, dps);

    return value;
}

template <class T>
void add_data_point(all_data_points& dps, uint32_t id, std::string const& name, T&& value = T{}) {
    auto& data_points = std::get<data_points_from_type<T>>(dps);

    for (auto& dp : data_points) {
        if (std::get<0>(dp) == id) {
            std::get<2>(dp) = value;
            return;
        }
    }

    data_points.emplace_back(id, name, value);
}

void __attribute__((noinline)) experiment() {
    all_data_points dps{};
    data_printer d_print{};

    auto add_id = 0;
    auto get_id = 0;

    add_data_point<bool>(dps, add_id++, "boolean", random_boolean());
    add_data_point<float>(dps, add_id++, "float", random_number<float>());
    add_data_point<uint32_t>(dps, add_id++, "u32", random_number<uint32_t>());
    add_data_point<int32_t>(dps, add_id++, "i32", random_number<int32_t>());
    add_data_point<uint16_t>(dps, add_id++, "u16", random_number<uint16_t>());
    add_data_point<int16_t>(dps, add_id++, "i16", random_number<int16_t>());
    add_data_point<uint8_t>(dps, add_id++, "u8", random_number<uint8_t>());
    add_data_point<int8_t>(dps, add_id++, "i8", -8);
    add_data_point<std::string>(dps, add_id++, "str", random_string(32));

    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));
    d_print.out(get_value(dps, get_id++));

    // enter repetition
}
