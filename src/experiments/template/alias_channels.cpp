// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdint>
#include <string>

#include "random_inputs.h"

class data_sink {
   private:
    double floating_point_channel;
    uint32_t unsigned_integer_channel;
    int32_t signed_integer_channel;

   public:
    void out(const float& out_value) { floating_point_channel = out_value; }

    void out(const double& out_value) { floating_point_channel = out_value; }

    void out(const uint32_t& out_value) { unsigned_integer_channel = out_value; }

    void out(const uint16_t& out_value) { unsigned_integer_channel = out_value; }

    void out(const uint8_t& out_value) { unsigned_integer_channel = out_value; }

    void out(const int32_t& out_value) { signed_integer_channel = out_value; }

    void out(const int16_t& out_value) { signed_integer_channel = out_value; }

    void out(const int8_t& out_value) { signed_integer_channel = out_value; }
};

void __attribute__((noinline)) experiment() {
    data_sink ds{};

    ds.out(random_number<float>());     //
    ds.out(random_number<double>());    //
    ds.out(random_number<uint32_t>());  //
    ds.out(random_number<int32_t>());   //
    ds.out(random_number<uint16_t>());  //
    ds.out(random_number<int16_t>());   //
    ds.out(random_number<uint8_t>());   //
    ds.out(random_number<int8_t>());    //
    // enter repetition
}
