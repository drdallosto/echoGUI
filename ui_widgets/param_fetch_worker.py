from PyQt6.QtCore import QObject, pyqtSignal, pyqtSlot
from ui_widgets.get_params import getParams


'''worker to get parameters associated with the selected device'''

class ParamFetchWorker(QObject):
    finished = pyqtSignal(object, str)  # (params dict, dev_name)

    def __init__(self, connection, all_params, dev_name):
        super().__init__()
        self.connection = connection
        self.all_params = all_params
        self.dev_name   = dev_name

    def run(self):
        # drain leftover stream messages before requesting params
        while self.connection.recv_match(blocking=False) is not None:
            pass
        new_params = {}
        getParams(self.connection, self.all_params, new_params, dev_name=self.dev_name)
        self.finished.emit(new_params, self.dev_name)