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
    template <typename T>
    std::enable_if_t<std::is_floating_point_v<T>, void> out(const T& out_value) {
        floating_point_channel = out_value;
    }

    template <typename T>
    std::enable_if_t<std::numeric_limits<T>::is_integer && std::is_unsigned_v<T>, void> out(const T& out_value) {
        unsigned_integer_channel = out_value;
    }

    template <typename T>
    std::enable_if_t<std::numeric_limits<T>::is_integer && std::is_signed_v<T>, void> out(const T& out_value) {
        signed_integer_channel = out_value;
    }
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
