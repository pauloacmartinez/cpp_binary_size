// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdint>
#include <string>

#include "random_inputs.h"

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
    void out(const auto& out_value) {
        if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, bool>) {
            b = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, float>) {
            f = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, uint32_t>) {
            u32 = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, int32_t>) {
            i32 = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, uint16_t>) {
            u16 = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, int16_t>) {
            i16 = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, uint8_t>) {
            u8 = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, int8_t>) {
            i8 = out_value;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(out_value)>, std::string>) {
            s = out_value;
        }
    }
};

void __attribute__((noinline)) experiment() {
    data_sink ds{};

    ds.out(random_number<bool>());      //
    ds.out(random_number<float>());     //
    ds.out(random_number<uint32_t>());  //
    ds.out(random_number<int32_t>());   //
    ds.out(random_number<uint16_t>());  //
    ds.out(random_number<int16_t>());   //
    ds.out(random_number<uint8_t>());   //
    ds.out(random_number<int8_t>());    //
    // enter repetition
    ds.out(random_string(32));  //
}
