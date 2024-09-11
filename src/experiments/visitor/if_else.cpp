// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

using value_t = std::variant<std::monostate, bool, float, uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t, std::string>;

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
        std::visit(
            [this](auto&& v) {
                using type = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<std::monostate, type>) {
                } else if constexpr (std::is_same_v<bool, type>) {
                    b = v;
                } else if constexpr (std::is_same_v<float, type>) {
                    f = v;
                } else if constexpr (std::is_same_v<uint32_t, type>) {
                    u32 = v;
                } else if constexpr (std::is_same_v<int32_t, type>) {
                    i32 = v;
                } else if constexpr (std::is_same_v<uint16_t, type>) {
                    u16 = v;
                } else if constexpr (std::is_same_v<int16_t, type>) {
                    i16 = v;
                } else if constexpr (std::is_same_v<uint8_t, type>) {
                    u8 = v;
                } else if constexpr (std::is_same_v<int8_t, type>) {
                    i8 = v;
                } else if constexpr (std::is_same_v<std::string, type>) {
                    s = v;
                }
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
