#include "flash.h"
uint32_t flash_data[flash_len];

void writeflash(uint32_t addr, uint32_t * data,uint32_t len)
{
	uint32_t i=0;
		uint32_t flash_buf[flash_len];
	RCC_HSICmd(ENABLE);	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);
	
	readflash(0, flash_buf,flash_len);
	
	for(i=0;i<len;i++)
	{
		flash_buf[addr]=*data;
		addr++;
		data++;
	}
	len=flash_len;
	addr=0;
	data=flash_buf;
	FLASH_ErasePage(Usaer_flash_addr);
	for(i=0;i<len;i++)
	{
		FLASH_ProgramWord(Usaer_flash_addr+addr,*data);
		data++;
		addr+=4;
	}
	
	FLASH_Lock();
	RCC_HSICmd(DISABLE);
}
void readflash(uint32_t addr, uint32_t * data,uint32_t len)
{
	
uint32_t i=0;
	addr=Usaer_flash_addr;
	for(i=0;i<len;i++)
	{
		*data=*(uint32_t *)addr;
		addr+=4;
		data++;
	}
}
void writeflash_bytes(uint32_t addr, uint8_t * data,uint32_t len)
{
	uint32_t i=0;
	uint16_t buf;
	RCC_HSICmd(ENABLE);	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);
	for(i=0;i<len;i+=2)
	{
//		buf[3]=*data;
//		
//		data++;
//		buf[2]=*data;
//		
//		buf[1]=*data;

//		data++;
//		buf[0]=*data;
//		data++;
		buf=* data;
		data++;
		buf+=((* data)<<8);
		data++;
//		FLASH_ProgramWord(addr,*(uint32_t *)buf);
		FLASH_ProgramHalfWord(addr,buf);
		addr+=2;
	}
	
	FLASH_Lock();
//	RCC_HSICmd(DISABLE);
}

