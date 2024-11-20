cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(PICO_BOARD pico CACHE STRING "Board type")
set(PICO_PLATFORM rp2040)
set(PICO_SDK_FETCH_FROM_GIT 1)
set(FREERTOS_FETCH_FROM_GIT 1)
# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.0.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.0.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
endif()

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

project(simple-pico-examples C CXX ASM)

# ====================================================================================
# ====================================================================================
# ====================================================================================
add_executable(hello-world-example hello-world-example.c )

pico_set_program_name(hello-world-example "hello-world-example")
pico_set_program_version(hello-world-example "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(hello-world-example 0)
pico_enable_stdio_usb(hello-world-example 1)

# Add the standard include files to the build
target_include_directories(hello-world-example PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)
# Add the required libraries
target_link_libraries(hello-world-example
        pico_stdlib
)

pico_add_extra_outputs(hello-world-example)


