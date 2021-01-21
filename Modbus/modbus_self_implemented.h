
typedef unsigned char byte;

struct response {
	uint8_t response_array[255];
	uint8_t response_size;
};


uint16_t ModRTU_CRC(byte buf[], int len);
struct response entry_func_dmamode(uint8_t **RTS_code, uint8_t count);
struct response entry_func_regmode(uint8_t *RTS_code, uint8_t count);

//extern volatile int16_t HoldingRegister[4096];
volatile int16_t HoldingRegister[7422];
//extern volatile uint16_t HoldingRegister_RTS[1000];
//extern volatile uint16_t HoldingRegister_MTC_X[4096]; //can't do one for each because data overflows in cypress fx3...
//extern volatile uint16_t HoldingRegister_MTC_Y[4096];
//extern volatile uint16_t HoldingRegister_MTC_Z[4096];
