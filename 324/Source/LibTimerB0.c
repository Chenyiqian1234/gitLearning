#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** ��������:LibTimerGet1S
** ��������:����ϵͳ��ʱ
** �������:��
** ���ز���:ϵͳ��ʱ��1Sʱ��
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
** ��������:LibTimerGet1MS
** ��������:����ϵͳ��ʱ
** �������:��
** ���ز���:ϵͳ��ʱ��1MSʱ��
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
** ��������:LibFunTimerB0InterruptDisable
** ��������:��ֹTimerB0�ж�
** *************************************************** */
void LibTimerB0InterruptDisable(void)
{
	REG_TIMERB0_SCR &= ~(1<<14);
}
/* ******************************************************
** ��������:LibFunTimerA0InterruptEnable
** ��������:����TimerB0�ж�
** *************************************************** */
void LibTimerB0InterruptEnable(void)
{
	REG_TIMERB0_SCR |= (1<<14);
}
/* ******************************************************
** ��������:LibFunTimerB0Init
** ��������:TimerA0��ʼ��,1MS�ж�
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
