#!/bin/bash
# launch_qemu_389.sh - helper to start the s32k389 QEMU machine
#
# Suggested monitor examples:
#  - Use a TCP monitor socket (connect with `telnet`):
#      ./build/qemu-system-arm -M s32k389 -kernel <kernel> -nographic \
#        -monitor tcp:127.0.0.1:4444,server,nowait -serial mon:stdio
#    Then connect from another terminal: `telnet 127.0.0.1 4444` to send monitor commands.
#  - Use a UNIX-domain monitor socket (connect with `nc -U`):
#      ./build/qemu-system-arm -M s32k389 -kernel <kernel> -nographic \
#        -monitor unix:/tmp/qemu-mon,server,nowait -serial mon:stdio
#    Then connect: `nc -U /tmp/qemu-mon`.
#  - For quick single-terminal usage, the helper script uses `-serial mon:stdio` so the
#    monitor and serial share the same stdio (interactive). Use this for scripted monitor
#    commands or when running without a separate monitor terminal.
#
# Suggested launch examples (using this helper script):
#  - User-mode networking (no host TAP required):
#      sudo ./launch_qemu_389.sh --ethernet user <kernel.elf>
#  - TAP networking + SocketCAN (auto-create tap/vcan if missing):
#      sudo ./launch_qemu_389.sh --ethernet tap --ethernet-ifname tap0 \
#           --can socketcan --can-ifname vcan0 <kernel.elf>
#  - CAN-only (internal QEMU CAN bus):
#      sudo ./launch_qemu_389.sh --can internal <kernel.elf>
#
# Notes:
#  - TAP mode will create and bring up the specified TAP interface (requires sudo/root
#    or appropriate CAP_NET_ADMIN privileges). If the TAP already exists it will be used.
#  - SocketCAN mode will create and bring up a vcan interface when requested (requires
#    `ip` command and sufficient privileges).
#  - To capture packets from the host side, run tcpdump or Wireshark on the TAP device:
#      sudo tcpdump -i tap0 -n -e
#
set -euo pipefail

MACHINE_TYPE="s32k389"
KERNEL_PATH=""
DEBUG_PARAMS=""
DEBUG_ARGS=()
CAN_ARGS=()
ETH_ARGS=()
CAN_MODE="auto"
CAN_IFNAME="vcan0"
ETH_BACKEND="off"
ETH_IFNAME="tap0"

usage() {
    cat <<EOF
Usage: $0 [options] <kernel-path> [debug-params]

Options:
  --ethernet <backend>      Enable Ethernet backend. backend: off, user, tap
  --ethernet-ifname <name>  TAP interface name for Ethernet backend (default: tap0)
  --can <mode>              CAN backend. mode: off, auto, internal, socketcan
  --can-ifname <name>       SocketCAN interface name (default: vcan0)
  --help, -h                Show this help message
EOF
}

parse_args() {
    local positional=()

    while [ $# -gt 0 ]; do
        case "$1" in
            --ethernet)
                [ $# -ge 2 ] || { echo "Error: --ethernet requires a value" >&2; exit 1; }
                ETH_BACKEND="$2"
                shift 2
                ;;
            --ethernet=*)
                ETH_BACKEND="${1#*=}"
                shift
                ;;
            --ethernet-ifname)
                [ $# -ge 2 ] || { echo "Error: --ethernet-ifname requires a value" >&2; exit 1; }
                ETH_IFNAME="$2"
                shift 2
                ;;
            --ethernet-ifname=*)
                ETH_IFNAME="${1#*=}"
                shift
                ;;
            --can)
                [ $# -ge 2 ] || { echo "Error: --can requires a value" >&2; exit 1; }
                CAN_MODE="$2"
                shift 2
                ;;
            --can=*)
                CAN_MODE="${1#*=}"
                shift
                ;;
            --can-ifname)
                [ $# -ge 2 ] || { echo "Error: --can-ifname requires a value" >&2; exit 1; }
                CAN_IFNAME="$2"
                shift 2
                ;;
            --can-ifname=*)
                CAN_IFNAME="${1#*=}"
                shift
                ;;
            --help|-h)
                usage
                exit 0
                ;;
            --)
                shift
                positional+=("$@")
                break
                ;;
            -*)
                echo "Error: unknown option '$1'" >&2
                usage >&2
                exit 1
                ;;
            *)
                positional+=("$1")
                shift
                ;;
        esac
    done

    if [ ${#positional[@]} -gt 2 ]; then
        echo "Error: too many positional arguments" >&2
        usage >&2
        exit 1
    fi

    if [ ${#positional[@]} -ge 1 ]; then
        KERNEL_PATH="${positional[0]}"
    fi

    if [ ${#positional[@]} -ge 2 ]; then
        DEBUG_PARAMS="${positional[1]}"
    fi
}

configure_can() {
    case "$CAN_MODE" in
        off)
            echo "CAN disabled"
            CAN_ARGS=()
            ;;
        internal)
            echo "Using internal QEMU CAN bus"
            CAN_ARGS=(
                -object can-bus,id=canbus0
                -machine canbus0=canbus0
            )
            ;;
        auto)
            if command -v ip >/dev/null 2>&1; then
                if ! ip link show "$CAN_IFNAME" >/dev/null 2>&1; then
                    if ! ip link add dev "$CAN_IFNAME" type vcan; then
                        echo "Unable to create $CAN_IFNAME; using an internal QEMU CAN bus"
                        CAN_ARGS=(
                            -object can-bus,id=canbus0
                            -machine canbus0=canbus0
                        )
                    else
                        echo "Created SocketCAN interface $CAN_IFNAME"
                    fi
                fi

                if ip link show "$CAN_IFNAME" >/dev/null 2>&1; then
                    ip link set up "$CAN_IFNAME" >/dev/null 2>&1 || true
                    CAN_ARGS=(
                        -object can-bus,id=canbus0
                        -object can-host-socketcan,id=socketcan0,if="$CAN_IFNAME",canbus=canbus0
                        -machine canbus0=canbus0
                    )
                    echo "Using SocketCAN interface $CAN_IFNAME for QEMU CAN traffic"
                fi
            else
                echo "ip command not available; using an internal QEMU CAN bus"
                CAN_ARGS=(
                    -object can-bus,id=canbus0
                    -machine canbus0=canbus0
                )
            fi
            ;;
        socketcan)
            if ! command -v ip >/dev/null 2>&1; then
                echo "Error: SocketCAN was requested but the 'ip' command is not available" >&2
                exit 1
            fi

            if ! ip link show "$CAN_IFNAME" >/dev/null 2>&1; then
                if ! ip link add dev "$CAN_IFNAME" type vcan; then
                    echo "Error: unable to create SocketCAN interface $CAN_IFNAME" >&2
                    exit 1
                fi
                echo "Created SocketCAN interface $CAN_IFNAME"
            fi

            ip link set up "$CAN_IFNAME" >/dev/null 2>&1 || true
            CAN_ARGS=(
                -object can-bus,id=canbus0
                -object can-host-socketcan,id=socketcan0,if="$CAN_IFNAME",canbus=canbus0
                -machine canbus0=canbus0
            )
            echo "Using SocketCAN interface $CAN_IFNAME for QEMU CAN traffic"
            ;;
        *)
            echo "Error: unsupported CAN mode '$CAN_MODE'" >&2
            exit 1
            ;;
    esac
}

ensure_tap_interface() {
    if ! command -v ip >/dev/null 2>&1; then
        echo "Error: TAP networking was requested but the 'ip' command is not available" >&2
        exit 1
    fi

    if ! ip link show "$ETH_IFNAME" >/dev/null 2>&1; then
        if ! ip tuntap add dev "$ETH_IFNAME" mode tap; then
            echo "Error: unable to create TAP interface $ETH_IFNAME" >&2
            exit 1
        fi
        echo "Created TAP interface $ETH_IFNAME"
    fi

    ip link set "$ETH_IFNAME" up >/dev/null 2>&1 || true
}

configure_ethernet() {
    case "$ETH_BACKEND" in
        off)
            echo "Ethernet disabled"
            ETH_ARGS=()
            ;;
        user)
            echo "Using user-mode Ethernet networking"
            # legacy -nic convenience creates both netdev and nic config which
            # registers a NIC mapping that platform code can match
            ETH_ARGS=( -nic "user,id=gmac0" )
            ;;
        tap)
            if [ -z "$ETH_IFNAME" ]; then
                ETH_IFNAME="tap0"
            fi
            ensure_tap_interface
            echo "Using TAP Ethernet backend '$ETH_IFNAME' (legacy -nic id=gmac0)"
            # Use -nic (legacy) so a NIC configuration entry is created with id=gmac0
            ETH_ARGS=( -nic "tap,ifname=$ETH_IFNAME,id=gmac0,script=no,downscript=no" )
            ;;
        *)
            echo "Error: unsupported Ethernet backend '$ETH_BACKEND'" >&2
            exit 1
            ;;
    esac
}

parse_args "$@"

if [ -z "$DEBUG_PARAMS" ]; then
    DEBUG_PARAMS="guest_errors"
fi

if [ "$DEBUG_PARAMS" = "debug" ] || [ "$DEBUG_PARAMS" = "gdb" ]; then
    DEBUG_ARGS=(-S -gdb tcp::1234)
    DEBUG_PARAMS="guest_errors"
    echo "Starting QEMU in GDB-stopped mode"
else
    echo "Starting QEMU normally"
fi

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}" )" &> /dev/null && pwd )"
QEMU_BIN="$SCRIPT_DIR/build/qemu-system-arm"

if [ -z "$KERNEL_PATH" ]; then
    usage
    exit 1
fi

if [ ! -x "$QEMU_BIN" ]; then
    echo "QEMU binary not found: $QEMU_BIN"
    exit 1
fi

configure_can
configure_ethernet

# Launch selected QEMU
exec "$QEMU_BIN" \
  -M "$MACHINE_TYPE" \
  -kernel "$KERNEL_PATH" \
  -nographic \
  -serial mon:stdio \
  "${DEBUG_ARGS[@]}" \
  "${CAN_ARGS[@]}" \
  "${ETH_ARGS[@]}" \
  -d "$DEBUG_PARAMS"
