function(add_fmt_lib version tag)
    cpmaddpackage(
        NAME fmt_${version}
        VERSION ${tag}
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG ${tag}
        DOWNLOAD_ONLY True
    )

    if(fmt_${version}_ADDED)
        add_library(fmt-${version}-header-only INTERFACE)

        target_include_directories(
            fmt-${version}-header-only
            INTERFACE
            $<BUILD_INTERFACE:${fmt_${version}_SOURCE_DIR}>
            $<BUILD_INTERFACE:${fmt_${version}_SOURCE_DIR}/include>
        )

        target_compile_definitions(
            fmt-${version}-header-only INTERFACE FMT_HEADER_ONLY=1
        )

        target_link_options(
            fmt-${version}-header-only
            INTERFACE
            -u _printf_float
        )

        # lib version with optimized flags
        add_library(fmt-${version}-header-only-opt INTERFACE)

        target_link_libraries(fmt-${version}-header-only-opt INTERFACE fmt-${version}-header-only)

        target_compile_definitions(
            fmt-${version}-header-only-opt
            INTERFACE
            FMT_REDUCE_INT_INSTANTIATIONS=1
            FMT_STATIC_THOUSANDS_SEPARATOR='.'
            FMT_USE_FLOAT128=0
            FMT_USE_LONG_DOUBLE=0
            FMT_USE_LOCALE=0
            FMT_BUILTIN_TYPES=0
            FMT_OPTIMIZE_SIZE=1
        )
    endif()
endfunction()

add_fmt_lib(4 4.x)
add_fmt_lib(5 5.3.0)
add_fmt_lib(6 6.2.1)
add_fmt_lib(7 7.1.3)
add_fmt_lib(8 8.1.1)
add_fmt_lib(9 9.1.0)
add_fmt_lib(10 10.2.1)
add_fmt_lib(11 11.0.2)
add_fmt_lib(latest 7a6a2a79ed85fbd49fbd358dcee39c6d1870097e)
