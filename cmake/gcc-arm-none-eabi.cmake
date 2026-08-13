set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

# Some default GCC settings
# arm-none-eabi- must be part of path environment
set(TOOLCHAIN_PREFIX                arm-none-eabi-)

# 自动查找 ARM GCC：
# 1. 优先用 PATH 里的 arm-none-eabi-gcc
# 2. PATH 里没有时，回退到 STM32CubeIDE 捆绑的工具链 (CUBE_BUNDLE_PATH)
find_program(ARM_GCC_FOUND arm-none-eabi-gcc)
if(NOT ARM_GCC_FOUND)
    if(WIN32)
        set(_bundle_root "$ENV{CUBE_BUNDLE_PATH}")
        if(NOT _bundle_root)
            set(_bundle_root "$ENV{LOCALAPPDATA}/stm32cube/bundles")
        endif()
        file(GLOB _gcc_versions "${_bundle_root}/gnu-tools-for-stm32/*")
        if(_gcc_versions)
            list(SORT _gcc_versions)
            list(REVERSE _gcc_versions)
            list(GET _gcc_versions 0 _latest_gcc)
            file(TO_CMAKE_PATH "${_latest_gcc}" _latest_gcc_cmake)
            set(TOOLCHAIN_PREFIX "${_latest_gcc_cmake}/bin/arm-none-eabi-")
            message(STATUS "Using STM32CubeIDE bundled ARM GCC: ${TOOLCHAIN_PREFIX}")
        else()
            message(FATAL_ERROR "arm-none-eabi-gcc not found in PATH or STM32CubeIDE bundle")
        endif()
    else()
        message(FATAL_ERROR "arm-none-eabi-gcc not found in PATH")
    endif()
endif()

# Windows 下使用完整路径时需要 .exe 后缀
if(WIN32 AND IS_ABSOLUTE "${TOOLCHAIN_PREFIX}")
    set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc.exe)
    set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
    set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++.exe)
    set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++.exe)
    set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy.exe)
    set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size.exe)
else()
    set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
    set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
    set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
    set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)
    set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
    set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)
endif()

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU specific flags
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard ")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp -MMD -MP")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fdata-sections -ffunction-sections -fstack-usage")

# The cyclomatic-complexity parameter must be defined for the Cyclomatic complexity feature in STM32CubeIDE to work.
# However, most GCC toolchains do not support this option, which causes a compilation error; for this reason, the feature is disabled by default.
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcyclomatic-complexity")

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-Os -g0")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -g0")

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_EXE_LINKER_FLAGS "${TARGET_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T \"${CMAKE_SOURCE_DIR}/STM32F407XX_FLASH.ld\"")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")
set(TOOLCHAIN_LINK_LIBRARIES "m")
