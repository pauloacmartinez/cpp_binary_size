cmake_minimum_required(VERSION 3.28)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(get_cpm)
include(standards)

project(cpp_binary_size LANGUAGES C CXX ASM)

add_subdirectory(platforms/${platform})
add_subdirectory(src)
