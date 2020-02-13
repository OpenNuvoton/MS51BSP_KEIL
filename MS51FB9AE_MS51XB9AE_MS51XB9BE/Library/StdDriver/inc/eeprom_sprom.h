
extern unsigned char Read_SPROM_BYTE(unsigned char code *u8_addr);
void Write_SPROM_DATAFLASH_ARRAY(unsigned int u16_addr, unsigned char *pDat, unsigned int num);
void Read_SPROM_DATAFLASH_ARRAY(unsigned int u16_addr, unsigned char *pDat, unsigned int num);
unsigned char WriteDataToSPOnePage(unsigned int u16_addr, const unsigned char *pDat, unsigned char num);
