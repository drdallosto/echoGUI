#create_NED_plot_qt5.py

from PyQt5.QtWidgets import (QLabel, QScrollArea, QLineEdit, QGridLayout,
                              QGroupBox, QVBoxLayout, QHBoxLayout, QWidget,
                              QScrollArea, QSizePolicy, QFrame)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt
import matplotlib
matplotlib.use('Qt5Agg')
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from collections import deque

plotSize = 8

def createNEDPlot(tab3, plot_ned_btn, dev_names):

    figNED = plt.figure(figsize=(plotSize, plotSize))
    axNED = figNED.add_subplot(111, projection='3d')
    canvasNED = FigureCanvasQTAgg(figNED)

    axNED.set_title("NED Trajectory")
    axNED.set_xlabel("North")
    axNED.set_ylabel("East")
    axNED.set_zlabel("Down")
    axNED.grid(True)

    ned_lines = {}
    colors = ["black", "blue", "green", "red"]
    for i, name in enumerate(dev_names):
        ned_line, = axNED.plot([], [], [], color=colors[i], label=name)
        ned_lines[name] = ned_line

    axNED.legend()
    canvasNED.draw()

    main_widget = QWidget()
    main_layout = QVBoxLayout(main_widget)
    main_layout.addWidget(canvasNED)

    scroll = QScrollArea()
    scroll.setWidgetResizable(True)
    scroll.setWidget(main_widget)

    tab_layout = QVBoxLayout()
    tab_layout.addWidget(scroll)

    bottom_layout = QHBoxLayout()
    bottom_layout.addWidget(plot_ned_btn)
    bottom_layout.addStretch()
    tab_layout.addLayout(bottom_layout)

    tab3.setLayout(tab_layout)

    return ned_lines, axNED, canvasNED
