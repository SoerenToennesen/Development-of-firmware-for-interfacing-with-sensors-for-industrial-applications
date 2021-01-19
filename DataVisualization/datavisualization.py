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


fig = plt.figure()
ax = fig.add_subplot(111)
plt.ion()
fig.show()
fig.canvas.draw()

var = 0
xyz = 0
time_array = numpy.array([0,1,2,3,4,5,6,7,8,9])
x = numpy.empty(0)
y = numpy.empty(0)
z = numpy.empty(0)


client = ModbusSerialClient(
    method='rtu',
    port='COM4',
    baudrate=9600,
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
x_count = 10 #should be 100
y_count = 10
z_count = 10
slave_id = 1

x = 0
while x < 100:
    x=x+1
    try:
        res_x  = client.read_holding_registers(address=x_address,count=x_count,unit=slave_id)
        #res_y  = client.read_holding_registers(address=y_address,count=y_count,unit=slave_id)
        #res_z  = client.read_holding_registers(address=z_address,count=z_count,unit=slave_id)
        if not res_x.isError():# and not res_y.isError() and not res_z.isError():
            x_data = res_x.registers #this is stored as a list
            #y_data = res_y.registers #this is stored as a list
            #z_data = res_z.registers #this is stored as a list
            ax.clear()
            ax.plot(time_array,x_data)
            fig.canvas.draw()
            time_array = [i + x_count for i in time_array]
            print(res_x.registers)
            #print(res_y.registers)
            #print(res_z.registers)
            continue
    except:
        print("An error has occurred...")








