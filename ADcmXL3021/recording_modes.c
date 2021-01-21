
#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyu3usb.h"
#include "cyu3i2c.h"
#include "cyu3spi.h"
#include "cyu3uart.h"

#include "../CyFxFiles/cyfxusbspidmamode.h"
#include "../GPIO/gpio.h"
#include "../SPI/spi.h"
#include "../UART/uart.h"
#include "../Modbus/modbus_self_implemented.h"





// We have to unplug the power to the accelerometer to reset from RTS mode, since we have no stop signal
// Otherwise, when restarting the program on the FX3 chip, it still records data from the beginning (w/o configuration)
CyU3PReturnStatus_t start_sampling_RTS() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	// SELECT RTS MODE ////////////////////////////////////// START

	data[0] = 0x00;
	data[1] = 0x80; //Page ID selector
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.35);

	data[0] = 0x00;
	data[1] = 0x81; //Page ID selector
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.25);

	data[0] = 0x00;
	data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.35);

	data[0] = 0x00;
	data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.35);

	data[0] = 0x03; //RTS selector (11 = 3 in decimal)
	data[1] = 0x9A; //REC_CTRL (9A - 80 = 1A)
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.25);

	data[0] = 0x11;
	data[1] = 0x9B; //REC_CTRL 2nd
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	// SELECT RTS MODE //////////////////////////////////////// END


	// WRITE TO TRIGGER DATA IN RTS MODE //////////////////// START

	CyU3PThreadSleep (150);

	data[0] = 0x00;
	data[1] = 0x80; //Page ID selector
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.45);

	data[0] = 0x03;
	data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.4);

	data[0] = 0x01;
	data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	data[0] = 0x00;
	data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (10);

	data[0] = 0x00;
	data[1] = 0x64; //MISC_CTRL read
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0xE4; //MISC_CTRL write (E4 - 80 = 64)
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0xE5; //MISC_CTRL write 2nd
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0xBE; //GLOB_CMD (3E + 80 = BE)
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x08; //Trigger capture
	data[1] = 0xBF; //GLOB_CMD 2nd
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	// WRITE TO TRIGGER DATA IN RTS MODE ////////////////////// END

	// RECORD DATA IN RTS MODE ////////////////////////////// START

	// Sending all 200 in the CyU3PSpiTransmitWords/CyU3PSpiReceiveWords function,
	// the execution time is much more immediate (seems to be similar to how the GUI does it)
	int i, ii;
	uint8_t  spi_data[200];
	for (i = 0; i < 150; i++) { // This should be an infinite while-loop, but this is just for testing purposes so we can get on with the application.
		CyU3PSpiSetSsnLine (CyFalse);
		//status = CyU3PSpiTransmitWords(data_for_sampling, 200);
		status = CyU3PSpiReceiveWords (spi_data, 0xC8); //0xC8 for 200, data should be stored in rxData
		CyU3PSpiSetSsnLine (CyTrue);
		for (ii = 0; ii < 100; ii++) {
			// 0x8000 is offset for signed,
			// 0x0773 is the multiplication factor to get it in mg. 0x03E8 is the division factor to divide it by 1000, as the mg multiplication factor was 1000 too much (as it is a decimal number)
			// Data is stored in mg (gravities)
			HoldingRegister[ii] = (((((spi_data[ii*2] << 8) | (spi_data[ii*2+1])) - 0x8000) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
		}
		CyU3PThreadSleep (12);
	}

	// RECORD DATA IN RTS MODE //////////////////////////////// END

	return status;
}


CyU3PReturnStatus_t start_sampling_MTC() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	// SELECT MTC MODE ////////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// SELECT MTC MODE //////////////////////////////////////// END

	// TRIGGER RECORDING //////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x08; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (100);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x66;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x68;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x8A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x8B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (20);

	data[0] = 0x00; data[1] = 0x0E;
	uint8_t receive_data[2];
	int i;
	for (i = -1; i < 99; i++) { // The reason why we do this as a loop (1 by 1) rather than sending 100 datapoints in at once, is because, after trial and error, this way yields the best results.
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiTransferWords (data, 2, receive_data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		if (i >= 0) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
			HoldingRegister[i] = ((((receive_data[0] << 8) | (receive_data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
		}
	}
	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	CyU3PSpiReceiveWords (data, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	HoldingRegister[99] = ((((data[0] << 8) | (data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8; // Do the last holding register, which is retreived from 0x0000.

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (20);

	data[0] = 0x00; data[1] = 0x10;
	for (i = 99; i < 199; i++) {
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiTransferWords (data, 2, receive_data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		if (i >= 100) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
			HoldingRegister[i] = ((((receive_data[0] << 8) | (receive_data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
		}
	}
	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	CyU3PSpiReceiveWords (data, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	HoldingRegister[199] = ((((data[0] << 8) | (data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8; // Do the last holding register, which is retreived from 0x0000.

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (20);

	data[0] = 0x00; data[1] = 0x12;
	for (i = 199; i < 299; i++) {
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiTransferWords (data, 2, receive_data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		if (i >= 200) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
			HoldingRegister[i] = ((((receive_data[0] << 8) | (receive_data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
		}
	}
	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	CyU3PSpiReceiveWords (data, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	HoldingRegister[299] = ((((data[0] << 8) | (data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8; // Do the last holding register, which is retreived from 0x0000.

	// TRIGGER RECORDING ////////////////////////////////////// END

	return status;
}


CyU3PReturnStatus_t start_sampling_MFFT() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	CyU3PThreadSleep (12);

	// SELECT MFFT MODE ///////////////////////////////////// START
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.20);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.20);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.20);

	data[0] = 0x00; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.20);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	// SELECT MFFT MODE /////////////////////////////////////// END

	CyU3PThreadSleep (12);

	// WRITE TO TRIGGER DATA CAPTURE IN MFFT MODE /////////// START
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.30);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x08; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (3000);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x3A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (10);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.42);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.40);

	data[0] = 0x00; data[1] = 0x66;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.75);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.50);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.40);

	data[0] = 0x00; data[1] = 0x68;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (5);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.42);

	data[0] = 0x00; data[1] = 0x8A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);//CyU3PThreadSleep (0.55);

	data[0] = 0x00; data[1] = 0x8B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (4);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (40);

	data[0] = 0x00; data[1] = 0x0E;
	uint8_t receive_data[2];
	int i;
	for (i = -1; i < 99; i++) { // The reason why we do this as a loop (1 by 1) rather than sending 100 datapoints in at once, is because, after trial and error, this way yields the best results.
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiTransferWords (data, 2, receive_data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		if (i >= 0) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
			HoldingRegister[i] = ((receive_data[0] << 8) | (receive_data[1]));
		}
	}
	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	CyU3PSpiReceiveWords (data, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	HoldingRegister[99] = ((data[0] << 8) | (data[1])); // Do the last holding register, which is retreived from 0x0000.

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (20);

	data[0] = 0x00; data[1] = 0x10;
	for (i = 99; i < 199; i++) {
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiTransferWords (data, 2, receive_data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		if (i >= 100) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
			HoldingRegister[i] = ((receive_data[0] << 8) | (receive_data[1]));
		}
	}
	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	CyU3PSpiReceiveWords (data, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	HoldingRegister[199] = ((data[0] << 8) | (data[1])); // Do the last holding register, which is retreived from 0x0000.

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (20);

	data[0] = 0x00; data[1] = 0x12;
	for (i = 199; i < 299; i++) {
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiTransferWords (data, 2, receive_data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		if (i >= 200) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
			HoldingRegister[i] = ((receive_data[0] << 8) | (receive_data[1]));
		}
	}
	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	CyU3PSpiReceiveWords (data, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	HoldingRegister[299] = ((data[0] << 8) | (data[1])); // Do the last holding register, which is retreived from 0x0000.

	// WRITE TO TRIGGER DATA CAPTURE IN MFFT MODE ///////////// END

	return status;
}


CyU3PReturnStatus_t start_sampling_AFFT() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	CyU3PThreadSleep (12);

	// SELECT AFFT MODE ///////////////////////////////////// START
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	// SELECT AFFT MODE /////////////////////////////////////// END

	CyU3PThreadSleep (150);

	// CHANGE FFT REGISTERS AND PROD REGISTERS ////////////// START

	// Write 0x02 to AVG_CNT (time average to 2^2)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0xBA;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBB;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// Read 0x02 from AVG_CNT (not needed - for testing purposes)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x3A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// Write 102 to FFT_AVG1 (configures SR0 FFT averaging to 2, and leaves SR1 rate at default)
	// Along with 0x02 in AVG_CNT, this sets the device for a capture duration of 1.8 seconds
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x86;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x87;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// Read what was just written (again, not needed, just for testing purposes)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x06;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// Write 2 to REC_PRD (configures device for automatic repeat time of 2 seconds)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9F;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// Read what was just written (again, not needed - just for testing purposes)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// CHANGE FFT REGISTERS AND PROD REGISTERS //////////////// END

	// TRIGGER RECORDING AFFT /////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x06;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x08;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x3A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (10);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x08; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1000);

	//Start recording automatically in a loop
	for (;;) {

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x3A;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x66;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x66;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x68;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (4);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x8A;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x8B;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (2);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (3);

		// Every time we print 0x0E, 0x10, 0x12, the BUF_PNTR automatically advances from 0-2047 (as there are so many stored in each buffer). FFT data is unsigned 16-bit.

		data[0] = 0x00; data[1] = 0x0E;
		uint8_t receive_data[2];
		int i;
		for (i = -1; i < 99; i++) { // The reason why we do this as a loop (1 by 1) rather than sending 100 datapoints in at once, is because, after trial and error, this way yields the best results.
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 0) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
				HoldingRegister[i] = ((receive_data[0] << 8) | (receive_data[1]));
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		HoldingRegister[99] = ((data[0] << 8) | (data[1])); // Do the last holding register, which is retreived from 0x0000.

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x10;
		for (i = 99; i < 199; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 100) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
				HoldingRegister[i] = ((receive_data[0] << 8) | (receive_data[1]));
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		HoldingRegister[199] = ((data[0] << 8) | (data[1])); // Do the last holding register, which is retreived from 0x0000.

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x12;
		for (i = 199; i < 299; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 200) { //-1 to 99 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
				HoldingRegister[i] = ((receive_data[0] << 8) | (receive_data[1]));
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		HoldingRegister[299] = ((data[0] << 8) | (data[1])); // Do the last holding register, which is retreived from 0x0000.

		CyU3PThreadSleep (1333); // set this timer depending on how often you want it to run
	}

	// TRIGGER RECORDING AFFT ///////////////////////////////// END

	return status;
}


CyU3PReturnStatus_t turnOnOrOffADcmXL3021() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

	uint8_t data1[2], data2[2], data3[2];
	data1[0] = 0x00;
	data1[1] = 0x80;
	data2[0] = 0x02;
	data2[1] = 0xBE;
	data3[0] = 0x00;
	data3[1] = 0xBF;

	//CyU3PSpiSetSsnLine (CyFalse);

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data1, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		return status;
	}

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data2, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		return status;
	}

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data3, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		return status;
	}

	//CyU3PSpiSetSsnLine (CyTrue);

	return status;
}
