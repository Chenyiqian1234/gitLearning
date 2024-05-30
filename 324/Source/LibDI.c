#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibFunGetValueDIL
** 功能描述:底层读取DIL数值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT8 LibGetValueDIL(UINT8 Channal)
{	
	switch(Channal)
	{
		case 0:
			if(REG_GPIOB_DR & (1<<6)){return 0;}else{return 1;}
		case 1:
			if(REG_GPIOD_DR & (1<<7)){return 0;}else{return 1;}
		case 2:
			if(REG_GPIOB_DR & (1<<7)){return 0;}else{return 1;}
		case 3:
			if(REG_GPIOD_DR & (1<<6)){return 0;}else{return 1;}
		case 4:
			if(REG_GPIOD_DR & (1<<8)){return 0;}else{return 1;}
		case 5:  // IRQB
			#if DefineHardwareNewVersion
				if(REG_ITCN_ICTL& (1<<3)){return 0;}else{return 1;}	
			#else 
				if(REG_GPIOD_DR & (1<<9)){return 0;}else{return 1;}
			#endif
		case 6:
			if(LibVar74HC165U6011 & (1<<6)){return 0;}else{return 1;}
		case 7:
			if(LibVar74HC165U6011 & (1<<7)){return 0;}else{return 1;}
		case 8:
			if(LibGetAiVoltage(0)>3000){return 1;}else{return 0;}
		case 9:
			if(LibGetAiVoltage(1)>3000){return 1;}else{return 0;}
		case 10:
			if(LibGetAiVoltage(2)>3000){return 1;}else{return 0;}
		case 11:
			if(LibGetAiVoltage(3)>3000){return 1;}else{return 0;}
		case 12:
			if(LibGetAiVoltage(4)>3000){return 1;}else{return 0;}
		case 13:
			if(LibGetAiVoltage(5)>3000){return 1;}else{return 0;}
		case 14:
			if(LibGetAiVoltage(6)>3000){return 1;}else{return 0;}
		case 15:
			if(LibGetAiVoltage(7)>3000){return 1;}else{return 0;}
		case 16:
			if(LibGetAiVoltage(8)>3000){return 1;}else{return 0;}
		case 17:
			if(LibGetAiVoltage(9)>3000){return 1;}else{return 0;}
		case 18:
			if(LibGetAiVoltage(10)>3000){return 1;}else{return 0;}
		case 19:
			if(LibGetAiVoltage(11)>3000){return 1;}else{return 0;}
		case 20:
			if(LibGetAiVoltage(12)>3000){return 1;}else{return 0;}
		case 21:
			if(LibGetAiVoltage(13)>3000){return 1;}else{return 0;}
	}
	return 1;
}
/* ******************************************************
** 函数名称:LibFunGetValueDIH
** 功能描述:底层读取DIH数值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT8 LibGetValueDIH(UINT8 Channal)
{
	switch(Channal)
	{
		case 0:
			if(REG_GPIOB_DR & (1<<0)){return 0;}else{return 1;}
		case 1:
			if(REG_GPIOF_DR & (1<<2)){return 0;}else{return 1;}
		case 2:
			if(REG_ITCN_ICTL& (1<<2)){return 0;}else{return 1;}  //IRQA
		case 3:
			if(REG_GPIOB_DR & (1<<1)){return 0;}else{return 1;}
		case 4:
			if(REG_GPIOF_DR & (1<<3)){return 0;}else{return 1;}
		case 5:
			#if DefineHardwareNewVersion
				if(REG_GPIOD_DR & (1<<9)){return 0;}else{return 1;}
			#else
				if(REG_ITCN_ICTL& (1<<3)){return 0;}else{return 1;} //IRQB
			#endif
		case 6:
			if(LibVar74HC165U6011 & (1<<1)){return 1;}else{return 0;}
		case 7:
			if(LibVar74HC165U6011 & (1<<4)){return 1;}else{return 0;}
		case 8:
			if(LibVar74HC165U6011 & (1<<2)){return 1;}else{return 0;}
		case 9:
			if(LibVar74HC165U6004 & (1<<5)){return 1;}else{return 0;}
		case 10:
			if(LibVar74HC165U6004 & (1<<1)){return 1;}else{return 0;}
		case 11:
			if(LibVar74HC165U6004 & (1<<7)){return 1;}else{return 0;}
		case 12:
			if(LibVar74HC165U6004 & (1<<3)){return 1;}else{return 0;}
		case 13:
			if(LibVar74HC165U6011 & (1<<0)){return 1;}else{return 0;}
		case 14:
			if(LibVar74HC165U6011 & (1<<5)){return 1;}else{return 0;}
		case 15:
			if(LibVar74HC165U6011 & (1<<3)){return 1;}else{return 0;}
		case 16:
			if(LibVar74HC165U6004 & (1<<4)){return 1;}else{return 0;}
		case 17:
			if(LibVar74HC165U6004 & (1<<0)){return 1;}else{return 0;}
		case 18:
			if(LibVar74HC165U6004 & (1<<6)){return 1;}else{return 0;}
		case 19:
			if(LibVar74HC165U6004 & (1<<2)){return 1;}else{return 0;}
		case 20:
			if(REG_GPIOB_DR & (1<<3)){return 0;}else{return 1;}
		case 21:
			if(REG_GPIOB_DR & (1<<5)){return 0;}else{return 1;}
		case 22:
			if(REG_GPIOB_DR & (1<<4)){return 0;}else{return 1;}
		case 23:
			if(REG_GPIOB_DR & (1<<2)){return 0;}else{return 1;}	
		case 24:
			if(LibGetAiVoltage(0)>4500){return 1;}else{return 0;}
		case 25:
			if(LibGetAiVoltage(1)>4500){return 1;}else{return 0;}
		case 26:
			if(LibGetAiVoltage(2)>4500){return 1;}else{return 0;}
		case 27:
			if(LibGetAiVoltage(3)>4500){return 1;}else{return 0;}
		case 28:
			if(LibGetAiVoltage(4)>4500){return 1;}else{return 0;}
		case 29:
			if(LibGetAiVoltage(5)>4500){return 1;}else{return 0;}
		case 30:
			if(LibGetAiVoltage(6)>4500){return 1;}else{return 0;}
		case 31:
			if(LibGetAiVoltage(7)>4500){return 1;}else{return 0;}
		case 32:
			if(LibGetAiVoltage(8)>4500){return 1;}else{return 0;}
		case 33:
			if(LibGetAiVoltage(9)>4500){return 1;}else{return 0;}
		case 34:
			if(LibGetAiVoltage(10)>4500){return 1;}else{return 0;}
		case 35:
			if(LibGetAiVoltage(11)>4500){return 1;}else{return 0;}
		case 36:
			if(LibGetAiVoltage(12)>4500){return 1;}else{return 0;}
		case 37:
			if(LibGetAiVoltage(13)>4500){return 1;}else{return 0;}
	}
	return 1;
}
/* *************************************************************** 
** File End
** ************************************************************ */
