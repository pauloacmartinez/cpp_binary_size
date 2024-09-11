add_library(
    utils
    STATIC
    platforms/${platform}.cpp
)

target_link_libraries(utils PRIVATE ${platform}_sdk)

target_include_directories(
    utils
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
