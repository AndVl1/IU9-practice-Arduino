import sys
from PyQt5 import QtWidgets
import serial
import design
from port import serial_ports, speeds


class LedApp(QtWidgets.QMainWindow, design.Ui_Form):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.Port.addItems(serial_ports())
        self.Speed.addItems(speeds)
        self.realport = None
        self.ConnectButton.clicked.connect(self.connect)
        self.Stronger.clicked.connect(self.set_stronger)
        self.Weaker.clicked.connect(self.set_weaker)

    def connect(self):
        try:
            self.realport = serial.Serial(self.Port.currentText(),int(self.Speed.currentText()))
            self.ConnectButton.setStyleSheet("background-color: green")
            self.ConnectButton.setText('Подключено')
        except Exception as e:
            print(e)


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