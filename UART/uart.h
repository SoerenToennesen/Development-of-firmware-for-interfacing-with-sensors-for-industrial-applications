



CyU3PReturnStatus_t CyFxDebugInit (void);







void CyFxUartLpDmaCallback (
        CyU3PDmaChannel   *chHandle, /* Handle to the DMA channel. */
        CyU3PDmaCbType_t  type,      /* Callback type.             */
        CyU3PDmaCBInput_t *input);
void
UartLpAppThread_Entry (
        uint32_t input);
void
CyFxUartLpApplnInit (void);






extern uint32_t  UartDataRdPtr;
extern uint32_t  UartDataWrPtr;
extern uint8_t  *UartDataBuffer;
extern uint32_t  UartDataCount;
//extern UART_RECEIVE_DATA_EVT;
//extern CY_FX_UARTLT_BUF_SIZE;
void
UartLpAppThread_Entry2 (
        uint32_t input);
void
CyFxUartLpApplnInit2 (void);

//void
//CyFxUartLpApplnCallback2 (
//        CyU3PUartEvt_t   evType,
//        CyU3PUartError_t evStatus);










extern uint32_t regValueEn, regValueDs;







