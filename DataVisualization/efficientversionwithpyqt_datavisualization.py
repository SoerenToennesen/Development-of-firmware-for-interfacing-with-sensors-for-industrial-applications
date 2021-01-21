###################################################################
#                                                                 #
#                    PLOT A LIVE GRAPH (PyQt5)                    #
#                  -----------------------------                  #
#            EMBED A MATPLOTLIB ANIMATION INSIDE YOUR             #
#            OWN GUI!                                             #
#                                                                 #
#                                                                 #
#            Based on K.Mulier's StackOverflow response on        #
#https://stackoverflow.com/questions/38469630/realtime-plotting-wi#
#th-pyqt-plotwidget-error-message-plotwidget-object-is-not?noredir#
#                         ect=1&lq=1                              #
#                                                                 #
# Edited by Soren Toennesen, for B.Sc. Project at DTU with Vaerks #
#                                                                 #
###################################################################

import sys
import os
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import functools
import numpy as np
import random as rd
import matplotlib
matplotlib.use("Qt5Agg")
from matplotlib.figure import Figure
from matplotlib.animation import TimedAnimation
from matplotlib.lines import Line2D
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import time
import threading
from pymodbus.client.sync import ModbusSerialClient

client = ModbusSerialClient(
    method='rtu',
    port='COM4',
    baudrate=115200,
    timeout=1,
    parity='N',
    stopbits=1,
    bytesize=8
    )
connection = client.connect()
print("Connected = " + str(connection))

count = 10
x_address = 50
y_address = 150
z_address = 250
x_count = 10
y_count = 10
z_count = 10
slave_id = 1



class CustomMainWindow(QMainWindow):
    def __init__(self):
        print("Initiating main window")
        super(CustomMainWindow, self).__init__()
        # Define the geometry of the main window
        self.setGeometry(500, 500, 1000, 800)
        self.setWindowTitle("Accelerometer data - Visualization tool")
        # Create FRAME_A
        self.FRAME_A = QFrame(self)
        self.FRAME_A.setStyleSheet("QWidget { background-color: %s }" % QColor(210,210,235,255).name())
        self.LAYOUT_A = QGridLayout()
        self.FRAME_A.setLayout(self.LAYOUT_A)
        self.setCentralWidget(self.FRAME_A)
        # Place the matplotlib figure
        self.myFig = CustomFigCanvas()
        self.LAYOUT_A.addWidget(self.myFig, *(0,1))
        # Add the callbackfunc to ..
        myDataLoop = threading.Thread(name = 'myDataLoop', target = dataSendLoop, daemon = True, args = (self.addData_callbackFunc,))
        myDataLoop.start()
        self.show()
        return


    def addData_callbackFunc(self, value):
        #print("Add data: " + str(value))
        self.myFig.addData(value)
        return

''' End Class '''


class CustomFigCanvas(FigureCanvas, TimedAnimation):
    def __init__(self):
        print("Initiating canvas")
        self.next_data = 0
        self.addedData = []
        # print(matplotlib.__version__)
        # The data
        self.xlim = 200
        self.n = np.linspace(0, self.xlim - 1, self.xlim)
        #self.next_data = 1
        self.y1 = (self.n * 0.0) + 50
        self.y2 = (self.n * 0.0) + 50
        self.y3 = (self.n * 0.0) + 50
        # The window
        self.fig = Figure(figsize=(5,5), dpi=100)
        self.fig.suptitle('Accelerometer data', fontsize=20, fontweight='bold')
        self.ax1 = self.fig.add_subplot(221)
        self.ax2 = self.fig.add_subplot(222)
        self.ax3 = self.fig.add_subplot(223)
        self.ax4 = self.fig.add_subplot(224)
        # self.ax1 settings
        self.ax1.set_title('X-axis', size = 10, fontweight='bold')
        self.ax1.set_xlabel('Time [data points]', size = 7)
        self.ax1.set_ylabel('X-axis data [gravities in mg]', size = 7)
        self.ax1.tick_params(axis="x", labelsize=5)
        self.ax1.tick_params(axis="y", labelsize=5)
        self.ax2.set_title('Y-axis', size = 10, fontweight='bold')
        self.ax2.set_xlabel('Time [data points]', size = 7)
        self.ax2.set_ylabel('Y-axis data [gravities in mg]', size = 7)
        self.ax2.tick_params(axis="x", labelsize=5)
        self.ax2.tick_params(axis="y", labelsize=5)
        self.ax3.set_title('Z-axis', size = 10, fontweight='bold')
        self.ax3.set_xlabel('Time [data points]', size = 7)
        self.ax3.set_ylabel('Z-axis data [gravities in mg]', size = 7)
        self.ax3.tick_params(axis="x", labelsize=5)
        self.ax3.tick_params(axis="y", labelsize=5)
        self.ax4.set_title('Triaxial', size = 10, fontweight='bold')
        self.ax4.set_xlabel('Time [data points]', size = 7)
        self.ax4.set_ylabel('Triaxial data [gravities in mg]', size = 7)
        self.ax4.tick_params(axis="x", labelsize=5)
        self.ax4.tick_params(axis="y", labelsize=5)
        self.line1 = Line2D([], [], color='slateblue', linewidth=0.5)
        self.line1_tail = Line2D([], [], color='blue', linewidth=0.5)
        self.line1_head = Line2D([], [], color='blue', marker='o', markeredgecolor='b')
        self.line2 = Line2D([], [], color='salmon', linewidth=0.5)
        self.line2_tail = Line2D([], [], color='red', linewidth=0.5)
        self.line2_head = Line2D([], [], color='red', marker='o', markeredgecolor='r')
        self.line3 = Line2D([], [], color='lightseagreen', linewidth=0.5)
        self.line3_tail = Line2D([], [], color='green', linewidth=0.5)
        self.line3_head = Line2D([], [], color='green', marker='o', markeredgecolor='g')
        self.line4_1 = Line2D([], [], color='slateblue', linewidth=0.5)
        self.line4_1_tail = Line2D([], [], color='blue', linewidth=0.5)
        self.line4_1_head = Line2D([], [], color='blue', marker='o', markeredgecolor='b')
        self.line4_2 = Line2D([], [], color='salmon', linewidth=0.5)
        self.line4_2_tail = Line2D([], [], color='red', linewidth=0.5)
        self.line4_2_head = Line2D([], [], color='red', marker='o', markeredgecolor='r')
        self.line4_3 = Line2D([], [], color='lightseagreen', linewidth=0.5)
        self.line4_3_tail = Line2D([], [], color='green', linewidth=0.5)
        self.line4_3_head = Line2D([], [], color='green', marker='o', markeredgecolor='g')
        self.ax1.add_line(self.line1)
        self.ax1.add_line(self.line1_tail)
        self.ax1.add_line(self.line1_head)
        self.ax2.add_line(self.line2)
        self.ax2.add_line(self.line2_tail)
        self.ax2.add_line(self.line2_head)
        self.ax3.add_line(self.line3)
        self.ax3.add_line(self.line3_tail)
        self.ax3.add_line(self.line3_head)
        self.ax4.add_line(self.line4_1)
        self.ax4.add_line(self.line4_1_tail)
        self.ax4.add_line(self.line4_1_head)
        self.ax4.add_line(self.line4_2)
        self.ax4.add_line(self.line4_2_tail)
        self.ax4.add_line(self.line4_2_head)
        self.ax4.add_line(self.line4_3)
        self.ax4.add_line(self.line4_3_tail)
        self.ax4.add_line(self.line4_3_head)
        self.ax1.set_xlim(0, self.xlim - 1)
        self.ax1.set_ylim(-1000, 70000)
        self.ax2.set_xlim(0, self.xlim - 1)
        self.ax2.set_ylim(-1000, 70000)
        self.ax3.set_xlim(0, self.xlim - 1)
        self.ax3.set_ylim(-1000, 70000)
        self.ax4.set_xlim(0, self.xlim - 1)
        self.ax4.set_ylim(-1000, 70000)
        FigureCanvas.__init__(self, self.fig)
        TimedAnimation.__init__(self, self.fig, interval = 20, blit = True)
        return

    def new_frame_seq(self):
        print("New frame new me")
        return iter(range(self.n.size))

    def _init_draw(self):
        print("Initiating drawings")
        
        if self.next_data == 1:
            lines1 = [self.line1, self.line1_tail, self.line1_head   ,   self.line4_1, self.line4_1_tail, self.line4_1_head]
            for l in lines1:
                l.set_data([], [])
        
        if self.next_data == 2:
            lines2 = [self.line2, self.line2_tail, self.line2_head   ,   self.line4_2, self.line4_2_tail, self.line4_2_head]
            for l in lines2:
                l.set_data([], [])
        
        if self.next_data == 3:
            lines3 = [self.line3, self.line3_tail, self.line3_head   ,   self.line4_3, self.line4_3_tail, self.line4_3_head]
            for l in lines3:
                l.set_data([], [])
        return

    def addData(self, value):
        if self.next_data >= 3:
            self.next_data = 1
        else:
            self.next_data = self.next_data + 1
        self.addedData.append(value)
        return

    def _step(self, *args):
        # Extends the _step() method for the TimedAnimation class.
        try:
            TimedAnimation._step(self, *args)
        except Exception as e:
            self.abc += 1
            print(str(self.abc))
            TimedAnimation._stop(self)
            pass
        return

    def _draw_frame(self, framedata):
        margin = 2
        
        if self.next_data == 1:
            while(len(self.addedData) > 0):
                self.y1 = np.roll(self.y1, -1)
                self.y1[-1] = self.addedData[0]
                del(self.addedData[0])
            self.line1.set_data(self.n[ 0 : self.n.size - margin ], self.y1[ 0 : self.n.size - margin ])
            self.line1_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y1[-10:-1 - margin], self.y1[-1 - margin]))
            self.line1_head.set_data(self.n[-1 - margin], self.y1[-1 - margin])
            self.line4_1.set_data(self.n[0: self.n.size - margin], self.y1[0: self.n.size - margin])
            self.line4_1_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y1[-10:-1 - margin], self.y1[-1 - margin]))
            self.line4_1_head.set_data(self.n[-1 - margin], self.y1[-1 - margin])
            
        elif self.next_data == 2:
            while(len(self.addedData) > 0):
                self.y2 = np.roll(self.y2, -1)
                self.y2[-1] = self.addedData[0]
                del(self.addedData[0])
            self.line2.set_data(self.n[ 0 : self.n.size - margin ], self.y2[ 0 : self.n.size - margin ])
            self.line2_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y2[-10:-1 - margin], self.y2[-1 - margin]))
            self.line2_head.set_data(self.n[-1 - margin], self.y2[-1 - margin])
            self.line4_2.set_data(self.n[0: self.n.size - margin], self.y2[0: self.n.size - margin])
            self.line4_2_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y2[-10:-1 - margin], self.y2[-1 - margin]))
            self.line4_2_head.set_data(self.n[-1 - margin], self.y2[-1 - margin])
            
        elif self.next_data == 3:
            while(len(self.addedData) > 0):
                self.y3 = np.roll(self.y3, -1)
                self.y3[-1] = self.addedData[0]
                del(self.addedData[0])
            self.line3.set_data(self.n[ 0 : self.n.size - margin ], self.y3[ 0 : self.n.size - margin ])
            self.line3_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y3[-10:-1 - margin], self.y3[-1 - margin]))
            self.line3_head.set_data(self.n[-1 - margin], self.y3[-1 - margin])
            self.line4_3.set_data(self.n[0: self.n.size - margin], self.y3[0: self.n.size - margin])
            self.line4_3_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y3[-10:-1 - margin], self.y3[-1 - margin]))
            self.line4_3_head.set_data(self.n[-1 - margin], self.y3[-1 - margin])

        self._drawn_artists = [self.line1, self.line1_tail, self.line1_head   ,   self.line2, self.line2_tail, self.line2_head   ,   self.line3, self.line3_tail, self.line3_head   ,   self.line4_1, self.line4_1_tail, self.line4_1_head, self.line4_2, self.line4_2_tail, self.line4_2_head, self.line4_3, self.line4_3_tail, self.line4_3_head]
        
        return

''' End Class '''


# You need to setup a signal slot mechanism, to
# send data to your GUI in a thread-safe way.
# Believe me, if you don't do this right, things
# go very very wrong..
class Communicate(QObject):
    data_signal = pyqtSignal(float)

''' End Class '''



def dataSendLoop(addData_callbackFunc):
    # Setup the signal-slot mechanism.
    mySrc = Communicate()
    mySrc.data_signal.connect(addData_callbackFunc)

    while True:
        try:
            res_x = client.read_holding_registers(address=x_address, count=x_count, unit=slave_id)
            res_y = client.read_holding_registers(address=y_address, count=y_count, unit=slave_id)
            res_z = client.read_holding_registers(address=z_address, count=z_count, unit=slave_id)
            if not res_x.isError() and not res_y.isError() and not res_z.isError():
                x_data = res_x.registers
                y_data = res_y.registers
                z_data = res_z.registers
                print("X-data: {}".format(x_data))
                print("Y-data: {}".format(y_data))
                print("Z-data: {}".format(z_data))
                data = []
                for i in range(count):
                    data.append(x_data[i])
                    data.append(y_data[i])
                    data.append(z_data[i])
                y = np.array(data)
                print("Length of sent data (x- + y- + z-data): {}".format(len(y)))
                for i in range(len(y)):
                    mySrc.data_signal.emit(y[i]) # <- Here you emit a signal!
                    time.sleep(0.01)
                print("")
                print("------------------------------------------")
                print("")
        except Exception as e:
            print("An error has occurred...")
            print(e)
    
    
    
        

if __name__== '__main__':
    app = QApplication(sys.argv)
    QApplication.setStyle(QStyleFactory.create('Plastique'))
    myGUI = CustomMainWindow()
    sys.exit(app.exec_())