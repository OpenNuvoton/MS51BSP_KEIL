extern unsigned char xdata IAPSPDataBuf[127];

void Erase_SPROM(void);
void Erase_Verify_SPROM(unsigned int u16IAPDataSize);
void Program_SPROM(unsigned int u16IAPDataSize);
void Read_Verify_SPROM( unsigned int u16IAPDataSize);
