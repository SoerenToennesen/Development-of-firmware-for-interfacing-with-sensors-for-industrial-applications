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
#include "../Application/application.h"
#include "../SPI/spi.h"
#include "../ADcmXL3021/adcmxl3021.h"
#include "../Modbus/modbus_self_implemented.h"



static          uint8_t  *UartDataBuffer = 0;   /* Buffer used for received UART data. */
static volatile uint32_t  UartDataCount  = 0;   /* Amount of data in the buffer. */
static          uint32_t  UartDataWrPtr  = 0;   /* Write pointer into the UART buffer. */
static          uint32_t  UartDataRdPtr  = 0;   /* Read pointer into the UART buffer. */
#define CY_FX_UARTLT_BUF_SIZE          (512)    /* Size of UART data buffer. */
#define UART_RECEIVE_DATA_EVT          (1 << 0) /* Flag for data received event. */


#define SLAVE_ADDRESS 1

CyU3PEvent  UartLpAppEvent2;                     /* Event flags group used by the application. */
uint8_t x = 0;
uint8_t databuffer[8];
//uint8_t * response_buffer;
struct response response_buffer;


/* UART event callback function. Schedules a UART receive call when the RX_DATA event is received. */
static void
CyFxUartLpApplnCallback2 (
        CyU3PUartEvt_t   evType,
        CyU3PUartError_t evStatus)
{
    uint8_t  rxData;
    uint32_t count;
    CyU3PReturnStatus_t status;
    if (evType == CY_U3P_UART_EVENT_RX_DATA) {
        do {
            /* Keep reading the incoming data into the buffer, as long as we have space. */
            count = CyU3PUartReceiveBytes (&rxData, 1, &status);


            if (count != 0) {
            	databuffer[x] = rxData;
				x++;
				// 8 because thats an RTU request length in bytes
				if (x == 8) {
					response_buffer = entry_func_regmode (databuffer, 8);

					CyU3PUartTransmitBytes (response_buffer.response_array, response_buffer.response_size, &status);
					x = 0;
				}
                /* Just drop the data if the buffer is already full. */
                if (UartDataCount < CY_FX_UARTLT_BUF_SIZE) {
                    UartDataBuffer[UartDataWrPtr] = rxData;
                    UartDataWrPtr++;
                    if (UartDataWrPtr == CY_FX_UARTLT_BUF_SIZE) UartDataWrPtr = 0;
                    UartDataCount++;
                }
            }
        } while (count != 0);
        CyU3PEventSet (&UartLpAppEvent, UART_RECEIVE_DATA_EVT, CYU3P_EVENT_OR);
    }
}

/* This function initializes the UART module */
void
CyFxUartLpApplnInit2 (void)
{
    CyU3PUartConfig_t uartConfig;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Initialize the UART module */
    //rs485_interface_init();
    apiRetStatus = CyU3PUartInit ();
    if (apiRetStatus != CY_U3P_SUCCESS) while(1);

    /* Configure the UART:
       Baud-rate = 9600, One stop bit, No parity, Flow control enabled.
     */
    CyU3PMemSet ((uint8_t *)&uartConfig, 0, sizeof(uartConfig));
    uartConfig.baudRate = CY_U3P_UART_BAUDRATE_9600;
    uartConfig.stopBit = CY_U3P_UART_ONE_STOP_BIT;
    uartConfig.parity = CY_U3P_UART_NO_PARITY;
    uartConfig.flowCtrl = CyFalse;
    uartConfig.txEnable = CyTrue;
    uartConfig.rxEnable = CyTrue;
    uartConfig.isDma = CyFalse; /* Register mode */

    /* Set the UART configuration */
    apiRetStatus = CyU3PUartSetConfig (&uartConfig, CyFxUartLpApplnCallback2);
    if (apiRetStatus != CY_U3P_SUCCESS) while(1);
}



/* Entry function for the UartLpAppThread. */
void
UartLpAppThread_Entry2 (
        uint32_t input)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint32_t            evStat;

    UartDataBuffer = (uint8_t *)CyU3PDmaBufferAlloc (CY_FX_UARTLT_BUF_SIZE);
    if (UartDataBuffer == 0) while (1);

    UartDataCount = 0;
    UartDataWrPtr = 0;
    UartDataRdPtr = 0;

    /* Initialize the UART example application */
    CyFxUartLpApplnInit2();

//    //init all HW interfaces
//    //rs485_interface_init();
//    //Init Modbus, set slave address
//    modbus_init(SLAVE_ADDRESS);
//    //Init your own reigsters
//    modbus_register_mapping_init();
//    modbus_variable_set_value(&modbus_variables_map.holding_register_1[0], 42);
//    for (;;) {
//    	//modbus_process();
//    	//modbus_variable_set_value(&HoldingRegister[HOLDING_REGISTER_1], 0x01);
//    	//CyU3PThreadSleep (3000);
//    	CyU3PThreadSleep (1);
//    	modbus_process();
//    	//modbus_variable_set_value(&HoldingRegister[HOLDING_REGISTER_1], 0x02);
//		//CyU3PThreadSleep (3000);
//    }




    /* We set a timeout of 1 for receive data and 50000 for transmit data.
     * Then wait until the callback notifies us of incoming data.
     * Once all of the data has been fetched, we loop the data back on the transmit side.
     */
    CyU3PUartSetTimeout (1, 50000);

    for (;;) {
    	status = CyU3PEventGet (&UartLpAppEvent, UART_RECEIVE_DATA_EVT, CYU3P_EVENT_OR_CLEAR, &evStat, CYU3P_WAIT_FOREVER);
    	if (status == CY_U3P_SUCCESS) {} // Just to make the compiler happy
    	// Below is a loopback function, that transmits bytes directly after they are received.
//        if (status == CY_U3P_SUCCESS) {
//            while (UartDataCount > 0) {
//                CyU3PUartTransmitBytes (UartDataBuffer + UartDataRdPtr, 1, &status);
//                if (status == CY_U3P_SUCCESS) {
//                    /* Move to the next byte. */
//                    UartDataRdPtr++;
//                    if (UartDataRdPtr == CY_FX_UARTLT_BUF_SIZE) UartDataRdPtr = 0;
//                    UartDataCount--;
//                } else {
//                    if (status != CY_U3P_ERROR_TIMEOUT) while (1);/* Failed to transmit the data back. Return error. */
//                }
//            }
//        }
    }
}


