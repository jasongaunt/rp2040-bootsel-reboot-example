#!/bin/bash

# Locate SDK up to two folders before this and import pico_sdk_import.cmake
PICO_SDK_PATH=$(find ../.. -name "pico_sdk_init.cmake")
if [[ "${PICO_SDK_PATH}" == "" ]]; then echo "Unable to locate pico-sdk, aborting!" 1>&2; exit 1; fi
export PICO_SDK_PATH=$(dirname "$(pwd)/${PICO_SDK_PATH}")
if [[ -f "./pico_sdk_import.cmake" ]]; then rm -f "./pico_sdk_import.cmake"; fi
cp "${PICO_SDK_PATH}/external/pico_sdk_import.cmake" "./pico_sdk_import.cmake"

# Scrub build folder and build inside of it
if [[ -d "build" ]]; then rm -rf "build"; fi
mkdir build && cd build
cmake .. && make -j$(cat /proc/cpuinfo | grep bogomips | wc -l)
