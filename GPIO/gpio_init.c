//GPIO initialization

#include <cyu3gpio.h>
#include "cyu3error.h"

#include "../SPI/spi.h"
#include "../Application/application.h"
#include "../UART/uart.h"

#define CY_FX_GPIOAPP_GPIO_HIGH_EVENT    (1 << 0)   /* GPIO high event */
#define CY_FX_GPIOAPP_GPIO_LOW_EVENT     (1 << 1)   /* GPIO low event */
CyU3PEvent glFxGpioAppEvent;    /* GPIO input event group. */


void CyFxGpioIntrCb (uint8_t gpioId) { /* Indicates the pin that triggered the interrupt */
    CyBool_t gpioValue = CyFalse;
    CyU3PReturnStatus_t apiRetStatus = CY_U3P_SUCCESS;

    /* Get the status of the pin */
    apiRetStatus = CyU3PGpioGetValue (gpioId, &gpioValue);
    if (apiRetStatus == CY_U3P_SUCCESS) {
        /* Check status of the pin */
        if (gpioValue == CyTrue) {
            /* Set GPIO high event */
            CyU3PEventSet(&glFxGpioAppEvent, CY_FX_GPIOAPP_GPIO_HIGH_EVENT, CYU3P_EVENT_OR);
        }
        else {
            /* Set GPIO low Event */
            CyU3PEventSet(&glFxGpioAppEvent, CY_FX_GPIOAPP_GPIO_LOW_EVENT, CYU3P_EVENT_OR);
        }
    }
}


void CyFxGpioInit (void) {
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
    if (apiRetStatus != 0) {
        /* Error Handling */
        CyU3PDebugPrint (4, "CyU3PGpioInit failed, error code = %d\n", apiRetStatus);
        for (;;) {}
    }

    /* Configure GPIO 45 as input with interrupt enabled for both edges */
    gpioConfig.outValue = CyTrue;
    gpioConfig.inputEn = CyTrue;
    gpioConfig.driveLowEn = CyFalse;
    gpioConfig.driveHighEn = CyFalse;
    gpioConfig.intrMode = CY_U3P_GPIO_INTR_BOTH_EDGE;
    apiRetStatus = CyU3PGpioSetSimpleConfig(45, &gpioConfig);
    if (apiRetStatus != CY_U3P_SUCCESS) {
        /* Error handling */
        CyU3PDebugPrint (4, "CyU3PGpioSetSimpleConfig failed, error code = %d\n", apiRetStatus);
        for (;;) {}

    }

    /* Override GPIO 21 as this pin is associated with GPIF Control signal.
     * The IO cannot be selected as GPIO by CyU3PDeviceConfigureIOMatrix call
     * as it is part of the GPIF IOs. Override API call must be made with
     * caution as this will change the functionality of the pin. If the IO
     * line is used as part of GPIF and is connected to some external device,
     * then the line will no longer behave as a GPIF IO.. Here CTL4 line is
     * not used and so it is safe to override.  */
    apiRetStatus = CyU3PDeviceGpioOverride (5, CyTrue);
    if (apiRetStatus != 0) {
        /* Error Handling */
        CyU3PDebugPrint (4, "CyU3PDeviceGpioOverride failed, error code = %d\n", apiRetStatus);
        for (;;) {}
    }

    /* Configure GPIO 21 as output */
    gpioConfig.outValue = CyFalse;
    gpioConfig.driveLowEn = CyTrue;
    gpioConfig.driveHighEn = CyTrue;
    gpioConfig.inputEn = CyFalse;
    gpioConfig.intrMode = CY_U3P_GPIO_NO_INTR;
    apiRetStatus = CyU3PGpioSetSimpleConfig(5, &gpioConfig);
    if (apiRetStatus != CY_U3P_SUCCESS) {
        /* Error handling */
        CyU3PDebugPrint (4, "CyU3PGpioSetSimpleConfig failed, error code = %d\n", apiRetStatus);
        for (;;) {}
    }
}
