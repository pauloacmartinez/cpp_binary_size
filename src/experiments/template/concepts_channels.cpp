// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <cstdint>
#include <string>

#include "random_inputs.h"

template <typename T>
concept is_signed_integer = std::numeric_limits<T>::is_integer && std::is_signed_v<T>;

template <typename T>
concept is_unsigned_integer = std::numeric_limits<T>::is_integer && std::is_unsigned_v<T>;

class data_sink {
   private:
    double floating_point_channel;
    uint32_t unsigned_integer_channel;
    int32_t signed_integer_channel;

   public:
    void out(std::floating_point auto out_value) { floating_point_channel = out_value; }

    void out(is_unsigned_integer auto out_value) { unsigned_integer_channel = out_value; }

    void out(is_signed_integer auto out_value) { signed_integer_channel = out_value; }
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
