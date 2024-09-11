// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <string>

#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef UartHandle;

void __attribute__((noinline)) experiment() {
    const auto timeout = 1'000;  // ms
    const std::string str = "Hello World!\n";

    HAL_UART_Transmit(&UartHandle, reinterpret_cast<const uint8_t *>(str.c_str()), str.length(), timeout);
}
