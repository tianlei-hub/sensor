cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME sensor)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# 自动收集 Core/Src 下所有用户 C 文件
file(GLOB USER_SOURCES "Core/Src/*.c" "Core/Src/*.C")
# 排除 CubeMX 已管理的 system_stm32f4xx.c（在 STM32_Drivers 库中已编译）
list(FILTER USER_SOURCES EXCLUDE REGEX "system_stm32f4xx\\.[cC]$")
message("User sources: ${USER_SOURCES}")

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${USER_SOURCES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

# Flash target — download firmware to STM32F407 via CMSIS-DAP
set(OPENOCD_EXE "C:/openocd/bin/openocd.exe")
set(OPENOCD_SCRIPTS "C:/openocd/share/openocd/scripts")

add_custom_target(flash
    COMMAND ${OPENOCD_EXE}
        -s ${OPENOCD_SCRIPTS}
        -f interface/cmsis-dap.cfg
        -f target/stm32f4x.cfg
        -c "program $<TARGET_FILE:${CMAKE_PROJECT_NAME}> verify reset exit"
    DEPENDS ${CMAKE_PROJECT_NAME}
    COMMENT "Flashing sensor.elf to STM32F407 via CMSIS-DAP..."
)

# Erase target — mass erase STM32F407 flash
add_custom_target(erase
    COMMAND ${OPENOCD_EXE}
        -s ${OPENOCD_SCRIPTS}
        -f interface/cmsis-dap.cfg
        -f target/stm32f4x.cfg
        -c "init; reset halt; stm32f4x mass_erase 0; reset run; exit"
    COMMENT "Mass erasing STM32F407 flash via CMSIS-DAP..."
)

# Erase + Flash target — erase chip then download firmware
add_custom_target(erase_flash
    COMMAND ${OPENOCD_EXE}
        -s ${OPENOCD_SCRIPTS}
        -f interface/cmsis-dap.cfg
        -f target/stm32f4x.cfg
        -c "init; reset halt; stm32f4x mass_erase 0; program $<TARGET_FILE:${CMAKE_PROJECT_NAME}> verify reset exit"
    DEPENDS ${CMAKE_PROJECT_NAME}
    COMMENT "Erasing + Flashing sensor.elf to STM32F407 via CMSIS-DAP..."
)
