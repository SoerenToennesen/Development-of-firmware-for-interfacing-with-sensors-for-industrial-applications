import serial
import re
import matplotlib.pyplot as plt
import numpy
import time
import pymodbus
from pymodbus.pdu import ModbusRequest
from pymodbus.client.sync import ModbusSerialClient as ModbusClient
from pymodbus.transaction import ModbusRtuFramer
from pymodbus.client.sync import ModbusSerialClient

my_dpi=96
fig = plt.figure()
fig.set_size_inches(7.5, 7.5)
#fig(figsize=(800/my_dpi, 800/my_dpi), dpi=my_dpi)
fig.suptitle('Accelerometer data', fontsize=14, fontweight='bold')
ax = fig.add_subplot(224)
ax_x = fig.add_subplot(221)
ax_y = fig.add_subplot(222)
ax_z = fig.add_subplot(223)
plt.ion()
fig.show()
fig.canvas.draw()

var = 0
xyz = 0
#time_array = numpy.array([0,1,2,3,4,5,6,7,8,9])
time_list = [1,2,3,4,5,6,7,8,9,10]
x = []
y = []
z = []


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

x_address = 0
y_address = 100
z_address = 200
count = 10
x_count = 10 #should be 100
y_count = 10
z_count = 10
slave_id = 1

i = 0
while i < 100:
    #time.sleep(0.1)
    i=i+1
    try:
        res_x  = client.read_holding_registers(address=x_address,count=x_count,unit=slave_id)
        res_y  = client.read_holding_registers(address=y_address,count=y_count,unit=slave_id)
        res_z  = client.read_holding_registers(address=z_address,count=z_count,unit=slave_id)
        if not res_x.isError() and not res_y.isError() and not res_z.isError():
            x_data = res_x.registers #this is stored as a list
            y_data = res_y.registers #this is stored as a list
            z_data = res_z.registers #this is stored as a list
            x.extend(x_data)
            y.extend(y_data)
            z.extend(z_data)
            
            print("x data")
            print(res_x.registers)
            print(x)
            print("y data")
            print(res_y.registers)
            print(y)
            print("z data")
            print(res_z.registers)
            print(z)
            
            print("time list")
            print(time_list)
            
            ax_x.clear()
            ax_y.clear()
            ax_z.clear()
            ax.clear()
            ax_x.plot(time_list, x, label='x-data', color='blue', linewidth=0.25)
            ax_y.plot(time_list, y, label='y-data', color='green', linewidth=0.25)
            ax_z.plot(time_list, z, label='z-data', color='red', linewidth=0.25)
            ax.plot(time_list, x, label='x-data', color='blue', linewidth=0.25)
            ax.plot(time_list, y, label='y-data', color='green', linewidth=0.25)
            ax.plot(time_list, z, label='z-data', color='red', linewidth=0.25)
            #ax_x.legend()
            #ax_y.legend()
            #ax_z.legend()
            ax.legend()
            ax_x.set_title('x-axis', size = 8)
            ax_y.set_title('y-axis', size = 8)
            ax_z.set_title('z-axis', size = 8)
            ax.set_title('Triaxial', size = 8)
            ax_x.set_xlabel('Time [units]', size = 5)
            ax_y.set_xlabel('Time [units]', size = 5)
            ax_z.set_xlabel('Time [units]', size = 5)
            ax.set_xlabel('Time [units]', size = 5)
            ax_x.set_ylabel('Frequency [Hz] ...or gravities [mg]?', size = 5)
            ax_y.set_ylabel('Frequency [Hz] ...or gravities [mg]?', size = 5)
            ax_z.set_ylabel('Frequency [Hz] ...or gravities [mg]?', size = 5)
            ax.set_ylabel('Frequency [Hz] ...or gravities [mg]?', size = 5)
            ax_x.tick_params(axis="x", labelsize=5)
            ax_x.tick_params(axis="y", labelsize=5)
            ax_y.tick_params(axis="x", labelsize=5)
            ax.tick_params(axis="x", labelsize=5)
            ax_y.tick_params(axis="y", labelsize=5)
            ax_z.tick_params(axis="x", labelsize=5)
            ax_z.tick_params(axis="y", labelsize=5)
            ax.tick_params(axis="y", labelsize=5)
            fig.canvas.draw()
            
            #time_array = [j + count for j in time_array]
            #time_array = [j * 2 for j in time_array]
            time_list.extend([j + count for j in time_list[-10:]])
            if len(time_list) >= count*10 or len(x) >= count*10 or len(y) >= count*10 or len(z) >= count*10:
                del time_list[:10]
                del x[:10]
                del y[:10]
                del z[:10]
            
            continue
    except Exception as e:
        print("An error has occurred...")
        print(e)
        break








