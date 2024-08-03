cmake_minimum_required(VERSION 3.13)

# Set path to Pico-sdk
if (NOT PICO_SDK_PATH)
    if(DEFINED ENV{PICO_SDK_PATH})
        set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
        message("Setting PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
    else()
        set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)
        message("Setting PICO_SDK_PATH from git submodule path ('${PICO_SDK_PATH}')")
    endif()
else()
    message("PICO_SDK_PATH is ('${PICO_SDK_PATH}')")
endif()

# Include pico_sdk_import.cmake from pico-sdk (instead of copying)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Project setup
set(PROJECT boot-selector)
project(${PROJECT})

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add the stuff
add_executable(${PROJECT})

target_sources(${PROJECT} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c
        ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/src/msc_disk.c
        ${CMAKE_CURRENT_LIST_DIR}/src/reboot.c
        ${CMAKE_CURRENT_LIST_DIR}/src/tud_dev_cb.c
        ${CMAKE_CURRENT_LIST_DIR}/src/console.c
        ${CMAKE_CURRENT_LIST_DIR}/src/boot_switch.c
        ${CMAKE_CURRENT_LIST_DIR}/src/at42qt1070.c
        )

target_include_directories(${PROJECT} PUBLIC
        ${PICO_SDK_PATH}/lib/tinyusb/src
        ${CMAKE_CURRENT_LIST_DIR}/src
        )

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(${PROJECT} PUBLIC 
        pico_stdlib 
        pico_unique_id 
        tinyusb_device 
        tinyusb_board
        pico_bootrom
        pico_multicore
        )

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(boot_selector PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

# Give me UF2
pico_add_extra_outputs(${PROJECT})
