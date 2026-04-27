import numpy as np
from PyQt6.QtWidgets import QVBoxLayout, QHBoxLayout, QSizePolicy, QWidget, QLabel, QLineEdit
from PyQt6.QtGui import QFont
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


circle_radius = 3

# fixed positions — dev1 top-left, dev2 top-right, dev3 bottom-right, dev4 bottom-left
dev_x_pos = [-1,  1,  1, -1]
dev_y_pos = [ 1,  1, -1, -1]

# label offsets so text doesn't overlap the dot
dev_labels = [(-0.3, 0.2), (0.1, 0.2), (0.1, -0.3), (-0.3, -0.3)]


def createSoundLoc(tab, dev_names, sound_loc_btn):
    figure = Figure()
    canvas = FigureCanvas(figure)
    canvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

    layout = QVBoxLayout(tab)
    layout.setContentsMargins(0, 0, 0, 0)

    # threshold bar at the top
    top_widget = QWidget()
    top_widget.setStyleSheet("background-color: lightgray;")
    top_layout = QHBoxLayout(top_widget)

    bold_font = QFont()
    bold_font.setBold(True)

    act_int_lbl = QLabel("Active Intensity\n   Threshold")
    act_int_lbl.setFont(bold_font)
    act_int_thresh_entry = QLineEdit("20")
    act_int_thresh_entry.setFixedWidth(75)
    act_int_thresh_entry.setStyleSheet("QLineEdit { background-color: white; }")
    top_layout.addWidget(act_int_lbl)
    top_layout.addWidget(act_int_thresh_entry)
    top_layout.addStretch()

    layout.addWidget(top_widget)
    layout.addWidget(canvas)

    ax = figure.add_subplot(111)
    ax.set_aspect("equal")

    # one blue dot per device with a label
    for i, name in enumerate(dev_names):
        ax.scatter(dev_x_pos[i], dev_y_pos[i], s=100, color="blue")
        dx, dy = dev_labels[i] 
        ax.text(dev_x_pos[i] + dx, dev_y_pos[i] + dy, name, fontsize=8, color="blue")

    # lines at (0,0)
    ax.axhline(0, color="black", linewidth=0.8)
    ax.axvline(0, color="black", linewidth=0.8)

    # circle
    theta = np.linspace(0, 2 * np.pi, 360)
    ax.plot(circle_radius * np.cos(theta), circle_radius * np.sin(theta), color="gray", linewidth=0.5)

    # one line per device
    azimuth_lines   = {}
    dev_positions   = {}
    for i, name in enumerate(dev_names):
        line,   = ax.plot([], [], "-", color="blue", linewidth=1)
        azimuth_lines[name]   = line
        dev_positions[name]   = (dev_x_pos[i], dev_y_pos[i])

    ax.set_xlim(-3, 3)
    ax.set_ylim(-3, 3)
    ax.set_title("Sound Localization")
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.grid(True)

    # removes borerlines 
    for spine in ax.spines.values(): # ax.spines are the four border lines 
        spine.set_visible(False)
    figure.subplots_adjust(left=0.0, right=1.0, top=1.0, bottom=0.0)

    canvas.draw()

    btn_row = QHBoxLayout()
    btn_row.addStretch()
    btn_row.addWidget(sound_loc_btn)
    btn_row.addStretch()
    layout.addLayout(btn_row)

    return azimuth_lines, dev_positions, canvas, act_int_thresh_entry
