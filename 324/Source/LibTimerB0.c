#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibTimerGet1S
** 功能描述:返回系统计时
** 传入参数:无
** 返回参数:系统计时器1S时间
** *************************************************** */
UINT32 LibTimerGet1S(void)
{
	UINT32 VarTempUlong;
	LibTimerB0InterruptDisable();
	VarTempUlong = LibVarTimer1MS/1000;
	LibTimerB0InterruptEnable();
	return VarTempUlong;
}
/* ******************************************************
** 函数名称:LibTimerGet1MS
** 功能描述:返回系统计时
** 传入参数:无
** 返回参数:系统计时器1MS时间
** *************************************************** */
UINT32 LibTimerGet1MS(void)
{
	UINT32 VarTempUlong;
	LibTimerB0InterruptDisable();
	VarTempUlong = LibVarTimer1MS;
	LibTimerB0InterruptEnable();
	return VarTempUlong;
}
/* ******************************************************
** 函数名称:LibFunTimerB0InterruptDisable
** 功能描述:禁止TimerB0中断
** *************************************************** */
void LibTimerB0InterruptDisable(void)
{
	REG_TIMERB0_SCR &= ~(1<<14);
}
/* ******************************************************
** 函数名称:LibFunTimerA0InterruptEnable
** 功能描述:允许TimerB0中断
** *************************************************** */
void LibTimerB0InterruptEnable(void)
{
	REG_TIMERB0_SCR |= (1<<14);
}
/* ******************************************************
** 函数名称:LibFunTimerB0Init
** 功能描述:TimerA0初始化,1MS中断
** *************************************************** */
void LibTimerB0Init(void)
{
	REG_SIM_PCE |= (1<<7);
	REG_TIMERB0_CTRL = 0x20;
	REG_TIMERB0_SCR = 0x00;
	REG_TIMERB0_LOAD = 0x00;
	REG_TIMERB0_CMP1 = (60000-26);   // 1ms
	REG_TIMERB0_CMPLD1 = (60000-26);
	REG_TIMERB0_COMSCR = 0x41;
	REG_TIMERB0_CTRL |= (0x08<<9);   // timerCLK = IPBUS/1
	REG_TIMERB0_CNTR = 0x00;
	REG_TIMERB0_CTRL |= (0x01<<13);
	REG_TIMERB0_SCR |= (1<<14);
	REG_ITCN_IPR7 |= (3<<6);
}
/* *************************************************************** 
** File End
** ************************************************************ */
