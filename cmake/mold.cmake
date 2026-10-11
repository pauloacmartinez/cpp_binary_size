option(MOLD_LINKER "Link STM32F4 firmware with mold instead of GNU ld" OFF)
if(MOLD_LINKER AND NOT platform STREQUAL "stm32f4")
    message(FATAL_ERROR "Mold linker is only supported on STM32F4")
endif()

cpmaddpackage(
    NAME
    mold
    VERSION
    3.0.0
    URL
    https://github.com/rui314/mold/releases/download/v3.0.0/mold-3.0.0-x86_64-linux.tar.gz
    URL_HASH
    SHA256=6c90d4a474c7c0409dfb575be03a5345878ac14fdba18de8b40fa58c60121189
    DOWNLOAD_ONLY
    True)

set(MOLD
    ${mold_SOURCE_DIR}/bin/mold
    CACHE FILEPATH "mold linker" FORCE)
