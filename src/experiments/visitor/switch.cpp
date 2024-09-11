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
        switch (v.index()) {
            case 0:
                break;
            case 1:
                b = std::get<1>(v);
                break;
            case 2:
                f = std::get<2>(v);
                break;
            case 3:
                u32 = std::get<3>(v);
                break;
            case 4:
                i32 = std::get<4>(v);
                break;
            case 5:
                u16 = std::get<5>(v);
                break;
            case 6:
                i16 = std::get<6>(v);
                break;
            case 7:
                u8 = std::get<7>(v);
                break;
            case 8:
                i8 = std::get<8>(v);
                break;
            case 9:
                s = std::get<9>(v);
                break;
            default:
                break;
        }
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
