

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

#define NULL ((void *)0)

#define CY_FX_GPIOAPP_THREAD_STACK       (0x0400)   /* GPIO application thread stack size */
#define CY_FX_GPIOAPP_THREAD_PRIORITY    (8)        /* GPIO application thread priority */

CyU3PThread appThread; //Application thread object.
//CyBool_t glIsApplnActive = CyFalse;
CyU3PThread gpioOutputThread;   /* GPIO thread structure */
CyU3PThread gpioInputThread;    /* GPIO thread structure */



/*
 * Entry function for the application thread. This function performs
 * the initialization of the Debug, SPI and USB modules and then
 * executes in a loop printing out heartbeat messages through the UART.
 */
// This is the main function of the program, where the infinite while-loop should be placed
void AppThread_Entry (uint32_t input) {
    uint8_t count = 0;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    /* Initialize the debug interface. */
    status = CyFxDebugInit ();
    if (status != CY_U3P_SUCCESS) {
    	CyU3PDebugPrint (4, "%x: Application failed to initialize. Error code: %d.\r\n", status);
		while(1);
    }

    /* Initialize the application. */
    status = CyFxUsbSpiInit ();
    if (status != CY_U3P_SUCCESS) {
    	CyU3PDebugPrint (4, "%x: Application failed to initialize. Error code: %d.\r\n", status);
    	while(1);
    }

    turnOnOrOffADcmXL3021();
    //start_sampling_MTC();
    //start_sampling_RTS();

    CyU3PThreadSleep (3000);
    turnOnOrOffADcmXL3021();

    CyU3PDebugPrint (4, "%x: Device initialized. Firmware ID: %x %x %x %x %x %x %x %x\r\n",
		count++, glFirmwareID[3], glFirmwareID[2], glFirmwareID[1], glFirmwareID[0],
		glFirmwareID[7], glFirmwareID[6], glFirmwareID[5], glFirmwareID[4]);
	CyU3PThreadSleep (1000);

	uint8_t random_data[6]; uint8_t random_data2[6];
	random_data[0] = 0; random_data[1] = 5; random_data[2] = 9; random_data[3] = 2; random_data[4] = 13; random_data[5] = 11;
	random_data2[0] = 5; random_data2[1] = 4; random_data2[2] = 3; random_data2[3] = 2; random_data2[4] = 1; random_data2[5] = 0;
	size_t n = sizeof(random_data)/sizeof(random_data[0]);
	size_t n2 = sizeof(random_data2)/sizeof(random_data2[0]);
	int k;
	int i;
    for (;;) {
    	if (k % 2 == 0) {
    		for (i = 0; i < n; i++) {
				char toPrint = random_data[i] + '0';
				CyU3PDebugPrint (2, " %x \r\n", toPrint);

			}
    	} else {
    		for (i = 0; i < n2; i++) {
				char toPrint = random_data2[i];
				CyU3PDebugPrint (2, " %x \r\n", toPrint);

			}
    	}

		CyU3PDebugPrint (4, "----------\r\n");

		k++;
		CyU3PThreadSleep (2500);
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

//	//-------------MAYBE COMMENT THIS PART OUT-------
//			//THIS WAS TO ENABLE THE BUTTON, WHEN CLICKING, IT SHOULD TRIGGER AN ACTION
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

