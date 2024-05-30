#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibFunTimerB1InterruptDisable
** 功能描述:禁止TimerA0中断
** *************************************************** */
void LibTimerB1InterruptDisable(void)
{
	REG_TIMERB1_SCR &= ~(1<<14);
}
/* ******************************************************
** 函数名称:LibFunTimerB1InterruptEnable
** 功能描述:允许TimerB1中断
** *************************************************** */
void LibTimerB1InterruptEnable(void)
{
	REG_TIMERB1_SCR |= (1<<14);
}
/* ******************************************************
** 函数名称:LibFunTimerB1Init
** 功能描述:TimerB1初始化
** *************************************************** */
void LibTimerB1Init(void)
{
	REG_SIM_PCE |= (1<<7);
	REG_TIMERB1_CTRL = 0x20;
	REG_TIMERB1_SCR = 0x00;
	REG_TIMERB1_LOAD = 0x00;
	REG_TIMERB1_CMP1 = (15000-20);        // 0.25ms
	REG_TIMERB1_CMPLD1 = (15000-20);
	REG_TIMERB1_COMSCR = 0x41;
	REG_TIMERB1_CTRL |= (0x08<<9);
	REG_TIMERB1_CNTR = 0x00;
	REG_TIMERB1_CTRL |= (0x01<<13);
	REG_TIMERB1_SCR |= (1<<14);
	REG_ITCN_IPR7 &= ~(3<<8);
	REG_ITCN_IPR7 |= (1<<8);	
}
/* *************************************************************** 
** File End
** ************************************************************ */
