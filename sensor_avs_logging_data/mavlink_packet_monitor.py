"""
MAVLink Packet Drop Monitor — 4x COM Ports (SiK 915 MHz)
Tracks sequence numbers per (sysid, compid) to detect dropped packets.

Requirements:
    pip install pymavlink pyserial
"""

import threading
import time
import serial
from collections import defaultdict
from pymavlink import mavutil

# ── Configure your COM ports and baud rate ──────────────────────────────────
PORTS = [
    "COM4",
]
BAUD = 57600       # Match your SiK radio baud rate (try 115200 if 57600 gets nothing)

# ── Diagnostics ─────────────────────────────────────────────────────────────
RAW_PROBE    = True   # Set True to confirm raw bytes arrive before MAVLink parsing
RAW_DURATION = 10     # Seconds to listen for raw bytes per port before full monitor
# ────────────────────────────────────────────────────────────────────────────

stats = {port: defaultdict(lambda: {"total": 0, "dropped": 0, "last_seq": -1}) for port in PORTS}
stats_lock = threading.Lock()
stop_event = threading.Event()


def probe_raw(port):
    """Listen for raw bytes on a port to confirm any data is flowing at all."""
    print(f"[{port}] RAW PROBE: listening for {RAW_DURATION}s at {BAUD} baud...")
    try:
        ser = serial.Serial(port, baudrate=BAUD, timeout=1)
    except Exception as e:
        print(f"[{port}] RAW PROBE ERROR: {e}")
        return False

    deadline = time.time() + RAW_DURATION
    byte_count = 0
    mavlink_starts = 0

    while time.time() < deadline:
        chunk = ser.read(64)
        if chunk:
            byte_count += len(chunk)
            # MAVLink v1 starts with 0xFE, v2 starts with 0xFD
            mavlink_starts += chunk.count(0xFE) + chunk.count(0xFD)

    ser.close()

    if byte_count == 0:
        print(f"[{port}] ❌ RAW PROBE: NO bytes received — check baud rate, cable, or vehicle power")
        return False
    else:
        print(f"[{port}] ✅ RAW PROBE: {byte_count} bytes received, "
              f"{mavlink_starts} possible MAVLink start bytes (0xFE/0xFD)")
        if mavlink_starts == 0:
            print(f"[{port}]    ⚠️  No MAVLink framing detected — wrong baud rate?")
            print(f"[{port}]    Try BAUD = 115200 if currently 57600, or vice versa.")
        return True


def monitor_port(port):
    if RAW_PROBE:
        ok = probe_raw(port)
        if not ok:
            print(f"[{port}] Skipping MAVLink monitor (no raw data).")
            return

    print(f"[{port}] Connecting MAVLink parser...")
    try:
        conn = mavutil.mavlink_connection(port, baud=BAUD)
        print(f"[{port}] Connected. Listening for MAVLink messages...")
    except Exception as e:
        print(f"[{port}] ERROR: {e}")
        return

    while not stop_event.is_set():
        try:
            msg = conn.recv_match(blocking=True, timeout=1.0)
            if msg is None:
                continue

            hdr = msg.get_header()
            sysid  = hdr.srcSystem
            compid = hdr.srcComponent
            seq    = hdr.seq          # ← fixed: was hdr.mseq

            with stats_lock:
                entry = stats[port][(sysid, compid)]
                last = entry["last_seq"]

                if last == -1:
                    dropped = 0
                else:
                    expected = (last + 1) % 256
                    dropped = (seq - expected) % 256 if seq != expected else 0

                entry["total"]   += 1
                entry["dropped"] += dropped
                entry["last_seq"] = seq

        except Exception as e:
            if not stop_event.is_set():
                print(f"[{port}] Read error: {e}")
            break


def print_stats():
    while not stop_event.is_set():
        time.sleep(5)
        print("\n" + "=" * 70)
        print(f"{'Port':<8} {'SysID':<7} {'CompID':<8} {'Received':>10} {'Dropped':>9} {'Loss %':>8}")
        print("-" * 70)
        with stats_lock:
            any_data = False
            for port in PORTS:
                for (sysid, compid), entry in sorted(stats[port].items()):
                    any_data = True
                    total   = entry["total"]
                    dropped = entry["dropped"]
                    loss    = (dropped / (total + dropped) * 100) if (total + dropped) > 0 else 0.0
                    print(f"{port:<8} {sysid:<7} {compid:<8} {total:>10} {dropped:>9} {loss:>7.1f}%")
            if not any_data:
                print("  (no MAVLink messages received yet)")
        print("=" * 70)


if __name__ == "__main__":
    # Print active config
    print(f"Config: ports={PORTS}  baud={BAUD}  raw_probe={RAW_PROBE}\n")

    threads = []
    for port in PORTS:
        t = threading.Thread(target=monitor_port, args=(port,), daemon=True)
        t.start()
        threads.append(t)

    printer = threading.Thread(target=print_stats, daemon=True)
    printer.start()

    print("\nMonitoring... Press Ctrl+C to stop.\n")
    try:
        while True:
            time.sleep(0.5)
    except KeyboardInterrupt:
        print("\nStopping...")
        stop_event.set()

    for t in threads:
        t.join(timeout=2)

    print("\n── Final Summary ──────────────────────────────────────────────────────")
    for port in PORTS:
        for (sysid, compid), entry in sorted(stats[port].items()):
            total   = entry["total"]
            dropped = entry["dropped"]
            loss    = (dropped / (total + dropped) * 100) if (total + dropped) > 0 else 0.0
            print(f"  {port} | SysID={sysid} CompID={compid} | "
                  f"Received={total}  Dropped={dropped}  Loss={loss:.1f}%")
