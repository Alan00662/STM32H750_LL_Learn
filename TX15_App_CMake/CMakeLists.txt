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
set(CMAKE_PROJECT_NAME TX15_App_Cmake)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)


file(GLOB BSP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/*.c)
file(GLOB LVGL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/app/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/demos/widgets/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/demos/widgets/assets/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/porting/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/core/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/stm32_dma2d/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/sw/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/layouts/*/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/*/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/basic/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/default/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/*/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/win/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/font/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/hal/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/misc/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/widgets/*.c


    )
# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${BSP_SOURCES}
    ${LVGL_SOURCES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/app
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/demos
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/demos/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/demos/widgets/assets
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/porting
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/stm32_dma2d
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/sw
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/layouts/*/
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/*/
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/basic
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/basic
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/default
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/*/
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/font
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/hal
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/misc
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/widgets


)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
    -DLV_CONF_INCLUDE_SIMPLE
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

add_custom_command(
    TARGET  ${CMAKE_PROJECT_NAME} 
    POST_BUILD 
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
)
