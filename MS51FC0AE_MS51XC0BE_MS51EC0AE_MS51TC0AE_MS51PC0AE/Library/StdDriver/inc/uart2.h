#define UART2_TXD   0
#define UART2_RXD   1


extern bit uart2rvflag;
extern unsigned char uart2rvbuffer;

void UART2_Open(unsigned long u32SysClock, unsigned long u32Baudrate);
void UART2_Receive_10byte(void);
unsigned char UART2_Receive_Data();
void UART2_Send_Data(unsigned char c);
void UART2_Interrupt(unsigned char u8UART2INTSel,unsigned char u8UART2INTStatus);