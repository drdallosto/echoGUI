#create_NED_plot.py

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

guiFontSize = 17
plotFontSize = 10 
plotSize = 8

de = deque()
# ----------- NED plot ---------------------------------------

def createNEDPlot(tab3, plot_ned_btn, dev_names): 

    # Create NED plot
    figNED = plt.figure(figsize=(plotSize,plotSize))
    axNED = figNED.add_subplot(111, projection='3d')
    canvasNED = FigureCanvasQTAgg (figNED)

    axNED.set_title("NED Trajectory") #, fontsize=plotFontSize+3)
    axNED.set_xlabel("North") #, fontsize=plotFontSize)
    axNED.set_ylabel("East") #, fontsize=plotFontSize)
    axNED.set_zlabel("Down")  #, fontsize=plotFontSize)
    axNED.grid(True)

    ned_lines = {}
    colors = ["black", "blue", "green", "red"]   # one color per drone
    for i,name in enumerate(dev_names):
        #print(i,name)
        ned_line, = axNED.plot([], [], [], color=colors[i], label=name)  # create empty 3d line object
        ned_lines[name]= ned_line
    
    #print(ned_lines)
    axNED.legend()
    canvasNED.draw()

    # Wrap canvas in a widget and scroll area
    main_widget = QWidget()
    main_layout = QVBoxLayout(main_widget)
    main_layout.addWidget(canvasNED)  

    scroll = QScrollArea()
    scroll.setWidgetResizable(True)
    scroll.setWidget(main_widget)

    # Set layout on tab3
    tab_layout = QVBoxLayout()
    tab_layout.addWidget(scroll)

    bottom_layout = QHBoxLayout()
    bottom_layout.addWidget(plot_ned_btn)    
    bottom_layout.addStretch()
    tab_layout.addLayout(bottom_layout)

    tab3.setLayout(tab_layout)

    return ned_lines, axNED, canvasNED
