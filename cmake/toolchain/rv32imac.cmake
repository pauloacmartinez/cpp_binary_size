set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          rv32imac)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

set(CMAKE_EXECUTABLE_SUFFIX .elf)

cpmaddpackage(
    NAME gcc-riscv-none-elf
    VERSION 13.3
    URL https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v13.3.0-1/xpack-riscv-none-elf-gcc-13.3.0-1-linux-x64.tar.gz
    URL_HASH SHA256=5386d1a7b261d37a6c34e644fc01ed2562132a9fae3e314083f64ad5e8cceb16
    DOWNLOAD_ONLY True
)

set(TARGET_TRIPLET riscv-none-elf)

set(CMAKE_C_COMPILER   ${gcc-riscv-none-elf_SOURCE_DIR}/bin/${TARGET_TRIPLET}-gcc)
set(CMAKE_ASM_COMPILER ${gcc-riscv-none-elf_SOURCE_DIR}/bin/${TARGET_TRIPLET}-gcc)
set(CMAKE_CXX_COMPILER ${gcc-riscv-none-elf_SOURCE_DIR}/bin/${TARGET_TRIPLET}-g++)
set(CMAKE_LINKER       ${gcc-riscv-none-elf_SOURCE_DIR}/bin/${TARGET_TRIPLET}-g++)
set(CMAKE_OBJCOPY      ${gcc-riscv-none-elf_SOURCE_DIR}/bin/${TARGET_TRIPLET}-objcopy)
set(CMAKE_SIZE         ${gcc-riscv-none-elf_SOURCE_DIR}/bin/${TARGET_TRIPLET}-size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(MCU_FLAGS "-march=rv32imac_zicsr_zifencei -mabi=ilp32 -mcmodel=medlow")

set(COMMON_FLAGS "${MCU_FLAGS} -O0 -g3 -Wno-psabi -ffunction-sections -fdata-sections -fdiagnostics-color=always")

set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -x assembler-with-cpp")
set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -fno-rtti -fno-exceptions")

set(CMAKE_C_LINK_FLAGS "--specs=nano.specs -nostartfiles")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--gc-sections")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS}") # -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group -Wl,--defsym=__stack_size=0x8000 -Wl,--defsym=__heap_size=0x8000")
