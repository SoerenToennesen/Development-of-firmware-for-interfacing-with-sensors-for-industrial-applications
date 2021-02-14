
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
#include "../Modbus/modbus_self_implemented.h"

#include <math.h>


//uint8_t ready_for_modbus = 0;



CyU3PReturnStatus_t setup_regs() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x06;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x08;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x0C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x1C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x20;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x22;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x24;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x26;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x28;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x2A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x2C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x2E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x30;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x32;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x34;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x36;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x38;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x3A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x3C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x40;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x42;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x44;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x46;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x48;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x4A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x4C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x4E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x52;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x53;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x54;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x55;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x56;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x58;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x5C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x64;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x66;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x68;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x6A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x6C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x6E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x70;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x72;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x74;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x76;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x78;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x7A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x7C;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x7E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);



	return status;

}



// We have to unplug the power to the accelerometer to reset from RTS mode, since we have no stop signal
// Otherwise, when restarting the program on the FX3 chip, it still records data from the beginning (w/o configuration)
CyU3PReturnStatus_t start_sampling_RTS() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	// SELECT RTS MODE ////////////////////////////////////// START

	data[0] = 0x00;
	data[1] = 0x80; //Page ID selector
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.35);

	data[0] = 0x00;
	data[1] = 0x81; //Page ID selector
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.25);

	data[0] = 0x00;
	data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.35);

	data[0] = 0x00;
	data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.35);

	data[0] = 0x03; //RTS selector (11 = 3 in decimal)
	data[1] = 0x9A; //REC_CTRL (9A - 80 = 1A)
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.25);

	data[0] = 0x11;
	data[1] = 0x9B; //REC_CTRL 2nd
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	// SELECT RTS MODE //////////////////////////////////////// END


	// WRITE TO TRIGGER DATA IN RTS MODE //////////////////// START

	CyU3PThreadSleep (150);

	data[0] = 0x00;
	data[1] = 0x80; //Page ID selector
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.45);

	data[0] = 0x03;
	data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (0.4);

	data[0] = 0x01;
	data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	data[0] = 0x00;
	data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (10);

	data[0] = 0x00;
	data[1] = 0x64; //MISC_CTRL read
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0xE4; //MISC_CTRL write (E4 - 80 = 64)
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0xE5; //MISC_CTRL write 2nd
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x00;
	data[1] = 0xBE; //GLOB_CMD (3E + 80 = BE)
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (0.1);

	data[0] = 0x08; //Trigger capture
	data[1] = 0xBF; //GLOB_CMD 2nd
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	// WRITE TO TRIGGER DATA IN RTS MODE ////////////////////// END

	// RECORD DATA IN RTS MODE ////////////////////////////// START
	int i, ii;
	uint8_t  spi_data[200];
	for (;;) {

		// Sending all 200 in the CyU3PSpiTransmitWords/CyU3PSpiReceiveWords function,
		// the execution time is much more immediate (seems to be similar to how the GUI does it)
		for (i = 0; i < 150; i++) { // This should be an infinite while-loop, but this is just for testing purposes so we can get on with the application.
			CyU3PSpiSetSsnLine (CyFalse);
			//status = CyU3PSpiTransmitWords(data_for_sampling, 200);
			status = CyU3PSpiReceiveWords (spi_data, 0xC8); //0xC8 for 200, data should be stored in rxData
			CyU3PSpiSetSsnLine (CyTrue);
			for (ii = 0; ii < 100; ii++) {
				// 0x8000 is offset for signed,
				// 0x0773 is the multiplication factor to get it in mg. 0x03E8 is the division factor to divide it by 1000, as the mg multiplication factor was 1000 too much (as it is a decimal number)
				// Data is stored in mg (gravities)
				HoldingRegister[ii] = (((((spi_data[ii*2] << 8) | (spi_data[ii*2+1])) - 0x8000) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
			}
			CyU3PThreadSleep (12);
		}

		for (i = 0; i < 200; i++) {
			CyU3PThreadSleep (5);
			if (button_click) {
				goto stop_measurements;
			}
		}
	}

	// RECORD DATA IN RTS MODE //////////////////////////////// END

	stop_measurements:

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0xE8; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0xE8; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B; // CHECK IF ITS 0x00 OR 0x11!!!
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (5);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (100);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	// STOP RECORDING //////////////////////////////////////// END

	//previously this led to trigger_recording.

	CyU3PThreadSleep (100);

	// SOFTWARE RESET ////////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x80; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	// SOFTWARE RESET //////////////////////////////////////// END


	return status;
}


CyU3PReturnStatus_t start_sampling_MTC() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	// SELECT MTC MODE ////////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (150);

	// SELECT MTC MODE //////////////////////////////////////// END

	// TRIGGER RECORDING //////////////////////////////////// START

	for (;;) {

		while (trigger_sampling != 1) {
			CyU3PThreadSleep (5);
			if (button_click) {
				goto stop_measurements;
			}
		}

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x1E;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (150);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0xBE;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x08; data[1] = 0xBF;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (100);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x66;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x68;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x8A;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x8B;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x0E;
		uint8_t receive_data[2];
		int i;
		// Buffer the prior points (due to not having enough space for 3*4096 points in the holding registers - this way we only store the middle 2048 points of each 4096 data points)
		for (i = 0; i < 1024; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
		}
		for (i = -1; i < 2047; i++) { // The reason why we do this as a loop (1 by 1) rather than sending 100 datapoints in at once, is because, after trial and error, this way yields the best results.
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 0) {
				HoldingRegister[i] = ((((receive_data[0] << 8) | (receive_data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		HoldingRegister[i] = ((((data[0] << 8) | (data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8; // Do the last holding register, which is retreived from 0x0000.
		// Buffer the after points
		data[0] = 0x00; data[1] = 0x0E;
		for (i = 0; i < 1024; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
		}

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x10;
		// Buffer the prior points
		for (i = 0; i < 1024; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
		}
		for (i = 2047; i < 4095; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 2048) {
				HoldingRegister[i] = ((((receive_data[0] << 8) | (receive_data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		HoldingRegister[i] = ((((data[0] << 8) | (data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8; // Do the last holding register, which is retreived from 0x0000.
		// Buffer the after points
		data[0] = 0x00; data[1] = 0x10;
		for (i = 0; i < 1024; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
		}

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x12;
		// Buffer the prior points
		for (i = 0; i < 1024; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
		}
		for (i = 4095; i < 6143; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 4096) {
				HoldingRegister[i] = ((((receive_data[0] << 8) | (receive_data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8;
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		HoldingRegister[i] = ((((data[0] << 8) | (data[1])) * 0x0773) + (0x03E8 / 2)) / 0x03E8; // Do the last holding register, which is retreived from 0x0000.
		// Buffer the after points
		data[0] = 0x00; data[1] = 0x12;
		for (i = 0; i < 1024; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			status = CyU3PSpiTransmitWords(data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
		}

//		//Testing purposes
//		int i;
//		for (i = 1024; i < 1024+10; i++) {
//			HoldingRegister[i] = 0xE666;
//		}
//		for (i = 3072; i < 3072+10; i++) {
//			HoldingRegister[i] = 0x0000;
//		}
//		for (i = 5144; i < 5144+10; i++) {
//			HoldingRegister[i] = 0x199A;
//		}

		trigger_sampling = 2;


		//CyU3PThreadSleep (1000);



	}

	// TRIGGER RECORDING ////////////////////////////////////// END

	stop_measurements:

	CyU3PThreadSleep (100);

	// SOFTWARE RESET ////////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x80; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	// SOFTWARE RESET //////////////////////////////////////// END

	return status;
}


CyU3PReturnStatus_t start_sampling_MFFT() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	CyU3PThreadSleep (100);

	// SELECT MFFT MODE ///////////////////////////////////// START
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

	data[0] = 0x00; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

	//setup_regs();

	// WRITE TO TRIGGER DATA CAPTURE IN MFFT MODE /////////// START

	CyU3PThreadSleep (100);

	for (;;) {
		while (trigger_sampling != 1) {
			CyU3PThreadSleep (5);
			if (button_click) {
				goto stop_measurements;
			}
		}

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.25);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.30);

		data[0] = 0x00; data[1] = 0x1E;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (12);

		//CyU3PThreadSleep (1333);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

		data[0] = 0x00; data[1] = 0xBE;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

		data[0] = 0x08; data[1] = 0xBF;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (3000); //We need a large wait time here, because we just started recording with the previous command

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.35);

		data[0] = 0x00; data[1] = 0x3A;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (12);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.42);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.40);

		data[0] = 0x00; data[1] = 0x66;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (12);//CyU3PThreadSleep (0.75);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.50);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.40);

		data[0] = 0x00; data[1] = 0x68;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.035);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (12);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.42);

		data[0] = 0x00; data[1] = 0x8A;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);//CyU3PThreadSleep (0.55);

		data[0] = 0x00; data[1] = 0x8B;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1000);

		//CyU3PThreadSleep (12);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (22);

		data[0] = 0x00; data[1] = 0x0E;
		uint8_t receive_data[2];
		float temp_data;
		int i;
		for (i = -1; i < 2047; i++) { // The reason why we do this as a loop (1 by 1) rather than sending 100 datapoints in at once, is because, after trial and error, this way yields the best results.
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 0) { //-1 to 2047 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
				temp_data = ((powf(2, ((float)((receive_data[0] << 8) | (receive_data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535; // This calculation can be found on page 18 on the datasheet, along with table 20 on page 23.
				HoldingRegister[i] = temp_data;
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		temp_data = ((powf(2, ((float)((data[0] << 8) | (data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
		HoldingRegister[i] = temp_data; // i is 2047 here (not 2046 as you might assume)

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x10;
		for (i = 2047; i < 4095; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 2048) {
				temp_data = ((powf(2, ((float)((receive_data[0] << 8) | (receive_data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
				HoldingRegister[i] = temp_data;
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		temp_data = ((powf(2, ((float)((data[0] << 8) | (data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
		HoldingRegister[i] = temp_data;

		CyU3PThreadSleep (200);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (20);

		data[0] = 0x00; data[1] = 0x12;
		for (i = 4095; i < 6143; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 4096) {
				temp_data = ((powf(2, ((float)((receive_data[0] << 8) | (receive_data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
				HoldingRegister[i] = temp_data;
				if (i < 5332) { // This is storing as many possible freq Hz values corresponding to the bin number, which is identical for each axis, so we only do it for the last
					HoldingRegister[i+2048] = round((float) ((i-4096) * 13.42773));
				}
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		temp_data = ((powf(2, ((float)((data[0] << 8) | (data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
		HoldingRegister[i] = temp_data;
//		HoldingRegister[i+2048] = round((float) (i * 13.42773)); // we cant have this as it wants to write to data outside the holding register range

//		for (i = 0; i < 250; i++) {
//			CyU3PThreadSleep (5);
//			if (button_click) {
//				for (;;) {
//					CyU3PThreadSleep (5);
//					if (!button_click) {
//						goto stop_measurements;
//					}
//				}
//			}
//		}

		trigger_sampling = 2;

		//CyU3PThreadSleep (1333);
	}

	// WRITE TO TRIGGER DATA CAPTURE IN MFFT MODE ///////////// END

	stop_measurements:

	CyU3PThreadSleep (100);

	// SOFTWARE RESET ////////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x80; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	// SOFTWARE RESET //////////////////////////////////////// END

	return status;
}


CyU3PReturnStatus_t start_sampling_AFFT() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	CyU3PThreadSleep (12);

	// SELECT AFFT MODE ///////////////////////////////////// START
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	// SELECT AFFT MODE /////////////////////////////////////// END

	CyU3PThreadSleep (500);

	setup_regs();

	CyU3PThreadSleep (500);

	// CHANGE FFT REGISTERS AND PROD REGISTERS ////////////// START

	// Write 0x02 to AVG_CNT (time average to 2^2)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0xBA;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBB;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (500);

	// Read 0x02 from AVG_CNT (not needed - for testing purposes)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x3A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (500);

	// Write 102 to FFT_AVG1 (configures SR0 FFT averaging to 2, and leaves SR1 rate at default)
	// Along with 0x02 in AVG_CNT, this sets the device for a capture duration of 1.8 seconds
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x86;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x87;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (500);

	// Read what was just written (again, not needed, just for testing purposes)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x06;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (500);

	// Write 2 to REC_PRD (configures device for automatic repeat time of 2 seconds)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9F;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (500);

	// Read what was just written (again, not needed - just for testing purposes)
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (500);

	// CHANGE FFT REGISTERS AND PROD REGISTERS //////////////// END

	// TRIGGER RECORDING AFFT /////////////////////////////// START

	//trigger_recording:
	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x06;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x08;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x3A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (10);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1E;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (12);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	//CyU3PThreadSleep (1);

	data[0] = 0x08; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (2500);

	//Start reading automatically in a loop
	for (;;) {

//		while (trigger_sampling != 1) {
//			CyU3PThreadSleep (5);
//			if (button_click) {
//				goto stop_measurements;
//			}
//		}



		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x3A;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (3);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x66;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x81;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x68;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (4);

		data[0] = 0x00; data[1] = 0x80; // Page ID selector
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x8A; // Points to start at buffer 0
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x8B; // Points to start at buffer 0
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		data[0] = 0x00; data[1] = 0x80; // Page ID selector
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		//CyU3PThreadSleep (1);

		// Every time we print 0x0E, 0x10, 0x12, the BUF_PNTR automatically advances from 0-2047 (as there are so many stored in each buffer). FFT data is unsigned 16-bit.

		data[0] = 0x00; data[1] = 0x0E;
		uint8_t receive_data[2];
		float temp_data;
		int i;
		for (i = -1; i < 2047; i++) { // The reason why we do this as a loop (1 by 1) rather than sending 100 datapoints in at once, is because, after trial and error, this way yields the best results.
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 0) { //-1 to 2047 and this check ensures we put the MISO data into the correct holding register (which is data from the previous MOSI data)
				temp_data = ((powf(2, ((float)((receive_data[0] << 8) | (receive_data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535; // This calculation can be found on page 18 on the datasheet, along with table 20 on page 23.
				HoldingRegister[i] = temp_data;
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		temp_data = ((powf(2, ((float)((data[0] << 8) | (data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
		HoldingRegister[i] = temp_data; // i is 2047 here (not 2046 as you might assume)

		CyU3PThreadSleep (150);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (15);

		data[0] = 0x00; data[1] = 0x10;
		for (i = 2047; i < 4095; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 2048) {
				temp_data = ((powf(2, ((float)((receive_data[0] << 8) | (receive_data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
				HoldingRegister[i] = temp_data;
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		temp_data = ((powf(2, ((float)((data[0] << 8) | (data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
		HoldingRegister[i] = temp_data;

		CyU3PThreadSleep (150);

		data[0] = 0x00; data[1] = 0x80;
		CyU3PSpiSetSsnLine (CyFalse);
		status = CyU3PSpiTransmitWords(data, 2);
		CyU3PSpiSetSsnLine (CyTrue);

		CyU3PThreadSleep (15);

		data[0] = 0x00; data[1] = 0x12;
		for (i = 4095; i < 6143; i++) {
			CyU3PSpiSetSsnLine (CyFalse);
			CyU3PSpiTransferWords (data, 2, receive_data, 2);
			CyU3PSpiSetSsnLine (CyTrue);
			if (i >= 4096) {
				temp_data = ((powf(2, ((float)((receive_data[0] << 8) | (receive_data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
				HoldingRegister[i] = temp_data;
				if (i < 5332) { // This is storing as many possible freq Hz values corresponding to the bin number, which is identical for each axis, so we only do it for the last
					HoldingRegister[i+2048] = round((float) ((i-4096) * 13.42773));
				}
			}
		}
		data[0] = 0x00; data[1] = 0x00;
		CyU3PSpiSetSsnLine (CyFalse);
		CyU3PSpiReceiveWords (data, 2);
		CyU3PSpiSetSsnLine (CyTrue);
		temp_data = ((powf(2, ((float)((data[0] << 8) | (data[1]))) / 2048)) / (13.42773 * (i + 1))) * 0.9535;
		HoldingRegister[i] = temp_data;

		//ready_for_modbus = 1;
		for (i = 0; i < 300; i++) {
			CyU3PThreadSleep (5);
			if (button_click) {
				goto stop_measurements;
			}
		}
		//ready_for_modbus = 0;

		//trigger_sampling = 2;

		//CyU3PThreadSleep (1333); // set this timer depending on how often you want it to run
	}

	// TRIGGER RECORDING AFFT ///////////////////////////////// END

	// STOP RECORDING /////////////////////////////////////// START

	stop_measurements:

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0xE8; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0xE8; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B; // CHECK IF ITS 0x00 OR 0x11!!!
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (5);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (100);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x01; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	// STOP RECORDING //////////////////////////////////////// END

	//previously this led to trigger_recording.

	CyU3PThreadSleep (100);

	// SOFTWARE RESET ////////////////////////////////////// START

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x80; data[1] = 0xBE;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0xBF;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	// SOFTWARE RESET //////////////////////////////////////// END

	return status;
}


CyU3PReturnStatus_t turnOnOrOffADcmXL3021() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

	uint8_t data1[2], data2[2], data3[2];
	data1[0] = 0x00;
	data1[1] = 0x80;
	data2[0] = 0x02;
	data2[1] = 0xBE;
	data3[0] = 0x00;
	data3[1] = 0xBF;

	//CyU3PSpiSetSsnLine (CyFalse);

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data1, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		return status;
	}

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data2, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		return status;
	}

	CyU3PThreadSleep (20);
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data3, 2);
	CyU3PSpiSetSsnLine (CyTrue);
	if (status != CY_U3P_SUCCESS) {
		return status;
	}

	//CyU3PSpiSetSsnLine (CyTrue);

	return status;
}

CyU3PReturnStatus_t start_ADcmXL3021() {
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	uint8_t data[2];

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (4);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (3);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (2);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (100);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x81;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x1A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x00;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x00; data[1] = 0x80;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x02; data[1] = 0x9A;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (1);

	data[0] = 0x11; data[1] = 0x9B;
	CyU3PSpiSetSsnLine (CyFalse);
	status = CyU3PSpiTransmitWords(data, 2);
	CyU3PSpiSetSsnLine (CyTrue);

	CyU3PThreadSleep (100);

	return status;
}


