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
#time_list = [1,2,3,4,5,6,7,8,9,10]
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


#ser = serial.Serial('COM4', 115200)
#packet = bytearray()
#packet.append(0xFF)



x_address = 0
y_address = 2048
z_address = 4096 #we cannot exceed counts of 5352 (meaning the address here + the count), since we dont have enough data memory in the FX3 to store as many holding registers for the freq bin values
count = 10
x_count = 10 #should be 100
y_count = 10
z_count = 10
slave_id = 1


first_read = 0
freq = []
for i in range(count):
    freq.append(0)


while True:
    for i in range(20):
        time.sleep(0.25)
        try:
            pass
        except KeyboardInterrupt:
            sys.exit(0)
    
    plt.close()
    try:
        res_x_g  = client.read_holding_registers(address=x_address,count=x_count,unit=slave_id)
        #res_x_freq  = client.read_holding_registers(address=x_address+1024,count=x_count,unit=slave_id)
        res_y_g  = client.read_holding_registers(address=y_address,count=y_count,unit=slave_id)
        #res_y_freq  = client.read_holding_registers(address=y_address+1024,count=y_count,unit=slave_id)
        res_z_g  = client.read_holding_registers(address=z_address,count=z_count,unit=slave_id)
        #res_z_freq  = client.read_holding_registers(address=z_address+1024,count=z_count,unit=slave_id)
        
        if first_read == 0:
            res_freq  = client.read_holding_registers(address=z_address+2048,count=count,unit=slave_id)
            if not res_freq.isError():
                freq = numpy.array(res_freq.registers)
                first_read = 1
        
        time.sleep(0.1)
        client.write_coil(0, True)
        #ser.write(packet) #one X,Y,Z sample has been received, next request starts a sample.
        
        if not res_x_g.isError() and not res_y_g.isError() and not res_z_g.isError():
            x_g = numpy.array(res_x_g.registers) #this is stored as a list
            #x_freq = res_x_freq.registers
            y_g = numpy.array(res_y_g.registers)
            #y_freq = res_y_freq.registers
            z_g = numpy.array(res_z_g.registers)
            #z_freq = res_z_freq.registers
            #freq = res_freq.registers
            
            print("x data")
            print(x_g)
            #print(res_x_freq.registers)
            #print(x)
            print("y data")
            print(y_g)
            #print(res_y_freq.registers)
            #print(y)
            print("z data")
            print(z_g)
            #print(res_z_freq.registers)
            #print(z)
            print("freq data")
            print(freq)
            #print("time list")
            #print(time_list)
            
            plt.plot(freq,x_g)
            plt.show()
            
            '''
            ax_x.clear()
            ax_y.clear()
            ax_z.clear()
            ax.clear()
            ax_x.plot(freq, x_g, label='x-data', color='blue', linewidth=0.25)
            ax_y.plot(freq, y_g, label='y-data', color='green', linewidth=0.25)
            ax_z.plot(freq, z_g, label='z-data', color='red', linewidth=0.25)
            ax.plot(freq, x_g, label='x-data', color='blue', linewidth=0.25)
            ax.plot(freq, y_g, label='y-data', color='green', linewidth=0.25)
            ax.plot(freq, z_g, label='z-data', color='red', linewidth=0.25)
            #ax_x.legend()
            #ax_y.legend()
            #ax_z.legend()
            ax.legend()
            ax_x.set_title('x-axis', size = 8)
            ax_y.set_title('y-axis', size = 8)
            ax_z.set_title('z-axis', size = 8)
            ax.set_title('Triaxial', size = 8)
            ax_x.set_xlabel('Frequency [Hz]', size = 5)
            ax_y.set_xlabel('Frequency [Hz]', size = 5)
            ax_z.set_xlabel('Frequency [Hz]', size = 5)
            ax.set_xlabel('Frequency [Hz]', size = 5)
            ax_x.set_ylabel('Gravities [mg]', size = 5)
            ax_y.set_ylabel('Gravities [mg]', size = 5)
            ax_z.set_ylabel('Gravities [mg]', size = 5)
            ax.set_ylabel('Gravities [mg]', size = 5)
            ax_x.tick_params(axis="x", labelsize=5)
            ax_x.tick_params(axis="y", labelsize=5)
            ax_y.tick_params(axis="x", labelsize=5)
            ax_y.tick_params(axis="y", labelsize=5)
            ax_z.tick_params(axis="x", labelsize=5)
            ax_z.tick_params(axis="y", labelsize=5)
            ax.tick_params(axis="x", labelsize=5)
            ax.tick_params(axis="y", labelsize=5)
            fig.canvas.draw()
            plt.pause(0.5)
            
            #time_array = [j + count for j in time_array]
            #time_array = [j * 2 for j in time_array]
            #time_list.extend([j + count for j in time_list[-10:]])
            #if len(time_list) >= count*10 or len(x) >= count*10 or len(y) >= count*10 or len(z) >= count*10:
            #    del time_list[:10]
            #    del x[:10]
            #    del y[:10]
            #    del z[:10]
            '''
            continue
    except Exception as e:
        print("An error has occurred...")
        print(e)
        break








