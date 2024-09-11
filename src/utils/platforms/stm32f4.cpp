// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include "stm32f4xx_hal.h"

extern RNG_HandleTypeDef RngHandle;

uint32_t get_seed() {
    uint32_t seed;
    if (HAL_RNG_GenerateRandomNumber(&RngHandle, &seed) != HAL_OK) seed = 0;

    return seed;
}
