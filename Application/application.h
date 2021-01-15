


extern CyU3PThread appThread;
extern CyU3PThread gpioOutputThread;
extern CyU3PThread gpioInputThread;
extern CyU3PThread USBUARTAppThread;
extern CyBool_t glIsApplnActive;



extern CyU3PEvent UartLpAppEvent;



void AppThread_Entry (uint32_t input);
void CyFxApplicationDefine (void);
