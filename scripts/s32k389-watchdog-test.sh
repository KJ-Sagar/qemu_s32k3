#!/usr/bin/env bash
set -euo pipefail

repo_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
qemu_bin="${QEMU_BIN:-$repo_dir/build/qemu-system-arm}"
firmware="${S32K389_WATCHDOG_ELF:-$repo_dir/Eth_InternalLoopback_S32K388/Debug_FLASH/Eth_InternalLoopback_S32K388_WatchdogFault.elf}"
action="${1:-reset}"
monitor_port="${MONITOR_PORT:-5555}"
run_seconds="${RUN_SECONDS:-3}"
log_file="${WATCHDOG_LOG:-$repo_dir/s32k389-watchdog-test.log}"

if [[ "$action" != "reset" && "$action" != "pause" ]]; then
    printf 'usage: %s [reset|pause]\n' "$0" >&2
    exit 2
fi

for tool in "$qemu_bin" "$firmware" nc timeout; do
    if [[ ! -e "$tool" && "$tool" != "nc" && "$tool" != "timeout" ]]; then
        printf 'missing required file: %s\n' "$tool" >&2
        exit 1
    fi
done
command -v nc >/dev/null || { printf 'missing required command: nc\n' >&2; exit 1; }

if nc -z 127.0.0.1 "$monitor_port" >/dev/null 2>&1; then
    printf 'monitor port %s is already in use\n' "$monitor_port" >&2
    exit 1
fi

rm -f "$log_file"
"$qemu_bin" \
    -M s32k389 \
    -kernel "$firmware" \
    -watchdog-action "$action" \
    -d int,guest_errors \
    -D "$log_file" \
    -msg timestamp=on \
    -display none \
    -serial null \
    -monitor "telnet:127.0.0.1:${monitor_port},server=on,wait=off" &
qemu_pid=$!
trap 'kill "$qemu_pid" 2>/dev/null || true; wait "$qemu_pid" 2>/dev/null || true' EXIT

for _ in $(seq 1 200); do
    if ! kill -0 "$qemu_pid" 2>/dev/null; then
        printf 'QEMU exited before opening monitor port %s\n' "$monitor_port" >&2
        exit 1
    fi
    if nc -z 127.0.0.1 "$monitor_port" >/dev/null 2>&1; then
        break
    fi
    sleep 0.1
done

if ! nc -z 127.0.0.1 "$monitor_port" >/dev/null 2>&1; then
    printf 'QEMU monitor did not open on port %s\n' "$monitor_port" >&2
    exit 1
fi

sleep "$run_seconds"

status="$(printf 'info status\n' |
    timeout 3 nc 127.0.0.1 "$monitor_port" 2>/dev/null |
    tr -d '\000' || true)"
printf '%s\n' "$status"

if ! grep -q 's32k3_swt\[0\]: watchdog timeout' "$log_file"; then
    printf 'watchdog timeout was not observed; see %s\n' "$log_file" >&2
    exit 1
fi

if [[ "$action" == "pause" ]]; then
    grep -q 'VM status: paused (watchdog)' <<<"$status" || {
        printf 'expected watchdog pause status was not observed\n' >&2
        exit 1
    }
else
    grep -q 'VM status: running' <<<"$status" || {
        printf 'expected running status after watchdog reset was not observed\n' >&2
        exit 1
    }
fi

printf 'watchdog %s test passed; log: %s\n' "$action" "$log_file"
