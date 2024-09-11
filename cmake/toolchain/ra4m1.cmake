set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

set(CMAKE_EXECUTABLE_SUFFIX .elf)

cpmaddpackage(
    NAME gcc-arm-none-eabi
    VERSION 13.3
    URL https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz
    URL_HASH SHA256=95c011cee430e64dd6087c75c800f04b9c49832cc1000127a92a97f9c8d83af4
    DOWNLOAD_ONLY True
)

set(TARGET_TRIPLET arm-none-eabi)

set(CMAKE_C_COMPILER   ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TARGET_TRIPLET}-gcc)
set(CMAKE_ASM_COMPILER ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TARGET_TRIPLET}-gcc)
set(CMAKE_CXX_COMPILER ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TARGET_TRIPLET}-g++)
set(CMAKE_LINKER       ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TARGET_TRIPLET}-g++)
set(CMAKE_OBJCOPY      ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TARGET_TRIPLET}-objcopy)
set(CMAKE_SIZE         ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TARGET_TRIPLET}-size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU specific flags
set(COMMON_FLAGS "-mthumb -mcpu=cortex-m4 -march=armv7e-m -mfpu=fpv4-sp-d16 -mfloat-abi=soft --specs=nosys.specs")

set(COMMON_FLAGS "${COMMON_FLAGS} -DF_CPU=48000000 -DARDUINO_UNOR4_MINIMA -DARDUINO_MINIMA -DARDUINO_ARCH_RENESAS_UNO -DARDUINO_ARCH_RENESAS -DARDUINO_FSP -D_XOPEN_SOURCE=700 -D_RA_CORE=CM4 -D_RENESAS_RA_ -DARDUINO=10607 -DCFG_TUSB_MCU=OPT_MCU_RAXXX")
set(COMMON_FLAGS "${COMMON_FLAGS} -g3 -MMD -nostdlib -Wall -Wextra -Wpedantic -Wno-psabi -Wno-strict-aliasing -fdata-sections -ffunction-sections -fdiagnostics-color=always -fsigned-char -fno-builtin")

set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -x assembler-with-cpp -fsigned-char")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -fmessage-length=0")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-use-cxa-atexit")

# set(CMAKE_C_LINK_FLAGS "${COMMON_FLAGS}")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --specs=nano.specs --specs=nosys.specs")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--gc-sections -static")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lgcc -lc -lm -Wl,--end-group")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")

# set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group")

set(CMAKE_EXE_LINKER_FLAGS
    "-Wl,--print-memory-usage -Wl,--gc-sections -static -specs=nano.specs"
)

set(CMAKE_C_LINK_EXECUTABLE
    "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> -Wl,--start-group <OBJECTS> <LINK_LIBRARIES> -Wl,--end-group -Wl,--start-group -lgcc -lm -lc -Wl,--end-group -o <TARGET>"
)
set(CMAKE_CXX_LINK_EXECUTABLE
    "<CMAKE_LINKER> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> -Wl,--start-group <OBJECTS> <LINK_LIBRARIES> -Wl,--end-group -Wl,--start-group -lgcc -lm -lc -lstdc++ -lsupc++ -Wl,--end-group -o <TARGET>"
)
