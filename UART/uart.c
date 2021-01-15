#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyu3usb.h"
#include "cyu3i2c.h"
#include "cyu3spi.h"
#include "cyu3uart.h"
#include <uart_regs.h>

#include "../CyFxFiles/cyfxusbspidmamode.h"
#include "../GPIO/gpio.h"
#include "../Application/application.h"
#include "../SPI/spi.h"
#include "../ADcmXL3021/adcmxl3021.h"
#include "../Modbus/modbus_self_implemented.h"



CyU3PDmaChannel glUartLpChHandle;                 /* DMA Channel handle */

volatile uint16_t glPktsPending = 0;            /* Number of packets that have been committed since last check. */
uint32_t regValueEn, regValueDs;
uint8_t block_transmit = 1;

CyU3PDmaBuffer_t response_buffer_new;
uint8_t test_buffer[12];
struct response response_buffer_dma;


/* Callback funtion for the DMA event notification */
void CyFxUartLpDmaCallback (
        CyU3PDmaChannel   *chHandle, /* Handle to the DMA channel. */
        CyU3PDmaCbType_t  type,      /* Callback type.             */
        CyU3PDmaCBInput_t *input)    /* Callback status.           */
{
    CyU3PReturnStatus_t status;
    //uint8_t * response = NULL;
    if (type == CY_U3P_DMA_CB_PROD_EVENT) {
        /* This is a produce event notification to the CPU. This notification is
         * received upon reception of every buffer. The buffer will not be sent
         * out unless it is explicitly committed. The call shall fail if there
         * is any application error. */
    	response_buffer_dma = entry_func_dmamode(&(input->buffer_p.buffer), input->buffer_p.count);
    	// response_buffer_dma needs to be sent out through the UART.´
    	// Has size response_buffer_dma.response_size
    	// Has array response_buffer_dma.response_array
    	// response_buffer_dma.response_array can vary in size, but we just need to send it all out at once through UART

    	//original code:
    	status = CyU3PDmaChannelCommitBuffer (chHandle, input->buffer_p.count, 0);

//    	//initial thought:
//    	input->buffer_p.count = response_buffer_dma.response_size;
//    	int j;
//    	for (j = 0; j < response_buffer_dma.response_size; j++) {
//    		input->buffer_p.buffer[j] = response_buffer_dma.response_array[j];
//    	}
//
//    	status = CyU3PDmaChannelCommitBuffer (chHandle, input->buffer_p.count, 0);
//		if (status != CY_U3P_SUCCESS) while(1);
//		glPktsPending++;

		//second thought (create a new channel buffer and send it through, but problem still persists!)
//		status = CyU3PDmaChannelGetBuffer(&glUartLpChHandle, &response_buffer_new, 0);
//		if (status != CY_U3P_SUCCESS) while(1);
//		//Test data
//		response_buffer.count = 9;
//		response_buffer.buffer[0] = 0x01;
//		response_buffer.buffer[1] = 0x03;
//		response_buffer.buffer[2] = 0x04;
//		response_buffer.buffer[3] = 0x03;
//		response_buffer.buffer[4] = 0xE8;
//		response_buffer.buffer[5] = 0x13;
//		response_buffer.buffer[6] = 0x88;
//		response_buffer.buffer[7] = 0x77;
//		response_buffer.buffer[8] = 0x15;
//		status = CyU3PDmaChannelCommitBuffer (chHandle, response_buffer.count, 0);

//		//Attempts at erasing whatever is contained in the buffer
//		status = CyU3PDmaChannelDiscardBuffer (chHandle);
//		if (status != CY_U3P_SUCCESS) while(1);
//		status = CyU3PDmaChannelReset (&glUartLpChHandle);
//		if (status != CY_U3P_SUCCESS) while(1);


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
    }
}



/* This function initializes the UART module */
void CyFxUartLpApplnInit (void) {
    CyU3PUartConfig_t uartConfig;
    CyU3PDmaChannelConfig_t dmaConfig;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Initialize the UART module */
    apiRetStatus = CyU3PUartInit ();
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
    	for (;;) {}
    }

    /* Configure the UART
       Baudrate = 9600, One stop bit, No parity, Hardware flow control enabled.
     */
    CyU3PMemSet ((uint8_t *)&uartConfig, 0, sizeof(uartConfig));
    uartConfig.baudRate = CY_U3P_UART_BAUDRATE_9600;
    uartConfig.stopBit = CY_U3P_UART_ONE_STOP_BIT;
    uartConfig.parity = CY_U3P_UART_NO_PARITY;
    uartConfig.flowCtrl = CyTrue;
    uartConfig.txEnable = CyTrue;
    uartConfig.rxEnable = CyTrue;
    uartConfig.isDma = CyTrue; /* DMA mode */

    /* Set the UART configuration */
    apiRetStatus = CyU3PUartSetConfig (&uartConfig, NULL);
    if (apiRetStatus != CY_U3P_SUCCESS ) while(1);

    // Create a DMA Manual channel between UART producer socket and UART consumer socket
    CyU3PMemSet ((uint8_t *)&dmaConfig, 0, sizeof(dmaConfig));
    dmaConfig.size = 64;
    dmaConfig.count = 4;
    dmaConfig.prodSckId = CY_U3P_LPP_SOCKET_UART_PROD;
    dmaConfig.consSckId = CY_U3P_LPP_SOCKET_UART_CONS;
    dmaConfig.dmaMode = CY_U3P_DMA_MODE_BYTE;
    dmaConfig.notification = CY_U3P_DMA_CB_PROD_EVENT;
    dmaConfig.cb = CyFxUartLpDmaCallback;
    dmaConfig.prodHeader = 0;
    dmaConfig.prodFooter = 0;
    dmaConfig.consHeader = 0;
    dmaConfig.prodAvailCount = 0;

    /* Create the channel */
    apiRetStatus = CyU3PDmaChannelCreate (&glUartLpChHandle, CY_U3P_DMA_TYPE_MANUAL, &dmaConfig);
    if (apiRetStatus != CY_U3P_SUCCESS) while(1);

    /* Set UART Tx and Rx transfer Size to infinite */
    apiRetStatus = CyU3PUartTxSetBlockXfer(0xFFFFFFFF);
    if (apiRetStatus != CY_U3P_SUCCESS) while(1);

    apiRetStatus = CyU3PUartRxSetBlockXfer(0xFFFFFFFF);
    if (apiRetStatus != CY_U3P_SUCCESS) while(1);

    /* Set DMA Channel transfer size */
    apiRetStatus = CyU3PDmaChannelSetXfer (&glUartLpChHandle, 0);
    if (apiRetStatus != CY_U3P_SUCCESS) while(1);

    //CyU3PUartSetTimeout (1, 50000);

}


/* Entry function for the UartLpAppThread */
void
UartLpAppThread_Entry (
        uint32_t input)
{
	//CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	regValueEn = 0;
	regValueDs = 0;

	// Initialize the UART Example Application
	CyFxUartLpApplnInit();

	/* UART Config Value for Enabling Rx Block */
	regValueEn = UART->lpp_uart_config;

	/* UART Config Value for Disabling the Rx Block  */
	regValueDs = UART->lpp_uart_config & (~(CY_U3P_LPP_UART_RTS | CY_U3P_LPP_UART_RX_ENABLE));

	for (;;) {

		while (block_transmit) {
			if (glIsApplnActive)
			{
				/* While the application is active, check for data sent during the last 50 ms. If no data
				   has been sent to the host, use the channel wrap-up feature to send any partial buffer to
				   the USB host.
				*/
				if (glPktsPending == 0)
				{
					/* Disable UART Receiver Block */
					UART->lpp_uart_config = regValueDs;

					//PARSE DATA IN BUFFER

					//MANUALLY INSERT DATA INTO BUFFER

					CyU3PDmaChannelSetWrapUp (&glUartLpChHandle);

					/* Enable UART Receiver Block */
					UART->lpp_uart_config = regValueEn;
				}

				glPktsPending = 0;
			}

			CyU3PThreadSleep (50);

		}
	}

}





















