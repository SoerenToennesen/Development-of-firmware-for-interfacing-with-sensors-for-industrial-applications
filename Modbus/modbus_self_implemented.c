

//#include "driver_init.h"
#include <inttypes.h>

#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyu3usb.h"
#include "cyu3i2c.h"
#include "cyu3spi.h"
#include "cyu3uart.h"
#include <uart_regs.h>
#include "../UART/uart.h"
#include "modbus_self_implemented.h"

#include <stdio.h>
#include <stdint.h>

typedef unsigned char byte;

#define slave_id 0x01

uint16_t reg_start, reg_num;
uint16_t calculated_CRC_code, given_CRC_code, response_CRC_code;
uint8_t * temp_buf = NULL;
uint8_t * ret_response = NULL;
int i;
int ii;
int iii;
int iiii;

struct response ans;

volatile int16_t HoldingRegister[4096];
//volatile uint16_t HoldingRegister_RTS[1000];
//volatile uint16_t HoldingRegister_MTC_X[4096]; //can't do one for each because data overflows in cypress fx3...
//volatile uint16_t HoldingRegister_MTC_Y[4096];
//volatile uint16_t HoldingRegister_MTC_Z[4096];

//Understanding Modbus RTU requests:
//Example for holding register request:
//01 03 02 58 00 02 44 60
// 1. Unit address
//1. 01: slave address
// 2-6. PDU message. This can vary in size according to the request
//2. 03: function code for holding registers
//3&4. 02 58: Hex for 600
//5&6. 00 02: Hex for amount of registers to read (in this case 2)
// 7-8. CRC
//7. 44: check of address field (CRC code 1st)
//8. 60: check of message field (CRC code 2nd)
//Response: 01 03 04 03 E8 13 88 77 15
//1. Slave address
//2. Function code for holding registers
//3. Byte count , or in other words: register count * 2
// Actual register data values, size depends on how many registers to read. 2 bytes for each register value (I think - check this!)
//4&5. 03 E8: Value 1000 in register 600
//6&7. 13 88: Value 5000 in register 601
// https://www.fernhillsoftware.com/help/drivers/modbus/modbus-protocol.html

//CRC algorithm for Modbus based on CCS at https://ctlsys.com/support/how_to_compute_the_modbus_rtu_message_crc/
uint16_t ModRTU_CRC(byte buf[], int len) {
  uint16_t crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++) {
	crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc

	for (int i = 8; i != 0; i--) {    // Loop over each bit
	  if ((crc & 0x0001) != 0) {      // If the LSB is set
		crc >>= 1;                    // Shift right and XOR 0xA001
		crc ^= 0xA001;
	  }
	  else                            // Else LSB is not set
		crc >>= 1;                    // Just shift right
	}
  }
  uint8_t hibyte = (crc & 0xff00) >> 8;
  uint8_t lobyte = (crc & 0xff);
  crc = lobyte << 8 | hibyte;
  return crc;
}

//*RTS_code needs to be **RTS_code in the input parameter when using DMA-mode
struct response entry_func_dmamode(uint8_t **RTS_code, uint8_t count) {
	//Testing purposes, reading from register 600 for 2 registers will return 1000 and 5000 for 600 and 601 respectively.
	//HoldingRegister[600] = 0x03E8;
	//HoldingRegister[601] = 0x1388;

	ans.response_size = 0;
	temp_buf = *RTS_code; //Needs to be *RTS_code when using DMA-mode

	// Match the slave ID
	if (temp_buf[0] != slave_id) return ans;

	// Calculate CRC-code
	given_CRC_code = (temp_buf[count - 2] << 8) | (temp_buf[count - 1]);
	byte buf[count - 2];
	for(i = 0; i < count - 2; i++) {
		buf[i] = temp_buf[i];
	}
	calculated_CRC_code = ModRTU_CRC(buf, count - 2);
	if (given_CRC_code != calculated_CRC_code) return ans; // Should return error code according to modbus. 255 is only temporary.

	// Holding registers (0x03)
	if (temp_buf[1] == 0x03) {

		// Identify starting register
		reg_start = (temp_buf[2] << 8) | (temp_buf[3]);

		// Identify how many registers from starting register to read
		reg_num = (temp_buf[4] << 8) | (temp_buf[5]);

		// Process response
		ans.response_array[0] = slave_id;
		ans.response_array[1] = 0x03;
		ans.response_array[2] = (reg_num & 0xff) * 2;
		iii = 0;
		for (ii = 3; ii < 3 + ((reg_num & 0xff) * 2); ii+=2) {
			ans.response_array[ii] = (HoldingRegister[reg_start + iii] & 0xff00) >> 8;
			ans.response_array[ii + 1] = HoldingRegister[reg_start + iii] & 0xff;
			iii++;
		}
		ii = ii - 2;
		uint8_t temp_data_final[ii + 2];
		for (iiii = 0; iiii < ii + 2; iiii++) {
			temp_data_final[iiii] = ans.response_array[iiii];
		}
		response_CRC_code = ModRTU_CRC(temp_data_final, ii + 2);
		ans.response_array[ii+2] = (response_CRC_code & 0xff00) >> 8;
		ans.response_array[ii+3] = response_CRC_code & 0xff;

		ans.response_size = ii+4;
		return ans;
	}

	// Rest of modbus functionality is not implemented
	return ans;
}


//*RTS_code needs to be **RTS_code in the input parameter when using DMA-mode
struct response entry_func_regmode(uint8_t *RTS_code, uint8_t count) {
	ans.response_size = 0;

	temp_buf = RTS_code;

	// Match the slave ID
	if (temp_buf[0] != slave_id) return ans;

	// Calculate CRC-code
	given_CRC_code = (temp_buf[count - 2] << 8) | (temp_buf[count - 1]);
	byte buf[count - 2];
	for(i = 0; i < count - 2; i++) {
		buf[i] = temp_buf[i];
	}
	calculated_CRC_code = ModRTU_CRC(buf, count - 2);
	if (given_CRC_code != calculated_CRC_code) return ans; // Should return error code according to modbus. 255 is only temporary.

	// Holding registers (0x03)
	if (temp_buf[1] == 0x03) {

		// Identify starting register
		reg_start = (temp_buf[2] << 8) | (temp_buf[3]);

		// Identify how many registers from starting register to read
		reg_num = (temp_buf[4] << 8) | (temp_buf[5]);

		// Process response
		ans.response_array[0] = slave_id;
		ans.response_array[1] = 0x03;
		ans.response_array[2] = (reg_num & 0xff) * 2;
		iii = 0;
		for (ii = 3; ii < 3 + ((reg_num & 0xff) * 2); ii+=2) {
			ans.response_array[ii] = (HoldingRegister[reg_start + iii] & 0xff00) >> 8;
			ans.response_array[ii + 1] = HoldingRegister[reg_start + iii] & 0xff;
			iii++;
		}
		ii = ii - 2;
		uint8_t temp_data_final[ii + 2];
		for (iiii = 0; iiii < ii + 2; iiii++) {
			temp_data_final[iiii] = ans.response_array[iiii];
		}
		response_CRC_code = ModRTU_CRC(temp_data_final, ii + 2);
		ans.response_array[ii+2] = (response_CRC_code & 0xff00) >> 8;
		ans.response_array[ii+3] = response_CRC_code & 0xff;

		ans.response_size = ii+4;
		return ans;
	}

	// Rest of modbus functionality is not implemented
	return ans;
}
