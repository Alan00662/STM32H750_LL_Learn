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
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/porting/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/core/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/stm32_dma2d/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/sw/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/layouts/flex/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/layouts/grid/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/bmp/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/ffmpeg/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/freetype/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/fsdrv/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/gif/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/png/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/qrcode/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/rlottie/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/sjpg/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/basic/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/default/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/animimg/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/calendar/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/chart/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/colorwheel/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/imgbtn/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/keyboard/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/led/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/list/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/menu/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/meter/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/msgbox/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/span/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/spinbox/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/spinner/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/tabview/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/tileview/*.c
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
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/porting
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/stm32_dma2d
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/draw/sw
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/layouts/flex
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/layouts/grid
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/bmp
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/ffmpeg
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/freetype
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/fsdrv
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/gif
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/png
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/qrcode
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/rlottie
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/libs/sjpg
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/basic
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/basic
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/themes/default
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/font
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/hal
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/misc
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/animimg
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/calendar
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/chart
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/colorwheel
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/imgbtn
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/keyboard
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/led
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/list
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/menu
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/meter
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/msgbox
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/span
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/spinbox
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/spinner
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/tabview
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/tileview
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/extra/widgets/win
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
