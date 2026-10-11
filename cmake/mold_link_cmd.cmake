cmake_minimum_required(VERSION 3.28)

set(link_command)
set(after_separator FALSE)
math(EXPR last_argument "${CMAKE_ARGC} - 1")
foreach(index RANGE 0 ${last_argument})
    if(after_separator)
        list(APPEND link_command "${CMAKE_ARGV${index}}")
    elseif(CMAKE_ARGV${index} STREQUAL "--")
        set(after_separator TRUE)
    endif()
endforeach()
list(FIND link_command "-o" output_index)
if(output_index EQUAL -1)
    message(FATAL_ERROR "mold launcher requires an explicit -o output.")
endif()
math(EXPR output_index "${output_index} + 1")
list(GET link_command ${output_index} output)
set(final_output "${output}")
set(output "${output}.mold")
list(REMOVE_AT link_command ${output_index})
list(INSERT link_command ${output_index} "${output}")

function(read_sections result)
    execute_process(COMMAND "${OBJDUMP}" -h "${output}" OUTPUT_VARIABLE headers COMMAND_ERROR_IS_FATAL ANY)
    string(REPLACE "\n" ";" lines "${headers}")
    set(sections)
    set(section)
    foreach(line IN LISTS lines)
        if(line MATCHES
           "^ *[0-9]+ +([^ ]+) +([0-9a-fA-F]+) +([0-9a-fA-F]+) +[0-9a-fA-F]+ +[0-9a-fA-F]+ +2\\*\\*([0-9]+)")
            set(section "${CMAKE_MATCH_1}|0x${CMAKE_MATCH_2}|0x${CMAKE_MATCH_3}|${CMAKE_MATCH_4}")
        elseif(section AND line MATCHES "ALLOC")
            list(APPEND sections "${section}|${line}")
            set(section)
        endif()
    endforeach()
    if(NOT sections)
        message(FATAL_ERROR "mold produced no allocatable ELF sections.")
    endif()
    list(SORT sections)
    set(${result}
        "${sections}"
        PARENT_SCOPE)
endfunction()

function(align_address address power result)
    math(EXPR mask "(1 << ${power}) - 1")
    math(EXPR aligned "(${address} + ${mask}) & ~${mask}" OUTPUT_FORMAT HEXADECIMAL)
    set(${result}
        "${aligned}"
        PARENT_SCOPE)
endfunction()

set(FLASH_ORIGIN 0x08000000)
set(FLASH_LIMIT 0x08100000)
set(RAM_ORIGIN 0x20000000)
set(RAM_LIMIT 0x20020000)
set(CCMRAM_ORIGIN 0x10000000)
set(HEAP_SIZE 0x200)
set(STACK_SIZE 0x400)

set(common_flags
    "-Wl,-e,Reset_Handler"
    "-Wl,--image-base=0x07ff0000"
    "-Wl,--no-eh-frame-hdr"
    "-Wl,-z,norelro"
    "-Wl,--build-id=none"
    "-Wl,--undefined=g_pfnVectors"
    "-Wl,--defsym=_estack=${RAM_LIMIT}"
    "-Wl,--defsym=_Min_Heap_Size=${HEAP_SIZE}"
    "-Wl,--defsym=_Min_Stack_Size=${STACK_SIZE}"
    "-Wl,-l:libc_nano.a,-l:libc.a")

set(startup_symbols
    _sidata
    _sdata
    _edata
    _sbss
    _ebss
    _end
    end
    __bss_start__
    __bss_end__
    _etext
    _siccmram
    _sccmram
    _eccmram)
set(probe_flags)
foreach(symbol IN LISTS startup_symbols)
    list(APPEND probe_flags "-Wl,--defsym=${symbol}=${RAM_ORIGIN}")
endforeach()
execute_process(COMMAND ${link_command} ${common_flags} ${probe_flags} COMMAND_ERROR_IS_FATAL ANY)
read_sections(measured_sections)

set(flash "${FLASH_ORIGIN}")
set(ram "${RAM_ORIGIN}")
set(layout_flags)
set(data_sections)
set(bss_sections)
set(data_alignment 2)
set(vector_found FALSE)

foreach(section IN LISTS measured_sections)
    string(REPLACE "|" ";" fields "${section}")
    list(GET fields 0 name)
    list(GET fields 1 size)
    if(name STREQUAL ".isr_vector")
        list(APPEND layout_flags "-Wl,--section-start=${name}=${FLASH_ORIGIN}")
        math(EXPR flash "${FLASH_ORIGIN} + ${size}" OUTPUT_FORMAT HEXADECIMAL)
        set(vector_found TRUE)
    endif()
endforeach()
if(NOT vector_found)
    message(FATAL_ERROR "STM32F4 firmware is missing .isr_vector.")
endif()

foreach(section IN LISTS measured_sections)
    string(REPLACE "|" ";" fields "${section}")
    list(GET fields 0 name)
    list(GET fields 1 size)
    list(GET fields 3 alignment)
    list(GET fields 4 attributes)
    if(name STREQUAL ".isr_vector")
        continue()
    elseif(name MATCHES "^\\.(data|got)(\\.|$)" OR name STREQUAL ".tm_clone_table")
        list(APPEND data_sections "${section}")
        if(alignment GREATER data_alignment)
            set(data_alignment "${alignment}")
        endif()
    elseif(name STREQUAL ".bss")
        list(APPEND bss_sections "${section}")
    elseif(attributes MATCHES "READONLY" OR name MATCHES "^\\.(preinit|init|fini)_array$")
        align_address("${flash}" "${alignment}" flash)
        list(APPEND layout_flags "-Wl,--section-start=${name}=${flash}")
        math(EXPR flash "${flash} + ${size}" OUTPUT_FORMAT HEXADECIMAL)
        if(name STREQUAL ".text")
            list(APPEND layout_flags "-Wl,--defsym=_etext=${flash}")
        endif()
    else()
        message(FATAL_ERROR "Unsupported allocatable section ${name} in mold STM32F4 firmware.")
    endif()
endforeach()

align_address("${flash}" "${data_alignment}" data_load)
set(copy_options)
foreach(section IN LISTS data_sections)
    string(REPLACE "|" ";" fields "${section}")
    list(GET fields 0 name)
    list(GET fields 1 size)
    list(GET fields 3 alignment)
    align_address("${ram}" "${alignment}" ram)
    math(EXPR load "${data_load} + ${ram} - ${RAM_ORIGIN}" OUTPUT_FORMAT HEXADECIMAL)
    list(APPEND layout_flags "-Wl,--section-start=${name}=${ram}")
    list(APPEND copy_options "--change-section-lma" "${name}=${load}")
    math(EXPR ram "${ram} + ${size}" OUTPUT_FORMAT HEXADECIMAL)
endforeach()
align_address("${ram}" 2 data_end)
math(EXPR flash_end "${data_load} + ${data_end} - ${RAM_ORIGIN}" OUTPUT_FORMAT HEXADECIMAL)
set(ram "${data_end}")
set(bss_start "${ram}")
foreach(section IN LISTS bss_sections)
    string(REPLACE "|" ";" fields "${section}")
    list(GET fields 0 name)
    list(GET fields 1 size)
    list(GET fields 3 alignment)
    align_address("${ram}" "${alignment}" ram)
    list(APPEND layout_flags "-Wl,--section-start=${name}=${ram}")
    math(EXPR ram "${ram} + ${size}" OUTPUT_FORMAT HEXADECIMAL)
endforeach()
align_address("${ram}" 2 bss_end)
align_address("${bss_end}" 3 heap_start)
math(EXPR ram_required "${heap_start} + ${HEAP_SIZE} + ${STACK_SIZE}")
if("${flash_end}" GREATER "${FLASH_LIMIT}" OR "${ram_required}" GREATER "${RAM_LIMIT}")
    message(FATAL_ERROR "mold STM32F4 firmware exceeds flash or RAM (including heap/stack reserves).")
endif()

list(
    APPEND
    layout_flags
    "-Wl,--defsym=_sidata=${data_load}"
    "-Wl,--defsym=_sdata=${RAM_ORIGIN}"
    "-Wl,--defsym=_edata=${data_end}"
    "-Wl,--defsym=_sbss=${bss_start}"
    "-Wl,--defsym=__bss_start__=${bss_start}"
    "-Wl,--defsym=_ebss=${bss_end}"
    "-Wl,--defsym=__bss_end__=${bss_end}"
    "-Wl,--defsym=_end=${heap_start}"
    "-Wl,--defsym=end=${heap_start}"
    "-Wl,--defsym=_siccmram=${flash_end}"
    "-Wl,--defsym=_sccmram=${CCMRAM_ORIGIN}"
    "-Wl,--defsym=_eccmram=${CCMRAM_ORIGIN}")
execute_process(COMMAND ${link_command} ${common_flags} ${layout_flags} COMMAND_ERROR_IS_FATAL ANY)
read_sections(final_sections)
list(LENGTH measured_sections measured_count)
list(LENGTH final_sections final_count)
if(NOT measured_count EQUAL final_count)
    message(FATAL_ERROR "mold changed the section set between layout passes.")
endif()
math(EXPR last "${measured_count} - 1")
foreach(index RANGE ${last})
    list(GET measured_sections ${index} measured)
    list(GET final_sections ${index} final)
    string(REPLACE "|" ";" measured "${measured}")
    string(REPLACE "|" ";" final "${final}")
    foreach(field 0 1 3 4)
        list(GET measured ${field} expected)
        list(GET final ${field} actual)
        if(NOT expected STREQUAL actual)
            message(FATAL_ERROR "mold changed section geometry between layout passes.")
        endif()
    endforeach()
    list(GET final 0 name)
    list(GET final 2 actual_address)
    set(address_found FALSE)
    foreach(flag IN LISTS layout_flags)
        string(FIND "${flag}" "-Wl,--section-start=${name}=" flag_position)
        if(flag_position EQUAL 0)
            string(REGEX REPLACE ".*=" "" expected_address "${flag}")
            if(NOT actual_address EQUAL expected_address)
                message(FATAL_ERROR "mold did not place ${name} at ${expected_address}.")
            endif()
            set(address_found TRUE)
            break()
        endif()
    endforeach()
    if(NOT address_found)
        message(FATAL_ERROR "No validated placement for mold section ${name}.")
    endif()
endforeach()

execute_process(COMMAND "${OBJCOPY}" ${copy_options} "${output}" "${output}.layout" COMMAND_ERROR_IS_FATAL ANY)

set(ELF_HEADER_SIZE 52)
set(PROGRAM_HEADER_SIZE 32)
set(HEADER_SEGMENT_COUNT 2)
set(ELF32_LE_IDENT 7f454c46010101)
set(PT_LOAD 1)
set(PT_PHDR 6)
math(EXPR IMAGE_BASE 0x07ff0000)
math(EXPR HEADERS_END "${ELF_HEADER_SIZE} + ${HEADER_SEGMENT_COUNT} * ${PROGRAM_HEADER_SIZE}")

file(
    READ "${output}.layout" elf_hex
    OFFSET 0
    LIMIT ${HEADERS_END}
    HEX)

function(read_le out offset size)
    math(EXPR hex_offset "2 * ${offset}")
    math(EXPR hex_size "2 * ${size}")
    string(SUBSTRING "${elf_hex}" ${hex_offset} ${hex_size} hex_bytes)
    string(REGEX MATCHALL ".." byte_list "${hex_bytes}")
    list(REVERSE byte_list)
    list(JOIN byte_list "" hex_value)
    math(EXPR value "0x${hex_value}")
    set(${out}
        ${value}
        PARENT_SCOPE)
endfunction()

function(program_header_offset out index)
    math(EXPR offset "${ELF_HEADER_SIZE} + ${index} * ${PROGRAM_HEADER_SIZE}")
    set(${out}
        ${offset}
        PARENT_SCOPE)
endfunction()

function(read_program_header out index field_offset)
    program_header_offset(header_offset ${index})
    math(EXPR offset "${header_offset} + ${field_offset}")
    read_le(value ${offset} 4)
    set(${out}
        ${value}
        PARENT_SCOPE)
endfunction()

string(SUBSTRING "${elf_hex}" 0 14 ident)
read_le(phdr_table_offset 28 4)
read_le(elf_header_size 40 2)
read_le(program_header_size 42 2)
read_le(program_header_count 44 2)
math(EXPR expected_headers_end "${ELF_HEADER_SIZE} + ${program_header_count} * ${PROGRAM_HEADER_SIZE}")

read_program_header(phdr_type 0 0)
read_program_header(phdr_offset 0 4)
read_program_header(phdr_vaddr 0 8)
read_program_header(phdr_paddr 0 12)
read_program_header(load_type 1 0)
read_program_header(load_offset 1 4)
read_program_header(load_vaddr 1 8)
read_program_header(load_paddr 1 12)
read_program_header(load_filesz 1 16)
read_program_header(load_memsz 1 20)

math(EXPR phdr_address "${IMAGE_BASE} + ${ELF_HEADER_SIZE}")
if(NOT ident STREQUAL ELF32_LE_IDENT
   OR NOT phdr_table_offset EQUAL ELF_HEADER_SIZE
   OR NOT elf_header_size EQUAL ELF_HEADER_SIZE
   OR NOT program_header_size EQUAL PROGRAM_HEADER_SIZE
   OR NOT phdr_type EQUAL PT_PHDR
   OR NOT phdr_offset EQUAL ELF_HEADER_SIZE
   OR NOT phdr_vaddr EQUAL phdr_address
   OR NOT phdr_paddr EQUAL phdr_address
   OR NOT load_type EQUAL PT_LOAD
   OR NOT load_offset EQUAL 0
   OR NOT load_vaddr EQUAL IMAGE_BASE
   OR NOT load_paddr EQUAL IMAGE_BASE)
    message(FATAL_ERROR "Unexpected mold ELF headers; refusing to alter firmware segments.")
endif()
if(NOT load_filesz EQUAL expected_headers_end OR NOT load_memsz EQUAL expected_headers_end)
    message(FATAL_ERROR "mold's header LOAD contains more than ELF headers.")
endif()

foreach(index RANGE 1)
    program_header_offset(type_offset ${index})
    execute_process(COMMAND "${DD}" if=/dev/zero "of=${output}.layout" bs=1 seek=${type_offset} count=4 conv=notrunc
                            status=none COMMAND_ERROR_IS_FATAL ANY)
endforeach()
file(RENAME "${output}.layout" "${final_output}")
file(REMOVE "${output}")
math(EXPR flash_used "${flash_end} - ${FLASH_ORIGIN}")
math(EXPR ram_used "${ram_required} - ${RAM_ORIGIN}")
math(EXPR flash_capacity "${FLASH_LIMIT} - ${FLASH_ORIGIN}")
math(EXPR ram_capacity "${RAM_LIMIT} - ${RAM_ORIGIN}")
message(
    STATUS
        "Memory usage:\n   FLASH ${flash_used} / ${flash_capacity} B\n   RAM   ${ram_used} / ${ram_capacity} B")
