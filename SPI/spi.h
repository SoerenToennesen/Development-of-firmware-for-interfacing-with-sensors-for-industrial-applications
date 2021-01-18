
#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyu3usb.h"
#include "cyu3i2c.h"
#include "cyu3spi.h"
#include "cyu3uart.h"


extern CyU3PDmaChannel glSpiTxHandle;   /* SPI Tx channel handle */
extern CyU3PDmaChannel glSpiRxHandle;   /* SPI Rx channel handle */
extern CyBool_t glIsApplnActive;
extern uint16_t glSpiPageSize;
extern const uint8_t glFirmwareID[32] __attribute__ ((aligned (32)));
extern uint8_t glEp0Buffer[4096] __attribute__ ((aligned (32)));
extern uint8_t glEp0Buffer2[4096] __attribute__ ((aligned (32)));



CyBool_t CyFxUSBSetupCB (uint32_t setupdat0, uint32_t setupdat1);
void CyFxUSBEventCB (CyU3PUsbEventType_t evtype, uint16_t evdata);
CyBool_t CyFxApplnLPMRqtCB (CyU3PUsbLinkPowerMode link_mode);
CyU3PReturnStatus_t CyFxUsbSpiInit (void);

CyU3PReturnStatus_t CyFxSpiInit (uint16_t pageLen);

