#!/bin/bash
QEMU_DIR="S32K148"
MACHINE_TYPE="s32k148-evb"
KERNEL_PATH=$1
DEBUG_PARAMS=$2

if [ -z "$DEBUG_PARAMS" ]; then
    DEBUG_PARAMS=guest_errors
fi

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}" )" &> /dev/null && pwd )"

# Launch selected QEMU
$SCRIPT_DIR/$QEMU_DIR/build/qemu-system-arm \
-M $MACHINE_TYPE \
-kernel $KERNEL_PATH \
-nographic \
-semihosting \
-serial mon:stdio \
-object can-bus,id=canbus0 \
-object can-host-socketcan,id=canhost0,if=vcan0,canbus=canbus0 \
-d $DEBUG_PARAMS
