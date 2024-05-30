#ifndef _swGpsPrivate_
#define _swGpsPrivate_

// 添加要在此处预编译的标头
#define  uint8_t unsigned char 
#define uint16_t unsigned short int
#define uint32_t unsigned long

#if 0
uint8_t DateLen = sizeof(int);
#if DateLen == 16
#define uint32_t unsigned long
#else if DateLen == 32
#define uint32_t unsigned int
#endif
#endif

extern uint16_t swTboxVerification(uint8_t *,uint8_t len);
extern uint32_t swNetworklessUnlock(uint32_t PH, uint32_t PL, uint8_t Sort);
extern uint32_t swGpsPermanentCancel(uint32_t PH, uint32_t PL, uint8_t Sort);
extern uint32_t swEmergentUnlock(uint32_t PH, uint32_t PL, uint8_t Sort);
extern uint32_t caculateCodeH(uint32_t code1, uint32_t code2);
extern uint32_t caculateCodeL(uint32_t code1, uint32_t code2);
extern uint8_t FunCharDeal(uint32_t Data, uint8_t Index);

#endif

