#define UART4_TXD   0
#define UART4_RXD   1


extern bit uart4rvflag;
extern unsigned char uart4rvbuffer;

void UART4_Open(unsigned long u32SysClock, unsigned long u32Baudrate);
void UART4_Receive_10byte(void);
unsigned char UART4_Receive_Data();
void UART4_Send_Data(unsigned char c);
void UART4_Interrupt(unsigned char u8UART4INTSel,unsigned char u8UART4INTStatus);