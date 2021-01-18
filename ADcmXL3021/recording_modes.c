
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
	uint16_t data_to_store;
	int16_t signed_data_to_store;
	//uint8_t data_for_sampling[200] = {0x00};
	for (i = 0; i < 150; i++) { // This should be an infinite while-loop, but this is just for testing purposes so we can get on with the application.
		CyU3PSpiSetSsnLine (CyFalse);
		//status = CyU3PSpiTransmitWords(data_for_sampling, 200);
		status = CyU3PSpiReceiveWords (spi_data, 0xC8); //0xC8 for 200, data should be stored in rxData
		CyU3PSpiSetSsnLine (CyTrue);
		for (ii = 0; ii < 100; ii++) {
			data_to_store = (spi_data[ii * 2] << 8) | (spi_data[ii * 2 + 1]);
			//0x8000 is offset for signed,
			//0x0773 is 1907 as the multiplication factor for gravity,
			//0x03E8 is 1000 which needs to be divided twice to get
			//the correct multiplication factor, and go from mg to g (gravities) (WE DONT DO THIS, SO DATA IS IN mg)
			if (data_to_store > 0x8000) {
				data_to_store = (data_to_store - 0x8000) * 0x0773 / 0x03E8;// / 0x03E8;
				signed_data_to_store = data_to_store;
				signed_data_to_store = -(signed_data_to_store);
				//HoldingRegister[ii] = signed_data_to_store;
			} else { // this is negatives, we need to be able to express this somehow (right now its all positives)
				data_to_store = (0x8000 - data_to_store) * 0x0773 / 0x03E8;// / 0x03E8;
				signed_data_to_store = data_to_store;
				//HoldingRegister[ii] = signed_data_to_store;
			}
			HoldingRegister[ii] = signed_data_to_store;
		}
		CyU3PThreadSleep (12);
	}

//	//Option 2 - using the "built-in" DMA functions to wait for responses
//	CyU3PMemSet (glEp0Buffer, 0, sizeof (glEp0Buffer));
//	CyU3PDmaBuffer_t buf_p;
//	buf_p.buffer = glEp0Buffer;
//	buf_p.status = 0;
//	buf_p.size  = 0x70; //0xC8 = 200, 0x64 = 100
//	buf_p.count = 0x70;
//
//	int i, ii;
//	for (i = 0; i < 150; i++) {
//		CyU3PSpiSetSsnLine (CyFalse);
//		CyU3PSpiSetBlockXfer (0, 0x64); //Probably should be 0xC8
//
//		//receives buffer
//		status = CyU3PDmaChannelSetupRecvBuffer (&glSpiRxHandle, &buf_p);
//		if (status != CY_U3P_SUCCESS) {
//			CyU3PSpiSetSsnLine (CyTrue);
//			return status;
//		}
//		status = CyU3PDmaChannelWaitForCompletion (&glSpiRxHandle, 2000);
//		/*if (status != CY_U3P_SUCCESS) {
//			CyU3PSpiSetSsnLine (CyTrue);
//			return status;
//		}*/
//
//		CyU3PSpiSetSsnLine (CyTrue);
//		CyU3PSpiDisableBlockXfer (CyFalse, CyTrue);
//		for (ii = 0; ii < 50; ii++) {
//			HoldingRegister[ii] = (buf_p.buffer[ii * 2] << 8) | (buf_p.buffer[ii * 2 + 1]);//buf_p.buffer[ii];
//			//HoldingRegister[600] = 0x03E8; //hard coding 1000 for testing purposes in reg 600
//			//HoldingRegister[601] = 0x1388; // -||- 5000
//		}
//		CyU3PThreadSleep (12);
//	}


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





	CyU3PMemSet (glEp0Buffer, 0, sizeof (glEp0Buffer));
	CyU3PDmaBuffer_t buf_p;
	buf_p.buffer = glEp0Buffer;
	buf_p.status = 0;
	buf_p.size  = 0x2000; //65520 (0x1 0000 - 0x10), since we cant have 0x1 0000 (since its larger than uint16)
	buf_p.count = 0x2000;

	CyU3PMemSet (glEp0Buffer2, 0, sizeof (glEp0Buffer2));
	CyU3PDmaBuffer_t buf2_p;
	buf2_p.buffer = glEp0Buffer2;
	buf2_p.status = 0;
	buf2_p.size  = 0x2000;
	buf2_p.count = 0x2000;

	int i;
	for (i = 0; i < 4096; i+=2) {
		buf_p.buffer[i * 2] = 0x00;
		buf_p.buffer[i * 2 + 1] = 0x0E;
	}

	CyU3PSpiTransferWords (&buf_p, 0x2000, &buf2_p, 0x2000);

	//Because of missing memory/data on FX3 board, we will only take the last 4096/3 = 1365 values of each measurement. This is not good though, and we need a board with more memory.
	//FIGURE OUT THE LOGIC TO INVOKE THE LAST 1365 BYTES OF THE BUFFER WHEN STORING IT IN THE HOLDING REGISTER
	//X-axis
	int ii = 0;
	for (i = 0; i < 1364; i+=2) {
		HoldingRegister[i] = (buf2_p.buffer[/*(4095 - 1365) + */ii * 2 + 2] << 8) | (buf2_p.buffer[/*(4095 - 1365) + */ii * 2 + 1 + 2]); // +2 to ignore the first one, because the read is always "1 behind" the transmit
		ii++;
	}
	uint8_t spi_data[1];
	status = CyU3PSpiReceiveWords (spi_data, 0x01); //The last value
	HoldingRegister[1364] = spi_data[0];

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	for (i = 0; i < 4096; i+=2) {
		buf_p.buffer[i * 2] = 0x00;
		buf_p.buffer[i * 2 + 1] = 0x10;
	}

	CyU3PThreadSleep (20);

	CyU3PSpiTransferWords (&buf_p, 0x2000, &buf2_p, 0x2000);
	//Y-axis
	ii = 0;
	for (i = 1365; i < 2729; i+=2) {
		HoldingRegister[i] = (buf2_p.buffer[/*(4095 - 1365) + */ii * 2 + 2] << 8) | (buf2_p.buffer[/*(4095 - 1365) + */ii * 2 + 1 + 2]); // +2 to ignore the first one, because the read is always "1 behind" the transmit
		ii++;
	}
	status = CyU3PSpiReceiveWords (spi_data, 0x01); //The last value
	HoldingRegister[2729] = spi_data[0];

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	for (i = 0; i < 4096; i+=2) {
		buf_p.buffer[i * 2] = 0x00;
		buf_p.buffer[i * 2 + 1] = 0x12;
	}

	CyU3PThreadSleep (20);

	CyU3PSpiTransferWords (&buf_p, 0x2000, &buf2_p, 0x2000);
	//Z-axis
	ii = 0;
	for (i = 2730; i < 4095; i+=2) {
		HoldingRegister[i] = (buf2_p.buffer[/*(4095 - 1365) + */ii * 2 + 2] << 8) | (buf2_p.buffer[/*(4095 - 1365) + */ii * 2 + 1 + 2]); // +2 to ignore the first one, because the read is always "1 behind" the transmit
		ii++;
	}
	status = CyU3PSpiReceiveWords (spi_data, 0x01); //The last value
	HoldingRegister[4095] = spi_data[0];



	//DMA which is I don't know how to send 2 directional data (send 0x0E00 and recieve something because of this)
//	int i, ii;
//	for (i = 0; i < 150; i++) {
//		CyU3PSpiSetSsnLine (CyFalse);
//		CyU3PSpiSetBlockXfer (0x2000, 0x2000); //0x2000 = 4096*2 (as each sample of the 4096 is 16 bytes)
//
//		//receives buffer
//		status = CyU3PDmaChannelSetupRecvBuffer (&glSpiRxHandle, &buf_p);
//		status = CyU3PDmaChannelWaitForCompletion (&glSpiRxHandle, 200);
//
//		CyU3PSpiSetSsnLine (CyTrue);
//		CyU3PSpiDisableBlockXfer (CyFalse, CyTrue);
//		for (ii = 0; ii < 50; ii++) {
//			HoldingRegister[ii] = (buf_p.buffer[ii * 2] << 8) | (buf_p.buffer[ii * 2 + 1]);//buf_p.buffer[ii];
//			//HoldingRegister[600] = 0x03E8; //hard coding 1000 for testing purposes in reg 600
//			//HoldingRegister[601] = 0x1388; // -||- 5000
//		}
//		CyU3PThreadSleep (12);
//	}






//	int i;
//	data[0] = 0x00; data[1] = 0x0E; //X_BUF
//	for (i = 0; i < 4096; i++) {
//		CyU3PSpiSetSsnLine (CyFalse);
//		status = CyU3PSpiTransmitWords(data, 2);
//		CyU3PSpiSetSsnLine (CyTrue);
//	}
//
//	data[0] = 0x00; data[1] = 0x00;
//	CyU3PSpiSetSsnLine (CyFalse);
//	status = CyU3PSpiTransmitWords(data, 2);
//	CyU3PSpiSetSsnLine (CyTrue);
//
//	CyU3PThreadSleep (200);
//
//	data[0] = 0x00; data[1] = 0x80;
//	CyU3PSpiSetSsnLine (CyFalse);
//	status = CyU3PSpiTransmitWords(data, 2);
//	CyU3PSpiSetSsnLine (CyTrue);
//
//	CyU3PThreadSleep (20);
//
//	data[0] = 0x00; data[1] = 0x10; //Y_BUF
//	for (i = 0; i < 4096; i++) {
//		CyU3PSpiSetSsnLine (CyFalse);
//		status = CyU3PSpiTransmitWords(data, 2);
//		CyU3PSpiSetSsnLine (CyTrue);
//	}
//
//	data[0] = 0x00; data[1] = 0x00;
//	CyU3PSpiSetSsnLine (CyFalse);
//	status = CyU3PSpiTransmitWords(data, 2);
//	CyU3PSpiSetSsnLine (CyTrue);
//
//	CyU3PThreadSleep (200);
//
//	data[0] = 0x00; data[1] = 0x80;
//	CyU3PSpiSetSsnLine (CyFalse);
//	status = CyU3PSpiTransmitWords(data, 2);
//	CyU3PSpiSetSsnLine (CyTrue);
//
//	CyU3PThreadSleep (20);
//
//	data[0] = 0x00; data[1] = 0x12; //Z_BUF
//	for (i = 0; i < 4096; i++) {
//		CyU3PSpiSetSsnLine (CyFalse);
//		status = CyU3PSpiTransmitWords(data, 2);
//		CyU3PSpiSetSsnLine (CyTrue);
//	}
//
//	data[0] = 0x00; data[1] = 0x00;
//	CyU3PSpiSetSsnLine (CyFalse);
//	status = CyU3PSpiTransmitWords(data, 2);
//	CyU3PSpiSetSsnLine (CyTrue);

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
	int i;
	for (i = 0; i < 2048; i++) {
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		//CyU3PThreadSleep (0.035);
	}

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (20);

	data[0] = 0x00; data[1] = 0x10;
	for (i = 0; i < 2048; i++) {
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		//CyU3PThreadSleep (0.035);
	}

	CyU3PThreadSleep (200);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (20);

	data[0] = 0x00; data[1] = 0x12;
	for (i = 0; i < 2048; i++) {
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		//CyU3PThreadSleep (0.035);
	}


	// WRITE TO TRIGGER DATA CAPTURE IN MFFT MODE ///////////// END

	// END CAPTURE ////////////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	// END CAPTURE //////////////////////////////////////////// END

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

		data[0] = 0x00; data[1] = 0x0E;
		int i;
		for (i = 0; i < 2048; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
		}

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x10;
		for (i = 0; i < 2048; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			//CyU3PThreadSleep (0.035);
		}

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x12;
		for (i = 0; i < 2048; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			//CyU3PThreadSleep (0.035);
		}

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1333);
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
