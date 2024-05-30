#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"

/* ******************************************************
** ��������:LibFunTimerB2InterruptDisable
** ��������:��ֹTimerB2�ж�
** *************************************************** */
void LibTimerB2InterruptDisable(void)
{
	REG_TIMERB2_SCR &= ~(1<<14);
}
/* ******************************************************
** ��������:LibFunTimerB2InterruptEnable
** ��������:����TimerB2�ж�
** *************************************************** */
void LibTimerB2InterruptEnable(void)
{
	REG_TIMERB2_SCR |= (1<<14);
}
/* ******************************************************
** ��������:LibFunTimerB2Init
** ��������:TimerB2��ʼ�� 1.1ms
** *************************************************** */
void LibTimerB2Init(void)
{
	REG_SIM_PCE |= (1<<7);
	REG_TIMERB2_CTRL = 0x20;
	REG_TIMERB2_SCR = 0x00;
	REG_TIMERB2_LOAD = 0x00;
	REG_TIMERB2_CMP1 = 65535;
	REG_TIMERB2_CMPLD1 = 65535;
	REG_TIMERB2_COMSCR = 0x41;
	REG_TIMERB2_CTRL |= (0x08<<9);
	REG_TIMERB2_CNTR = 0x00;
	REG_TIMERB2_CTRL |= (0x01<<13);
	REG_TIMERB2_SCR |= (1<<14);
	REG_ITCN_IPR7 &= ~(3<<10);
	REG_ITCN_IPR7 |= (1<<10);	
}
/* *************************************************************** 
** File End
** ************************************************************ */
