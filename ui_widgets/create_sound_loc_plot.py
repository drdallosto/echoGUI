# ui_widgets/create_sound_loc_plot.py
import numpy as np
from PyQt6.QtWidgets import (QVBoxLayout, QHBoxLayout, QSizePolicy,
                              QWidget, QLabel, QLineEdit)
from PyQt6.QtGui import QFont
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.ticker import MultipleLocator
from matplotlib.patches import Circle, Polygon as MplPolygon

from ui_widgets.dev_style import dev_color, dev_marker

small_rad   = 1
HEAT_GRID_N = 150       # heatmap grid resolution (150×150)
PLOT_RANGE  = 3.0       # plot spans -PLOT_RANGE … +PLOT_RANGE

# fixed corner positions: top-left, top-right, bottom-right, bottom-left
dev_x_pos  = [-1,  1,  1, -1]
dev_y_pos  = [ 1,  1, -1, -1]
dev_labels = [(-0.35,  0.20),
              ( 0.10,  0.20),
              ( 0.10, -0.30),
              (-0.35, -0.30)]


def createSoundLoc(tab, dev_names, sound_loc_btn, log_data_btn):

    figure = Figure()
    canvas = FigureCanvas(figure)
    canvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

    layout = QVBoxLayout(tab)
    layout.setContentsMargins(0, 0, 0, 0)

    # ── threshold / control bar ────────────────────────────────────────
    top_widget = QWidget()
    top_widget.setStyleSheet("background-color: lightgray;")
    top_layout = QHBoxLayout(top_widget)

    bold_font = QFont()
    bold_font.setBold(True)

    def _labeled_entry(label_text, default_val):
        lbl = QLabel(label_text)
        lbl.setFont(bold_font)
        entry = QLineEdit(default_val)
        entry.setFixedWidth(75)
        entry.setStyleSheet("QLineEdit { background-color: white; }")
        return lbl, entry

    ai_lbl, act_int_thresh_entry = _labeled_entry("Active Intensity\n   Threshold", "20")
    q_lbl,  q_thresh_entry       = _labeled_entry("Q-Factor\nThreshold",             "2")
    h_lbl,  hist_thresh_entry    = _labeled_entry("Histogram\nThreshold",            "5")
    bw_lbl, beam_width_entry     = _labeled_entry("Beam Width\n    (deg)",           "30")
    tc_lbl, time_const_entry     = _labeled_entry("Time Const\n      (s)",           "5")

    for lbl, entry in [(ai_lbl, act_int_thresh_entry),
                       (q_lbl,  q_thresh_entry),
                       (h_lbl,  hist_thresh_entry),
                       (bw_lbl, beam_width_entry),
                       (tc_lbl, time_const_entry)]:
        top_layout.addWidget(lbl)
        top_layout.addWidget(entry)
        top_layout.addSpacing(20)

    # color-coded device chips
    sep = QLabel("│")
    sep.setStyleSheet("color: #888888;")
    top_layout.addWidget(sep)
    top_layout.addSpacing(10)
    for i, name in enumerate(dev_names):
        chip = QLabel(f"● {name}")
        chip.setFont(bold_font)
        chip.setStyleSheet(f"color: {dev_color(i)};")
        top_layout.addWidget(chip)
        top_layout.addSpacing(12)

    top_layout.addStretch()
    layout.addWidget(top_widget)
    layout.addWidget(canvas)

    # ── axes ──────────────────────────────────────────────────────────
    ax = figure.add_subplot(111)
    ax.set_aspect("equal", adjustable="box")

    theta = np.linspace(0, 2 * np.pi, 360)

    # ── heatmap layer (zorder=1, drawn first / lowest) ─────────────────
    # Initialised as fully transparent RGBA — worker writes into this each frame
    heat_init = np.zeros((HEAT_GRID_N, HEAT_GRID_N, 4), dtype=np.float32)
    heatmap_img = ax.imshow(
        heat_init,
        extent=[-PLOT_RANGE, PLOT_RANGE, -PLOT_RANGE, PLOT_RANGE],
        origin="lower",
        aspect="equal",
        zorder=1,
        interpolation="bilinear",
    )

    # outer dashed reference circle
    ax.plot(2.6 * np.cos(theta), 2.6 * np.sin(theta),
            color="#cccccc", linewidth=0.6, linestyle="--", zorder=0)

    # compass rose
    for angle_deg, label, ha, va in [
        ( 90, "N", "center", "bottom"),
        (  0, "E", "left",   "center"),
        (270, "S", "center", "top"),
        (180, "W", "right",  "center"),
    ]:
        r = np.radians(angle_deg)
        ax.text(2.82 * np.cos(r), 2.82 * np.sin(r), label,
                ha=ha, va=va, fontsize=9, fontweight="bold", color="#999999")

    # ── beam wedge patches (zorder=2, between heatmap and lines) ──────
    beam_patches = {}
    for i, name in enumerate(dev_names):
        color = dev_color(i)
        patch = MplPolygon(
            np.zeros((3, 2)), closed=True,
            facecolor=color, alpha=0.13,
            edgecolor=color, linewidth=0.8,
            linestyle="--", zorder=2, visible=False,
        )
        ax.add_patch(patch)
        beam_patches[name] = patch

    # ── devices (zorder=4-5) ──────────────────────────────────────────
    azimuth_lines = {}
    dev_positions = {}

    for i, name in enumerate(dev_names):
        color  = dev_color(i)
        marker = dev_marker(i)

        ax.scatter(dev_x_pos[i], dev_y_pos[i],
                   s=90, color=color, marker=marker, zorder=5)

        dx, dy = dev_labels[i]
        ax.text(dev_x_pos[i] + dx, dev_y_pos[i] + dy, name,
                fontsize=8, fontweight="bold", color=color)

        halo = Circle((dev_x_pos[i], dev_y_pos[i]), small_rad,
                      fill=False, edgecolor=color, linewidth=0.9, alpha=0.30, zorder=3)
        ax.add_patch(halo)

        # centre-line ray drawn on top of wedge and heatmap
        line, = ax.plot([], [], "-", color=color, linewidth=1.6, alpha=0.95, zorder=4)
        azimuth_lines[name] = line
        dev_positions[name] = (dev_x_pos[i], dev_y_pos[i])

    # ── source estimate artists ────────────────────────────────────────
    source_point, = ax.plot([], [], "*", color="gold",
                            markersize=14, markeredgecolor="#b8860b",
                            markeredgewidth=0.6, zorder=10)

    source_ring = Circle((0, 0), 0.0, fill=True, facecolor="gold",
                         edgecolor="#b8860b", linewidth=0.8, alpha=0.20, zorder=9)
    source_ring.set_visible(False)
    ax.add_patch(source_ring)

    source_status = ax.text(0, -2.88, "", ha="center", va="bottom",
                            fontsize=8, color="#555555", style="italic")

    # ── grid / styling ────────────────────────────────────────────────
    ax.axhline(0, color="#dddddd", linewidth=0.7, zorder=0)
    ax.axvline(0, color="#dddddd", linewidth=0.7, zorder=0)

    ax.set_title("Sound Localization", fontsize=11, fontweight="bold", pad=8)
    ax.xaxis.set_major_locator(MultipleLocator(1))
    ax.yaxis.set_major_locator(MultipleLocator(1))
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.grid(True, color="#eeeeee", linewidth=0.5)
    ax.set_xlim(-PLOT_RANGE, PLOT_RANGE)
    ax.set_ylim(-PLOT_RANGE, PLOT_RANGE)

    for spine in ax.spines.values():
        spine.set_visible(False)

    canvas.draw()

    # ── button row ────────────────────────────────────────────────────
    btn_row = QHBoxLayout()
    btn_row.addStretch()
    btn_row.addWidget(sound_loc_btn)
    btn_row.addSpacing(20)
    btn_row.addWidget(log_data_btn)
    btn_row.addStretch()
    layout.addLayout(btn_row)

    # ── scroll zoom ───────────────────────────────────────────────────
    def on_scroll(event, ax, canvas):
        scale = 0.9 if event.button == "up" else 1.1
        ax.set_xlim([x * scale for x in ax.get_xlim()])
        ax.set_ylim([y * scale for y in ax.get_ylim()])
        canvas.draw_idle()

    canvas.mpl_connect("scroll_event", lambda e: on_scroll(e, ax, canvas))

    return (azimuth_lines, dev_positions, canvas,
            act_int_thresh_entry, q_thresh_entry, hist_thresh_entry,
            source_point, source_ring, source_status,
            heatmap_img, beam_patches,
            beam_width_entry, time_const_entry)
