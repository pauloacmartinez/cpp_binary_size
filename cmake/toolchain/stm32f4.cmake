set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

cpmaddpackage(
    NAME gcc-arm-none-eabi
    VERSION 13.3
    URL https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz
    URL_HASH SHA256=95c011cee430e64dd6087c75c800f04b9c49832cc1000127a92a97f9c8d83af4
    DOWNLOAD_ONLY True
)

set(TOOLCHAIN_TRIPLET               arm-none-eabi)

set(CMAKE_C_COMPILER                ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc)
set(CMAKE_ASM_COMPILER              ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc)
set(CMAKE_CXX_COMPILER              ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-g++)
set(CMAKE_LINKER                    ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-g++)
set(CMAKE_AR                        ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc-ar)
SET(CMAKE_RANLIB                    ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc-ranlib)
# set(CMAKE_LINKER                    ${MOLD})
set(CMAKE_OBJCOPY                   ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-objcopy)
set(CMAKE_SIZE                      ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-size)

set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")

set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# default is "-O3 -DNDEBUG"
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_ASM_FLAGS_RELEASE "-O2 -DNDEBUG")

set(MCU_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(COMMON_FLAGS "${MCU_FLAGS} -g3 -Wall -Wextra -Wpedantic -Wno-psabi -Wno-strict-aliasing -flto=auto -fdata-sections -ffunction-sections -fdiagnostics-color=always -MMD -MP")

set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -x assembler-with-cpp")
set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_C_LINK_FLAGS "-flto=auto --specs=nano.specs --specs=nosys.specs")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--gc-sections")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lc -lgcc -lm -Wl,--end-group")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group")
