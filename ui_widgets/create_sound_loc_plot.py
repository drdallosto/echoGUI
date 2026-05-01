import numpy as np
from PyQt6.QtWidgets import QVBoxLayout, QHBoxLayout, QSizePolicy, QWidget, QLabel, QLineEdit
from PyQt6.QtGui import QFont
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.ticker import MultipleLocator


small_rad = 1

# fixed positions — dev1 top-left, dev2 top-right, dev3 bottom-right, dev4 bottom-left
dev_x_pos = [-1,  1,  1, -1]
dev_y_pos = [ 1,  1, -1, -1]

# label offsets so text doesn't overlap the dot
dev_labels = [(-0.3, 0.2), (0.1, 0.2), (0.1, -0.3), (-0.3, -0.3)]


def createSoundLoc(tab, dev_names, sound_loc_btn, log_data_btn):
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
    top_layout.addSpacing(20)

    q_factor_lbl = QLabel("Q-Factor\nThreshold")
    q_factor_lbl.setFont(bold_font)
    q_thresh_entry = QLineEdit("2")
    q_thresh_entry.setFixedWidth(75)
    q_thresh_entry.setStyleSheet("QLineEdit { background-color: white; }")
    top_layout.addWidget(q_factor_lbl)
    top_layout.addWidget(q_thresh_entry)
    top_layout.addSpacing(20)

    hist_lbl = QLabel("Histogram\nThreshold")
    hist_lbl.setFont(bold_font)
    hist_thresh_entry = QLineEdit("5")
    hist_thresh_entry.setFixedWidth(75)
    hist_thresh_entry.setStyleSheet("QLineEdit { background-color: white; }")
    top_layout.addWidget(hist_lbl)
    top_layout.addWidget(hist_thresh_entry)
    top_layout.addStretch()

    layout.addWidget(top_widget)
    layout.addWidget(canvas)

    ax = figure.add_subplot(111)
    ax.set_aspect("equal", adjustable="box")

    # one line per device
    azimuth_lines   = {}
    dev_positions   = {}
    theta = np.linspace(0, 2 * np.pi, 360)
    # one blue dot per device with a label
    for i, name in enumerate(dev_names):
        ax.scatter(dev_x_pos[i], dev_y_pos[i], s=50, color="blue")
        dx_lbl, dy_lbl = dev_labels[i] 
        ax.text(dev_x_pos[i] + dx_lbl, dev_y_pos[i] + dy_lbl, name, fontsize=8, color="blue")

        # circle around each 
        ax.plot(dev_x_pos[i] + small_rad * np.cos(theta),dev_y_pos[i] + small_rad * np.sin(theta),color="none", linewidth=0.8)

        line,   = ax.plot([], [], "-", color="blue", linewidth=.9)
        azimuth_lines[name]   = line
        dev_positions[name]   = (dev_x_pos[i], dev_y_pos[i])

    # lines through (0,0)
    ax.axhline(0, color="black", linewidth=0.8)
    ax.axvline(0, color="black", linewidth=0.8)

    # # circle
    # theta = np.linspace(0, 2 * np.pi, 360)
    # ax.plot(circle_radius * np.cos(theta), circle_radius * np.sin(theta), color="gray", linewidth=0.5)

    # # one line per device
    # azimuth_lines   = {}
    # dev_positions   = {}
    # for i, name in enumerate(dev_names):
    #     line,   = ax.plot([], [], "-", color="blue", linewidth=1)
    #     azimuth_lines[name]   = line
    #     dev_positions[name]   = (dev_x_pos[i], dev_y_pos[i])

    ax.set_title("Sound Localization")
    ax.xaxis.set_major_locator(MultipleLocator(1))
    ax.yaxis.set_major_locator(MultipleLocator(1))
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.grid(True)

    ax.set_xlim(-3, 3)
    ax.set_ylim(-3, 3)

    #removes border lines 
    for spine in ax.spines.values(): # ax.spines are the four border lines 
        spine.set_visible(False)

    canvas.draw()

    btn_row = QHBoxLayout()
    btn_row.addStretch()
    btn_row.addWidget(sound_loc_btn)
    btn_row.addSpacing(20)
    btn_row.addWidget(log_data_btn)
    btn_row.addStretch()
    layout.addLayout(btn_row)

    def on_scroll(event, ax, canvas):
        scale = 0.9 if event.button == 'up' else 1.1
        xlim = ax.get_xlim()
        ylim = ax.get_ylim()
        ax.set_xlim([x * scale for x in xlim])
        ax.set_ylim([y * scale for y in ylim])
        canvas.draw_idle()

    canvas.mpl_connect('scroll_event', lambda event: on_scroll(event, ax, canvas))

    return azimuth_lines, dev_positions, canvas, act_int_thresh_entry, q_thresh_entry, hist_thresh_entry
