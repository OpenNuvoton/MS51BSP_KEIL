

void Write_DATAFLASH_BYTE(unsigned int u16EPAddr,unsigned char u8EPData);
unsigned char read_APROM_BYTE(unsigned int code *u16_addr);

void Write_DATAFLASH_ARRAY(unsigned int u16_addr,unsigned char *pDat,unsigned int num);
void Read_DATAFLASH_ARRAY(unsigned int u16_addr,unsigned char *pDat,unsigned int num);
unsigned char WriteDataToOnePage(unsigned int u16_addr,const unsigned char *pDat,unsigned char num);