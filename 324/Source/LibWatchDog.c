#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** ��������:LibFunWatchDogInit
** ��������:
** �������:
** ��������:
** *************************************************** */
void LibWatchDogInit(UINT16 OverflowTimeMS)
{
	UINT32 temp;
	REG_COP_COPCTL = 0;
	if(OverflowTimeMS<20)OverflowTimeMS=20;
	if(OverflowTimeMS>8000)OverflowTimeMS=8000;
	temp = OverflowTimeMS;
	temp *= 125;
	temp = temp/16 + 1;
	if(temp>0xFFFF)temp = 0xFFFF;
	REG_COP_COPTO = (UINT16)temp;
	REG_COP_COPCTL = (1<<1);	
}
/* ******************************************************
** ��������:LibFunWatchDogFeed
** ��������:
** �������:
** ��������:
** *************************************************** */
void LibWatchDogFeed(void)
{
	REG_COP_COPCTR = 0x5555;
	REG_COP_COPCTR = 0xAAAA;
}
/* ******************************************************
** ��������:LibFunWatchDogFeed
** ��������:
** �������:
** ��������:
** *************************************************** */
void LibWatchDogDisable(void)
{
	REG_COP_COPCTL = 0;
}
/* *************************************************************** 
** File End
** ************************************************************ */
