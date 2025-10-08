set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

if(USE_ARM_TOOLCHAIN)
    cpmaddpackage(
        NAME gcc-arm-none-eabi
        VERSION 14.3
        URL https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz
        URL_HASH SHA256=8f6903f8ceb084d9227b9ef991490413014d991874a1e34074443c2a72b14dbd
        DOWNLOAD_ONLY True
    )
else()
    cpmaddpackage(
        NAME gcc-arm-none-eabi
        VERSION 14.3
        URL https://github.com/pauloacmartinez/cpp_binary_size/releases/download/14.3/arm-none-eabi-tools.tar.xz
        URL_HASH SHA256=9147592f17b1ba6f2a54788e0686694314dd256f19aa81f2d5e3ec4365ddf674
        DOWNLOAD_ONLY True
    )
endif()

set(TOOLCHAIN_TRIPLET               arm-none-eabi)

set(CMAKE_C_COMPILER                ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc)
set(CMAKE_ASM_COMPILER              ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc)
set(CMAKE_CXX_COMPILER              ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-g++)
set(CMAKE_LINKER                    ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-g++)
set(CMAKE_AR                        ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc-ar)
SET(CMAKE_RANLIB                    ${gcc-arm-none-eabi_SOURCE_DIR}/bin/${TOOLCHAIN_TRIPLET}-gcc-ranlib)
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
