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
    template <typename T>
    std::enable_if_t<std::is_same_v<T, bool>, void> out(const T& out_value) {
        b = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, float>, void> out(const T& out_value) {
        f = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, uint32_t>, void> out(const T& out_value) {
        u32 = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, int32_t>, void> out(const T& out_value) {
        i32 = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, int16_t>, void> out(const T& out_value) {
        i16 = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, uint16_t>, void> out(const T& out_value) {
        u16 = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, int8_t>, void> out(const T& out_value) {
        i8 = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, uint8_t>, void> out(const T& out_value) {
        u8 = out_value;
    }

    template <typename T>
    std::enable_if_t<std::is_same_v<T, std::string>, void> out(const T& out_value) {
        s = out_value;
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
