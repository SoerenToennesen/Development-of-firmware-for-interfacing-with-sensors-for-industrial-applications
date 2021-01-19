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

    	//WHEN I REQUEST OVER 30 DATA POINTS (OR MORE) FROM THE HOLDINGREGISTER, THE OUTPUT BUFFER WILL BE OVER 64 BYTES LONG, AND THUS CRASH THE PROGRAM. CHANGE THE BYTES AMOUNT IF NEEDED.
    	if (input->buffer_p.count != 0) {
			response_buffer_dma = entry_func_dmamode(&(input->buffer_p.buffer), input->buffer_p.count);
			input->buffer_p.count = response_buffer_dma.response_size;
			int j;
			for (j = 0; j < response_buffer_dma.response_size; j++) {
				input->buffer_p.buffer[j] = response_buffer_dma.response_array[j];
			}
			status = CyU3PDmaChannelCommitBuffer (chHandle, input->buffer_p.count, 0);
			if (status != CY_U3P_SUCCESS) while(1);
			glPktsPending++;
    	} else {
    		status = CyU3PDmaChannelDiscardBuffer (chHandle);
			if (status != CY_U3P_SUCCESS) while(1);
    	}
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
    dmaConfig.size = 256; // used to be 32, but now we can request a size of ...125*2+6 = 256... 125 bytes. The modbus master simulator maximum requests 125 bytes. The request for 125 data points takes around 0.125 seconds including the request and receive.
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





















