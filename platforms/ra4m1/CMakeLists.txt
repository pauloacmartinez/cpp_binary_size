cpmaddpackage(
    NAME arduino_core_renesas
    VERSION 1.2.0
    GITHUB_REPOSITORY arduino/ArduinoCore-renesas
    GIT_TAG 1.2.0
    DOWNLOAD_ONLY True
)

add_library(ra4m1_sdk STATIC)

target_sources(ra4m1_sdk PRIVATE
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_adc/r_adc.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_agt/r_agt.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_can/r_can.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_dac/r_dac.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_gpt/r_gpt.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_icu/r_icu.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_iic_master/r_iic_master.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_iic_slave/r_iic_slave.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_ioport/r_ioport.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_rtc/r_rtc.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_sci_i2c/r_sci_i2c.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_sci_spi/r_sci_spi.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_sci_uart/r_sci_uart.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_spi/r_spi.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/r_wdt/r_wdt.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_clocks.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_common.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_delay.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_group_irq.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_guard.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_io.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_irq.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_register_protection.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_rom_registers.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_sbrk.c
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/src/bsp/mcu/all/bsp_security.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/analog.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/cortex_handlers.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/dac.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/digital.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/FspTimer.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/Interrupts.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/IRQManager.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/itoa.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/main.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/pinDefinitions.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/pulse.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/pwm.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/shift.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/Serial.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/SerialObj1.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/SerialObj2.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/SerialObj3.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/time.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/Tone.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/variant_helper.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/vector_table.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/WMath.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/cm_backtrace/cm_backtrace.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/cm_backtrace/fault_handler/gcc/cmb_fault.S
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/audio/audio_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/bth/bth_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/cdc/cdc_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/cdc/cdc_host.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/cdc/cdc_rndis_host.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/dfu/dfu_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/dfu/dfu_rt_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/hid/hid_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/hid/hid_host.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/midi/midi_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/msc/msc_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/msc/msc_host.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/net/ecm_rndis_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/net/ncm_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/usbtmc/usbtmc_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/vendor/vendor_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/vendor/vendor_host.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/class/video/video_device.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/common/tusb_fifo.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/device/usbd.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/device/usbd_control.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/host/hub.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/host/usbh.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/rusb2/dcd_rusb2.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/rusb2/hcd_rusb2.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/rusb2/rusb2_common.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb/tusb.c
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/usb/SerialUSB.cpp
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/usb/USB.cpp
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/variant.cpp
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/tmp_gen_c_files/pin_data.c
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/tmp_gen_c_files/common_data.c
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/tmp_gen_c_files/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/api/Common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api/CanMsg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api/CanMsgRingbuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api/PluggableUSB.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api/Print.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api/IPAddress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api/Stream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/api/String.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base.cpp
)

target_include_directories(ra4m1_sdk PUBLIC
    ${arduino_core_renesas_SOURCE_DIR}
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra_cfg/fsp_cfg
    ${arduino_core_renesas_SOURCE_DIR}/extras/fsp/ra/fsp/inc/instances
    ${arduino_core_renesas_SOURCE_DIR}/cores/arduino/tinyusb
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/inc
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/inc/api
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/inc/instances
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/arm/CMSIS_5/CMSIS/Core/Include
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra_gen
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra_cfg/fsp_cfg/bsp
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra_cfg/fsp_cfg
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/src/r_usb_basic/src/driver/inc
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/src/r_sce/crypto_procedures/src/sce5/plainkey/private/inc
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/src/r_sce/crypto_procedures/src/sce5/plainkey/public/inc
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/src/r_sce/crypto_procedures/src/sce5/plainkey/primitive
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/src/r_sce/common
    ${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/includes/ra/fsp/src/r_sce
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ra4m1_sdk
    PUBLIC
    -T${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA/fsp.ld
    -L${arduino_core_renesas_SOURCE_DIR}/variants/MINIMA
)

function(experiment_platform_setup target)
    # target_sources(${target}
    #     PRIVATE
    #     ${cpp_binary_size_SOURCE_DIR}/platforms/rv32imac/base.cpp
    # )

    add_custom_target(
        flash_${target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND dfu-util --device 0x2341:0x0069,:0x0369 -D ${target}.bin -a0
        DEPENDS ${target}
    )
endfunction()
