// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

using value_t = std::variant<std::monostate, bool, float, uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t, std::string>;

template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

class data_sink {
   private:
    bool b;
    float f;
    uint32_t u32;
    int32_t i32;
    uint16_t u16;
    int16_t i16;
    uint8_t u8;
    int8_t i8;
    std::string s;

   public:
    void out(const value_t& v) {
        std::visit(overloaded{
                       [this](const std::monostate&) {},
                       [this](const bool& v) { b = v; },
                       [this](const float& v) { f = v; },
                       [this](const uint32_t& v) { u32 = v; },
                       [this](const int32_t& v) { i32 = v; },
                       [this](const uint16_t& v) { u16 = v; },
                       [this](const int16_t& v) { i16 = v; },
                       [this](const uint8_t& v) { u8 = v; },
                       [this](const int8_t& v) { i8 = v; },
                       [this](const std::string& v) { s = v; },
                   },
                   v);
    }
};

void __attribute__((noinline)) experiment() {
    std::vector<value_t> values = {
        true,                       //
        42.f,                       //
        static_cast<uint32_t>(32),  //
        static_cast<int32_t>(-32),  //
        static_cast<uint16_t>(16),  //
        static_cast<int16_t>(-16),  //
        static_cast<uint8_t>(8),    //
        static_cast<int8_t>(-8),    //
        // enter repetition
        "foo"  //
    };

    data_sink ds{};

    for (const auto& value : values) {
        ds.out(value);
    }
}
