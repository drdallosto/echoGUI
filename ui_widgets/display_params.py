# #display_params.py

# from PyQt6.QtWidgets import QLabel, QLineEdit, QGridLayout, QGroupBox, QVBoxLayout, QHBoxLayout, QWidget, QScrollArea, QSizePolicy, QComboBox
# from PyQt6.QtGui import QFont
# from PyQt6.QtCore import Qt, QSize

# ''' Function to display both haptic and ares parameters in the GUI 
#     additionally create buttons to update, log data, and sync time '''


# def displayParams(tab1, storeHapParams, hap_description,
#                   update_param_btn, log_data_btn, sync_time_btn, dev_names):
#     print()
#     print('---- parameters displayed in GUI ----\n')
#     print()

#     # --- Device selector ---
#     dev_selector_layout = QHBoxLayout()
#     dev_selector_lbl = QLabel("Device:")
#     dev_combo = QComboBox()
#     dev_combo.addItems(dev_names)
#     dev_selector_layout.addWidget(dev_selector_lbl)
#     dev_selector_layout.addWidget(dev_combo)
#     dev_selector_layout.addStretch()

#     # --- Haptic Parameters ---
#     hap_group = QGroupBox("HAPTIC PARAMETERS")
#     hap_group.setSizePolicy(QSizePolicy.Policy.Maximum, QSizePolicy.Policy.Preferred)

#     hap_grid = QGridLayout()  
#     hap_grid.setColumnStretch(2, 1) 

#     updateHapParams = {}
#     for idx, (name, value) in enumerate(storeHapParams.items()):
#         new = name + ' ' + hap_description[idx]
#         lbl = QLabel(new)
#         hap_grid.addWidget(lbl, idx, 0) 
#         e = QLineEdit()
#         e.setText(str(value))
#         e.setFixedWidth(120)
#         hap_grid.addWidget(e, idx, 1)
#         updateHapParams[name] = e

#     hap_group.setLayout(hap_grid)

#     # # --- AVS Parameters  ---
#     # avs_group = QGroupBox("AVS PARAMETERS")
#     # avs_group.setSizePolicy(QSizePolicy.Policy.Maximum, QSizePolicy.Policy.Preferred)

#     # avs_grid = QGridLayout()
#     # avs_grid.setColumnStretch(2, 1)

#     # updateAvsParams = {}
#     # for idx, (name, value) in enumerate(storeAvsParams.items()):
#     #     new = name + ' ' + avs_description[idx]
#     #     lbl = QLabel(new)
#     #     avs_grid.addWidget(lbl, idx, 0)
#     #     e = QLineEdit()
#     #     e.setText(str(value))
#     #     e.setFixedWidth(120)
#     #     avs_grid.addWidget(e, idx, 1)
#     #     updateAvsParams[name] = e

#     # avs_group.setLayout(avs_grid)

#     # --- Log Data ---
#     log_data_group = QGroupBox("LOG DATA")
#     log_data_group.setSizePolicy(QSizePolicy.Policy.Maximum, QSizePolicy.Policy.Preferred)

#     log_grid = QGridLayout()  
#     log_grid.setColumnStretch(2, 1) 

#     lbl = QLabel('Timer (seconds):')
#     log_grid.addWidget(lbl, 0, 0)

#     timerEntry = QLineEdit()
#     timerEntry.setText(str(15)) # default value for timer
#     timerEntry.setFixedWidth(75)
#     log_grid.addWidget(timerEntry, 0, 1)
#     log_data_group.setLayout(log_grid)

#     # --- Place groups side by side ---
#     main_widget = QWidget() # create a main widget to hold the groups and the buttons
#     container_layout = QHBoxLayout()

#     # left side: hap group
#     left_layout = QVBoxLayout() # create a vertical layout for the left side 
#     left_layout.setAlignment(Qt.AlignmentFlag.AlignTop)
#     left_layout.addWidget(hap_group)
#     left_layout.addStretch()

#     left_widget = QWidget() # create a widget for the left side and set the layout
#     left_widget.setLayout(left_layout)

#     # # right side: avs + log data stacked vertically
#     right_layout = QVBoxLayout()
#     right_layout.setAlignment(Qt.AlignmentFlag.AlignTop)
#     # right_layout.addWidget(avs_group)
#     right_layout.addWidget(log_data_group)
#     right_layout.addStretch()

#     right_widget = QWidget()
#     right_widget.setLayout(right_layout)

#     container_layout.addWidget(left_widget)
#     container_layout.addWidget(right_widget)
#     container_layout.addStretch()
#     main_widget.setLayout(container_layout)

#     scroll = QScrollArea()
#     scroll.setWidgetResizable(True)
#     scroll.setWidget(main_widget)

#     layout = QVBoxLayout()
#     layout.addLayout(dev_selector_layout)
#     layout.addWidget(scroll)

#     bottom_layout = QHBoxLayout()
#     bottom_layout.addWidget(update_param_btn)  
#     bottom_layout.addWidget(sync_time_btn)  
#     bottom_layout.addWidget(log_data_btn)  
#     bottom_layout.addStretch()
#     layout.addLayout(bottom_layout)

#     tab1.setLayout(layout)

#     return updateHapParams, timerEntry, dev_combo