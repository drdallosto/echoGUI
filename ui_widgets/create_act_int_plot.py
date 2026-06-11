# ui_widgets/create_act_int_plot.py
import numpy as np
from PyQt6.QtWidgets import (QVBoxLayout, QHBoxLayout, QSizePolicy,
                              QWidget, QLabel, QLineEdit, QSlider)
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure

from ui_widgets.dev_style import dev_color, dev_marker, dev_line_style


def createActIntPlot(tab, plot_act_int_btn, cap_btn, log_csv_data_btn,
                     cap_off_data_btn, dev_names):

    layout = QVBoxLayout(tab)
    layout.setContentsMargins(0, 0, 0, 0)

    bold_font = QFont()
    bold_font.setBold(True)

    # ── threshold bar ──────────────────────────────────────────────────
    top_widget = QWidget()
    top_widget.setStyleSheet("background-color: lightgray;")
    top_layout = QHBoxLayout(top_widget)

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
    t_lbl,  log_data_entry       = _labeled_entry("Log Duration\n   (seconds)",      "10")

    for lbl, entry in [(ai_lbl, act_int_thresh_entry),
                       (q_lbl,  q_thresh_entry),
                       (h_lbl,  hist_thresh_entry),
                       (t_lbl,  log_data_entry)]:
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

    # ── scale slider bar ───────────────────────────────────────────────
    slider_widget = QWidget()
    slider_widget.setStyleSheet("background-color: #e8e8e8;")
    slider_layout = QHBoxLayout(slider_widget)
    slider_layout.setContentsMargins(10, 4, 10, 4)

    def _labeled_slider(label_text, min_val, max_val, default_val, width=160):
        lbl = QLabel(label_text)
        lbl.setFont(bold_font)
        lbl.setFixedWidth(90)
        val_lbl = QLabel(str(default_val))
        val_lbl.setFixedWidth(40)
        val_lbl.setStyleSheet("color: #333333;")
        slider = QSlider(Qt.Orientation.Horizontal)
        slider.setMinimum(min_val)
        slider.setMaximum(max_val)
        slider.setValue(default_val)
        slider.setFixedWidth(width)
        slider.valueChanged.connect(lambda v: val_lbl.setText(str(v)))
        return lbl, slider, val_lbl

    # Intensity Y-axis
    int_sep = QLabel("Intensity Axis:")
    int_sep.setFont(bold_font)
    int_sep.setStyleSheet("color: #1565C0;")
    slider_layout.addWidget(int_sep)
    slider_layout.addSpacing(6)

    int_min_lbl, int_min_slider, int_min_val = _labeled_slider("Y-Min", -500, 0,    0)
    int_max_lbl, int_max_slider, int_max_val = _labeled_slider("Y-Max",   10, 1000, 200)

    for w in (int_min_lbl, int_min_slider, int_min_val):
        slider_layout.addWidget(w)
    slider_layout.addSpacing(8)
    for w in (int_max_lbl, int_max_slider, int_max_val):
        slider_layout.addWidget(w)

    slider_layout.addSpacing(24)

    # Azimuth Y-axis
    az_sep = QLabel("Azimuth Axis:")
    az_sep.setFont(bold_font)
    az_sep.setStyleSheet("color: #2E7D32;")
    slider_layout.addWidget(az_sep)
    slider_layout.addSpacing(6)

    az_min_lbl, az_min_slider, az_min_val = _labeled_slider("Y-Min", -360, 0,    -180)
    az_max_lbl, az_max_slider, az_max_val = _labeled_slider("Y-Max",    0, 360,   180)

    for w in (az_min_lbl, az_min_slider, az_min_val):
        slider_layout.addWidget(w)
    slider_layout.addSpacing(8)
    for w in (az_max_lbl, az_max_slider, az_max_val):
        slider_layout.addWidget(w)

    slider_layout.addStretch()
    layout.addWidget(slider_widget)

    # ── figure ─────────────────────────────────────────────────────────
    figure = Figure()
    canvas = FigureCanvas(figure)
    canvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
    layout.addWidget(canvas)

    # ── axes ───────────────────────────────────────────────────────────
    intAx = figure.add_subplot(2, 1, 1)
    azAx  = figure.add_subplot(2, 1, 2, sharex=intAx)
    figure.subplots_adjust(hspace=0.35)

    # disable Y autoscaling so sliders are always in control
    intAx.set_autoscaley_on(False)
    azAx.set_autoscaley_on(False)

    intAx.set_ylim(0, 200)
    azAx.set_ylim(-180, 180)

    act_int_lines = {}
    azm_lines     = {}

    for i, name in enumerate(dev_names):
        color  = dev_color(i)
        marker = dev_marker(i)
        ls     = dev_line_style(i)

        line_act, = intAx.plot(
            [], [], ls,
            color=color, linewidth=1.4,
            marker=marker, markersize=3,
            label=name,
        )
        line_az, = azAx.plot(
            [], [], ls,
            color=color, linewidth=1.4,
            marker=marker, markersize=3,
            label=name,
        )
        act_int_lines[name] = line_act
        azm_lines[name]     = line_az

    intAx.axhline(0, color="#cccccc", linewidth=0.6, linestyle="--", zorder=0)
    azAx.axhline(0,  color="#cccccc", linewidth=0.6, linestyle="--", zorder=0)

    intAx.set_title("Active Intensity",  fontsize=10, fontweight="bold", pad=6)
    azAx.set_title("Azimuth (filtered)", fontsize=10, fontweight="bold", pad=6)

    intAx.set_ylabel("Intensity",  fontsize=8)
    azAx.set_ylabel("Azimuth (°)", fontsize=8)
    azAx.set_xlabel("Time (s)",    fontsize=8)

    intAx.set_xlim(0, 10)
    azAx.set_xlim(0, 10)

    for ax in (intAx, azAx):
        ax.tick_params(labelsize=7)
        ax.grid(True, color="#eeeeee", linewidth=0.5)
        ax.legend(loc="upper left", fontsize=7, framealpha=0.6)
        for spine in ax.spines.values():
            spine.set_visible(False)

    canvas.draw()

    # ── wire sliders → axes ────────────────────────────────────────────
    def _update_int_ylim():
        lo = int_min_slider.value()
        hi = int_max_slider.value()
        if hi > lo:
            intAx.set_ylim(lo, hi)
            canvas.draw_idle()

    def _update_az_ylim():
        lo = az_min_slider.value()
        hi = az_max_slider.value()
        if hi > lo:
            azAx.set_ylim(lo, hi)
            canvas.draw_idle()

    int_min_slider.valueChanged.connect(lambda _: _update_int_ylim())
    int_max_slider.valueChanged.connect(lambda _: _update_int_ylim())
    az_min_slider.valueChanged.connect(lambda _: _update_az_ylim())
    az_max_slider.valueChanged.connect(lambda _: _update_az_ylim())

    # ── button row ─────────────────────────────────────────────────────
    btn_row = QHBoxLayout()
    btn_row.addStretch()
    for btn in (plot_act_int_btn, cap_btn, log_csv_data_btn, cap_off_data_btn):
        btn_row.addWidget(btn)
        btn_row.addSpacing(12)
    btn_row.addStretch()
    layout.addLayout(btn_row)

    return (act_int_lines, azm_lines,
            intAx, azAx, canvas,
            act_int_thresh_entry, q_thresh_entry,
            hist_thresh_entry, log_data_entry)
