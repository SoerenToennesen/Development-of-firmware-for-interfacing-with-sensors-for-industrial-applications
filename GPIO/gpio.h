


extern CyU3PEvent glFxGpioAppEvent;

void CyFxGpioIntrCb (uint8_t gpioId);
void CyFxGpioInit (void);

void GpioOutputThread_Entry (uint32_t input);
void GpioInputThread_Entry (uint32_t input);


extern volatile uint8_t button_click;
