"""
ULog (.ulg) File Parser and Plotter
Requires: pip install pyulog matplotlib pandas
"""

import sys
import os
import ctypes
from typing import Optional
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mpl
from pyulog import ULog


# ── HiDPI fix for Windows Surface Pro ────────────────────────────────────────

try:
    ctypes.windll.shcore.SetProcessDpiAwareness(2)
except Exception:
    pass

mpl.rcParams.update({
    "figure.dpi":         120,
    "savefig.dpi":        150,
    "font.size":          12,
    "axes.titlesize":     13,
    "axes.labelsize":     11,
    "xtick.labelsize":    10,
    "ytick.labelsize":    10,
    "legend.fontsize":    10,
    "lines.linewidth":    1.5,
    "axes.linewidth":     1.0,
    "grid.linewidth":     0.6,
    "grid.alpha":         0.4,
    "axes.spines.top":    False,
    "axes.spines.right":  False,
    "figure.facecolor":   "white",
    "axes.facecolor":     "#f9f9f9",
    "ytick.major.pad":    4,
    "axes.ymargin":       0.15,
})

plt.style.use("seaborn-v0_8-whitegrid")


# ── Configuration ─────────────────────────────────────────────────────────────

ULG_FILE = "your_file.ulg"   # <-- Change this to your file path

# Topics to plot: { "topic_name": ["field1", "field2", ...] }
# Leave empty {} to auto-plot all non-constant numeric fields from top topics.
TOPICS_TO_PLOT = {
    # Examples:
    # "vehicle_attitude": ["roll", "pitch", "yaw"],
    # "vehicle_local_position": ["x", "y", "z"],
    # "battery_status": ["voltage_v", "current_a"],
}

MAX_AUTO_TOPICS    = 5   # Max topics in auto mode
MAX_FIELDS_PER_FIG = 6   # Max subplots per figure (splits into multiple if more)
MIN_STD_RATIO      = 1e-6  # Fields with std/|mean| below this are treated as constant


# ── Helpers ───────────────────────────────────────────────────────────────────

def load_ulog(filepath: str) -> ULog:
    print(f"\nLoading: {filepath}")
    ulog = ULog(filepath)
    print(f"  Duration : {ulog.last_timestamp / 1e6:.2f} s")
    print(f"  Topics   : {[d.name for d in ulog.data_list]}")
    return ulog


def topic_to_dataframe(ulog: ULog, topic_name: str, multi_id: int = 0) -> Optional[pd.DataFrame]:
    matches = [d for d in ulog.data_list if d.name == topic_name and d.multi_id == multi_id]
    if not matches:
        print(f"  [!] Topic '{topic_name}' not found.")
        return None
    df = pd.DataFrame(matches[0].data)
    df["timestamp_s"] = df["timestamp"] / 1e6
    return df


def filter_constant_fields(df: pd.DataFrame, fields: list) -> list:
    """Remove fields that are constant or near-constant — boring to plot."""
    keep = []
    for f in fields:
        if f not in df.columns:
            continue
        series = df[f].dropna()
        if len(series) < 2:
            continue
        std = series.std()
        mean = abs(series.mean())
        # Keep if std is meaningfully large relative to the signal
        ratio = std / mean if mean > 1e-9 else std
        if ratio >= MIN_STD_RATIO and std > 1e-12:
            keep.append(f)
        else:
            print(f"    Skipping constant field: {f}")
    return keep


def chunk_list(lst: list, n: int) -> list:
    """Split list into chunks of size n."""
    return [lst[i:i+n] for i in range(0, len(lst), n)]


# ── Plot ──────────────────────────────────────────────────────────────────────

def plot_topic(df: pd.DataFrame, topic_name: str, fields: list):
    """Plot fields for a topic, splitting into multiple figures if needed."""
    available = [f for f in fields if f in df.columns]
    missing   = [f for f in fields if f not in df.columns]
    if missing:
        print(f"  [!] Fields not found in '{topic_name}': {missing}")
    if not available:
        print(f"  [!] No plottable fields for '{topic_name}'.")
        return

    colors   = plt.cm.tab10.colors
    chunks   = chunk_list(available, MAX_FIELDS_PER_FIG)
    n_figs   = len(chunks)

    for fig_idx, chunk in enumerate(chunks):
        n = len(chunk)
        fig, axes = plt.subplots(
            n, 1,
            figsize=(13, max(5, 2.8 * n)),
            sharex=True
        )
        if n == 1:
            axes = [axes]

        for i, (ax, field) in enumerate(zip(axes, chunk)):
            ax.plot(df["timestamp_s"], df[field],
                    color=colors[i % len(colors)],
                    linewidth=1.5)
            # Short label: trim long names
            label = field if len(field) <= 20 else field[:18] + "…"
            ax.set_ylabel(label, fontsize=10, labelpad=6)
            ax.yaxis.set_tick_params(labelsize=9)
            # Format y-axis ticks to avoid crowding
            ax.yaxis.set_major_locator(mpl.ticker.MaxNLocator(nbins=4, prune="both"))

        axes[-1].set_xlabel("Time (s)", labelpad=8)

        suffix = f" ({fig_idx+1}/{n_figs})" if n_figs > 1 else ""
        fig.suptitle(f"Topic: {topic_name}{suffix}",
                     fontsize=14, fontweight="bold", y=1.01)
        plt.tight_layout(pad=2.5, h_pad=1.2)
        plt.show()


# ── Auto Plot ─────────────────────────────────────────────────────────────────

def auto_plot(ulog: ULog):
    """Auto-plot non-constant numeric fields for the first N topics."""
    topics = ulog.data_list[:MAX_AUTO_TOPICS]
    for data in topics:
        df = topic_to_dataframe(ulog, data.name, data.multi_id)
        if df is None:
            continue

        numeric_fields = [
            c for c in df.columns
            if c not in ("timestamp", "timestamp_s")
            and pd.api.types.is_numeric_dtype(df[c])
        ]

        interesting = filter_constant_fields(df, numeric_fields)

        if not interesting:
            print(f"  Skipping '{data.name}' — all fields are constant.")
            continue

        print(f"  Plotting '{data.name}': {interesting}")
        plot_topic(df, data.name, interesting)


# ── Entry Point ───────────────────────────────────────────────────────────────

def main():
    filepath = sys.argv[1] if len(sys.argv) > 1 else ULG_FILE

    if not os.path.exists(filepath):
        print(f"Error: File not found — {filepath}")
        sys.exit(1)

    ulog = load_ulog(filepath)

    if TOPICS_TO_PLOT:
        for topic, fields in TOPICS_TO_PLOT.items():
            df = topic_to_dataframe(ulog, topic)
            if df is not None:
                plot_topic(df, topic, fields)
    else:
        print(f"\nNo topics specified — auto-plotting first {MAX_AUTO_TOPICS} topics "
              f"(skipping constant fields, max {MAX_FIELDS_PER_FIG} per figure)...")
        auto_plot(ulog)


if __name__ == "__main__":
    main()
