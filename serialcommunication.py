import serial
import re
import matplotlib.pyplot as plt
import numpy
import time
import pymodbus
from pymodbus.pdu import ModbusRequest
from pymodbus.client.sync import ModbusSerialClient as ModbusClient
from pymodbus.transaction import ModbusRtuFramer

client = ModbusClient(method = 'rtu', port='com4', baudrate=9600, parity = 'O', timeout=1)
connection = client.connect()
print(connection) # returns true, but cannot have the below "serialport" open as well...
registers  = client.read_holding_registers(0,100,unit=1) # start_address, count, slave_id
print (registers.registers)

#write = client.write_register(1,425,unit=1) # address = 1, value to set = 425, slave ID = 1


'''

serialport = "com4"
ser = serial.Serial(serialport, 9600)

fig = plt.figure()
ax = fig.add_subplot(111)
plt.ion()
fig.show()
fig.canvas.draw()

var = 0
xyz = 0
time_array = numpy.array([1,2])
x = numpy.empty(0)
y = numpy.empty(0)
z = numpy.empty(0)

while(1):
    val = ser.readline()
    char_num = 9
    
    if val[char_num] == 45:
    	ax.clear()
    	ax.plot(time_array,x)
    	fig.canvas.draw()
    
    	print("---------")
    	x = numpy.empty(0)
    	y = numpy.empty(0)
    	z = numpy.empty(0)
    	xyz = 0
    	#if var % 2 == 0:
    	#	time_array = [i + 2 for i in time_array]
    	#else:
    	#	time_array = [i - 2 for i in time_array]
    	#var = var + 1
    	time_array = [i + 2 for i in time_array]
    	continue
    
    while val[char_num] != 32:
    	char_num = char_num + 1
    val = val[9:char_num]
    val = int(val, 16)
    
    if xyz < 2:
    	x = numpy.append(x, val)
    	xyz = xyz + 1
    elif 2 <= xyz < 4:
    	y = numpy.append(y, val)
    	xyz = xyz + 1
    else:
    	z = numpy.append(z, val)
    	xyz = xyz + 1
    
    print(val)

'''