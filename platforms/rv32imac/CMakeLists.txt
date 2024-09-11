cpmaddpackage(
    NAME freedom-metal
    GITHUB_REPOSITORY sifive/freedom-metal
    GIT_TAG fa026d2ee08e5ba49e8ae703fb4cbcbb710a6a69
    DOWNLOAD_ONLY True
    PATCH_COMMAND git apply ${CMAKE_CURRENT_LIST_DIR}/freedom-metal.patch # fix compilation errors
)

add_library(rv32imac_sdk STATIC)

target_sources(rv32imac_sdk PRIVATE
    ${freedom-metal_SOURCE_DIR}/src/atomic.c
    ${freedom-metal_SOURCE_DIR}/src/button.c
    ${freedom-metal_SOURCE_DIR}/src/cache.c
    ${freedom-metal_SOURCE_DIR}/src/clock.c
    ${freedom-metal_SOURCE_DIR}/src/cpu.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/fixed-clock.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/fixed-factor-clock.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/inline.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/riscv_clint0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/riscv_cpu.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/riscv_plic0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_buserror0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_ccache0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_clic0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_fe310-g000_hfrosc.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_fe310-g000_hfxosc.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_fe310-g000_lfrosc.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_fe310-g000_pll.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_fe310-g000_prci.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_global-external-interrupts0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_gpio-buttons.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_gpio-leds.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_gpio-switches.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_gpio0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_i2c0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_local-external-interrupts0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_pwm0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_rtc0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_simuart0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_spi0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_test0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_trace.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_uart0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/sifive_wdog0.c
    ${freedom-metal_SOURCE_DIR}/src/drivers/ucb_htif0.c
    # ${freedom-metal_SOURCE_DIR}/src/entry.S
    ${freedom-metal_SOURCE_DIR}/src/gpio.c
    ${freedom-metal_SOURCE_DIR}/src/hpm.c
    ${freedom-metal_SOURCE_DIR}/src/i2c.c
    ${freedom-metal_SOURCE_DIR}/src/init.c
    ${freedom-metal_SOURCE_DIR}/src/interrupt.c
    ${freedom-metal_SOURCE_DIR}/src/led.c
    ${freedom-metal_SOURCE_DIR}/src/lock.c
    ${freedom-metal_SOURCE_DIR}/src/memory.c
    ${freedom-metal_SOURCE_DIR}/src/pmp.c
    ${freedom-metal_SOURCE_DIR}/src/privilege.c
    ${freedom-metal_SOURCE_DIR}/src/pwm.c
    ${freedom-metal_SOURCE_DIR}/src/rtc.c
    ${freedom-metal_SOURCE_DIR}/src/scrub.S
    ${freedom-metal_SOURCE_DIR}/src/shutdown.c
    ${freedom-metal_SOURCE_DIR}/src/spi.c
    ${freedom-metal_SOURCE_DIR}/src/switch.c
    ${freedom-metal_SOURCE_DIR}/src/synchronize_harts.c
    ${freedom-metal_SOURCE_DIR}/src/time.c
    ${freedom-metal_SOURCE_DIR}/src/timer.c
    # ${freedom-metal_SOURCE_DIR}/src/trap.S
    ${freedom-metal_SOURCE_DIR}/src/tty.c
    ${freedom-metal_SOURCE_DIR}/src/uart.c
    ${freedom-metal_SOURCE_DIR}/src/vector.S
    ${freedom-metal_SOURCE_DIR}/src/watchdog.c
    # ${freedom-metal_SOURCE_DIR}/gloss/crt0.S
    ${freedom-metal_SOURCE_DIR}/gloss/nanosleep.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_access.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_chdir.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_chmod.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_chown.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_clock_gettime.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_close.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_execve.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_exit.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_faccessat.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_fork.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_fstat.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_fstatat.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_ftime.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_getcwd.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_getpid.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_gettimeofday.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_isatty.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_kill.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_link.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_lseek.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_lstat.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_open.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_openat.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_read.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_sbrk.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_stat.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_sysconf.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_times.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_unlink.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_utime.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_wait.c
    ${freedom-metal_SOURCE_DIR}/gloss/sys_write.c
)

target_include_directories(rv32imac_sdk PUBLIC
    ${freedom-metal_SOURCE_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/sifive-hifive1-revb
)

target_link_libraries(
    rv32imac_sdk
    PUBLIC
    -L${CMAKE_CURRENT_LIST_DIR}/sifive-hifive1-revb
    -Tmetal.default.lds
)

function(experiment_platform_setup target)
    cpm_get_fetch_properties(freedom-metal)
    target_sources(${target}
        PRIVATE
        ${freedom-metal_SOURCE_DIR}/gloss/crt0.S
        ${freedom-metal_SOURCE_DIR}/src/entry.S
        ${freedom-metal_SOURCE_DIR}/src/trap.S
        ${cpp_binary_size_SOURCE_DIR}/platforms/rv32imac/base.cpp
    )

    add_custom_target(
        flash_${target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND openocd -f ${cpp_binary_size_SOURCE_DIR}/configs/openocd/rv32imac.cfg -c "program ${target}.bin reset exit 0x20000000"
        DEPENDS ${target}
    )
endfunction()
