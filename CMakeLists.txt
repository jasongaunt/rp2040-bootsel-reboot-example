# Import SDK
cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(rp2040-bootsel-reboot-example)
pico_sdk_init()

# Build application
add_executable(
	rp2040-bootsel-reboot-example
	rp2040-bootsel-reboot-example.cpp
	bootsel-reboot.cpp
)

# Debug output - Enable for USB CDC and disable for on-board UART
# You can change these around (or even have both active) by changing the 1s and 0s
pico_enable_stdio_usb(rp2040-bootsel-reboot-example 1)
pico_enable_stdio_uart(rp2040-bootsel-reboot-example 0)

# Build dependencies and link application
pico_add_extra_outputs(rp2040-bootsel-reboot-example)
target_link_libraries(
	rp2040-bootsel-reboot-example
	pico_stdlib
)