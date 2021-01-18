
typedef unsigned char byte;

struct response {
	uint8_t response_array[255];
	uint8_t response_size;
};


uint16_t ModRTU_CRC(byte buf[], int len);
struct response entry_func_dmamode(uint8_t **RTS_code, uint8_t count);
struct response entry_func_regmode(uint8_t *RTS_code, uint8_t count);

extern volatile int16_t HoldingRegister[4096];
//extern volatile uint16_t HoldingRegister_RTS[1000];
//extern volatile uint16_t HoldingRegister_MTC_X[4096]; //can't do one for each because data overflows in cypress fx3...
//extern volatile uint16_t HoldingRegister_MTC_Y[4096];
//extern volatile uint16_t HoldingRegister_MTC_Z[4096];



//HoldingRegister[0] = 0x0001;
//HoldingRegister[1] = 0x0002;
//HoldingRegister[2] = 0x000A;
//HoldingRegister[3] = 0x0006;
//HoldingRegister[4] = 0x0005;
//HoldingRegister[5] = 0x0003;
//HoldingRegister[6] = 0x0001;
//HoldingRegister[7] = 0x0009;
//HoldingRegister[8] = 0x15BF;
//HoldingRegister[9] = 0x0E5B;
//HoldingRegister[10] = 0x0123;
//HoldingRegister[11] = 0x0002;
//HoldingRegister[12] = 0x000A;
//HoldingRegister[13] = 0x0006;
//HoldingRegister[14] = 0x0005;
//HoldingRegister[15] = 0x0003;
//HoldingRegister[16] = 0x0001;
//HoldingRegister[17] = 0x0009;
//HoldingRegister[18] = 0x15BF;
//HoldingRegister[19] = 0x0E5B;
//HoldingRegister[20] = 0x0002;
//HoldingRegister[21] = 0x0002;
//HoldingRegister[22] = 0x000A;
//HoldingRegister[23] = 0x0006;
//HoldingRegister[24] = 0x0005;
//HoldingRegister[25] = 0x0003;
//HoldingRegister[26] = 0x0001;
//HoldingRegister[27] = 0x0009;
//HoldingRegister[28] = 0x15BF;
//HoldingRegister[29] = 0x0E5B;
//HoldingRegister[598] = 0x0001;
//HoldingRegister[599] = 0x0023;
//HoldingRegister[600] = 0x00A3;
//HoldingRegister[601] = 0x15BF;
//HoldingRegister[602] = 0x0327;
//HoldingRegister[603] = 0x000A;
//HoldingRegister[604] = 0x100A;
