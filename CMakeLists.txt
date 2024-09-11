cmake_minimum_required(VERSION 3.22)

if(NOT DEFINED ENV{CPM_SOURCE_CACHE})
    set(ENV{CPM_SOURCE_CACHE} ${CMAKE_CURRENT_LIST_DIR}/.cpm)
endif()
include(${CMAKE_CURRENT_LIST_DIR}/cmake/get_cpm.cmake)

# Setup compiler settings
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "MinSizeRel")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME cpp_binary_size)

# Include mold linker
# include(${CMAKE_CURRENT_LIST_DIR}/cmake/mold.cmake)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})

# Enable CMake support for ASM, C and C++ languages
enable_language(ASM C CXX)

# Add platform specific SDK
add_subdirectory(platforms/${platform})

# Add source
add_subdirectory(src)
