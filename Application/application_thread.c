

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
#include "../ADcmXL3021/adcmxl3021.h"
#include "../Modbus/modbus_self_implemented.h"

#define NULL ((void *)0)

#define SLAVE_ADDRESS 1

#define CY_FX_GPIOAPP_THREAD_STACK       (0x0400)   /* GPIO application thread stack size */
#define CY_FX_GPIOAPP_THREAD_PRIORITY    (8)        /* GPIO application thread priority */

#define CY_FX_UARTLP_THREAD_STACK       (0x0400)  /* UART application thread stack size */
#define CY_FX_UARTLP_THREAD_PRIORITY    (8)       /* UART application thread priority */


CyU3PThread UartLpAppThread;
CyU3PThread UartLpAppThread2;
CyU3PEvent  UartLpAppEvent;                     /* Event flags group used by the application. */

CyU3PThread appThread; //Application thread object.
CyBool_t glIsApplnActive = CyFalse;
CyU3PThread gpioOutputThread;   /* GPIO thread structure */
CyU3PThread gpioInputThread;    /* GPIO thread structure */
CyU3PThread USBUARTAppThread;



/*
 * Entry function for the application thread. This function performs
 * the initialization of the Debug, SPI and USB modules and then
 * executes in a loop printing out heartbeat messages through the UART.
 */
// This is the main function of the program, where the infinite while-loop should be placed
void AppThread_Entry (uint32_t input) {
    //uint8_t count = 0;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Initialize the application. */
    status = CyFxUsbSpiInit ();
    if (status != CY_U3P_SUCCESS) while(1);

    start_sampling:
    //turnOnOrOffADcmXL3021(); //Currently, this runs forever, turning the ADcmXL3021 on and off again.
    //start_sampling_RTS(); //This runs forever but only writes to the holding registers once. If you want to configure it such that it writes continously, you would have to put the data collection into a while loop.
    //start_sampling_MTC(); //This runs once and only writes to the holding registers once. If you want to configure it such that it writes continously, you would have to put invoking data collection and the data collection into a while loop.
    //start_sampling_MFFT(); //This runs once and only writes to the holding registers once. If you want to configure it such that it writes continously, you would have to put invoking data collection and the data collection into a while loop.
    start_sampling_AFFT(); //This runs forever and writes to the holding registers continously.

    for (;;) {
    	CyU3PThreadSleep (5);
    	if (button_click) {
    		for (;;) {
    			CyU3PThreadSleep (5);
    			if (!button_click) {
    				goto start_sampling;
    			}
    		}
    	}
    }

}



/* Application define function which creates the application threads. */
void CyFxApplicationDefine (void) {
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
    if (retThrdCreate != 0) {
        // Thread creation failed with the error code retThrdCreate
        // Add custom recovery or debug actions here
        // Application cannot continue. Loop indefinitely
        while(1);
    }

    // Allocate the memory for the threads
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

	// Check the return code
	if (retThrdCreate != 0)	{
		// Thread creation failed with the error code retThrdCreate
		// Add custom recovery or debug actions here
		// Application cannot continue
		// Loop indefinitely
		while(1);
	}

	/* Allocate the memory for the threads */
	ptr = CyU3PMemAlloc (CY_FX_GPIOAPP_THREAD_STACK);

	/* Create the thread for the application */
	retThrdCreate = CyU3PThreadCreate (&gpioInputThread,          /* GPIO Example App Thread structure */
						  "22:GPIO_simple_input",                 /* Thread ID and Thread name */
						  GpioInputThread_Entry,                  /* GPIO Example App Thread entry function */
						  0,                                      /* No input parameter to thread */
						  ptr,                                    /* Pointer to the allocated thread stack */
						  CY_FX_GPIOAPP_THREAD_STACK,             /* Thread stack size */
						  CY_FX_GPIOAPP_THREAD_PRIORITY,          /* Thread priority */
						  CY_FX_GPIOAPP_THREAD_PRIORITY,          /* Pre-emption threshold for the thread */
						  CYU3P_NO_TIME_SLICE,                    /* No time slice for the application thread */
						  CYU3P_AUTO_START                        /* Start the Thread immediately */
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

	/* Allocate the memory for the threads */
	ptr = CyU3PMemAlloc (CY_FX_UARTLP_THREAD_STACK);

	/* Create the thread for the application */
	retThrdCreate = CyU3PThreadCreate (&UartLpAppThread,           /* UART Example App Thread structure */
						  "21:UART_loopback_DMA_mode",             /* Thread ID and Thread name */
						  UartLpAppThread_Entry,                   /* UART Example App Thread Entry function */
						  0,                                       /* No input parameter to thread */
						  ptr,                                     /* Pointer to the allocated thread stack */
						  CY_FX_UARTLP_THREAD_STACK,               /* UART Example App Thread stack size */
						  CY_FX_UARTLP_THREAD_PRIORITY,            /* UART Example App Thread priority */
						  CY_FX_UARTLP_THREAD_PRIORITY,            /* UART Example App Thread priority */
						  CYU3P_NO_TIME_SLICE,                     /* No time slice for the application thread */
						  CYU3P_AUTO_START                         /* Start the Thread immediately */
						  );

	/* Check the return code */
	if (retThrdCreate != 0)
	{
		/* Thread Creation failed with the error code retThrdCreate */

		/* Add custom recovery or debug actions here */

		/* Application cannot continue */
		/* Loop indefinitely */
		while(1);
	}



//	// THIS THREAD IS USED TO INVOKE UART REGISTER MODE IF THAT IS PREFERRED
//	// (CURRENTLY ONLY WORKS FOR RTU, AS THEY ARE CONSTANTLY SENT AS 8 BYTES).
//	// IN OUR CASE WE USE DMA.
//	/* Create the event flag used for receive data signaling. */
//	retThrdCreate = CyU3PEventCreate (&UartLpAppEvent);
//	if (retThrdCreate != CY_U3P_SUCCESS) while (1);
//
//	/* Allocate the memory for the thread stack. */
//	ptr = CyU3PMemAlloc (CY_FX_UARTLP_THREAD_STACK);
//	if (ptr == 0) while (1);
//
//	/* Create the thread for the application */
//	retThrdCreate = CyU3PThreadCreate (&UartLpAppThread2,                  /* UART Example App Thread structure */
//						  "21:UART_loopback_register_mode",     /* Thread ID and Thread name */
//						  UartLpAppThread_Entry2,                /* UART Example App Thread Entry function */
//						  0,                                    /* No input parameter to thread */
//						  ptr,                                  /* Pointer to the allocated thread stack */
//						  CY_FX_UARTLP_THREAD_STACK,            /* UART Example App Thread stack size */
//						  CY_FX_UARTLP_THREAD_PRIORITY,         /* UART Example App Thread priority */
//						  CY_FX_UARTLP_THREAD_PRIORITY,         /* UART Example App Thread priority */
//						  CYU3P_NO_TIME_SLICE,                  /* No time slice for the application thread */
//						  CYU3P_AUTO_START                      /* Start the Thread immediately */
//						  );
//
//	if (retThrdCreate != CY_U3P_SUCCESS) {
//			while(1);
//	}



}

