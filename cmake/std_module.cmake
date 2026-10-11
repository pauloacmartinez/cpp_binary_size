execute_process(
    COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libstdc++.modules.json
    OUTPUT_VARIABLE std_manifest
    OUTPUT_STRIP_TRAILING_WHITESPACE
    COMMAND_ERROR_IS_FATAL ANY
)

if(NOT EXISTS "${std_manifest}")
    message(FATAL_ERROR "The selected compiler does not provide libstdc++.modules.json.")
endif()

file(READ "${std_manifest}" std_manifest_content)
string(JSON std_module_count LENGTH "${std_manifest_content}" modules)
if(std_module_count EQUAL 0)
    message(FATAL_ERROR "The libstdc++ module manifest contains no modules.")
endif()

cmake_path(GET std_manifest PARENT_PATH std_manifest_dir)
math(EXPR std_module_last "${std_module_count} - 1")
foreach(module_index RANGE ${std_module_last})
    string(
        JSON
        module_name
        GET
        "${std_manifest_content}"
        modules
        ${module_index}
        logical-name
    )
    if(module_name STREQUAL "std")
        string(
            JSON
            module_path
            GET
            "${std_manifest_content}"
            modules
            ${module_index}
            source-path
        )
        cmake_path(ABSOLUTE_PATH module_path BASE_DIRECTORY "${std_manifest_dir}" OUTPUT_VARIABLE std_source)
        break()
    endif()
endforeach()
if(NOT DEFINED std_source OR NOT EXISTS "${std_source}")
    message(FATAL_ERROR "The libstdc++ manifest does not provide an existing std module source.")
endif()

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${std_manifest}" "${std_source}")
file(READ "${std_source}" std_content)

function(guard_std_exports condition)
    foreach(symbol IN LISTS ARGN)
        set(declaration "  using ${symbol};")
        string(FIND "${std_content}" "${declaration}" position)
        if(position EQUAL -1)
            message(FATAL_ERROR "Unsupported libstdc++ std module source: missing ${symbol} export.")
        endif()
        string(
            REPLACE
            "${declaration}"
            "#if ${condition}\n${declaration}\n#endif"
            std_content
            "${std_content}"
        )
    endforeach()
    set(std_content "${std_content}" PARENT_SCOPE)
endfunction()

guard_std_exports(
    "defined(__cpp_lib_atomic_wait)"
    std::atomic_flag_notify_all
    std::atomic_flag_notify_one
    std::atomic_flag_wait
    std::atomic_flag_wait_explicit
    std::atomic_notify_all
    std::atomic_notify_one
    std::atomic_wait
    std::atomic_wait_explicit
)
guard_std_exports(
    "defined(_GLIBCXX_HAS_GTHREADS)"
    std::condition_variable
    std::condition_variable_any
    std::cv_status
    std::notify_all_at_thread_exit
    std::mutex
    std::recursive_mutex
    std::recursive_timed_mutex
    std::timed_mutex
)
guard_std_exports("defined(__cpp_lib_latch)" std::latch)
guard_std_exports("__cpp_lib_memory_resource >= 201603L" std::pmr::synchronized_pool_resource)
guard_std_exports("defined(__cpp_lib_semaphore)" std::binary_semaphore std::counting_semaphore)
guard_std_exports("defined(__cpp_lib_shared_mutex)" std::shared_mutex)
guard_std_exports("defined(__cpp_lib_shared_timed_mutex)" std::shared_timed_mutex)
guard_std_exports("defined(__cpp_lib_jthread)" std::jthread)

set(std_generated_source "${CMAKE_CURRENT_BINARY_DIR}/std_module/std.cxx")
file(CONFIGURE OUTPUT "${std_generated_source}" CONTENT "${std_content}" @ONLY)

add_library(cpp_std_module STATIC)
set_target_properties(cpp_std_module PROPERTIES CXX_SCAN_FOR_MODULES ON)
target_sources(
    cpp_std_module
    PUBLIC FILE_SET CXX_MODULES
    BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/std_module"
    FILES "${std_generated_source}"
)
