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
    void out(const auto& out_value) {
        using type = std::decay_t<decltype(out_value)>;
        if constexpr (std::is_floating_point_v<type>) {
            floating_point_channel = out_value;
        } else if constexpr (std::numeric_limits<type>::is_integer && std::is_unsigned_v<type>) {
            unsigned_integer_channel = out_value;
        } else if constexpr (std::numeric_limits<type>::is_integer && std::is_signed_v<type>) {
            signed_integer_channel = out_value;
        }
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
