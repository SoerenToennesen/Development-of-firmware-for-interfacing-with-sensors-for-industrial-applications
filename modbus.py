
from pymodbus.client.sync import ModbusSerialClient as ModbusClient
#from pymodbus.register_read_message import ReadInputRegisterResponse


client = ModbusClient(method='rtu', port='\\\\.\\COM3', stopbits=1, bytesize=8, parity='N', baudrate=9600, timeout=0.3)


connection = client.connect()
print(connection)

#value = client.read_input_registers(300, 4, unit=0x01)
#print(value.registers)






