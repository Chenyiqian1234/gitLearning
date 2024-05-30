#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "MC56F8367Reg.h"
#include "LibFunDefine.h"
#include "AppVar.h"

/* *************************************************************** 
** main function
** ************************************************************ */
INT16 main(void)
{
	UINT8 i;
	
	asm(bfclr  #0x0300,SR);
	
	for(i=0;i<80;i++)
	{
		LibVarPinoutsSelect[i] = 0;
		LibPinoutsSelect(i,0);
	}
	for(i=0;i<4;i++)
	{
		LibSetValueDOL(i,1);
	}
	for(i=0;i<28;i++)
	{
		LibSetValueDOH(i,0);
	}
	for(i=0;i<40;i++)
	{
		LibVarTimer[i] = 0;
		LivVarTimeTriggerLast[i] = 0;
		LibVarTimeSignalLast[i] = 0;
		LibVarTimeEdgeStart[i] = 0;
	}
	for(i=0;i<14;i++)
	{
		LibVarCan0BufferMode[i] = 0;
		LibVarCan1BufferMode[i] = 0;
	}
	LibIrqaDisable();
	LibIrqbDisable();
	LibWatchDogDisable();
	LibPwmInit(0,250);
	LibPwmInit(1,250);
	LibSystem5vOutput(0);
	LibSystem12vOutput(0);
	LibTimerB0Init();
	LibTimerB1Init();
	LibTimerB2Init();
	LibPiInit();
	LibMcuAdcInit();
	LibFunSpi0Init();
	LibSpi1Init();
	LibSciInit(115200);
	//LibEepromWriteStatus(0x0C);
	
	LibVarSciStartEchoCount = 1;
	LibSciSendString((UINT8 *)"Hello,SUNWARD!\r\n\0");
	
	AppInit();
	
	if(LibVarPinoutsSelect[57]==2 || LibVarPinoutsSelect[64]==2)
	{
		LibDecInit();
	}
	
	LibCan0Init(250);
	LibCan1Init(250);
	
	LibVarCan0IMaskInit = REG_CAN0_FCIMASK1;
	LibVarCan1IMaskInit = REG_CAN1_FCIMASK1;
	
	if(LibVarPinoutsSelect[60]==2 || LibVarPinoutsSelect[61]==2)
	{
		LibTimerB2Init();
	}
	
	while(1)
	{
		//LibSciSendLoop();
		if(LibVarSciStartEchoCount<=4)
		{
			if( LibVarTimer1MS >= LibVarSciStartEchoLastTime1MS+500 )
			{
				LibVarSciStartEchoLastTime1MS = LibVarTimer1MS;
				LibVarSciStartEchoCount++;
				LibSciSendString((UINT8 *)"Hello,SUNWARD!\r\n\0");
			}
		}
		LibSystemSerialIO();
		LibPiComputFrequency();
		LibWatchDogFeed();
		AppMain();
		//CAN
		if(LibVarCan0NoIntTimer1Ms>30000 || LibVarCan0NeedInit>0)
		{
			LibVarCan0NoIntTimer1Ms = 0;
			LibVarCan0NeedInit = 0;	
			LibCan0Init(250);
			LibVarCan0InitCount++;
		}
		if(LibVarCan1NoIntTimer1Ms>30000 || LibVarCan1NeedInit>0)
		{
			LibVarCan1NoIntTimer1Ms = 0;
			LibVarCan1NeedInit = 0;
			LibCan1Init(250);
			LibVarCan1InitCount++;
		}
		REG_CAN0_FCIMASK1 = LibVarCan0IMaskInit;
		REG_CAN1_FCIMASK1 = LibVarCan1IMaskInit;
		//ADC
		if(LibVarMcuAdcaNoIntTimer1MS>250 || LibVarMcuAdcbNoIntTimer1MS>250)
		{
			LibVarMcuAdcaNoIntTimer1MS = 0;
			LibVarMcuAdcbNoIntTimer1MS = 0;
			LibMcuAdcInit();
		}
		//SPI
		LibSpi1Restart();
		//TON TOF
		for(i=0;i<32;i++)
		{
			if((LibVarTonEnable&(1L<<i))==0)
			{
				LibVarTonEt[i] = 0;;
			}
			if((LibVarTofEnable&(1L<<i))==0)
			{
				LibVarTofEt[i] = 0;;
			}
		}
	}
	return(0);
}
/* *************************************************************** 
** File End
** ************************************************************ */
