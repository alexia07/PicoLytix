# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.0)
set(toolchainVersion RISCV_ZCB_RPI_2_3_0_0)
set(picotoolVersion 2.3.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# 1. Set Board Type
set(PICO_BOARD pico2 CACHE STRING "Board type")

# 2. Import SDK
include(environment/pico_sdk_import.cmake)

# 3. Define Project
project(PicoLytix C CXX ASM)

# 4. Initialize SDK
pico_sdk_init()

# 5. Initialize Source Variables
# We start with empty lists that subdirectories will append to
set(PICOLYTIX_SOURCES "")
set(PICOLYTIX_INCLUDES "")

# 6. Add Subdirectories
# This runs src/CMakeLists.txt, which adds files to the variables above
add_subdirectory(src)

# 7. Create the Executable in ROOT using the collected variables
add_executable(PicoLytix
    ${PICOLYTIX_SOURCES}
)

# 8. Apply Include Directories
target_include_directories(PicoLytix PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}       # Root
    ${PICOLYTIX_INCLUDES}           # Collected from subdirs
)

# 9. Set Program Metadata
pico_set_program_name(PicoLytix "PicoLytix")
pico_set_program_version(PicoLytix "0.1")

# 10. Generate PIO Header
pico_generate_pio_header(PicoLytix ${CMAKE_CURRENT_LIST_DIR}/src/blink.pio)

# 11. Configure I/O
pico_enable_stdio_uart(PicoLytix 0)
pico_enable_stdio_usb(PicoLytix 1)

# 12. Link Libraries
target_link_libraries(PicoLytix
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_dma
    hardware_pio
    hardware_interp
    hardware_timer
    hardware_watchdog
    hardware_clocks
    pico_stdio_usb
)

# 13. Generate Outputs
pico_add_extra_outputs(PicoLytix)