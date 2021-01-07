//GPIO thread (LED blinking, perhaps button implementation, etc.)

#include <cyu3gpio.h>
#include "cyu3error.h"
#include "gpio.h"

#include "../SPI/spi.h"
#include "../Application/application.h"
#include "../UART/uart.h"

#define CY_FX_GPIOAPP_GPIO_HIGH_EVENT    (1 << 0)   /* GPIO high event */
#define CY_FX_GPIOAPP_GPIO_LOW_EVENT     (1 << 1)   /* GPIO low event */

//CyU3PThread gpioOutputThread;   /* GPIO thread structure */
//CyU3PThread gpioInputThread;    /* GPIO thread structure */
//CyU3PEvent glFxGpioAppEvent;    /* GPIO input event group. */

/* Entry function for the gpioOutputThread */
void GpioOutputThread_Entry (uint32_t input) {
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    /* Initialize GPIO module. */
    CyFxGpioInit();
    for (;;) {
    	/* Set the GPIO 5 to high */
        apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
        if (apiRetStatus != CY_U3P_SUCCESS) {
            /* Error handling */
            CyU3PDebugPrint (4, "CyU3PGpioSetValue failed, error code = %d\n", apiRetStatus);
            for (;;) {}
        }

        CyU3PThreadSleep(1000);

        /* Set the GPIO 5 to low */
        apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
        if (apiRetStatus != CY_U3P_SUCCESS) {
            /* Error handling */
            CyU3PDebugPrint (4, "CyU3PGpioSetValue failed, error code = %d\n", apiRetStatus);
            for (;;) {}
        }

        CyU3PThreadSleep(1000);
    }
}

/* Entry function for the gpioInputThread */
void GpioInputThread_Entry (uint32_t input) {
    uint32_t eventFlag;
    CyU3PReturnStatus_t txApiRetStatus = CY_U3P_SUCCESS;
    for (;;) {
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
