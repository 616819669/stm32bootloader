#ifndef FLASH_H
#define FLASH_H
#include "public.h"
#define USE_IAP 0

#define  SECOND_START     0X3A
#define  START_UPDATE     0X81   //开始升级


//#define RESTART 0xa1
//#define UPDATA  0xa5
//#define START_UPDATA  0xa6
//#define UPDATA_finish  0xa0
//#define APP_FLASH_ADDR    (uint32_t)0x08003000
//#define Usaer_flash_addr 0x0800F800

//cmd
#define SY_PAIR 0x01
#define sys_CMD_STATE  0x30//当前系统状态
#define UPDATA_finish  0xa0
#define RESTART 0xa1
#define UPDATA  0xa5
#define START_UPDATA  0xa6
#define APP_FLASH_ADDR    (uint32_t)0x08003000
#define Usaer_flash_addr 0x0800F800

///*flash addr*/
//#define flash_len 64
//#define  flash_addr_SOFT_state 63//软件初始化
//#define flash_addr_syn480Rid 62//要是id
//#define flash_addr_iap_state 61//升级状态
//#define flash_addr_HARD_ver 60//硬件版本
//#define flash_addr_SOFT_ver 59//软件件版本


//#define flash_CODE_HARD_ver 0x01//硬件版本
//#define flash_CODE_SOFT_ver 0x01//软件件版本

//#define flash_code_startupdata 0xaa5a5a5//启动升级
//#define flash_code_nomallboot 0xaa5a5a0//正常启动

//#define  flash_CODE_SOFT_state_fisrt 0xa865877
/*flash addr*/
#define flash_len 64
#define  flash_addr_SOFT_state 63//软件初始化
#define flash_addr_syn480Rid 62//要是id
#define flash_addr_iap_state 61//升级状态
#define flash_addr_HARD_ver 60//硬件版本
#define flash_addr_SOFT_ver 59//软件件版本
#define flash_addr_Bootloader_ver 58//引导程序软件版本

#define flash_CODE_HARD_ver 0x01//硬件版本
#define flash_CODE_SOFT_ver 0x01//软件件版本
#define flash_CODE_Bootloader_ver 0x01//引导程序软件版本

#define flash_code_startupdata 0xaa5a5a5//启动升级
#define flash_code_nomallboot 0xaa5a5a0//正常启动
#define flash_code_Reboot 0x12323420//重启

#define  flash_CODE_SOFT_state_fisrt 0xa865877
/*flsah*/

extern uint32_t flash_data[flash_len];
void writeflash(uint32_t addr, uint32_t * data,uint32_t len);
void readflash(uint32_t addr, uint32_t * data,uint32_t len);
void writeflash_bytes(uint32_t addr, uint8_t * data,uint32_t len);
#endif
