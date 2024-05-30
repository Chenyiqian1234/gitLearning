#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibFunPower5vEnable
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibSystem5vOutput(unsigned char Command)
{
	REG_GPIOF_PUR |= (1<<14);
	REG_GPIOF_DDR |= (1<<14);
	REG_GPIOF_PER &= ~(1<<14);
	if(Command>0)
	{
		REG_GPIOF_DR  &= ~(1<<14);
	}
	else
	{
		REG_GPIOF_DR  |= (1<<14);
	}
}
/* ******************************************************
** 函数名称:LibFunPinoutsRead
** 功能描述:读取当前复用管脚工作模式
** 传入参数: 
** 返回数据: 
** *************************************************** */
unsigned char LibPinoutsRead(unsigned char Pinouts)
{
	if(Pinouts>0 && Pinouts<=80)
	{
		return LibVarPinoutsSelect[Pinouts-1];
	}
	else
	{
		return 0;
	}
}
/* ******************************************************
** 函数名称:LibFunPinoutsSelect
** 功能描述:用户设置复用管脚工作模式
** 传入参数:  Pinouts:   1~80 代表控制器连接器1~80号管脚
**            Function:  功能序号
** 返回数据: 错误代码=0无错误 =1管脚序号错误 =2赋值超出范围错误
** *************************************************** */
unsigned char LibPinoutsSelect(unsigned char Pinouts,unsigned char Function)
{
	unsigned char ErrCode=0;
	
	if(Pinouts>=1 && Pinouts<=80)
	{
		switch(Pinouts)
		{
			case 1: if(Function<=0){LibSystemPinoutsDriverPin1(Function);}else{ErrCode=2;}break;
			case 2: if(Function<=0){LibSystemPinoutsDriverPin2(Function);}else{ErrCode=2;}break;
			case 3: if(Function<=0){LibSystemPinoutsDriverPin3(Function);}else{ErrCode=2;}break;
			case 4: if(Function<=5){LibSystemPinoutsDriverPin4(Function);}else{ErrCode=2;}break;
			case 5: if(Function<=5){LibSystemPinoutsDriverPin5(Function);}else{ErrCode=2;}break;
			case 6: if(Function<=5){LibSystemPinoutsDriverPin6(Function);}else{ErrCode=2;}break;
			case 7: if(Function<=5){LibSystemPinoutsDriverPin7(Function);}else{ErrCode=2;}break;
			case 8: if(Function<=5){LibSystemPinoutsDriverPin8(Function);}else{ErrCode=2;}break;
			case 9: if(Function<=5){LibSystemPinoutsDriverPin9(Function);}else{ErrCode=2;}break;
			case 10:if(Function<=5){LibSystemPinoutsDriverPin10(Function);}else{ErrCode=2;}break;
			case 11:if(Function<=5){LibSystemPinoutsDriverPin11(Function);}else{ErrCode=2;}break;
			case 12:if(Function<=0){LibSystemPinoutsDriverPin12(Function);}else{ErrCode=2;}break;
			case 13:if(Function<=0){LibSystemPinoutsDriverPin13(Function);}else{ErrCode=2;}break;
			case 14:if(Function<=0){LibSystemPinoutsDriverPin14(Function);}else{ErrCode=2;}break;
			case 15:if(Function<=1){LibSystemPinoutsDriverPin15(Function);}else{ErrCode=2;}break;
			case 16:if(Function<=5){LibSystemPinoutsDriverPin16(Function);}else{ErrCode=2;}break;
			case 17:if(Function<=5){LibSystemPinoutsDriverPin17(Function);}else{ErrCode=2;}break;
			case 18:if(Function<=0){LibSystemPinoutsDriverPin18(Function);}else{ErrCode=2;}break;
			case 19:if(Function<=5){LibSystemPinoutsDriverPin19(Function);}else{ErrCode=2;}break;
			case 20:if(Function<=5){LibSystemPinoutsDriverPin20(Function);}else{ErrCode=2;}break;
			case 21:if(Function<=5){LibSystemPinoutsDriverPin21(Function);}else{ErrCode=2;}break;
			case 22:if(Function<=0){LibSystemPinoutsDriverPin22(Function);}else{ErrCode=2;}break;
			case 23:if(Function<=5){LibSystemPinoutsDriverPin23(Function);}else{ErrCode=2;}break;
			case 24:if(Function<=0){LibSystemPinoutsDriverPin24(Function);}else{ErrCode=2;}break;
			case 25:if(Function<=0){LibSystemPinoutsDriverPin25(Function);}else{ErrCode=2;}break;
			case 26:if(Function<=0){LibSystemPinoutsDriverPin26(Function);}else{ErrCode=2;}break;
			case 27:if(Function<=0){LibSystemPinoutsDriverPin27(Function);}else{ErrCode=2;}break;
			case 28:if(Function<=0){LibSystemPinoutsDriverPin28(Function);}else{ErrCode=2;}break;
			case 29:if(Function<=0){LibSystemPinoutsDriverPin29(Function);}else{ErrCode=2;}break;
			case 30:if(Function<=0){LibSystemPinoutsDriverPin30(Function);}else{ErrCode=2;}break;
			case 31:if(Function<=1){LibSystemPinoutsDriverPin31(Function);}else{ErrCode=2;}break;
			case 32:if(Function<=1){LibSystemPinoutsDriverPin32(Function);}else{ErrCode=2;}break;
			case 33:if(Function<=1){LibSystemPinoutsDriverPin33(Function);}else{ErrCode=2;}break;
			case 34:if(Function<=1){LibSystemPinoutsDriverPin34(Function);}else{ErrCode=2;}break;
			case 35:if(Function<=1){LibSystemPinoutsDriverPin35(Function);}else{ErrCode=2;}break;
			case 36:if(Function<=1){LibSystemPinoutsDriverPin36(Function);}else{ErrCode=2;}break;
			case 37:if(Function<=1){LibSystemPinoutsDriverPin37(Function);}else{ErrCode=2;}break;
			case 38:if(Function<=1){LibSystemPinoutsDriverPin38(Function);}else{ErrCode=2;}break;
			case 39:if(Function<=1){LibSystemPinoutsDriverPin39(Function);}else{ErrCode=2;}break;
			case 40:if(Function<=1){LibSystemPinoutsDriverPin40(Function);}else{ErrCode=2;}break;
			case 41:if(Function<=1){LibSystemPinoutsDriverPin41(Function);}else{ErrCode=2;}break;
			case 42:if(Function<=1){LibSystemPinoutsDriverPin42(Function);}else{ErrCode=2;}break;
			case 43:if(Function<=1){LibSystemPinoutsDriverPin43(Function);}else{ErrCode=2;}break;
			case 44:if(Function<=1){LibSystemPinoutsDriverPin44(Function);}else{ErrCode=2;}break;
			case 45:if(Function<=1){LibSystemPinoutsDriverPin45(Function);}else{ErrCode=2;}break;
			case 46:if(Function<=1){LibSystemPinoutsDriverPin46(Function);}else{ErrCode=2;}break;
			case 47:if(Function<=1){LibSystemPinoutsDriverPin47(Function);}else{ErrCode=2;}break;
			case 48:if(Function<=1){LibSystemPinoutsDriverPin48(Function);}else{ErrCode=2;}break;
			case 49:if(Function<=0){LibSystemPinoutsDriverPin49(Function);}else{ErrCode=2;}break;
			case 50:if(Function<=0){LibSystemPinoutsDriverPin50(Function);}else{ErrCode=2;}break;
			case 51:if(Function<=0){LibSystemPinoutsDriverPin51(Function);}else{ErrCode=2;}break;
			case 52:if(Function<=0){LibSystemPinoutsDriverPin52(Function);}else{ErrCode=2;}break;
			case 53:if(Function<=0){LibSystemPinoutsDriverPin53(Function);}else{ErrCode=2;}break;
			case 54:if(Function<=0){LibSystemPinoutsDriverPin54(Function);}else{ErrCode=2;}break;
			case 55:if(Function<=0){LibSystemPinoutsDriverPin55(Function);}else{ErrCode=2;}break;
			case 56:if(Function<=0){LibSystemPinoutsDriverPin56(Function);}else{ErrCode=2;}break;
			case 57:if(Function<=0){LibSystemPinoutsDriverPin57(Function);}else{ErrCode=2;}break;
			case 58:if(Function<=2){LibSystemPinoutsDriverPin58(Function);}else{ErrCode=2;}break;
			case 59:if(Function<=0){LibSystemPinoutsDriverPin59(Function);}else{ErrCode=2;}break;
			case 60:if(Function<=0){LibSystemPinoutsDriverPin60(Function);}else{ErrCode=2;}break;
			case 61:if(Function<=2){LibSystemPinoutsDriverPin61(Function);}else{ErrCode=2;}break;
			case 62:if(Function<=2){LibSystemPinoutsDriverPin62(Function);}else{ErrCode=2;}break;
			case 63:if(Function<=0){LibSystemPinoutsDriverPin63(Function);}else{ErrCode=2;}break;
			case 64:if(Function<=0){LibSystemPinoutsDriverPin64(Function);}else{ErrCode=2;}break;
			case 65:if(Function<=2){LibSystemPinoutsDriverPin65(Function);}else{ErrCode=2;}break;
			case 66:if(Function<=1){LibSystemPinoutsDriverPin66(Function);}else{ErrCode=2;}break;
			case 67:if(Function<=1){LibSystemPinoutsDriverPin67(Function);}else{ErrCode=2;}break;
			case 68:if(Function<=1){LibSystemPinoutsDriverPin68(Function);}else{ErrCode=2;}break;
			case 69:if(Function<=1){LibSystemPinoutsDriverPin69(Function);}else{ErrCode=2;}break;
			case 70:if(Function<=1){LibSystemPinoutsDriverPin70(Function);}else{ErrCode=2;}break;
			case 71:if(Function<=1){LibSystemPinoutsDriverPin71(Function);}else{ErrCode=2;}break;
			case 72:if(Function<=1){LibSystemPinoutsDriverPin72(Function);}else{ErrCode=2;}break;
			case 73:if(Function<=1){LibSystemPinoutsDriverPin73(Function);}else{ErrCode=2;}break;
			case 74:if(Function<=0){LibSystemPinoutsDriverPin74(Function);}else{ErrCode=2;}break;
			case 75:if(Function<=0){LibSystemPinoutsDriverPin75(Function);}else{ErrCode=2;}break;
			case 76:
			case 77:
			case 78:
			case 79:
					if(Function<=1)
					{
						LibSystemPinoutsDriverPin76(Function);
						LibSystemPinoutsDriverPin77(Function);
						LibSystemPinoutsDriverPin78(Function);
						LibSystemPinoutsDriverPin79(Function);
					}
					else
					{
						ErrCode=2;
					}
					break;
		
			case 80:if(Function<=1){LibSystemPinoutsDriverPin80(Function);}else{ErrCode=2;}break;
		}
	}
	else
	{
		ErrCode = 1;
	}
	return ErrCode;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin80
** 功能描述:控制器Pin80输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin80(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[79] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin79
** 功能描述:控制器Pin79输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin79(unsigned char Function)
{
	if(Function<2)
	{
		REG_GPIOD_PUR &= ~(1<<11);
		REG_GPIOD_DDR |= (1<<11);
		REG_GPIOD_PER &= ~(1<<11);
		REG_GPIOD_DR &= ~(1<<11);
		LibVarPinoutsSelect[78] = Function;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin78
** 功能描述:控制器Pin78输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin78(unsigned char Function)
{
	if(Function<2)
	{
		REG_GPIOD_PUR &= ~(1<<10);
		REG_GPIOD_DDR |= (1<<10);
		REG_GPIOD_PER &= ~(1<<10);
		REG_GPIOD_DR &= ~(1<<10);
		LibVarPinoutsSelect[77] = Function;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin77
** 功能描述:控制器Pin77输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin77(unsigned char Function)
{
	if(Function<2)
	{
		REG_GPIOD_PUR &= ~(1<<2);
		REG_GPIOD_DDR |= (1<<2);
		REG_GPIOD_PER &= ~(1<<2);
		REG_GPIOD_DR &= ~(1<<2);
		LibVarPinoutsSelect[76] = Function;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin76
** 功能描述:控制器Pin76输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin76(unsigned char Function)
{
	if(Function<2)
	{
		REG_GPIOD_PUR &= ~(1<<4);
		REG_GPIOD_DDR |= (1<<4);
		REG_GPIOD_PER &= ~(1<<4);
		REG_GPIOD_DR &= ~(1<<4);
		LibVarPinoutsSelect[75] = Function;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin75
** 功能描述:控制器Pin75输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin75(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[74] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin74
** 功能描述:控制器Pin74输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin74(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[73] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin73
** 功能描述:控制器Pin73输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin73(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[72] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[72] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin72
** 功能描述:控制器Pin72输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin72(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[71] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[71] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin71
** 功能描述:控制器Pin71输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin71(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[70] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[70] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin70
** 功能描述:控制器Pin70输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin70(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[69] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[69] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin69
** 功能描述:控制器Pin69输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin69(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[68] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[68] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin68
** 功能描述:控制器Pin68输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin68(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[67] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[67] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin67
** 功能描述:控制器Pin67输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin67(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[66] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[66] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin66
** 功能描述:控制器Pin66输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin66(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[65] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[65] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin65
** 功能描述:控制器Pin65输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin65(unsigned char Function)
{
	if(Function==0)
	{
		#if DefineHardwareNewVersion
			REG_GPIOC_PUR &= ~(1<<5);
			REG_GPIOC_DDR &= ~(1<<5);
			REG_GPIOC_PER |= (1<<5);
		#else
			REG_GPIOE_PUR &= ~(1<<13);
			REG_GPIOE_DDR &= ~(1<<13);
			REG_GPIOE_PER |= (1<<13);
		#endif
		LibVarPinoutsSelect[64] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOB_PUR &= ~(1<<2);
		REG_GPIOB_DDR &= ~(1<<2);
		REG_GPIOB_PER &= ~(1<<2);
		LibVarPinoutsSelect[64] = 1;
	}
	else if(Function==2)
	{
		REG_GPIOC_PER |= (1<<5);
		LibVarPinoutsSelect[57] = 2;
		LibVarPinoutsSelect[64] = 2;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin64
** 功能描述:控制器Pin64输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin64(unsigned char Function)
{
	if(Function==0)
	{
		#if DefineHardwareNewVersion
			//IRQB
			REG_SIM_PUDR |= (1<<10);
			REG_ITCN_ICTL |= (1<<1);
			REG_ITCN_IPR2 |= (0x01<<2);
			//IRQA
		//	REG_SIM_PUDR |= (1<<10);
		//	REG_ITCN_ICTL |= (1<<0);
		//	REG_ITCN_IPR2 |= (0x01<<0);
		#else
			REG_GPIOD_PUR &= ~(1<<9);
			REG_GPIOD_DDR &= ~(1<<9);
			REG_GPIOD_PER &= ~(1<<9);
		#endif
		LibVarPinoutsSelect[63] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin63
** 功能描述:控制器Pin63输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin63(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOD_PUR &= ~(1<<8);
		REG_GPIOD_DDR &= ~(1<<8);
		REG_GPIOD_PER &= ~(1<<8);
		LibVarPinoutsSelect[62] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin62
** 功能描述:控制器Pin62输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin62(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOE_PUR &= ~(1<<10);
		REG_GPIOE_DDR &= ~(1<<10);
		REG_GPIOE_PER |= (1<<10);
		LibVarPinoutsSelect[61] = 0;
	}
	else if(Function==1 || Function==2)
	{
		REG_GPIOB_PUR &= ~(1<<4);
		REG_GPIOB_DDR &= ~(1<<4);
		REG_GPIOB_PER &= ~(1<<4);
		LibVarPinoutsSelect[61] = Function;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin61
** 功能描述:控制器Pin61输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin61(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOE_PUR &= ~(1<<11);
		REG_GPIOE_DDR &= ~(1<<11);
		REG_GPIOE_PER |= (1<<11);
		LibVarPinoutsSelect[60] = 0;
	}
	else if(Function==1 || Function==2)
	{
		REG_GPIOB_PUR &= ~(1<<5);
		REG_GPIOB_DDR &= ~(1<<5);
		REG_GPIOB_PER &= ~(1<<5);
		LibVarPinoutsSelect[60] = Function;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin60
** 功能描述:控制器Pin60输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin60(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[59] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin59
** 功能描述:控制器Pin59输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin59(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[58] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin58
** 功能描述:控制器Pin58输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin58(unsigned char Function)
{
	if(Function==0)
	{
		#if DefineHardwareNewVersion
			REG_GPIOC_PUR &= ~(1<<4);
			REG_GPIOC_DDR &= ~(1<<4);
			REG_GPIOC_PER |= (1<<4);
		#else
			REG_GPIOE_PUR &= ~(1<<12);
			REG_GPIOE_DDR &= ~(1<<12);
			REG_GPIOE_PER |= (1<<12);
		#endif
		LibVarPinoutsSelect[57] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOB_PUR &= ~(1<<3);
		REG_GPIOB_DDR &= ~(1<<3);
		REG_GPIOB_PER &= ~(1<<3);
		LibVarPinoutsSelect[57] = 1;
	}
	else if(Function==2)
	{
		REG_GPIOC_PER |= (1<<4);
		LibVarPinoutsSelect[57] = 2;
		LibVarPinoutsSelect[64] = 2;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin57
** 功能描述:控制器Pin57输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin57(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[56] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin56
** 功能描述:控制器Pin56输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin56(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[55] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin55
** 功能描述:控制器Pin55输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin55(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[54] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin54
** 功能描述:控制器Pin54输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin54(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOE_PUR |= (1<<0);
		REG_GPIOE_DDR &= ~(1<<0);
		REG_GPIOE_PER |= (1<<0);
		LibVarPinoutsSelect[53] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin53
** 功能描述:控制器Pin53输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin53(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOE_PUR |= (1<<1);
		REG_GPIOE_DDR &= ~(1<<1);
		REG_GPIOE_PER |= (1<<1);
		LibVarPinoutsSelect[52] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin52
** 功能描述:控制器Pin52输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin52(unsigned char Function)
{
	if(Function==0)
	{
		#if DefineHardwareNewVersion
			REG_GPIOD_PUR &= ~(1<<9);
			REG_GPIOD_DDR &= ~(1<<9);
			REG_GPIOD_PER &= ~(1<<9);
		#else
			REG_SIM_PUDR &= ~(1<<10);
			REG_ITCN_ICTL |= (1<<1);
			REG_ITCN_IPR2 |= (0x03<<2);
		#endif
		LibVarPinoutsSelect[51] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin51
** 功能描述:控制器Pin51输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin51(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOF_PUR &= ~(1<<3);
		REG_GPIOF_DDR &= ~(1<<3);
		REG_GPIOF_PER &= ~(1<<3);
		LibVarPinoutsSelect[50] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin50
** 功能描述:控制器Pin50输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin50(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOB_PUR &= ~(1<<1);
		REG_GPIOB_DDR &= ~(1<<1);
		REG_GPIOB_PER &= ~(1<<1);
		LibVarPinoutsSelect[49] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin49
** 功能描述:控制器Pin49输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin49(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[48] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin48
** 功能描述:控制器Pin48输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin48(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOF_PUR |= (1<<4);
		REG_GPIOF_DDR |= (1<<4);
		REG_GPIOF_PER &= (~(1<<4));
		LibVarPinoutsSelect[47] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOF_PUR |= ~(1<<4);
		REG_GPIOF_DDR |= (1<<4);
		REG_GPIOF_PER &= (~(1<<4));
		REG_GPIOF_DR  &= (~(1<<4));
		LibVarPinoutsSelect[47] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin47
** 功能描述:控制器Pin46输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin47(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOF_PUR |= (1<<6);
		REG_GPIOF_DDR |= (1<<6);
		REG_GPIOF_PER &= (~(1<<6));
		LibVarPinoutsSelect[46] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOF_PUR |= ~(1<<6);
		REG_GPIOF_DDR |= (1<<6);
		REG_GPIOF_PER &= (~(1<<6));
		REG_GPIOF_DR  &= (~(1<<6));
		LibVarPinoutsSelect[46] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin46
** 功能描述:控制器Pin46输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin46(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOF_PUR |= (1<<8);
		REG_GPIOF_DDR |= (1<<8);
		REG_GPIOF_PER &= (~(1<<8));
		LibVarPinoutsSelect[45] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOF_PUR |= ~(1<<8);
		REG_GPIOF_DDR |= (1<<8);
		REG_GPIOF_PER &= (~(1<<8));
		REG_GPIOF_DR  &= (~(1<<8));
		LibVarPinoutsSelect[45] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin45
** 功能描述:控制器Pin45输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin45(unsigned char Function)
{
	if(Function==0)
	{ // E12   // E4
		REG_GPIOE_PUR |= (1<<12);
		REG_GPIOE_DDR |= (1<<12);
		REG_GPIOE_PER &= (~(1<<12));
		LibVarPinoutsSelect[44] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOE_PUR |= ~(1<<12);
		REG_GPIOE_DDR |= (1<<12);
		REG_GPIOE_PER &= (~(1<<12));
		REG_GPIOE_DR  &= (~(1<<12));
		LibVarPinoutsSelect[44] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin44
** 功能描述:控制器Pin44输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin44(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR |= (1<<3);
		REG_GPIOA_DDR |= (1<<3);
		REG_GPIOA_PER &= (~(1<<3));
		LibVarPinoutsSelect[43] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR |= ~(1<<3);
		REG_GPIOA_DDR |= (1<<3);
		REG_GPIOA_PER &= (~(1<<3));
		REG_GPIOA_DR  &= (~(1<<3));
		LibVarPinoutsSelect[43] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin43
** 功能描述:控制器Pin43输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin43(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR |= (1<<5);
		REG_GPIOA_DDR |= (1<<5);
		REG_GPIOA_PER &= (~(1<<5));
		LibVarPinoutsSelect[42] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR |= ~(1<<5);
		REG_GPIOA_DDR |= (1<<5);
		REG_GPIOA_PER &= (~(1<<5));
		REG_GPIOA_DR  &= (~(1<<5));
		LibVarPinoutsSelect[42] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin42
** 功能描述:控制器Pin42输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin42(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR |= (1<<6);
		REG_GPIOA_DDR |= (1<<6);
		REG_GPIOA_PER &= (~(1<<6));
		LibVarPinoutsSelect[41] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR |= ~(1<<6);
		REG_GPIOA_DDR |= (1<<6);
		REG_GPIOA_PER &= (~(1<<6));
		REG_GPIOA_DR  &= (~(1<<6));
		LibVarPinoutsSelect[41] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin41
** 功能描述:控制器Pin41输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin41(unsigned char Function)
{
	REG_GPIOF_PUR |= ~(1<<1);
	REG_GPIOF_DDR |= (1<<1);
	REG_GPIOF_PER &= (~(1<<1));
	REG_GPIOF_DR  &= (~(1<<1));
	if(Function==0)
	{
		LibVarPinoutsSelect[40] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[40] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin40
** 功能描述:控制器Pin40输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin40(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[39] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[39] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin39
** 功能描述:控制器Pin39输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin39(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[38] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[38] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin38
** 功能描述:控制器Pin38输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin38(unsigned char Function)
{
	if(Function==0)
	{
		LibVarPinoutsSelect[37] = 0;
	}
	else if(Function==1)
	{
		LibVarPinoutsSelect[37] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin37
** 功能描述:控制器Pin37输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin37(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOE_PUR |= (1<<9);
		REG_GPIOE_DDR |= (1<<9);
		REG_GPIOE_PER &= (~(1<<9));
		LibVarPinoutsSelect[36] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOE_PUR |= ~(1<<9);
		REG_GPIOE_DDR |= (1<<9);
		REG_GPIOE_PER &= (~(1<<9));
		REG_GPIOE_DR  &= (~(1<<9));
		LibVarPinoutsSelect[36] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin36
** 功能描述:控制器Pin36输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin36(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOF_PUR |= (1<<5);
		REG_GPIOF_DDR |= (1<<5);
		REG_GPIOF_PER &= (~(1<<5));
		LibVarPinoutsSelect[35] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOF_PUR |= ~(1<<5);
		REG_GPIOF_DDR |= (1<<5);
		REG_GPIOF_PER &= (~(1<<5));
		REG_GPIOF_DR  &= (~(1<<5));
		LibVarPinoutsSelect[35] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin35
** 功能描述:控制器Pin35输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin35(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOF_PUR |= (1<<7);
		REG_GPIOF_DDR |= (1<<7);
		REG_GPIOF_PER &= (~(1<<7));
		LibVarPinoutsSelect[34] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOF_PUR |= ~(1<<7);
		REG_GPIOF_DDR |= (1<<7);
		REG_GPIOF_PER &= (~(1<<7));
		REG_GPIOF_DR  &= (~(1<<7));
		LibVarPinoutsSelect[34] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin34
** 功能描述:控制器Pin34输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin34(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR |= (1<<8);
		REG_GPIOA_DDR |= (1<<8);
		REG_GPIOA_PER &= (~(1<<8));
		LibVarPinoutsSelect[33] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR |= ~(1<<8);
		REG_GPIOA_DDR |= (1<<8);
		REG_GPIOA_PER &= (~(1<<8));
		REG_GPIOA_DR  &= (~(1<<8));
		LibVarPinoutsSelect[33] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin33
** 功能描述:控制器Pin33输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin33(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR |= (1<<2);
		REG_GPIOA_DDR |= (1<<2);
		REG_GPIOA_PER &= (~(1<<2));
		LibVarPinoutsSelect[32] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR |= ~(1<<2);
		REG_GPIOA_DDR |= (1<<2);
		REG_GPIOA_PER &= (~(1<<2));
		REG_GPIOA_DR  &= (~(1<<2));
		LibVarPinoutsSelect[32] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin32
** 功能描述:控制器Pin32输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin32(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR |= (1<<4);
		REG_GPIOA_DDR |= (1<<4);
		REG_GPIOA_PER &= (~(1<<4));
		LibVarPinoutsSelect[31] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR |= ~(1<<4);
		REG_GPIOA_DDR |= (1<<4);
		REG_GPIOA_PER &= (~(1<<4));
		REG_GPIOA_DR  &= (~(1<<4));
		LibVarPinoutsSelect[31] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin31
** 功能描述:控制器Pin31输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin31(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR |= (1<<7);
		REG_GPIOA_DDR |= (1<<7);
		REG_GPIOA_PER &= (~(1<<7));
		LibVarPinoutsSelect[30] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR |= ~(1<<7);
		REG_GPIOA_DDR |= (1<<7);
		REG_GPIOA_PER &= (~(1<<7));
		REG_GPIOA_DR  &= (~(1<<7));
		LibVarPinoutsSelect[30] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin30
** 功能描述:控制器Pin30输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin30(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[29] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin29
** 功能描述:控制器Pin29输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin29(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[28] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin28
** 功能描述:控制器Pin28输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin28(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[27] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin27
** 功能描述:控制器Pin27输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin27(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[26] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin26
** 功能描述:控制器Pin26输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin26(unsigned char Function)
{
	if(Function==0)  
	{
		REG_SIM_PUDR |= (1<<10);
		REG_ITCN_ICTL |= (1<<0);
		REG_ITCN_IPR2 |= (0x01<<0);
		LibVarPinoutsSelect[25] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin25
** 功能描述:控制器Pin25输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin25(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOD_PUR &= ~(1<<6);
		REG_GPIOD_DDR &= ~(1<<6);
		REG_GPIOD_PER &= ~(1<<6);
		LibVarPinoutsSelect[24] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin24
** 功能描述:控制器Pin24输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin24(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOB_PUR &= ~(1<<7);
		REG_GPIOB_DDR &= ~(1<<7);
		REG_GPIOB_PER &= ~(1<<7);
		LibVarPinoutsSelect[23] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin23
** 功能描述:控制器Pin23输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin23(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOA_PUR &= ~(1<<1);
		REG_GPIOA_DDR |= (1<<1);
		REG_GPIOA_PER &= (~(1<<1));
		REG_GPIOA_DR  &= (~(1<<1));
		
		REG_GPIOA_PUR &= ~(1<<0);
		REG_GPIOA_DDR |= (1<<0);
		REG_GPIOA_PER &= (~(1<<0));
		REG_GPIOA_DR  &= (~(1<<0));
		
		LibVar74HC595U4001 &= ~(1<<7);  
		LibVarPinoutsSelect[22] = 0;
	}
	else if(Function==1)
	{
		REG_GPIOA_PUR &= ~(1<<1);
		REG_GPIOA_DDR |= (1<<1);
		REG_GPIOA_PER &= (~(1<<1));
		REG_GPIOA_DR  |= (1<<1);
		
		REG_GPIOA_PUR &= ~(1<<0);
		REG_GPIOA_DDR |= (1<<0);
		REG_GPIOA_PER &= (~(1<<0));
		REG_GPIOA_DR  &= ~(1<<0);
		
		LibVar74HC595U4001 &= ~(1<<7); 
		LibVarPinoutsSelect[22] = 1;
	}
	else if(Function==2)
	{
		REG_GPIOA_PUR &= ~(1<<1);
		REG_GPIOA_DDR |= (1<<1);
		REG_GPIOA_PER &= (~(1<<1));
		REG_GPIOA_DR  &= (~(1<<1));
		
		REG_GPIOA_PUR &= ~(1<<0);
		REG_GPIOA_DDR |= (1<<0);
		REG_GPIOA_PER &= (~(1<<0));
		REG_GPIOA_DR  |= (1<<0);
		
		LibVar74HC595U4001 &= ~(1<<7);
		LibVarPinoutsSelect[22] = 2;
	}
	else if(Function==3)
	{
		REG_GPIOA_PUR &= ~(1<<1);
		REG_GPIOA_DDR |= (1<<1);
		REG_GPIOA_PER &= (~(1<<1));
		REG_GPIOA_DR  &= (~(1<<1));
		
		REG_GPIOA_PUR &= ~(1<<0);
		REG_GPIOA_DDR |= (1<<0);
		REG_GPIOA_PER &= (~(1<<0));
		REG_GPIOA_DR  &= (~(1<<0));
		
		LibVar74HC595U4001 |= (1<<7);   
		LibVarPinoutsSelect[22] = 3;
	}
	else if(Function==4)
	{
		REG_GPIOA_PUR |= (1<<1);
		REG_GPIOA_DDR |= (1<<1);
		REG_GPIOA_PER &= (~(1<<1));
		REG_GPIOA_DR  |= (1<<1);
		
		REG_GPIOA_PUR &= ~(1<<0);
		REG_GPIOA_DDR |= (1<<0);
		REG_GPIOA_PER &= (~(1<<0));
		REG_GPIOA_DR  &= (~(1<<0));
		
		LibVar74HC595U4001 &= ~(1<<7); 
		LibVarPinoutsSelect[22] = 4;
	}
	else if(Function==5)
	{
		REG_GPIOA_PUR &= ~(1<<1);
		REG_GPIOA_DDR |= (1<<1);
		REG_GPIOA_PER &= (~(1<<1));
		REG_GPIOA_DR  &= (~(1<<1));
		
		REG_GPIOA_PUR &= ~(1<<0);
		REG_GPIOA_DDR |= (1<<0);
		REG_GPIOA_PER &= (~(1<<0));
		REG_GPIOA_DR  &= (~(1<<0));
		
		LibVar74HC595U4001 |= (1<<7);
		LibVarPinoutsSelect[22] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin22
** 功能描述:控制器Pin14输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin22(unsigned char Function)
{
	if(Function==0)
	{
		REG_GPIOD_PUR &= ~(1<<7);
		REG_GPIOD_DDR &= ~(1<<7);
		REG_GPIOD_PER &= (~(1<<7));
		LibVarPinoutsSelect[21] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin21
** 功能描述:控制器Pin21输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin21(unsigned char Function)
{
	if(Function==0)
	{
		LibVar74HC595U4001 &= ~(1<<0);  
		LibVar74HC595U4002 &= ~(1<<0);  
		LibVar74HC595U4002 &= ~(1<<1);  
		LibVarPinoutsSelect[20] = 0;
	}
	else if(Function==1)
	{
		LibVar74HC595U4001 |= (1<<0);  
		LibVar74HC595U4002 &= ~(1<<0);  
		LibVar74HC595U4002 &= ~(1<<1); 
		LibVarPinoutsSelect[20] = 1;
	}
	else if(Function==2)
	{
		LibVar74HC595U4001 &= ~(1<<0);  
		LibVar74HC595U4002 |= (1<<0);  
		LibVar74HC595U4002 &= ~(1<<1); 
		LibVarPinoutsSelect[20] = 2;
	}
	else if(Function==3)
	{
		LibVar74HC595U4001 &= ~(1<<0);  
		LibVar74HC595U4002 &= ~(1<<0);  
		LibVar74HC595U4002 |= (1<<1); 
		LibVarPinoutsSelect[20] = 3;
	}
	else if(Function==4)
	{
		LibVar74HC595U4001 |= (1<<0);  
		LibVar74HC595U4002 &= ~(1<<0);  
		LibVar74HC595U4002 &= ~(1<<1);
		LibVarPinoutsSelect[20] = 4;
	}
	else if(Function==5)
	{
		LibVar74HC595U4001 &= ~(1<<0);  
		LibVar74HC595U4002 &= ~(1<<0);  
		LibVar74HC595U4002 |= (1<<1);
		LibVarPinoutsSelect[20] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin20
** 功能描述:控制器Pin20输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin20(unsigned char Function)
{
	if(Function==0)          
	{
		LibVar74HC595U4005 &= ~(1<<6);  
		LibVar74HC595U4003 &= ~(1<<0);  
		LibVar74HC595U4005 &= ~(1<<7);  
		LibVarPinoutsSelect[19] = 0;
	}
	else if(Function==1)     
	{
		LibVar74HC595U4005 |= (1<<6);  
		LibVar74HC595U4003 &= ~(1<<0);   
		LibVar74HC595U4005 &= ~(1<<7); 
		LibVarPinoutsSelect[19] = 1;
	}
	else if(Function==2)     
	{
		LibVar74HC595U4005 &= ~(1<<6);  
		LibVar74HC595U4003 |= (1<<0);   
		LibVar74HC595U4005 &= ~(1<<7); 
		LibVarPinoutsSelect[19] = 2;
	}
	else if(Function==3)     
	{
		LibVar74HC595U4005 &= ~(1<<6);  
		LibVar74HC595U4003 &= ~(1<<0);  
		LibVar74HC595U4005 |= (1<<7);   
		LibVarPinoutsSelect[19] = 3;
	}
	else if(Function==4)     
	{
		LibVar74HC595U4005 |= (1<<6);  
		LibVar74HC595U4003 &= ~(1<<0); 
		LibVar74HC595U4005 &= ~(1<<7); 
		LibVarPinoutsSelect[19] = 4;
	}
	else if(Function==5)     
	{
		LibVar74HC595U4005 &= ~(1<<6);
		LibVar74HC595U4003 &= ~(1<<0);
		LibVar74HC595U4005 |= (1<<7);
		LibVarPinoutsSelect[19] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin19
** 功能描述:控制器Pin19输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin19(unsigned char Function)
{
	if(Function==0)          
	{
		LibVar74HC595U4005 &= ~(1<<4);  
		LibVar74HC595U4005 &= ~(1<<3);  
		LibVar74HC595U4005 &= ~(1<<5);  
		LibVarPinoutsSelect[18] = 0;
	}
	else if(Function==1)     
	{
		LibVar74HC595U4005 |= (1<<4);  
		LibVar74HC595U4005 &= ~(1<<3);   
		LibVar74HC595U4005 &= ~(1<<5); 
		LibVarPinoutsSelect[18] = 1;
	}
	else if(Function==2)     
	{
		LibVar74HC595U4005 &= ~(1<<4);  
		LibVar74HC595U4005 |= (1<<3);   
		LibVar74HC595U4005 &= ~(1<<5); 
		LibVarPinoutsSelect[18] = 2;
	}
	else if(Function==3)     
	{
		LibVar74HC595U4005 &= ~(1<<4);  
		LibVar74HC595U4005 &= ~(1<<3);  
		LibVar74HC595U4005 |= (1<<5);   
		LibVarPinoutsSelect[18] = 3;
	}
	else if(Function==4)     
	{
		LibVar74HC595U4005 |= (1<<4);  
		LibVar74HC595U4005 &= ~(1<<3); 
		LibVar74HC595U4005 &= ~(1<<5); 
		LibVarPinoutsSelect[18] = 4;
	}
	else if(Function==5)     
	{
		LibVar74HC595U4005 &= ~(1<<4);
		LibVar74HC595U4005 &= ~(1<<3);
		LibVar74HC595U4005 |= (1<<5);
		LibVarPinoutsSelect[18] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin18
** 功能描述:控制器Pin18输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin18(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[17] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin17
** 功能描述:控制器Pin17输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin17(unsigned char Function)
{
	if(Function==0)          
	{
		LibVar74HC595U4002 &= ~(1<<5);  
		LibVar74HC595U4002 &= ~(1<<6);  
		LibVar74HC595U4002 &= ~(1<<7);  
		LibVarPinoutsSelect[16] = 0;
	}
	else if(Function==1)     
	{
		LibVar74HC595U4002 |= (1<<5);  
		LibVar74HC595U4002 &= ~(1<<6);   
		LibVar74HC595U4002 &= ~(1<<7); 
		LibVarPinoutsSelect[16] = 1;
	}
	else if(Function==2)     
	{
		LibVar74HC595U4002 &= ~(1<<5);  
		LibVar74HC595U4002 |= (1<<6);   
		LibVar74HC595U4002 &= ~(1<<7); 
		LibVarPinoutsSelect[16] = 2;
	}
	else if(Function==3)     
	{
		LibVar74HC595U4002 &= ~(1<<5);  
		LibVar74HC595U4002 &= ~(1<<6);  
		LibVar74HC595U4002 |= (1<<7); 
		LibVarPinoutsSelect[16] = 3;  
	}
	else if(Function==4)     
	{
		LibVar74HC595U4002 |= (1<<5);  
		LibVar74HC595U4002 &= ~(1<<6); 
		LibVar74HC595U4002 &= ~(1<<7); 
		LibVarPinoutsSelect[16] = 4;
	}
	else if(Function==5)     
	{
		LibVar74HC595U4002 &= ~(1<<5);
		LibVar74HC595U4002 &= ~(1<<6);
		LibVar74HC595U4002 |= (1<<7);
		LibVarPinoutsSelect[16] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin16
** 功能描述:控制器Pin16输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin16(unsigned char Function)
{
	if(Function==0)          
	{
		LibVar74HC595U4002 &= ~(1<<3);  
		LibVar74HC595U4002 &= ~(1<<2);  
		LibVar74HC595U4002 &= ~(1<<4);  
		LibVarPinoutsSelect[15] = 0;
	}
	else if(Function==1)     
	{
		LibVar74HC595U4002 |= (1<<3);  
		LibVar74HC595U4002 &= ~(1<<2);   
		LibVar74HC595U4002 &= ~(1<<4); 
		LibVarPinoutsSelect[15] = 1;
	}
	else if(Function==2)     
	{
		LibVar74HC595U4002 &= ~(1<<3);  
		LibVar74HC595U4002 |= (1<<2);   
		LibVar74HC595U4002 &= ~(1<<4); 
		LibVarPinoutsSelect[15] = 2;
	}
	else if(Function==3)     
	{
		LibVar74HC595U4002 &= ~(1<<3);  
		LibVar74HC595U4002 &= ~(1<<2);  
		LibVar74HC595U4002 |= (1<<4);   
		LibVarPinoutsSelect[15] = 3;
	}
	else if(Function==4)     
	{
		LibVar74HC595U4002 |= (1<<3);  
		LibVar74HC595U4002 &= ~(1<<2); 
		LibVar74HC595U4002 &= ~(1<<4); 
		LibVarPinoutsSelect[15] = 4;
	}
	else if(Function==5)     
	{
		LibVar74HC595U4002 &= ~(1<<3);
		LibVar74HC595U4002 &= ~(1<<2);
		LibVar74HC595U4002 |= (1<<4);
		LibVarPinoutsSelect[15] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin15
** 功能描述:控制器Pin15输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin15(unsigned char Function)
{
	REG_GPIOF_PUR |= ~(1<<0);
	REG_GPIOF_DDR |= (1<<0);
	REG_GPIOF_PER &= (~(1<<0));
	REG_GPIOF_DR  &= (~(1<<0));	
	if(Function==0)         
	{
		LibVarPinoutsSelect[14] = 0;
	}
	else if(Function==1)    
	{
		LibVarPinoutsSelect[14] = 1;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin14
** 功能描述:控制器Pin14输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin14(unsigned char Function)
{
	if(Function==0)          
	{
		REG_GPIOF_PUR &= ~(1<<2);
		REG_GPIOF_DDR &= ~(1<<2);
		REG_GPIOF_PER &= (~(1<<2));
		LibVarPinoutsSelect[13] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin13
** 功能描述:控制器Pin13输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin13(unsigned char Function)
{
	if(Function==0)          
	{
		REG_GPIOB_PUR &= ~(1<<0);
		REG_GPIOB_DDR &= ~(1<<0);
		REG_GPIOB_PER &= ~(1<<0);
		LibVarPinoutsSelect[12] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin12
** 功能描述:控制器Pin11输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin12(unsigned char Function)
{
	if(Function==0)         
	{
		REG_GPIOB_PUR &= ~(1<<6);
		REG_GPIOB_DDR &= ~(1<<6);
		REG_GPIOB_PER &= ~(1<<6);
		LibVarPinoutsSelect[11] = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin11
** 功能描述:控制器Pin11输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin11(unsigned char Function)
{
	if(Function==0)          
	{
		LibVar74HC595U4001 &= ~(1<<3);  
		LibVar74HC595U4001 &= ~(1<<6);  
		LibVar74HC595U4001 &= ~(1<<4);  
		LibVarPinoutsSelect[10] = 0;
	}
	else if(Function==1)     
	{
		LibVar74HC595U4001 |= (1<<3);  
		LibVar74HC595U4001 &= ~(1<<6);   
		LibVar74HC595U4001 &= ~(1<<4); 
		LibVarPinoutsSelect[10] = 1;
	}
	else if(Function==2)     
	{
		LibVar74HC595U4001 &= ~(1<<3);  
		LibVar74HC595U4001 |= (1<<6);   
		LibVar74HC595U4001 &= ~(1<<4); 
		LibVarPinoutsSelect[10] = 2;
	}
	else if(Function==3)     
	{
		LibVar74HC595U4001 &= ~(1<<3);  
		LibVar74HC595U4001 &= ~(1<<6);  
		LibVar74HC595U4001 |= (1<<4);   
		LibVarPinoutsSelect[10] = 3;
	}
	else if(Function==4)     
	{
		LibVar74HC595U4001 |= (1<<3);  
		LibVar74HC595U4001 &= ~(1<<6); 
		LibVar74HC595U4001 &= ~(1<<4); 
		LibVarPinoutsSelect[10] = 4;
	}
	else if(Function==5)     
	{
		LibVar74HC595U4001 &= ~(1<<3);
		LibVar74HC595U4001 &= ~(1<<6);
		LibVar74HC595U4001 |= (1<<4);
		LibVarPinoutsSelect[10] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin10
** 功能描述:控制器Pin10输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin10(unsigned char Function)
{
	if(Function==0)          
	{
		LibVar74HC595U4001 &= ~(1<<1);  
		LibVar74HC595U4001 &= ~(1<<5);  
		LibVar74HC595U4001 &= ~(1<<2);  
		LibVarPinoutsSelect[9] = 0;
	}
	else if(Function==1)     
	{
		LibVar74HC595U4001 |= (1<<1);  
		LibVar74HC595U4001 &= ~(1<<5);   
		LibVar74HC595U4001 &= ~(1<<2);
		LibVarPinoutsSelect[9] = 1; 
	}
	else if(Function==2)     
	{
		LibVar74HC595U4001 &= ~(1<<1);  
		LibVar74HC595U4001 |= (1<<5);   
		LibVar74HC595U4001 &= ~(1<<2);
		LibVarPinoutsSelect[9] = 2; 
	}
	else if(Function==3)     
	{
		LibVar74HC595U4001 &= ~(1<<1);  
		LibVar74HC595U4001 &= ~(1<<5);  
		LibVar74HC595U4001 |= (1<<2);   
		LibVarPinoutsSelect[9] = 3;
	}
	else if(Function==4)     
	{
		LibVar74HC595U4001 |= (1<<1);  
		LibVar74HC595U4001 &= ~(1<<5); 
		LibVar74HC595U4001 &= ~(1<<2); 
		LibVarPinoutsSelect[9] = 4;
	}
	else if(Function==5)     
	{
		LibVar74HC595U4001 &= ~(1<<1);
		LibVar74HC595U4001 &= ~(1<<5);
		LibVar74HC595U4001 |= (1<<2);
		LibVarPinoutsSelect[9] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriver_Pin9
** 功能描述:控制器Pin9输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin9(unsigned char Function)
{
	if(Function==0)          
	{
		LibVar74HC595U4004 &= ~(1<<5);  
		LibVar74HC595U4004 &= ~(1<<7);  
		LibVar74HC595U4004 &= ~(1<<6);  
		LibVarPinoutsSelect[8] = 0;
	}
	else if(Function==1)     
	{
		LibVar74HC595U4004 |= (1<<5);  
		LibVar74HC595U4004 &= ~(1<<7);   
		LibVar74HC595U4004 &= ~(1<<6); 
		LibVarPinoutsSelect[8] = 1;
	}
	else if(Function==2)     
	{
		LibVar74HC595U4004 &= ~(1<<5);  
		LibVar74HC595U4004 |= (1<<7);   
		LibVar74HC595U4004 &= ~(1<<6); 
		LibVarPinoutsSelect[8] = 2;
	}
	else if(Function==3)     
	{
		LibVar74HC595U4004 &= ~(1<<5);  
		LibVar74HC595U4004 &= ~(1<<7);  
		LibVar74HC595U4004 |= (1<<6);  
		LibVarPinoutsSelect[8] = 3; 
	}
	else if(Function==4)     
	{
		LibVar74HC595U4004 |= (1<<5);  
		LibVar74HC595U4004 &= ~(1<<7); 
		LibVar74HC595U4004 &= ~(1<<6); 
		LibVarPinoutsSelect[8] = 4;
	}
	else if(Function==5)     
	{
		LibVar74HC595U4004 &= ~(1<<5);
		LibVar74HC595U4004 &= ~(1<<7);
		LibVar74HC595U4004 |= (1<<6);
		LibVarPinoutsSelect[8] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriver_Pin8
** 功能描述:控制器Pin8输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin8(unsigned char Function)
{
	if(Function==0)
	{
		LibVar74HC595U4004 &= ~(1<<3);  
		LibVar74HC595U4004 &= ~(1<<0);  
		LibVar74HC595U4004 &= ~(1<<4);  
		LibVarPinoutsSelect[7] = 0;
	}
	else if(Function==1)
	{
		LibVar74HC595U4004 |= (1<<3);  
		LibVar74HC595U4004 &= ~(1<<0);   
		LibVar74HC595U4004 &= ~(1<<4); 
		LibVarPinoutsSelect[7] = 1;
	}
	else if(Function==2)
	{
		LibVar74HC595U4004 &= ~(1<<3);  
		LibVar74HC595U4004 |= (1<<0);   
		LibVar74HC595U4004 &= ~(1<<4); 
		LibVarPinoutsSelect[7] = 2;
	}
	else if(Function==3)
	{
		LibVar74HC595U4004 &= ~(1<<3);  
		LibVar74HC595U4004 &= ~(1<<0);  
		LibVar74HC595U4004 |= (1<<4);  
		LibVarPinoutsSelect[7] = 3; 
	}
	else if(Function==4)
	{
		LibVar74HC595U4004 |= (1<<3);  
		LibVar74HC595U4004 &= ~(1<<0); 
		LibVar74HC595U4004 &= ~(1<<4); 
		LibVarPinoutsSelect[7] = 4;
	}
	else if(Function==5)
	{
		LibVar74HC595U4004 &= ~(1<<3);
		LibVar74HC595U4004 &= ~(1<<0);
		LibVar74HC595U4004 |= (1<<4);
		LibVarPinoutsSelect[7] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin7
** 功能描述:控制器Pin7输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin7(unsigned char Function)
{
	if(Function==0)
	{
		LibVar74HC595U4004 &= ~(1<<2);  
		LibVar74HC595U4004 &= ~(1<<1);  
		LibVar74HC595U4003 &= ~(1<<7);  
		LibVarPinoutsSelect[6] = 0;
	}
	else if(Function==1) 
	{
		LibVar74HC595U4004 |= (1<<2);  
		LibVar74HC595U4004 &= ~(1<<1);   
		LibVar74HC595U4003 &= ~(1<<7); 
		LibVarPinoutsSelect[6] = 1; 
	}
	else if(Function==2) 
	{
		LibVar74HC595U4004 &= ~(1<<2);  
		LibVar74HC595U4004 |= (1<<1);   
		LibVar74HC595U4003 &= ~(1<<7); 
		LibVarPinoutsSelect[6] = 2; 
	}
	else if(Function==3)
	{
		LibVar74HC595U4004 &= ~(1<<2);  
		LibVar74HC595U4004 &= ~(1<<1);  
		LibVar74HC595U4003 |= (1<<7);  
		LibVarPinoutsSelect[6] = 3; 
	}
	else if(Function==4)
	{
		LibVar74HC595U4004 |= (1<<2);   
		LibVar74HC595U4004 &= ~(1<<1);  
		LibVar74HC595U4003 &= ~(1<<7); 
		LibVarPinoutsSelect[6] = 4; 
	}
	else if(Function==5)
	{
		LibVar74HC595U4004 &= ~(1<<2);  
		LibVar74HC595U4004 &= ~(1<<1);  
		LibVar74HC595U4003 |= (1<<7);
		LibVarPinoutsSelect[6] = 5;  
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin6
** 功能描述:控制器Pin6输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin6(unsigned char Function)
{
	if(Function==0)
	{
		LibVar74HC595U4005 &= ~(1<<0);  
		LibVar74HC595U4005 &= ~(1<<1);  
		LibVar74HC595U4005 &= ~(1<<2);  
		LibVarPinoutsSelect[5] = 0;
	}
	else if(Function==1)
	{
		LibVar74HC595U4005 |= (1<<0);  
		LibVar74HC595U4005 &= ~(1<<1);  
		LibVar74HC595U4005 &= ~(1<<2);  
		LibVarPinoutsSelect[5] = 1;
	}
	else if(Function==2)
	{
		LibVar74HC595U4005 &= ~(1<<0);  
		LibVar74HC595U4005 |= (1<<1);  
		LibVar74HC595U4005 &= ~(1<<2);  
		LibVarPinoutsSelect[5] = 2;
	}
	else if(Function==3)
	{
		LibVar74HC595U4005 &= ~(1<<0);  
		LibVar74HC595U4005 &= ~(1<<1);  
		LibVar74HC595U4005 |= (1<<2);   
		LibVarPinoutsSelect[5] = 3;
	}
	else if(Function==4)
	{
		LibVar74HC595U4005 |= (1<<0);   
		LibVar74HC595U4005 &= ~(1<<1);  
		LibVar74HC595U4005 &= ~(1<<2);  
		LibVarPinoutsSelect[5] = 4;
	}
	else if(Function==5)
	{
		LibVar74HC595U4005 &= ~(1<<0);  
		LibVar74HC595U4005 &= ~(1<<1);  
		LibVar74HC595U4005 |= (1<<2);   
		LibVarPinoutsSelect[5] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin5
** 功能描述:控制器Pin5输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin5(unsigned char Function)
{
	if(Function==0)
	{
		LibVar74HC595U4003 &= ~(1<<4);  
		LibVar74HC595U4003 &= ~(1<<6);  
		LibVar74HC595U4003 &= ~(1<<5); 
		LibVarPinoutsSelect[4] = 0;
	}
	else if(Function==1)
	{
		LibVar74HC595U4003 |= (1<<4);  
		LibVar74HC595U4003 &= ~(1<<6);   
		LibVar74HC595U4003 &= ~(1<<5); 
		LibVarPinoutsSelect[4] = 1; 
	}
	else if(Function==2)
	{
		LibVar74HC595U4003 &= ~(1<<4);  
		LibVar74HC595U4003 |= (1<<6);   
		LibVar74HC595U4003 &= ~(1<<5); 
		LibVarPinoutsSelect[4] = 2; 
	}
	else if(Function==3)
	{
		LibVar74HC595U4003 &= ~(1<<4); 
		LibVar74HC595U4003 &= ~(1<<6); 
		LibVar74HC595U4003 |= (1<<5);  
		LibVarPinoutsSelect[4] = 3;
	}
	else if(Function==4)
	{
		LibVar74HC595U4003 |= (1<<4);  
		LibVar74HC595U4003 &= ~(1<<6); 
		LibVar74HC595U4003 &= ~(1<<5);  
		LibVarPinoutsSelect[4] = 4;
	}
	else if(Function==5)
	{
		LibVar74HC595U4003 &= ~(1<<4);  
		LibVar74HC595U4003 &= ~(1<<6); 
		LibVar74HC595U4003 |= (1<<5);   
		LibVarPinoutsSelect[4] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin4
** 功能描述:控制器Pin4输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin4(unsigned char Function)
{
	if(Function==0)
	{
		LibVar74HC595U4003 &= ~(1<<1); 
		LibVar74HC595U4003 &= ~(1<<2); 
		LibVar74HC595U4003 &= ~(1<<3);  
		LibVarPinoutsSelect[3] = 0;
	}
	else if(Function==1)
	{
		LibVar74HC595U4003 |= (1<<1); 
		LibVar74HC595U4003 &= ~(1<<2);  
		LibVar74HC595U4003 &= ~(1<<3); 
		LibVarPinoutsSelect[3] = 1;
	}
	else if(Function==2)
	{
		LibVar74HC595U4003 &= ~(1<<1);  
		LibVar74HC595U4003 |= (1<<2); 
		LibVar74HC595U4003 &= ~(1<<3); 
		LibVarPinoutsSelect[3] = 2; 
	}
	else if(Function==3)
	{
		LibVar74HC595U4003 &= ~(1<<1);   
		LibVar74HC595U4003 &= ~(1<<2);  
		LibVar74HC595U4003 |= (1<<3); 
		LibVarPinoutsSelect[3] = 3;
	}
	else if(Function==4)
	{
		LibVar74HC595U4003 |= (1<<1);  
		LibVar74HC595U4003 &= ~(1<<2); 
		LibVar74HC595U4003 &= ~(1<<3);  
		LibVarPinoutsSelect[3] = 4;
	}
	else if(Function==5)
	{
		LibVar74HC595U4003 &= ~(1<<1);  
		LibVar74HC595U4003 &= ~(1<<2); 
		LibVar74HC595U4003 |= (1<<3);  
		LibVarPinoutsSelect[3] = 5;
	}
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin3
** 功能描述:控制器Pin3输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin3(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[2] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin2
** 功能描述:控制器Pin2输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin2(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[1] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemPinoutsDriverPin1
** 功能描述:控制器Pin1输出复用管脚功能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemPinoutsDriverPin1(unsigned char Function)
{
	Function = Function;
	LibVarPinoutsSelect[0] = 0;
}
/* ******************************************************
** 函数名称:LibFunSystemSerialIO
** 功能描述:串行74HC595输出数据和74HC165输入数据
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibSystemSerialIO(void)
{
	UINT16 i=0;
	UINT16 VarOutputData0;
	UINT16 VarOutputData1;
	UINT16 VarOutputData2;
	
	UINT16 VarGetDataPart1=0;
	UINT16 VarGetDataPart2=0;
	
	/* ***************** 74HC165 ******************* */
	
	//GPIOC8,输入,不上拉
	REG_GPIOC_PUR &= ~(1<<8);
	REG_GPIOC_DDR &= ~(1<<8);
	REG_GPIOC_PER &= ~(1<<8);
	//GPIOF12,输出,上拉
	REG_GPIOF_PUR |= (1<<12);
	REG_GPIOF_DDR |= (1<<12);
	REG_GPIOF_PER &= ~(1<<12);
	//GPIOF13,输出,上拉
	REG_GPIOF_PUR |= (1<<13);
	REG_GPIOF_DDR |= (1<<13);
	REG_GPIOF_PER &= ~(1<<13);
	//GPIOE8,输入,不上拉
	REG_GPIOE_PUR &= ~(1<<8);
	REG_GPIOE_DDR &= ~(1<<8);
	REG_GPIOE_PER &= ~(1<<8);
	//GPIOC9,输出,上拉
	REG_GPIOC_PUR |= (1<<9);
	REG_GPIOC_DDR |= (1<<9);
	REG_GPIOC_PER &= ~(1<<9);
	//GPIOC10,输出,上拉
	REG_GPIOC_PUR |= (1<<10);
	REG_GPIOC_DDR |= (1<<10);
	REG_GPIOC_PER &= ~(1<<10);
	
	REG_GPIOF_DR &= ~(1<<12); //165 Part1 output clock
	REG_GPIOC_DR &= ~(1<<10); //165 Part1 output clock
	
	REG_GPIOF_DR &= ~(1<<13); //165 Part1 Load Begin
	REG_GPIOC_DR &= ~(1<<9);  //165 Part1 Load Begin
	
	/********************* 74HC595 ************* */
	VarOutputData0 = LibVar74HC595U4002;
	VarOutputData0 = VarOutputData0<<8;
	VarOutputData0 += LibVar74HC595U4005;
	
	VarOutputData1 = LibVar74HC595U4001;
	
	VarOutputData2 = LibVar74HC595U4003;
	VarOutputData2 = VarOutputData2<<8;
	VarOutputData2 += LibVar74HC595U4004;	
	//GPIOA13
	REG_GPIOA_PUR |= (1<<13);
	REG_GPIOA_DDR |= (1<<13);
	REG_GPIOA_PER &= (~(1<<13));
	//GPIOE2
	REG_GPIOE_PUR |= (1<<2);
	REG_GPIOE_DDR |= (1<<2);
	REG_GPIOE_PER &= (~(1<<2));
	//GPIOE3
	REG_GPIOE_PUR |= (1<<3);
	REG_GPIOE_DDR |= (1<<3);
	REG_GPIOE_PER &= (~(1<<3));
	
	#if DefineHardwareNewVersion
		//GPIOe13
		REG_GPIOE_PUR |= (1<<13);
		REG_GPIOE_DDR |= (1<<13);
		REG_GPIOE_PER &= (~(1<<13));
	#else
		//GPIOC5
		REG_GPIOC_PUR |= (1<<5);
		REG_GPIOC_DDR |= (1<<5);
		REG_GPIOC_PER &= (~(1<<5));
	#endif
	
	//GPIOC6
	REG_GPIOC_PUR |= (1<<6);
	REG_GPIOC_DDR |= (1<<6);
	REG_GPIOC_PER &= (~(1<<6));
	//GPIOC7
	REG_GPIOC_PUR |= (1<<7);
	REG_GPIOC_DDR |= (1<<7);
	REG_GPIOC_PER &= (~(1<<7));
	//GPIOA10
	REG_GPIOA_PUR |= (1<<10);
	REG_GPIOA_DDR |= (1<<10);
	REG_GPIOA_PER &= (~(1<<10));
	//GPIOA11
	REG_GPIOA_PUR |= (1<<11);
	REG_GPIOA_DDR |= (1<<11);
	REG_GPIOA_PER &= (~(1<<11));
	//GPIOA12
	REG_GPIOA_PUR |= (1<<12);
	REG_GPIOA_DDR |= (1<<12);
	REG_GPIOA_PER &= (~(1<<12));
	
	/* ************** 置初值 ************** */
	
	REG_GPIOF_DR |= (1<<13);  //165 Part1 Load end
	REG_GPIOC_DR |= (1<<9);   //165 Part1 Load end
	
	REG_GPIOA_DR &= ~(1<<13); //595 Part0 Data=0
	REG_GPIOE_DR &= ~(1<<2);  //595 Part0 LatchClk=0
	REG_GPIOE_DR &= ~(1<<3);  //595 Part0 ShiftClk=0
	#if DefineHardwareNewVersion
		REG_GPIOE_DR &= ~(1<<13);  //595 Part1 Data=0
	#else
		REG_GPIOC_DR &= ~(1<<5);   //595 Part1 Data=0
	#endif
	REG_GPIOC_DR &= ~(1<<6);  //595 CPart1 LatchClk=0
	REG_GPIOC_DR &= ~(1<<7);  //595 Part1 ShiftClk=0
	REG_GPIOA_DR &= ~(1<<10); //595 Part2 Data=0
	REG_GPIOA_DR &= ~(1<<11); //595 Part2 LatchClk=0
	REG_GPIOA_DR &= ~(1<<12); //595 Part2 ShiftClk=0	
		
	/* ************** 输出 *************** */
	for(i=0;i<16;i++)
	{
		VarGetDataPart1 = VarGetDataPart1<<1;
		VarGetDataPart2 = VarGetDataPart2<<1;
		
		if(REG_GPIOC_DR & (1<<8)){VarGetDataPart1 |= 0x0001;}else{VarGetDataPart1 &= ~(1<<0);}
		if(REG_GPIOE_DR & (1<<8)){VarGetDataPart2 |= 0x0001;}else{VarGetDataPart2 &= ~(1<<0);}
		
		REG_GPIOF_DR &= ~(1<<12);
		REG_GPIOC_DR &= ~(1<<10);
		
		REG_GPIOE_DR &= ~(1<<3);
		REG_GPIOC_DR &= ~(1<<7);
		REG_GPIOA_DR &= ~(1<<12);
		
		if(VarOutputData0 & 0x8000){REG_GPIOA_DR |= (1<<13);}else{REG_GPIOA_DR &= ~(1<<13);}
		
		#if DefineHardwareNewVersion
			if(VarOutputData1 & 0x8000){REG_GPIOE_DR |= (1<<13);}else{REG_GPIOE_DR &= ~(1<<13);}
		#else
			if(VarOutputData1 & 0x8000){REG_GPIOC_DR |= (1<<5);}else{REG_GPIOC_DR &= ~(1<<5);}
		#endif
		
		if(VarOutputData2 & 0x8000){REG_GPIOA_DR |= (1<<10);}else{REG_GPIOA_DR &= ~(1<<10);}
				
		REG_GPIOF_DR |= (1<<12);
		REG_GPIOC_DR |= (1<<10);
		
		REG_GPIOE_DR |= (1<<3);
		REG_GPIOC_DR |= (1<<7);
		REG_GPIOA_DR |= (1<<12);
		
		VarOutputData0 = VarOutputData0<<1;
		VarOutputData1 = VarOutputData1<<1;
		VarOutputData2 = VarOutputData2<<1;
	}
	//结束
	REG_GPIOA_DR |= (1<<13);
	REG_GPIOE_DR |= (1<<2);
	REG_GPIOE_DR |= (1<<3);
	#if DefineHardwareNewVersion
		REG_GPIOE_DR |= (1<<13);
	#else
		REG_GPIOC_DR |= (1<<5);
	#endif
	REG_GPIOC_DR |= (1<<6);
	REG_GPIOC_DR |= (1<<7);
	REG_GPIOA_DR |= (1<<10);
	REG_GPIOA_DR |= (1<<11);
	REG_GPIOA_DR |= (1<<12);
		
	LibVar74HC165U6004 = (unsigned char)(VarGetDataPart1>>8);
	LibVar74HC165U6005 = (unsigned char)VarGetDataPart1;
	LibVar74HC165U6011 = (unsigned char)(VarGetDataPart2>>8);
	LibVar74HC165U6012 = (unsigned char)VarGetDataPart2;
}
/* ******************************************************
** 函数名称:LibFunPower12vEnable
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibSystem12vOutput(unsigned char Command)
{
	REG_GPIOF_PUR |= (1<<15);
	REG_GPIOF_DDR |= (1<<15);
	REG_GPIOF_PER &= ~(1<<15);
	if(Command>0)
	{
		REG_GPIOF_DR  &= ~(1<<15);
	}
	else
	{
		REG_GPIOF_DR  |= (1<<15);
	}
}
/* ******************************************************
** 函数名称:LibIrqaEnable
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibIrqaEnable(void)
{
	REG_ITCN_IPR2 &= ~(3<<0);
	REG_ITCN_IPR2 |= (1<<1);
}
/* ******************************************************
** 函数名称:LibIrqaDisable
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibIrqaDisable(void)
{
	REG_ITCN_IPR2 &= ~(3<<0);
}
/* ******************************************************
** 函数名称:LibIrqaEnable
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibIrqbEnable(void)
{
	REG_ITCN_IPR2 &= ~(3<<2);
	REG_ITCN_IPR2 |= (1<<2);
}
/* ******************************************************
** 函数名称:LibIrqaDisable
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibIrqbDisable(void)
{
	REG_ITCN_IPR2 &= ~(3<<2);
}
/* ******************************************************
** 函数名称:LibSystemRestart
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibSystemRestart(void)
{
	LibWatchDogDisable();
	LibWatchDogInit(1);
	while(1)
	{
		;
	}
}
/* ******************************************************
** 函数名称:LibSystemSleep
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibSystemSleep(void)
{	
	asm(STOP);
	while(1)
	{
		;
	}
}
/* ******************************************************
** 函数名称:LibSystemSleep
** 功能描述:
** 传入参数:
** 返回数据: 
** *************************************************** */
void LibSystemDelay1MS(UINT16 Count)
{
	UINT16 j;
	for(;Count>0;Count--)
	{
		for(j=0;j<1470;j++)
		{
			;
		}
	}
}
/* *************************************************************** 
** File End
** ************************************************************ */
