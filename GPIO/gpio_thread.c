//GPIO thread (LED blinking, perhaps button implementation, etc.)

#include <cyu3gpio.h>
#include "cyu3error.h"
#include "gpio.h"

#include "../SPI/spi.h"
#include "../Application/application.h"
#include "../UART/uart.h"
#include "../ADcmXL3021/adcmxl3021.h"

#define CY_FX_GPIOAPP_GPIO_HIGH_EVENT    (1 << 0)   /* GPIO high event */
#define CY_FX_GPIOAPP_GPIO_LOW_EVENT     (1 << 1)   /* GPIO low event */

volatile uint8_t button_click;
uint8_t mode_select = 1;

/* Entry function for the gpioOutputThread */
void GpioOutputThread_Entry (uint32_t input) {
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    /* Initialize GPIO module. */
    CyFxGpioInit();
    button_click = 0;
    for (;;) {
    	if (mode_select == 1) {
    		/* Set the GPIO 5 to high */
			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			/* Set the GPIO 5 to low */
			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(1000);
    	}
    	if (mode_select == 2) {
			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(1000);
		}
    	if (mode_select == 3) {
    		apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(1000);
		}
    	if (mode_select == 4) {
    		apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyTrue);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(100);

			apiRetStatus = CyU3PGpioSetValue (5, CyFalse);
			if (apiRetStatus != CY_U3P_SUCCESS) while(1);

			CyU3PThreadSleep(1000);
		}
    }
}

/* Entry function for the gpioInputThread */
void GpioInputThread_Entry (uint32_t input) {
    //uint32_t eventFlag;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;
    CyBool_t bool;
    for (;;) {
    	CyU3PThreadSleep(10);
    	apiRetStatus = CyU3PGpioGetValue (45, &bool);
    	if (apiRetStatus != CY_U3P_SUCCESS) while(1);
    	if (bool) {
    		button_click = 0;
    	} else {
    		button_click = 1;
    	}
    }
}
