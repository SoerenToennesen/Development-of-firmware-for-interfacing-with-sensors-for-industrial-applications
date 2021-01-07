
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

	//Sending all 200 in the CyU3PSpiTransmitWords function, the execution time is much more immediate (seems to be similar to how the GUI does it)
	int i;
	uint8_t data_for_sampling[200] = {0x00};
	for (i = 0; i < 150; i++) { //150 is an arbitrary amount of times - I would like to do it 4096 times, but it seems to take much longer than the GUI in execution time
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data_for_sampling, 200);
		CyU3PSpiSetSsnLine (CyTrue);
	}

	/*
	//Option 2 - using the "built-in" DMA functions to wait for responses
	CyU3PMemSet (glEp0Buffer, 0, sizeof (glEp0Buffer));
	CyU3PDmaBuffer_t buf_p;
	buf_p.buffer = glEp0Buffer;
	buf_p.status = 0;
	buf_p.size  = 0x70;
	buf_p.count = 0x70;
	CyU3PSpiSetSsnLine (CyFalse);
	CyU3PSpiSetBlockXfer (0, 0x64);

	//receives buffer
	status = CyU3PDmaChannelSetupRecvBuffer (&glSpiRxHandle, &buf_p);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "CyU3PDmaChannelSetupRecvBuffer failed\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}
	status = CyU3PDmaChannelWaitForCompletion (&glSpiRxHandle, CY_FX_USB_SPI_TIMEOUT);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "CyU3PDmaChannelWaitForCompletion failed\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PSpiSetSsnLine (CyTrue);
	CyU3PSpiDisableBlockXfer (CyFalse, CyTrue);
	*/

	// RECORD DATA IN RTS MODE //////////////////////////////// END

	CyU3PDebugPrint (2, "End of RTS-mode sampling\r\n");

	return status;
}

// Attempt at MTC mode
CyU3PReturnStatus_t start_sampling_MTC() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

	uint8_t data1[2], data2[2], data3[2], data4[2];
	data1[0] = 0x00;
	data1[1] = 0x80;
	data2[0] = 0x00;
	data2[1] = 0x81;
	data3[0] = 0x00;
	data3[1] = 0x1E;
	data4[0] = 0x00;
	data4[1] = 0x00;

	CyU3PSpiSetSsnLine (CyFalse);

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data1, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed1\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data2, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed2\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data3, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data4, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (120);

	data1[0] = 0x00;
	data1[1] = 0x80;
	data2[0] = 0x00;
	data2[1] = 0xBE;
	data3[0] = 0x08;
	data3[1] = 0xBF;
	//data4[0] = 0x00; //not present
	//data4[1] = 0x00; //not present

	CyU3PSpiSetSsnLine (CyFalse);

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data1, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed1\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data2, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed2\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data3, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	/*CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data4, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}*/

	CyU3PThreadSleep (120);

	data1[0] = 0x00;
	data1[1] = 0x80;
	data2[0] = 0x00;
	data2[1] = 0x81;
	data3[0] = 0x00;
	data3[1] = 0x66;
	data4[0] = 0x00; // Maybe we have to delete these two lines because Saleae Logic indicates its the
	data4[1] = 0x00; // solely a return signal from MISCO. The same is apparant for the following signals.

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data1, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed1\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data2, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed2\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data3, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data4, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (40);

	data1[0] = 0x00;
	data1[1] = 0x80;
	data2[0] = 0x00;
	data2[1] = 0x81;
	data3[0] = 0x00;
	data3[1] = 0x68;
	data4[0] = 0x00;
	data4[1] = 0x00;

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data1, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed1\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data2, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed2\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data3, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data4, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (4);

	data1[0] = 0x00;
	data1[1] = 0x80;
	data2[0] = 0x00;
	data2[1] = 0x8A;
	data3[0] = 0x00;
	data3[1] = 0x8B;
	//data4[0] = 0x00; //not present
	//data4[1] = 0x00; //not present

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data1, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed1\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data2, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed2\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data3, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	/*CyU3PThreadSleep (1);
	status = CyU3PSpiTransmitWords(data4, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}*/

	CyU3PThreadSleep (4);

	// -------------START HERE TO SAMPLE-------------

	//Start sampling indicator
	CyU3PThreadSleep (12);
	uint8_t data_min1[2];
	data_min1[0] = 0x00;
	data_min1[1] = 0x80;
	status = CyU3PSpiTransmitWords(data_min1, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	//CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (40);

	//CyU3PSpiSetSsnLine (CyFalse);

	//Actual sampling - WE MIGHT NOT TO SLEEP FOR 12MS BETWEEN EVERY RECORDING, AS IT IS NOT INDICATED BY THE DIAGRAM (FIGURE 4) IN THE DATASHEET
	int i;
	uint8_t data[2];
	data[0] = 0x00;
	data[1] = 0x0E;
	for (i = 0; i < 200; i++) {
		CyU3PThreadSleep (0.1);
		status = CyU3PSpiTransmitWords(data, 2);
		if (status != CY_U3P_SUCCESS) {
			CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
			CyU3PSpiSetSsnLine (CyTrue);
			return status;
		}
	}

	//End sampling indicator
	CyU3PThreadSleep (0.1);
	uint8_t data_min2[2];
	data_min2[0] = 0x00;
	data_min2[1] = 0x00;
	status = CyU3PSpiTransmitWords(data_min2, 2);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PSpiSetSsnLine (CyTrue);

	// ----------------END SAMPLE HERE---------------

	CyU3PDebugPrint (2, "End of sampling\r\n");
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
		CyU3PDebugPrint (2, "SPI WRITE command failed1\r\n");
		return status;
	}

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data2, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed2\r\n");
		return status;
	}

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data3, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed3\r\n");
		return status;
	}

	//CyU3PSpiSetSsnLine (CyTrue);

	return status;
}
