import matplotlib.pyplot as plt
import numpy as np
import time
import matplotlib.pyplot as plt
import pymodbus
from pymodbus.pdu import ModbusRequest
from pymodbus.client.sync import ModbusSerialClient as ModbusClient
from pymodbus.transaction import ModbusRtuFramer
from pymodbus.client.sync import ModbusSerialClient

client = ModbusSerialClient(
    method='rtu',
    port='COM4',
    baudrate=115200,
    timeout=4,
    parity='N',
    stopbits=1,
    bytesize=8
)
connection = client.connect()
print("Connected = " + str(connection))

x_address = 0 + 5
y_address = 2048 + 5
z_address = 4096 + 5 #we cannot exceed counts of 5332 (meaning the address here + the count), since we dont have enough data memory in the FX3 to store as many holding registers for the freq bin values
count = 10
x_count = 10 #should be 100
y_count = 10
z_count = 10
slave_id = 1

first_read = 0
freq = []
for i in range(count):
    freq.append(0)

plt.ion()
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
                freq = np.array(res_freq.registers)
                first_read = 1
        time.sleep(0.1)
        client.write_coil(0, True)
        
        if not res_x_g.isError() and not res_y_g.isError() and not res_z_g.isError():
            
            plt.clf()
            
            x_g = np.array(res_x_g.registers)
            y_g = np.array(res_y_g.registers)
            z_g = np.array(res_z_g.registers)
            
            print("x data")
            print(x_g)
            print("y data")
            print(y_g)
            print("z data")
            print(z_g)
            print("frequency")
            print(freq)
            
            print("")
            print("----------------------------------")
            print("")
            
            plt.title('Acceleration data (frequency domain)')
            plt.xlabel('Frequency [Hz]')
            plt.ylabel('Gravities [mg]')
            plt.bar(freq, x_g, label="x-axis")
            plt.bar(freq, y_g, label="y-axis")
            plt.bar(freq, z_g, label="z-axis")
            plt.legend()
            plt.draw()
            plt.pause(1)
            
            print("time in between")
            
            #plt.clf()
            
            continue
    except Exception as e:
        print("An error has occurred...")
        print(e)
        break