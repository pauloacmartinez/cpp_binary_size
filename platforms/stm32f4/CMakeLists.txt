cpmaddpackage(
    NAME stm32cubef4
    VERSION 1.28.1
    GITHUB_REPOSITORY STMicroelectronics/STM32CubeF4
    GIT_TAG v1.28.1
    DOWNLOAD_ONLY True
    # fix syscalls for lto, cleanup warnings and add RNG
    PATCH_COMMAND git apply ${CMAKE_CURRENT_LIST_DIR}/stm32cubef4.patch
)

add_library(stm32f4_sdk STATIC)

target_compile_definitions(stm32f4_sdk
    PUBLIC
    USE_HAL_DRIVER
    STM32F407xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_compile_options(stm32f4_sdk
    PRIVATE
    -Wno-unused-parameter
)

target_include_directories(stm32f4_sdk PUBLIC
    ${stm32cubef4_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${stm32cubef4_SOURCE_DIR}/Drivers/CMSIS/Include
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/Inc
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(stm32f4_sdk PRIVATE
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
    ${stm32cubef4_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c
    ${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/Src/system_stm32f4xx.c
    ${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/STM32CubeIDE/Example/Startup/startup_stm32f407vgtx.s
    ${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/STM32CubeIDE/Example/User/sysmem.c
    base.cpp
    stm32f4_discovery.c
)

target_link_libraries(
    stm32f4_sdk
    PUBLIC
    -L${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/STM32CubeIDE
    -TSTM32F407VGTX_FLASH.ld
)

function(experiment_platform_setup target)
    cpm_get_fetch_properties(gcc-arm-none-eabi)
    cpm_get_fetch_properties(stm32cubef4)

    target_sources(${target}
        PRIVATE
        ${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/Src/stm32f4xx_hal_msp.c
        ${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/Src/stm32f4xx_it.c
        ${stm32cubef4_SOURCE_DIR}/Projects/STM32F4-Discovery/Examples/UART/UART_TwoBoards_ComPolling/STM32CubeIDE/Example/User/syscalls.c
    )

    add_custom_target(
        flash_${target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND openocd -f ${cpp_binary_size_SOURCE_DIR}/configs/openocd/stm32f4.cfg -c "program ${target}.bin reset exit 0x8000000"
        DEPENDS ${target}
    )

    configure_file(${CMAKE_SOURCE_DIR}/renode/stm32f4.resc.in ${CMAKE_CURRENT_BINARY_DIR}/${target}.resc)
    configure_file(${CMAKE_SOURCE_DIR}/configs/gdb/read_timer.sh.in ${CMAKE_CURRENT_BINARY_DIR}/${target}_read_timer.sh)

    add_custom_target(
        emulate_${target}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND renode ${CMAKE_CURRENT_BINARY_DIR}/${target}.resc
        DEPENDS ${target}
    )

    add_custom_target(
        read_timer_${target}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${target}_read_timer.sh
        DEPENDS flash_${target}
    )
endfunction()
