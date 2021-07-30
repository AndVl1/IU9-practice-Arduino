import sys
from PyQt5 import QtWidgets
import serial
import design
from port import serial_ports, speeds


class LedApp(QtWidgets.QMainWindow, design.Ui_Form):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.port.addItems(serial_ports())
        self.speed.addItems(speeds)
        self.realport = None
        self.connectButton.clicked.connect(self.connect)
        self.stopMinValue.valueChanged.connect(self.stop_value_change)
        self.runningBrightness.valueChanged.connect(self.brighntess_value_change)
        self.orangeBlinking.valueChanged.connect(self.blink_value_change)


    def connect(self):
        try:
            self.realport = serial.Serial(self.port.currentText(),int(self.speed.currentText()))
            self.connectButton.setStyleSheet("background-color: green")
            self.connectButton.setText('Подключено')
        except Exception as e:
            print(e)


    def stop_value_change(self):
        if self.realport:
            self.realport.write(str('S'+str(self.stopMinValue.value())).encode())


    def blink_value_change(self):
        if self.realport:
            self.realport.write(str('B'+str(self.orangeBlinking.value())).encode())


    def brighntess_value_change(self):
        if self.realport:
            self.realport.write(str('R'+str(self.runningBrightness.value())).encode())


    def get_stop_min_value(self):
        if self.realport:
            self.realport.write(b'r')
            print(self.realport.readline())


    def set_stronger(self):
        if self.realport:
            self.realport.write(b'+')
            self.realport.write(b'r')
            self.progressBar.setValue(int(int(self.realport.readline()) / 1023 * 100))
        

    def set_weaker(self):
        if self.realport:
            self.realport.write(b'-')
            self.realport.write(b'r')
            self.progressBar.setValue(int(int(self.realport.readline()) / 1023 * 100))


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = LedApp()
    window.show()
    app.exec_()


if __name__ == '__main__':
    main()