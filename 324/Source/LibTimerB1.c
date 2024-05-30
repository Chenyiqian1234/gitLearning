#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** ��������:LibFunTimerB1InterruptDisable
** ��������:��ֹTimerA0�ж�
** *************************************************** */
void LibTimerB1InterruptDisable(void)
{
	REG_TIMERB1_SCR &= ~(1<<14);
}
/* ******************************************************
** ��������:LibFunTimerB1InterruptEnable
** ��������:����TimerB1�ж�
** *************************************************** */
void LibTimerB1InterruptEnable(void)
{
	REG_TIMERB1_SCR |= (1<<14);
}
/* ******************************************************
** ��������:LibFunTimerB1Init
** ��������:TimerB1��ʼ��
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
