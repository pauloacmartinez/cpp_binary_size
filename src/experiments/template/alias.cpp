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
    void out(const bool& out_value) { b = out_value; }

    void out(const float& out_value) { f = out_value; }

    void out(const uint32_t& out_value) { u32 = out_value; }

    void out(const int32_t& out_value) { i32 = out_value; }

    void out(const uint16_t& out_value) { u16 = out_value; }

    void out(const int16_t& out_value) { i16 = out_value; }

    void out(const uint8_t& out_value) { u8 = out_value; }

    void out(const int8_t& out_value) { i8 = out_value; }

    void out(const std::string& out_value) { s = out_value; }
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
