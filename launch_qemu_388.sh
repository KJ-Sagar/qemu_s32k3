#!/bin/bash
set -euo pipefail

MACHINE_TYPE="s32k388"
KERNEL_PATH="${1:-}"
DEBUG_PARAMS="${2:-}"

if [ -z "$DEBUG_PARAMS" ]; then
    DEBUG_PARAMS="guest_errors"
fi

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}" )" &> /dev/null && pwd )"
QEMU_BIN="$SCRIPT_DIR/build/qemu-system-arm"

if [ -z "$KERNEL_PATH" ]; then
    echo "Usage: $0 <kernel-path> [debug-params]"
    exit 1
fi

if [ ! -x "$QEMU_BIN" ]; then
    echo "QEMU binary not found: $QEMU_BIN"
    exit 1
fi

CAN_ARGS=()
if command -v ip >/dev/null 2>&1 && ip link show vcan0 >/dev/null 2>&1; then
    CAN_ARGS=(
        -object can-bus,id=canbus0
        -object can-host-socketcan,id=socketcan0,if=vcan0,canbus=canbus0
        -machine canbus0=canbus0
    )
else
    ip link add dev vcan0 type vcan
    ip link set up vcan0
    echo "SocketCAN interface vcan0 not available; launching without CAN support"
fi

NET_ARGS=()
if [ -n "${QEMU_NET_ARGS:-}" ]; then
    # shellcheck disable=SC2206
    NET_ARGS=($QEMU_NET_ARGS)
else
    NET_ARGS=(-nic user,model=npcm-gmac)
fi

# Launch selected QEMU
exec "$QEMU_BIN" \
  -M "$MACHINE_TYPE" \
  -kernel "$KERNEL_PATH" \
  -nographic \
  -serial mon:stdio \
  "${CAN_ARGS[@]}" \
  "${NET_ARGS[@]}" \
  -d "$DEBUG_PARAMS"
