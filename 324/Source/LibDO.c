#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibFunMcuLedOutput
** 功能描述:单片机指示灯输出,GPIOF11
** 传入参数:Data=0灯灭,Data>0灯亮
** 返回数据:无
** *************************************************** */
void LibMcuLedOutput(UINT8 Data)
{
	REG_GPIOF_PUR |= (1<<11);
	REG_GPIOF_DDR |= (1<<11);
	REG_GPIOF_PER &= (~(1<<11));
	if(Data>0)
	{
		REG_GPIOF_DR &= ~(1<<11);
	}
	else
	{
		REG_GPIOF_DR |= (1<<11);
	}	
}
/* ******************************************************
** 函数名称:LibFunMcuLedState
** 功能描述:单片机指示灯输出,GPIOF11
** 传入参数:无
** 返回数据:Data=0灯灭,Data>0灯亮
** *************************************************** */
UINT8 LibFunMcuLedState(void)
{
	unsigned int Data=0;
	if( ((REG_GPIOF_DDR&(1<<11))>0) &&
	    ((REG_GPIOF_PER&(1<<11))==0)
	)
	{
		Data = (REG_GPIOF_DR>>11);
		Data = !(Data&0x01);
	}
	return (UINT8)Data;
}
/* ******************************************************
** 函数名称:LibFunGetValueDOL
** 功能描述:读取当前DOL输出设置值
** 传入参数:
** 返回数据:无
** *************************************************** */
UINT8 LibGetValueDOL(UINT8 Channal)
{
	if(Channal<4)
	{
		return LibVarSetValueDOL[Channal];
	}
	else
	{
		return 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSetValueDOL
** 功能描述:设置DOL输出值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT8 LibSetValueDOL(UINT8 Channal,UINT8 Data)
{
	if(Channal>=4)
	{
		return 1;
	}
	LibVarSetValueDOL[Channal] = Data;
	switch(Channal)
	{
		case 0:
			REG_GPIOF_PUR |= (1<<0);
			REG_GPIOF_DDR |= (1<<0);
			REG_GPIOF_PER &= (~(1<<0));
			if(Data==0 && LibVarPinoutsSelect[14]==0){REG_GPIOF_DR |= (1<<0);}else{REG_GPIOF_DR &= ~(1<<0);}
			break;
		case 1:
			REG_GPIOF_PUR |= (1<<1);
			REG_GPIOF_DDR |= (1<<1);
			REG_GPIOF_PER &= (~(1<<1));
			if(Data==0 && LibVarPinoutsSelect[40]==0){REG_GPIOF_DR |= (1<<1);}else{REG_GPIOF_DR &= ~(1<<1);}
			break;
		case 2:
			if(LibVarPinoutsSelect[76]==1)
			{
				REG_GPIOD_PUR |= (1<<2);
				REG_GPIOD_DDR |= (1<<2);
				REG_GPIOD_PER &= (~(1<<2));
				if(Data==0){REG_GPIOD_DR |= (1<<2);}else{REG_GPIOD_DR &= ~(1<<2);}
			}
			break;
		case 3:
			if(LibVarPinoutsSelect[78]==1)
			{
				REG_GPIOD_PUR |= (1<<11);
				REG_GPIOD_DDR |= (1<<11);
				REG_GPIOD_PER &= (~(1<<11));
				if(Data==0){REG_GPIOD_DR |= (1<<11);}else{REG_GPIOD_DR &= ~(1<<11);}
			}
			break;
	}
	return 0;
}	
/* ******************************************************
** 函数名称:LibFunGetValueDOH
** 功能描述:读取当前DOH输出设置值
** 传入参数:
** 返回数据:无
** *************************************************** */
UINT8 LibGetValueDOH(UINT8 Channal)
{
	if(Channal<28)
	{
		return LibVarSetValueDOH[Channal];
	}
	else
	{
		return 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSetValueDOH
** 功能描述:设置DOH输出值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT8 LibSetValueDOH(UINT8 Channal,UINT8 Data)
{
	if(Channal>=28)
	{
		return 1;
	}
	LibVarSetValueDOH[Channal] = Data;
	switch(Channal)
	{
		case 0:
			REG_GPIOA_PUR &= ~(1<<7);
			REG_GPIOA_DDR |= (1<<7);
			REG_GPIOA_PER &= (~(1<<7));
			if(Data>0 && LibVarPinoutsSelect[30]==0){REG_GPIOA_DR |= (1<<7);}else{REG_GPIOA_DR &= ~(1<<7);}
			break;
		case 1:
			REG_GPIOA_PUR &= ~(1<<4);
			REG_GPIOA_DDR |= (1<<4);
			REG_GPIOA_PER &= (~(1<<4));
			if(Data>0 && LibVarPinoutsSelect[31]==0){REG_GPIOA_DR |= (1<<4);}else{REG_GPIOA_DR &= ~(1<<4);}
			break;
		case 2:
			REG_GPIOA_PUR &= ~(1<<2);
			REG_GPIOA_DDR |= (1<<2);
			REG_GPIOA_PER &= ~(1<<2);
			if(Data>0 && LibVarPinoutsSelect[32]==0){REG_GPIOA_DR |= (1<<2);}else{REG_GPIOA_DR &= ~(1<<2);}
			break;
		case 3:
			REG_GPIOA_PUR &= ~(1<<8);
			REG_GPIOA_DDR |= (1<<8);
			REG_GPIOA_PER &= ~(1<<8);
			if(Data>0 && LibVarPinoutsSelect[33]==0){REG_GPIOA_DR |= (1<<8);}else{REG_GPIOA_DR &= ~(1<<8);}
			break;
		case 4:
			REG_GPIOF_PUR &= ~(1<<7);
			REG_GPIOF_DDR |= (1<<7);
			REG_GPIOF_PER &= (~(1<<7));
			if(Data>0 && LibVarPinoutsSelect[34]==0){REG_GPIOF_DR |= (1<<7);}else{REG_GPIOF_DR &= ~(1<<7);}
			break;
		case 5:
			REG_GPIOF_PUR &= ~(1<<5);
			REG_GPIOF_DDR |= (1<<5);
			REG_GPIOF_PER &= (~(1<<5));
			if(Data>0 && LibVarPinoutsSelect[35]==0){REG_GPIOF_DR |= (1<<5);}else{REG_GPIOF_DR &= ~(1<<5);}
			break;
		case 6:
			REG_GPIOE_PUR &= ~(1<<9);
			REG_GPIOE_DDR |= (1<<9);
			REG_GPIOE_PER &= (~(1<<9));
			if(Data>0 && LibVarPinoutsSelect[36]==0){REG_GPIOE_DR |= (1<<9);}else{REG_GPIOE_DR &= ~(1<<9);}
			break;
		case 7:
			REG_GPIOA_PUR &= ~(1<<6);
			REG_GPIOA_DDR |= (1<<6);
			REG_GPIOA_PER &= (~(1<<6));
			if(Data>0 && LibVarPinoutsSelect[41]==0){REG_GPIOA_DR |= (1<<6);}else{REG_GPIOA_DR &= ~(1<<6);}
			break;
		case 8:
			REG_GPIOA_PUR &= ~(1<<5);
			REG_GPIOA_DDR |= (1<<5);
			REG_GPIOA_PER &= (~(1<<5));
			if(Data>0 && LibVarPinoutsSelect[42]==0){REG_GPIOA_DR |= (1<<5);}else{REG_GPIOA_DR &= ~(1<<5);}
			break;
		case 9:
			REG_GPIOA_PUR &= ~(1<<3);
			REG_GPIOA_DDR |= (1<<3);
			REG_GPIOA_PER &= (~(1<<3));
			if(Data>0 && LibVarPinoutsSelect[43]==0){REG_GPIOA_DR |= (1<<3);}else{REG_GPIOA_DR &= ~(1<<3);}
			break;
		case 10:
			#if DefineHardwareNewVersion
				REG_GPIOE_PUR &= ~(1<<12);
				REG_GPIOE_DDR |= (1<<12);
				REG_GPIOE_PER &= (~(1<<12));
				if(Data>0 && LibVarPinoutsSelect[44]==0){REG_GPIOE_DR |= (1<<12);}else{REG_GPIOE_DR &= ~(1<<12);}
			#else
				REG_GPIOC_PUR &= ~(1<<4);
				REG_GPIOC_DDR |= (1<<4);
				REG_GPIOC_PER &= (~(1<<4));
				if(Data>0 && LibVarPinoutsSelect[44]==0){REG_GPIOC_DR |= (1<<4);}else{REG_GPIOC_DR &= ~(1<<4);}
			#endif
			break;
		case 11:
			REG_GPIOF_PUR &= ~(1<<8);
			REG_GPIOF_DDR |= (1<<8);
			REG_GPIOF_PER &= (~(1<<8));
			if(Data>0 && LibVarPinoutsSelect[45]==0){REG_GPIOF_DR |= (1<<8);}else{REG_GPIOF_DR &= ~(1<<8);}
			break;
		case 12:
			REG_GPIOF_PUR &= ~(1<<6);
			REG_GPIOF_DDR |= (1<<6);
			REG_GPIOF_PER &= (~(1<<6));
			if(Data>0 && LibVarPinoutsSelect[46]==0){REG_GPIOF_DR |= (1<<6);}else{REG_GPIOF_DR &= ~(1<<6);}
			break;
		case 13:
			REG_GPIOF_PUR &= ~(1<<4);
			REG_GPIOF_DDR |= (1<<4);
			REG_GPIOF_PER &= (~(1<<4));
			if(Data>0 && LibVarPinoutsSelect[47]==0){REG_GPIOF_DR |= (1<<4);}else{REG_GPIOF_DR &= ~(1<<4);}
			break;
		case 14:
			if(LibVarPinoutsSelect[37]==1)
			{
				if(Data>0){LibSetPwmRatio(0,0xFFFF);}else{LibSetPwmRatio(0,0);}
			}
			break;
		case 15:
			if(LibVarPinoutsSelect[38]==1)
			{
				if(Data>0){LibSetPwmRatio(1,0xFFFF);}else{LibSetPwmRatio(1,0);}
			}
			break;
		case 16:
			if(LibVarPinoutsSelect[39]==1)
			{
				if(Data>0){LibSetPwmRatio(2,0xFFFF);}else{LibSetPwmRatio(2,0);}
			}
			break;
		case 17:
			if(LibVarPinoutsSelect[65]==1)
			{
				if(Data>0){LibSetPwmRatio(3,0xFFFF);}else{LibSetPwmRatio(3,0);}
			}
			break;
		case 18:
			if(LibVarPinoutsSelect[66]==1)
			{
				if(Data>0){LibSetPwmRatio(4,0xFFFF);}else{LibSetPwmRatio(4,0);}
			}
			break;
		case 19:
			if(LibVarPinoutsSelect[67]==1)
			{
				if(Data>0){LibSetPwmRatio(5,0xFFFF);}else{LibSetPwmRatio(5,0);}
			}
			break;
		case 20:
			if(LibVarPinoutsSelect[68]==1)
			{
				if(Data>0){LibSetPwmRatio(6,0xFFFF);}else{LibSetPwmRatio(6,0);}
			}
			break;
		case 21:
			if(LibVarPinoutsSelect[69]==1)
			{
				if(Data>0){LibSetPwmRatio(7,0xFFFF);}else{LibSetPwmRatio(7,0);}
			}
			break;
		case 22:
			if(LibVarPinoutsSelect[70]==1)
			{
				if(Data>0){LibSetPwmRatio(8,0xFFFF);}else{LibSetPwmRatio(8,0);}
			}
			break;
		case 23:
			if(LibVarPinoutsSelect[71]==1)
			{
				if(Data>0){LibSetPwmRatio(9,0xFFFF);}else{LibSetPwmRatio(9,0);}
			}
			break;
		case 24:
			if(LibVarPinoutsSelect[72]==1)
			{
				if(Data>0){LibSetPwmRatio(10,0xFFFF);}else{LibSetPwmRatio(10,0);}
			}
			break;
		case 25:
			if(LibVarPinoutsSelect[79]==1)
			{
				if(Data>0){LibSetPwmRatio(11,0xFFFF);}else{LibSetPwmRatio(11,0);}
			}
			break;
		case 26:
			if(LibVarPinoutsSelect[75]==1)
			{
				REG_GPIOD_PUR |= (1<<4);
				REG_GPIOD_DDR |= (1<<4);
				REG_GPIOD_PER &= (~(1<<4));
				if(Data>0){REG_GPIOD_DR |= (1<<4);}else{REG_GPIOD_DR &= ~(1<<4);}
			}
			break;
		case 27:
			if(LibVarPinoutsSelect[77]==1)
			{
				REG_GPIOD_PUR |= (1<<10);
				REG_GPIOD_DDR |= (1<<10);
				REG_GPIOD_PER &= (~(1<<10));
				if(Data>0){REG_GPIOD_DR |= (1<<10);}else{REG_GPIOD_DR &= ~(1<<10);}
			}
			break;
	}
	return 0;
}		
/* *************************************************************** 
** File End
** ************************************************************ */
