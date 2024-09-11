include(${CMAKE_SOURCE_DIR}/cmake/fmt.cmake)

function(add_experiment source target)
    add_library(experiment_${target} STATIC ${source}.cpp)

    target_link_libraries(experiment_${target} PRIVATE utils ${ARGN})

    add_executable(${target})

    target_link_options(${target} PRIVATE -Wl,-Map=${target}.map)

    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND echo "${target}.elf to ${target}.bin"
        COMMAND ${CMAKE_OBJCOPY} -O binary -S
                ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf
                ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin
    )

    experiment_platform_setup(${target})

    target_link_libraries(${target} PUBLIC ${platform}_sdk experiment_${target})
endfunction(add_experiment)

# WIP: to be used with GCC >= 14
function(add_module_experiment source target)
    add_library(experiment_${target})
    target_sources(experiment_${target}
        PUBLIC
            FILE_SET CXX_MODULES FILES
                ${source}.cxx
    )

    target_link_libraries(experiment_${target} PRIVATE utils ${ARGN})

    add_executable(${target})

    target_link_options(${target} PRIVATE -Wl,-Map=${target}.map)

    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND echo "${target}.elf to ${target}.bin"
        COMMAND ${CMAKE_OBJCOPY} -O binary -S
                ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf
                ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin
    )

    experiment_platform_setup(${target})

    target_link_libraries(${target} PUBLIC ${platform}_sdk experiment_${target})
endfunction(add_module_experiment)

add_experiment(baseline/baseline baseline)

# formatting (format)

add_experiment(formatting/fmt_4_7 fmt_4 fmt-4-header-only)
add_experiment(formatting/fmt_4_7 fmt_4_opt fmt-4-header-only-opt)
add_experiment(formatting/fmt_4_7 fmt_5 fmt-5-header-only)
add_experiment(formatting/fmt_4_7 fmt_5_opt fmt-5-header-only-opt)
add_experiment(formatting/fmt_4_7 fmt_6 fmt-6-header-only)
add_experiment(formatting/fmt_4_7 fmt_6_opt fmt-6-header-only-opt)
add_experiment(formatting/fmt_4_7 fmt_7 fmt-7-header-only)
add_experiment(formatting/fmt_4_7 fmt_7_opt fmt-7-header-only-opt)
add_experiment(formatting/fmt_8_11 fmt_8 fmt-8-header-only)
add_experiment(formatting/fmt_8_11 fmt_8_opt fmt-8-header-only-opt)
add_experiment(formatting/fmt_8_11_compile fmt_8_compile fmt-8-header-only)
add_experiment(formatting/fmt_8_11_compile fmt_8_compile_opt fmt-8-header-only-opt)
add_experiment(formatting/fmt_8_11 fmt_9 fmt-9-header-only)
add_experiment(formatting/fmt_8_11 fmt_9_opt fmt-9-header-only-opt)
add_experiment(formatting/fmt_8_11_compile fmt_9_compile fmt-9-header-only)
add_experiment(formatting/fmt_8_11_compile fmt_9_compile_opt fmt-9-header-only-opt)
add_experiment(formatting/fmt_8_11 fmt_10 fmt-10-header-only)
add_experiment(formatting/fmt_8_11 fmt_10_opt fmt-10-header-only-opt)
add_experiment(formatting/fmt_8_11_compile fmt_10_compile fmt-10-header-only)
add_experiment(formatting/fmt_8_11_compile fmt_10_compile_opt fmt-10-header-only-opt)
add_experiment(formatting/fmt_8_11 fmt_11 fmt-11-header-only)
add_experiment(formatting/fmt_8_11 fmt_11_opt fmt-11-header-only-opt)
add_experiment(formatting/fmt_8_11_compile fmt_11_compile fmt-11-header-only)
add_experiment(formatting/fmt_8_11_compile fmt_11_compile_opt fmt-11-header-only-opt)
add_experiment(formatting/fmt_8_11 fmt_latest fmt-latest-header-only)
add_experiment(formatting/fmt_8_11 fmt_latest_opt fmt-latest-header-only-opt)
add_experiment(formatting/fmt_8_11_compile fmt_latest_compile fmt-latest-header-only)
add_experiment(formatting/fmt_8_11_compile fmt_latest_compile_opt fmt-latest-header-only-opt)
add_experiment(formatting/format format)

# formatting (format_to_n)

add_experiment(formatting/fmt_5_7_format_to_n fmt_5_format_to_n fmt-5-header-only)
add_experiment(formatting/fmt_5_7_format_to_n fmt_5_opt_format_to_n fmt-5-header-only-opt)
add_experiment(formatting/fmt_5_7_format_to_n fmt_6_format_to_n fmt-6-header-only)
add_experiment(formatting/fmt_5_7_format_to_n fmt_6_opt_format_to_n fmt-6-header-only-opt)
add_experiment(formatting/fmt_5_7_format_to_n fmt_7_format_to_n fmt-7-header-only)
add_experiment(formatting/fmt_5_7_format_to_n fmt_7_opt_format_to_n fmt-7-header-only-opt)
add_experiment(formatting/fmt_8_11_format_to_n fmt_8_format_to_n fmt-8-header-only)
add_experiment(formatting/fmt_8_11_format_to_n fmt_8_opt_format_to_n fmt-8-header-only-opt)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_8_compile_format_to_n fmt-8-header-only)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_8_compile_opt_format_to_n fmt-8-header-only-opt)
add_experiment(formatting/fmt_8_11_format_to_n fmt_9_format_to_n fmt-9-header-only)
add_experiment(formatting/fmt_8_11_format_to_n fmt_9_opt_format_to_n fmt-9-header-only-opt)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_9_compile_format_to_n fmt-9-header-only)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_9_compile_opt_format_to_n fmt-9-header-only-opt)
add_experiment(formatting/fmt_8_11_format_to_n fmt_10_format_to_n fmt-10-header-only)
add_experiment(formatting/fmt_8_11_format_to_n fmt_10_opt_format_to_n fmt-10-header-only-opt)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_10_compile_format_to_n fmt-10-header-only)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_10_compile_opt_format_to_n fmt-10-header-only-opt)
add_experiment(formatting/fmt_8_11_format_to_n fmt_11_format_to_n fmt-11-header-only)
add_experiment(formatting/fmt_8_11_format_to_n fmt_11_opt_format_to_n fmt-11-header-only-opt)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_11_compile_format_to_n fmt-11-header-only)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_11_compile_opt_format_to_n fmt-11-header-only-opt)
add_experiment(formatting/fmt_8_11_format_to_n fmt_latest_format_to_n fmt-latest-header-only)
add_experiment(formatting/fmt_8_11_format_to_n fmt_latest_opt_format_to_n fmt-latest-header-only-opt)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_latest_compile_format_to_n fmt-latest-header-only)
add_experiment(formatting/fmt_8_11_compile_format_to_n fmt_latest_compile_opt_format_to_n fmt-latest-header-only-opt)
add_experiment(formatting/format_to_n format_to_n)

if(platform STREQUAL "stm32f4")
    add_experiment(hello_world/hal_uart hal_uart stm32f4_sdk)
endif()
add_experiment(hello_world/iostream iostream)
add_experiment(hello_world/stdio_fwrite stdio_fwrite)
add_experiment(hello_world/stdio_putc stdio_putc)
add_experiment(hello_world/stdio_putchar stdio_putchar)
add_experiment(hello_world/stdio_puts stdio_puts)
# add_module_experiment(hello_world/iostream_module iostream_module)

add_experiment(template/alias alias)
add_experiment(template/alias_channels alias_channels)
add_experiment(template/concepts_channels concepts_channels)
add_experiment(template/if_constexpr if_constexpr)
add_experiment(template/if_constexpr_channels if_constexpr_channels)
add_experiment(template/sfinae sfinae)
add_experiment(template/sfinae_channels sfinae_channels)

add_experiment(container_access/operator_at operator_at)
add_experiment(container_access/operator_subscript operator_subscript)

add_experiment(ctors/string_assign string_assign)
add_experiment(ctors/string_move string_move)
add_experiment(ctors/string_rule_of_zero string_rule_of_zero)

add_experiment(data_container/map map fmt-11-header-only-opt)
add_experiment(data_container/tuple_algorithm tuple_algorithm fmt-11-header-only-opt)
add_experiment(data_container/tuple_for tuple_for fmt-11-header-only-opt)
add_experiment(data_container/unordered_map unordered_map fmt-11-header-only-opt)
add_experiment(data_container/vector vector fmt-11-header-only-opt)

add_experiment(factory/concepts concepts)
add_experiment(factory/virtual virtual)

add_experiment(inline/birds birds)
add_experiment(inline/birds_inline birds_inline)
add_experiment(inline/birds_template birds_template)
add_experiment(inline/dead_code_inline dead_code_inline)
add_experiment(inline/dead_code_orig dead_code_orig)

add_experiment(type_erasure/inheritance inheritance)
add_experiment(type_erasure/inheritance_copy inheritance_copy)
add_experiment(type_erasure/inheritance_sbo inheritance_sbo)
add_experiment(type_erasure/static_func static_func)
add_experiment(type_erasure/static_func_copy static_func_copy)
add_experiment(type_erasure/static_func_sbo static_func_sbo)
add_experiment(type_erasure/v_table v_table)
add_experiment(type_erasure/v_table_copy v_table_copy)
add_experiment(type_erasure/v_table_sbo v_table_sbo)

add_experiment(unique_ptr/make_unique make_unique)
add_experiment(unique_ptr/make_unique_emplace make_unique_emplace)
add_experiment(unique_ptr/new_emplace new_emplace)
add_experiment(unique_ptr/new_static_cast_emplace new_static_cast_emplace)

add_experiment(visitor/class_overload class_overload)
add_experiment(visitor/get_if get_if)
add_experiment(visitor/holds_alternative holds_alternative)
add_experiment(visitor/if_else if_else)
add_experiment(visitor/overloaded overloaded)
add_experiment(visitor/switch switch)
