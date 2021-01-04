/*
## Cypress USB 3.0 Platform source file (cyfxusbspidmamode.c)
## ===========================
##
##  Copyright Cypress Semiconductor Corporation, 2010-2018,
##  All Rights Reserved
##  UNPUBLISHED, LICENSED SOFTWARE.
##
##  CONFIDENTIAL AND PROPRIETARY INFORMATION
##  WHICH IS THE PROPERTY OF CYPRESS.
##
##  Use of this file is governed
##  by the license agreement included in the file
##
##     <install>/license/license.txt
##
##  where <install> is the Cypress software
##  installation root directory path.
##
## ===========================
*/

/* This application is used read / write to SPI flash devices from USB.
   The firmware enumerates as a custom device communicating with the
   cyUsb3.sys driver and provides a set of vendor commands that can be
   access the attached SPI flash device.
 */

#include "stdint.h"
#include "stdio.h"

#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyu3usb.h"
#include "cyu3i2c.h"
#include "cyu3spi.h"
#include "cyu3uart.h"
#include "cyfxusbspidmamode.h"

#include <cyu3gpio.h>





#define CY_FX_GPIOAPP_THREAD_STACK       (0x0400)   /* GPIO application thread stack size */
#define CY_FX_GPIOAPP_THREAD_PRIORITY    (8)        /* GPIO application thread priority */

#define CY_FX_GPIOAPP_GPIO_HIGH_EVENT    (1 << 0)   /* GPIO high event */
#define CY_FX_GPIOAPP_GPIO_LOW_EVENT     (1 << 1)   /* GPIO low event */

CyU3PThread gpioOutputThread;   /* GPIO thread structure */
CyU3PThread gpioInputThread;    /* GPIO thread structure */
CyU3PEvent glFxGpioAppEvent;    /* GPIO input event group. */



CyU3PDmaBuffer_t buffer_p;

CyU3PThread appThread;                  /* Application thread object. */
CyBool_t glIsApplnActive = CyFalse;

/* Firmware ID variable that may be used to verify SPI firmware. */
const uint8_t glFirmwareID[32] __attribute__ ((aligned (32))) = { 'F', 'X', '3', ' ', 'S', 'P', 'I', '\0' };

uint8_t glEp0Buffer[4096] __attribute__ ((aligned (32)));

uint16_t glSpiPageSize = 0x100;  /* SPI Page size to be used for transfers. */

CyU3PDmaChannel glSpiTxHandle;   /* SPI Tx channel handle */
CyU3PDmaChannel glSpiRxHandle;   /* SPI Rx channel handle */

/* Initialize the debug module with UART. */
CyU3PReturnStatus_t
CyFxDebugInit (
        void)
{
    CyU3PUartConfig_t uartConfig;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Initialize and configure the UART for logging. */
    status = CyU3PUartInit ();
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    CyU3PMemSet ((uint8_t *)&uartConfig, 0, sizeof (uartConfig));
    uartConfig.baudRate = CY_U3P_UART_BAUDRATE_115200;
    uartConfig.stopBit  = CY_U3P_UART_ONE_STOP_BIT;
    uartConfig.parity   = CY_U3P_UART_NO_PARITY;
    uartConfig.txEnable = CyTrue;
    uartConfig.rxEnable = CyFalse;
    uartConfig.flowCtrl = CyFalse;
    uartConfig.isDma    = CyTrue;
    status = CyU3PUartSetConfig (&uartConfig, NULL);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Set the dma for an inifinity transfer */
    status = CyU3PUartTxSetBlockXfer (0xFFFFFFFF);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Start the debug module for printing log messages. */
    status = CyU3PDebugInit (CY_U3P_LPP_SOCKET_UART_CONS, 8);

    return status;
}



/* SPI initialization for application. */
CyU3PReturnStatus_t
CyFxSpiInit (uint16_t pageLen)
{
    CyU3PSpiConfig_t spiConfig;
    CyU3PDmaChannelConfig_t dmaConfig;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Start the SPI module and configure the master. */
    status = CyU3PSpiInit();
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Start the SPI master block. Run the SPI clock at 8MHz
     * and configure the word length to 8 bits. Also configure
     * the slave select using FW. */
    CyU3PMemSet ((uint8_t *)&spiConfig, 0, sizeof(spiConfig));
    spiConfig.isLsbFirst = CyFalse;
    spiConfig.cpol       = CyTrue;
    spiConfig.ssnPol     = CyFalse;
    spiConfig.cpha       = CyTrue;
    spiConfig.leadTime   = CY_U3P_SPI_SSN_LAG_LEAD_HALF_CLK;
    spiConfig.lagTime    = CY_U3P_SPI_SSN_LAG_LEAD_HALF_CLK;
    spiConfig.ssnCtrl    = CY_U3P_SPI_SSN_CTRL_FW;
    spiConfig.clock      = 8000000;
    spiConfig.wordLen    = 8;

    status = CyU3PSpiSetConfig (&spiConfig, NULL);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Create the DMA channels for SPI write and read. */
    CyU3PMemSet ((uint8_t *)&dmaConfig, 0, sizeof(dmaConfig));
    dmaConfig.size           = pageLen;
    /* No buffers need to be allocated as this channel
     * will be used only in override mode. */
    dmaConfig.count          = 0;
    dmaConfig.prodAvailCount = 0;
    dmaConfig.dmaMode        = CY_U3P_DMA_MODE_BYTE;
    dmaConfig.prodHeader     = 0;
    dmaConfig.prodFooter     = 0;
    dmaConfig.consHeader     = 0;
    dmaConfig.notification   = 0;
    dmaConfig.cb             = NULL;

    /* Channel to write to SPI flash. */
    dmaConfig.prodSckId = CY_U3P_CPU_SOCKET_PROD;
    dmaConfig.consSckId = CY_U3P_LPP_SOCKET_SPI_CONS;
    status = CyU3PDmaChannelCreate (&glSpiTxHandle,
            CY_U3P_DMA_TYPE_MANUAL_OUT, &dmaConfig);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Channel to read from SPI flash. */
    dmaConfig.prodSckId = CY_U3P_LPP_SOCKET_SPI_PROD;
    dmaConfig.consSckId = CY_U3P_CPU_SOCKET_CONS;
    status = CyU3PDmaChannelCreate (&glSpiRxHandle,
            CY_U3P_DMA_TYPE_MANUAL_IN, &dmaConfig);

    if (status == CY_U3P_SUCCESS)
    {
        glSpiPageSize = pageLen;
    }

    return status;
}


/* Read real-time data */

CyU3PReturnStatus_t readData(uint8_t *buffer) {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	CyU3PDmaBuffer_t buf_p;


	buf_p.buffer = buffer;
	buf_p.status = 0;
    buf_p.size  = 0x70;
    buf_p.count = 0x70;

	uint8_t data[5];    //rasx
	data[0] = 0x00;
	data[1] = 0x3E;
	data[2] = 0x00;
	data[3] = 0x08;
	data[4] = 0x00;
	data[5] = 0x00;

	uint8_t data2[2];
	data[0] = 0x3E;
	data[1] = 0x02;

	//uint8_t data[] = {0x00, 0x3E,0x00, 0x08, 0x00, 0x00};
	//uint8_t data[] = {0x02, 0x3E, 0x08};
	//uint8_t data[] = {0x08, 0x3E, 0x02};

	CyU3PSpiSetSsnLine (CyFalse);

	status = CyU3PSpiTransmitWords(data2, 3);

	//Do we need to reset DMA channels? Check cy3spi.h descriptions ...

	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
	}

	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep(20); //min 12ms delay

	CyU3PSpiSetSsnLine (CyFalse);

	//status = CyU3PSpiReceiveWords(dataBuffer, 200);   //this is register mode

	// The second parameter is Number of words (200/2 (wordlenth) to be received  (not bytes)
	//enables the DMA mode
	//rasx
	CyU3PSpiSetBlockXfer (0, 0x64);

	//receives buffer
	status = CyU3PDmaChannelSetupRecvBuffer (&glSpiRxHandle, &buf_p);
	if (status != CY_U3P_SUCCESS)
	{
		CyU3PDebugPrint (2, "CyU3PDmaChannelSetupRecvBuffer failed\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}
	status = CyU3PDmaChannelWaitForCompletion (&glSpiRxHandle,
	CY_FX_USB_SPI_TIMEOUT);
	if (status != CY_U3P_SUCCESS)
	{
		CyU3PDebugPrint (2, "CyU3PDmaChannelWaitForCompletion failed\r\n");
		CyU3PSpiSetSsnLine (CyTrue);
		return status;
	}

	CyU3PSpiSetSsnLine (CyTrue);
	CyU3PSpiDisableBlockXfer (CyFalse, CyTrue);

	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI READ command failed\r\n");
	}

	//CyU3PSpiSetSsnLine (CyTrue);


	return status;

}



CyBool_t
CyFxUSBSetupCB (
        uint32_t setupdat0,
        uint32_t setupdat1)
{
    /* Fast enumeration is used. Only requests addressed to the interface, class,
     * vendor and unknown control requests are received by this function. */

    uint8_t  bRequest, bReqType;
    uint8_t  bType, bTarget;
    uint16_t wValue, wIndex, wLength;
    CyBool_t isHandled = CyFalse;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Decode the fields from the setup request. */
    bReqType = (setupdat0 & CY_U3P_USB_REQUEST_TYPE_MASK);
    bType    = (bReqType & CY_U3P_USB_TYPE_MASK);
    bTarget  = (bReqType & CY_U3P_USB_TARGET_MASK);
    bRequest = ((setupdat0 & CY_U3P_USB_REQUEST_MASK) >> CY_U3P_USB_REQUEST_POS);
    wValue   = ((setupdat0 & CY_U3P_USB_VALUE_MASK)   >> CY_U3P_USB_VALUE_POS);
    wIndex   = ((setupdat1 & CY_U3P_USB_INDEX_MASK)   >> CY_U3P_USB_INDEX_POS);
    wLength   = ((setupdat1 & CY_U3P_USB_LENGTH_MASK)   >> CY_U3P_USB_LENGTH_POS);

    if (bType == CY_U3P_USB_STANDARD_RQT)
    {
        /* Handle SET_FEATURE(FUNCTION_SUSPEND) and CLEAR_FEATURE(FUNCTION_SUSPEND)
         * requests here. It should be allowed to pass if the device is in configured
         * state and failed otherwise. */
        if ((bTarget == CY_U3P_USB_TARGET_INTF) && ((bRequest == CY_U3P_USB_SC_SET_FEATURE)
                    || (bRequest == CY_U3P_USB_SC_CLEAR_FEATURE)) && (wValue == 0))
        {
            if (glIsApplnActive)
                CyU3PUsbAckSetup ();
            else
                CyU3PUsbStall (0, CyTrue, CyFalse);

            isHandled = CyTrue;
        }
    }

    /* Handle supported vendor requests. */
    if (bType == CY_U3P_USB_VENDOR_RQT)
    {
        isHandled = CyTrue;

        switch (bRequest)
        {
            case CY_FX_RQT_ID_CHECK:
                CyU3PUsbSendEP0Data (8, (uint8_t *)glFirmwareID);
                break;

            /*case CY_FX_RQT_SPI_FLASH_WRITE:
                status = CyU3PUsbGetEP0Data (wLength, glEp0Buffer, NULL);
                if (status == CY_U3P_SUCCESS)
                {
                    status = CyFxSpiTransfer (wIndex, wLength,
                            glEp0Buffer, CyFalse);
                }
                break;*/

            case CY_FX_RQT_SPI_FLASH_READ:
                CyU3PMemSet (glEp0Buffer, 0, sizeof (glEp0Buffer));
                status = readData (glEp0Buffer);
                if (status == CY_U3P_SUCCESS)
                {
                    status = CyU3PUsbSendEP0Data (wLength, glEp0Buffer);
                }
                break;

            /*case CY_FX_RQT_SPI_FLASH_ERASE_POLL:
                status = CyFxSpiEraseSector ((wValue) ? CyTrue : CyFalse,
                        (wIndex & 0xFF), glEp0Buffer);
                if (status == CY_U3P_SUCCESS)
                {
                    if (wValue == 0)
                    {
                        status = CyU3PUsbSendEP0Data (wLength, glEp0Buffer);
                    }
                    else
                    {
                        CyU3PUsbAckSetup ();
                    }
                }
                break;*/

            default:
                /* This is unknown request. */
                isHandled = CyFalse;
                break;
        }

        /* If there was any error, return not handled so that the library will
         * stall the request. Alternatively EP0 can be stalled here and return
         * CyTrue. */
        if (status != CY_U3P_SUCCESS)
        {
            isHandled = CyFalse;
        }
    }

    return isHandled;
}

/* This is the callback function to handle the USB events. */
void
CyFxUSBEventCB (
    CyU3PUsbEventType_t evtype, /* Event type */
    uint16_t            evdata  /* Event data */
    )
{
    switch (evtype)
    {
        case CY_U3P_USB_EVENT_SETCONF:
            glIsApplnActive = CyTrue;
            /* Disable the low power entry to optimize USB throughput */
            CyU3PUsbLPMDisable();
            break;

        case CY_U3P_USB_EVENT_RESET:
        case CY_U3P_USB_EVENT_DISCONNECT:
            glIsApplnActive = CyFalse;
            /* Reset the SPI DMA channels. */
            CyU3PDmaChannelReset (&glSpiTxHandle);
            CyU3PDmaChannelReset (&glSpiRxHandle);
            break;

        default:
            break;
    }
}

/* Callback function to handle LPM requests from the USB 3.0 host. This function is invoked by the API
   whenever a state change from U0 -> U1 or U0 -> U2 happens. If we return CyTrue from this function, the
   FX3 device is retained in the low power state. If we return CyFalse, the FX3 device immediately tries
   to trigger an exit back to U0.

   This application does not have any state in which we should not allow U1/U2 transitions; and therefore
   the function always return CyTrue.
 */
CyBool_t
CyFxApplnLPMRqtCB (
        CyU3PUsbLinkPowerMode link_mode)
{
    return CyTrue;
}

/* Initialize all interfaces for the application. */
CyU3PReturnStatus_t
CyFxUsbSpiInit (
        void)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Initialize the SPI interface for flash of page size 256 bytes. */
    status = CyFxSpiInit (0x100);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Start the USB functionality. */
    status = CyU3PUsbStart();
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* The fast enumeration is the easiest way to setup a USB connection,
     * where all enumeration phase is handled by the library. Only the
     * class / vendor requests need to be handled by the application. */
    CyU3PUsbRegisterSetupCallback(CyFxUSBSetupCB, CyTrue);

    /* Setup the callback to handle the USB events. */
    CyU3PUsbRegisterEventCallback(CyFxUSBEventCB);

    /* Register a callback to handle LPM requests from the USB 3.0 host. */
    CyU3PUsbRegisterLPMRequestCallback(CyFxApplnLPMRqtCB);

    /* Set the USB Enumeration descriptors */

    /* Super speed device descriptor. */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_DEVICE_DESCR, 0, (uint8_t *)CyFxUSB30DeviceDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* High speed device descriptor. */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_HS_DEVICE_DESCR, 0, (uint8_t *)CyFxUSB20DeviceDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* BOS descriptor */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_BOS_DESCR, 0, (uint8_t *)CyFxUSBBOSDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Device qualifier descriptor */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_DEVQUAL_DESCR, 0, (uint8_t *)CyFxUSBDeviceQualDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Super speed configuration descriptor */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_SS_CONFIG_DESCR, 0, (uint8_t *)CyFxUSBSSConfigDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* High speed configuration descriptor */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_HS_CONFIG_DESCR, 0, (uint8_t *)CyFxUSBHSConfigDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Full speed configuration descriptor */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_FS_CONFIG_DESCR, 0, (uint8_t *)CyFxUSBFSConfigDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* String descriptor 0 */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 0, (uint8_t *)CyFxUSBStringLangIDDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* String descriptor 1 */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 1, (uint8_t *)CyFxUSBManufactureDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* String descriptor 2 */
    status = CyU3PUsbSetDesc(CY_U3P_USB_SET_STRING_DESCR, 2, (uint8_t *)CyFxUSBProductDscr);
    if (status != CY_U3P_SUCCESS)
    {
        return status;
    }

    /* Connect the USB Pins with super speed operation enabled. */
    status = CyU3PConnectState(CyTrue, CyTrue);

    return status;
}




/* Write start command */

CyU3PReturnStatus_t startSampling() {   //not used
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	// Register address: 0x3E
	// Start Command: 0x0800
	uint8_t data[5];    //rasx
	data[0] = 0x00;
	data[1] = 0x3E;
	data[2] = 0x00;
	data[3] = 0x08;
	data[4] = 0x00;
	data[5] = 0x00;

	//uint8_t data[] = {0x00, 0x3E,0x00, 0x08, 0x00, 0x00};
	//uint8_t data[] = {0x02, 0x3E, 0x08};
	//uint8_t data[] = {0x08, 0x3E, 0x02};

	CyU3PSpiSetSsnLine (CyFalse);

	status = CyU3PSpiTransmitWords(data, 3);

	//Do we need to reset DMA channels? Check cy3spi.h descriptions ...

	if (status != CY_U3P_SUCCESS) {
		CyU3PDebugPrint (2, "SPI WRITE command failed\r\n");
		 CyU3PSpiSetSsnLine (CyTrue);
	}

	CyU3PSpiSetSsnLine (CyTrue);
	return status;
}








/*
 * Entry function for the application thread. This function performs
 * the initialization of the Debug, SPI and USB modules and then
 * executes in a loop printing out heartbeat messages through the UART.
 */
void
AppThread_Entry (
        uint32_t input)
{
    uint8_t count = 0;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    //uint8_t databuffer[200];

    /* Initialize the debug interface. */
    status = CyFxDebugInit ();
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_error;
    }

    /* Initialize the application. */
    status = CyFxUsbSpiInit ();
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_error;
    }


    CyU3PMemSet (glEp0Buffer, 0, sizeof (glEp0Buffer));
	status = readData (glEp0Buffer);
	if (status == CY_U3P_SUCCESS){
		status = CyU3PUsbSendEP0Data (200, glEp0Buffer);
	}


    for (;;)
    {
        CyU3PDebugPrint (4, "%x: Device initialized. Firmware ID: %x %x %x %x %x %x %x %x\r\n",
                count++, glFirmwareID[3], glFirmwareID[2], glFirmwareID[1], glFirmwareID[0],
                glFirmwareID[7], glFirmwareID[6], glFirmwareID[5], glFirmwareID[4]);
        CyU3PThreadSleep (1000);

    }

handle_error:
    CyU3PDebugPrint (4, "%x: Application failed to initialize. Error code: %d.\r\n", status);
    while (1);
}






/* Application error handler. */
void
CyFxAppErrorHandler (
        CyU3PReturnStatus_t apiRetStatus    /* API return status */
        )
{
    /* Application failed with the error code apiRetStatus */

    /* Add custom debug or recovery actions here */

    /* Loop indefinitely */
    for (;;)
    {
        /* Thread sleep : 100 ms */
        //CyU3PThreadSleep (100);
    }
}




void CyFxGpioIntrCb (
        uint8_t gpioId /* Indicates the pin that triggered the interrupt */
        )
{
    CyBool_t gpioValue = CyFalse;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Get the status of the pin */
    apiRetStatus = CyU3PGpioGetValue (gpioId, &gpioValue);
    if (apiRetStatus == CY_U3P_SUCCESS)
    {
        /* Check status of the pin */
        if (gpioValue == CyTrue)
        {
            /* Set GPIO high event */
            CyU3PEventSet(&glFxGpioAppEvent, CY_FX_GPIOAPP_GPIO_HIGH_EVENT,
                    CYU3P_EVENT_OR);
        }
        else
        {
            /* Set GPIO low Event */
            CyU3PEventSet(&glFxGpioAppEvent, CY_FX_GPIOAPP_GPIO_LOW_EVENT,
                    CYU3P_EVENT_OR);
        }
    }
}


void
CyFxGpioInit (void)
{
    CyU3PGpioClock_t gpioClock;
    CyU3PGpioSimpleConfig_t gpioConfig;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Init the GPIO module */
    gpioClock.fastClkDiv = 2;
    gpioClock.slowClkDiv = 0;
    gpioClock.simpleDiv = CY_U3P_GPIO_SIMPLE_DIV_BY_2;
    gpioClock.clkSrc = CY_U3P_SYS_CLK;
    gpioClock.halfDiv = 0;

    apiRetStatus = CyU3PGpioInit(&gpioClock, CyFxGpioIntrCb);
    if (apiRetStatus != 0)
    {
        /* Error Handling */
        CyU3PDebugPrint (4, "CyU3PGpioInit failed, error code = %d\n", apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus);
    }

    /* Configure GPIO 45 as input with interrupt enabled for both edges */
    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyTrue;
    gpioConfig.driveLowEn = CyFalse;
    gpioConfig.driveHighEn = CyFalse;
    gpioConfig.intrMode = CY_U3P_GPIO_INTR_BOTH_EDGE;
    apiRetStatus = CyU3PGpioSetSimpleConfig(45, &gpioConfig);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        /* Error handling */
        CyU3PDebugPrint (4, "CyU3PGpioSetSimpleConfig failed, error code = %d\n",
                apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus);
    }

    /* Override GPIO 21 as this pin is associated with GPIF Control signal.
     * The IO cannot be selected as GPIO by CyU3PDeviceConfigureIOMatrix call
     * as it is part of the GPIF IOs. Override API call must be made with
     * caution as this will change the functionality of the pin. If the IO
     * line is used as part of GPIF and is connected to some external device,
     * then the line will no longer behave as a GPIF IO.. Here CTL4 line is
     * not used and so it is safe to override.  */
    apiRetStatus = CyU3PDeviceGpioOverride (5, CyTrue);
    if (apiRetStatus != 0)
    {
        /* Error Handling */
        CyU3PDebugPrint (4, "CyU3PDeviceGpioOverride failed, error code = %d\n",
                apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus);
    }

    /* Configure GPIO 21 as output */
    gpioConfig.outValue = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    apiRetStatus = CyU3PGpioSetSimpleConfig(5, &gpioConfig);
    if (apiRetStatus != CY_U3P_SUCCESS)
    {
        /* Error handling */
        CyU3PDebugPrint (4, "CyU3PGpioSetSimpleConfig failed, error code = %d\n",
                apiRetStatus);
        CyFxAppErrorHandler(apiRetStatus);
    }

}







/* Entry function for the gpioOutputThread */
void
GpioOutputThread_Entry (
        uint32_t input)
{
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Initialize GPIO module. */
    CyFxGpioInit ();

    for (;;)
    {

    	/* Set the GPIO 5 to high */
        apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
        if (apiRetStatus != CY_U3P_SUCCESS)
        {
            /* Error handling */
            CyU3PDebugPrint (4, "CyU3PGpioSetValue failed, error code = %d\n",
                    apiRetStatus);
            CyFxAppErrorHandler(apiRetStatus);
        }

        /* Wait for two seconds */
        CyU3PThreadSleep(1000);

        /* Set the GPIO 5 to low */
        apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
        if (apiRetStatus != CY_U3P_SUCCESS)
        {
            /* Error handling */
            CyU3PDebugPrint (4, "CyU3PGpioSetValue failed, error code = %d\n",
                    apiRetStatus);
            CyFxAppErrorHandler(apiRetStatus);
        }

        /* Wait for two seconds */
        CyU3PThreadSleep(1000);
    }
}

/* Entry function for the gpioInputThread */
void
GpioInputThread_Entry (
        uint32_t input)
{
    uint32_t eventFlag;
    CyU3PReturnStatus_t txApiRetStatus = CY_U3P_SUCCESS;

    for (;;)
    {
    	//CyU3PDebugPrint (4, "Here2\r\n");
    	/* Wait for a GPIO event */
        txApiRetStatus = CyU3PEventGet (&glFxGpioAppEvent,
                (CY_FX_GPIOAPP_GPIO_HIGH_EVENT | CY_FX_GPIOAPP_GPIO_LOW_EVENT),
                CYU3P_EVENT_OR_CLEAR, &eventFlag, CYU3P_WAIT_FOREVER);
        //CyU3PDebugPrint (4, "%d\r\n", txApiRetStatus);
        //CyU3PDebugPrint (4, "%d\r\n", CY_U3P_SUCCESS);

        if (txApiRetStatus == CY_U3P_SUCCESS)
        {
        	if (eventFlag & CY_FX_GPIOAPP_GPIO_HIGH_EVENT)
            {
                /* Print the status of the pin */
                CyU3PDebugPrint (4, "GPIO 45 is set to high\r\n");
            }
            else
            {
                /* Print the status of the pin */
                CyU3PDebugPrint (4, "GPIO 45 is set to low\r\n");
            }
        }
    }
}











/* Application define function which creates the application threads. */
void
CyFxApplicationDefine (
        void)
{
    void *ptr = NULL;
    uint32_t retThrdCreate = CY_U3P_SUCCESS;

    /* Allocate the memory for the threads and create threads */
    ptr = CyU3PMemAlloc (APPTHREAD_STACK);
    retThrdCreate = CyU3PThreadCreate (&appThread, /* Thread structure. */
            "21:AppThread",                        /* Thread ID and name. */
            AppThread_Entry,                       /* Thread entry function. */
            0,                                     /* Thread input parameter. */
            ptr,                                   /* Pointer to the allocated thread stack. */
            APPTHREAD_STACK,                       /* Allocated thread stack size. */
            APPTHREAD_PRIORITY,                    /* Thread priority. */
            APPTHREAD_PRIORITY,                    /* Thread pre-emption threshold: No preemption. */
            CYU3P_NO_TIME_SLICE,                   /* No time slice. Thread will run until task is
                                                      completed or until the higher priority
                                                      thread gets active. */
            CYU3P_AUTO_START                       /* Start the thread immediately. */
            );

    /* Check the return code */
    if (retThrdCreate != 0)
    {
        /* Thread creation failed with the error code retThrdCreate */

        /* Add custom recovery or debug actions here */

        /* Application cannot continue. Loop indefinitely */
        while(1);
    }







    /* Allocate the memory for the threads */
	ptr = CyU3PMemAlloc (CY_FX_GPIOAPP_THREAD_STACK);

	/* Create the thread for the application */
	retThrdCreate = CyU3PThreadCreate (&gpioOutputThread,        /* GPIO Example App Thread structure */
						  "21:GPIO_simple_output",               /* Thread ID and Thread name */
						  GpioOutputThread_Entry,                /* GPIO Example App Thread Entry function */
						  0,                                     /* No input parameter to thread */
						  ptr,                                   /* Pointer to the allocated thread stack */
						  CY_FX_GPIOAPP_THREAD_STACK,            /* Thread stack size */
						  CY_FX_GPIOAPP_THREAD_PRIORITY,         /* Thread priority */
						  CY_FX_GPIOAPP_THREAD_PRIORITY,         /* Pre-emption threshold for the thread. */
						  CYU3P_NO_TIME_SLICE,                   /* No time slice for the application thread */
						  CYU3P_AUTO_START                       /* Start the Thread immediately */
						  );

	/* Check the return code */
	if (retThrdCreate != 0)
	{
		/* Thread creation failed with the error code retThrdCreate */

		/* Add custom recovery or debug actions here */

		/* Application cannot continue */
		/* Loop indefinitely */
		while(1);
	}



//	//-------------MAYBE COMMENT THIS PART OUT-------
//
//	/* Allocate the memory for the threads */
//	ptr = CyU3PMemAlloc (CY_FX_GPIOAPP_THREAD_STACK);
//
//	/* Create the thread for the application */
//	retThrdCreate = CyU3PThreadCreate (&gpioInputThread,          /* GPIO Example App Thread structure */
//						  "22:GPIO_simple_input",                 /* Thread ID and Thread name */
//						  GpioInputThread_Entry,                  /* GPIO Example App Thread entry function */
//						  0,                                      /* No input parameter to thread */
//						  ptr,                                    /* Pointer to the allocated thread stack */
//						  CY_FX_GPIOAPP_THREAD_STACK,             /* Thread stack size */
//						  CY_FX_GPIOAPP_THREAD_PRIORITY,          /* Thread priority */
//						  CY_FX_GPIOAPP_THREAD_PRIORITY,          /* Pre-emption threshold for the thread */
//						  CYU3P_NO_TIME_SLICE,                    /* No time slice for the application thread */
//						  CYU3P_AUTO_START                        /* Start the Thread immediately */
//						  );
//
//	/* Check the return code */
//	if (retThrdCreate != 0)
//	{
//		/* Thread creation failed with the error code retThrdCreate */
//
//		/* Add custom recovery or debug actions here */
//
//		/* Application cannot continue */
//		/* Loop indefinitely */
//		while(1);
//	}
//
//	//-------------MAYBE COMMENT THIS PART OUT-------







}

/*
 * Main function
 */
int
main (void)
{
    CyU3PIoMatrixConfig_t io_cfg;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Initialize the device */
    status = CyU3PDeviceInit (NULL);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Initialize the caches. Enable both Instruction and Data Caches. */
    status = CyU3PDeviceCacheControl (CyTrue, CyTrue, CyTrue);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* Configure the IO matrix for the device. On the FX3 DVK board, the COM port 
     * is connected to the IO(53:56). So since we need to use SPI, we will have to
     * either not use UART or use an external UART controller on the IO(46:49). */
    CyU3PMemSet ((uint8_t *)&io_cfg, 0, sizeof(io_cfg));
    io_cfg.isDQ32Bit = CyFalse;
    io_cfg.s0Mode = CY_U3P_SPORT_INACTIVE;
    io_cfg.s1Mode = CY_U3P_SPORT_INACTIVE;
    io_cfg.useUart   = CyTrue;
    io_cfg.useI2C    = CyFalse;
    io_cfg.useI2S    = CyFalse;
    io_cfg.useSpi    = CyTrue;
    io_cfg.lppMode   = CY_U3P_IO_MATRIX_LPP_DEFAULT;
    /* No GPIOs are enabled. */
    io_cfg.gpioSimpleEn[0]  = 0;
    io_cfg.gpioSimpleEn[1]  = (1 << (45 - 32));
    io_cfg.gpioComplexEn[0] = 0;
    io_cfg.gpioComplexEn[1] = 0;
    status = CyU3PDeviceConfigureIOMatrix (&io_cfg);
    if (status != CY_U3P_SUCCESS)
    {
        goto handle_fatal_error;
    }

    /* This is a non returnable call for initializing the RTOS kernel */
    CyU3PKernelEntry ();

    /* Dummy return to make the compiler happy */
    return 0;

handle_fatal_error:

    /* Cannot recover from this error. */
    while (1);
}

/* [ ] */

