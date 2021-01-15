import time
import serial

ser=serial.Serial(port='com4', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)
invoke_data = 0x41
invoke_data2 = hex(ord('A'))
invoke_data3 = hex(3)
invoke_data4 = 0x03

print ("Serial is open: " + str(ser.isOpen()))
print ("Now Writing")
ser.write(b'\x0101')

'''
while True:
    data_response = ser.readline()
    print(data_response.decode('utf-8'))

'''

'''
while True:
    print("Writing data")
    ser.write(invoke_data)
    print("Waiting for response data")
    data_response = ser.readline()
    print(data_response.decode('utf-8'))
    time.sleep(5)
'''
while True:
    for i in range(150):
        ser.write('A'.encode()) #A
        ser.write(b'\x42')      #B
    time.sleep(0.5)

ser.close