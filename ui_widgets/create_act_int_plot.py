#create_act_int_plot.py
from PyQt6.QtWidgets import (QLabel, QScrollArea, QLineEdit, QGridLayout,
                              QGroupBox, QVBoxLayout, QHBoxLayout, QWidget,
                              QScrollArea, QSizePolicy, QFrame)
from PyQt6.QtGui import QFont
from PyQt6.QtCore import Qt
import matplotlib
matplotlib.use('QtAgg')
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg 
from collections import deque

plotSize = 4
plotFontSize = 8

def createActIntPlot(tab2,plot_act_int_btn,dev_names):

    act_int_group = QGroupBox() #"Active Intensity")
    act_int_group.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

    # ----------- active intensity plot ---------------------------------------
    intFrame = QFrame(parent=act_int_group)
    intFrame.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
    intFrameLayout = QVBoxLayout(intFrame)
    intFrameLayout.setContentsMargins(0, 0, 0, 0)

    # Create figure with two subplots
    intFig, (intAx, azAx) = plt.subplots(2, 1, figsize=(plotSize, plotSize))

    # Create canvas and add to layout
    intCanvas = FigureCanvasQTAgg(intFig)
    intCanvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
    intFrameLayout.addWidget(intCanvas)

    # Configure intAx (Active Intensity)
    intAx.set_xlabel("Time") #, fontsize=plotFontSize)
    intAx.set_ylabel("Active intensity") #, fontsize=plotFontSize)
    intAx.set_title("Active Intensity Over Time") #, fontsize=plotFontSize + 3)

    # Configure azAx (Azimuth)
    azAx.set_xlabel("Time") #, fontsize=plotFontSize)
    azAx.set_ylabel("Azimuth") #, fontsize=plotFontSize)
    azAx.set_title("Azimuth Over Time") #, fontsize=plotFontSize + 3)

    act_int_lines = {}
    azm_lines     = {}
    colors = ["black", "blue", "green", "red"]   

    for i,name in enumerate(dev_names):
        # Create empty line objects
        act_int_line, = intAx.plot([], [], color = colors[i], label=name)
        azm_line, = azAx.plot([], [], marker='o', linestyle='None', color = colors[i], label=name)

        azm_lines[name]=azm_line
        act_int_lines[name]=act_int_line

    #Set axis limits
    # azAx.legend()
    # intAx.legend()
    intAx.set_ylim(0, 60)
    azAx.set_ylim(0, 360)

    if azm_lines:
        azAx.legend(loc='upper right')
    if act_int_lines:
        intAx.legend(loc='upper right')

    # # Tick params
    # intAx.tick_params(axis='both', which='major', labelsize=12)
    # azAx.tick_params(axis='both', which='major', labelsize=12)

    intFig.tight_layout()
    intCanvas.draw()

    # Add intFrame into the group box
    group_layout = QVBoxLayout()
    group_layout.addWidget(intFrame)
    act_int_group.setLayout(group_layout)

    # Wrap in scroll area and set on tab
    main_widget = QWidget()
    main_widget.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
    container_layout = QVBoxLayout()
    container_layout.setContentsMargins(0, 0, 0, 0)
    main_widget.setLayout(container_layout)
    container_layout.addWidget(act_int_group)

    scroll = QScrollArea()
    scroll.setWidgetResizable(True)
    scroll.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
    scroll.setWidget(main_widget)

    layout = QVBoxLayout()
    
    top_widget = QWidget() # to wrap top_layout for background color change 
    top_widget.setStyleSheet("background-color:lightgray;")
    top_layout = QHBoxLayout()
    top_widget.setLayout(top_layout)
    layout.addWidget(top_widget)
    
#    top_layout = QHBoxLayout()

    bold_font = QFont()
    bold_font.setBold(True)

    act_int_lbl = QLabel("Active Intensity\n   Treshold")
    act_int_lbl.setFont(bold_font)
    act_int_thresh_entry = QLineEdit('20')
    act_int_thresh_entry.setFixedWidth(75)
    act_int_thresh_entry.setStyleSheet("QLineEdit { background-color: white; }")
    top_layout.addWidget(act_int_lbl) 
    top_layout.addWidget(act_int_thresh_entry) 
    #top_layout.addStretch()
    top_layout.addSpacing(15)

    q_thresh_lbl = QLabel("Q-factor\n Treshold")
    q_thresh_lbl.setFont(bold_font)
    q_thresh_entry = QLineEdit('2')
    q_thresh_entry.setFixedWidth(75)
    q_thresh_entry.setStyleSheet("QLineEdit { background-color: white; }")
    top_layout.addWidget(q_thresh_lbl) 
    top_layout.addWidget(q_thresh_entry) 
    #top_layout.addStretch()
    top_layout.addSpacing(15)
   
    hist_thresh_lbl = QLabel("Histogram\n Treshold")
    hist_thresh_lbl.setFont(bold_font)
    hist_thresh_entry = QLineEdit('5')
    hist_thresh_entry.setFixedWidth(75)
    hist_thresh_entry.setStyleSheet("QLineEdit { background-color: white; }")
    top_layout.addWidget(hist_thresh_lbl) 
    top_layout.addWidget(hist_thresh_entry) 
    top_layout.addStretch()

    #layout.addLayout(top_layout)
    layout.addWidget(scroll)

    bottom_layout = QHBoxLayout()
    bottom_layout.addStretch()
    bottom_layout.addWidget(plot_act_int_btn)
    bottom_layout.addStretch()
    layout.addLayout(bottom_layout)

    tab2.setLayout(layout)

    return act_int_lines, azm_lines, intAx, azAx, intCanvas, act_int_thresh_entry, q_thresh_entry, hist_thresh_entry

