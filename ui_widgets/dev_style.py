# ui_widgets/dev_style.py
"""
Shared visual constants for all device plots.
Import from here to keep colors, markers, and line styles in sync across all tabs.
Supports up to 4 simultaneous devices.
"""

DEV_COLORS = [
    "#1565C0",   # dev1 — blue
    "#C62828",   # dev2 — red
    "#2E7D32",   # dev3 — green
    "#E65100",   # dev4 — orange
]

DEV_MARKERS = [
    "o",   # dev1 — circle
    "s",   # dev2 — square
    "^",   # dev3 — triangle
    "D",   # dev4 — diamond
]

DEV_LINE_STYLES = [
    "-",    # dev1 — solid
    "--",   # dev2 — dashed
    "-.",   # dev3 — dash-dot
    ":",    # dev4 — dotted
]


def dev_color(i: int) -> str:
    return DEV_COLORS[i % len(DEV_COLORS)]

def dev_marker(i: int) -> str:
    return DEV_MARKERS[i % len(DEV_MARKERS)]

def dev_line_style(i: int) -> str:
    return DEV_LINE_STYLES[i % len(DEV_LINE_STYLES)]
