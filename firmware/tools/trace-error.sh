#!/bin/bash

# Path to the addr2line tool
ADDR2LINE_TOOL="$HOME/.platformio/packages/toolchain-xtensa-esp32s3/bin/xtensa-esp32s3-elf-addr2line"

# ELF file path
ELF_FILE=".pio/build/development/firmware.elf"

# Check if at least one argument is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <trace_address_1> [trace_address_2] ... [trace_address_N]"
    exit 1
fi

# Perform the addr2line call with the provided addresses
$ADDR2LINE_TOOL -C -a -i -f -p -e $ELF_FILE "$@"