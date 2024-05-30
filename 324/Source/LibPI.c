#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** ��������:LibDecGetPosition
** ��������:��ȡ������Ŀ
** �������:
** ��������: 
** *************************************************** */
UINT32 LibDecGetPosition(UINT8 Channal)
{
	UINT32 Data=0;
	if(Channal==0)
	{
		//Data = (UINT32)REG_DEC0_UPOS;
		//Data= Data<<16;
		//Data += REG_DEC0_LPOS;
		Data = LibVarQD0Position;
	}
	else if(Channal==1)
	{
		Data = LibVarQD1Position;
	}
	return Data;
}
/* ******************************************************
** ��������:LibDecSetPosition
** ��������:���ü�����Ŀ
** �������:
** ��������: 
** *************************************************** */
void LibDecSetPosition(UINT8 Channal,UINT32 Data)
{
	if(Channal==0)
	{
		LibVarQD0Position = Data;
		//REG_DEC0_LPOS = (UINT16)(Data>>0);
		//REG_DEC0_UPOS = (UINT16)(Data>>16);
	}
	else if(Channal==1)
	{
		LibVarQD1Position = Data;
	}
}
/* ******************************************************
** ��������:LibDecInit
** ��������:��ת��������ʼ��
** �������:
** ��������: 
** *************************************************** */
void LibDecInit(void)
{
	REG_DEC0_DECCR = 2U;
	REG_DEC0_FIR = 10U;
	REG_DEC1_FIR = 0U;
	REG_SIM_PCE |= (1<<11)|(1<<10);
	REG_GPIOC_PER |= (1<<5)|(1<<4);
	REG_DEC0_UIR = 0U;
	REG_DEC0_LIR = 0U;
	REG_DEC0_DECCR = 512U;
}
/* ******************************************************
** ��������:LibFunPiSetSampleTime
** ��������:����PI����ʱ��
** �������:
** ��������: 
** *************************************************** */
UINT8 LibPiSetSampleTime(UINT8 Channal,UINT16 SampleTime)
{
	if(Channal<4)
	{
		if(SampleTime!=0)
		{
			SampleTime = SampleTime/10;
			SampleTime = SampleTime*10;
			LibVarPiSampleTimeMS[Channal] = SampleTime;
			if(LibVarPiSampleTimeMS[Channal]<10){LibVarPiSampleTimeMS[Channal]=10;}
			if(LibVarPiSampleTimeMS[Channal]>1000){LibVarPiSampleTimeMS[Channal]=1000;}
		}
		return 	0;
	}
	else
	{
		return 1;
	}	
}
/* ******************************************************
** ��������:LibFunPiReadFrequency
** ��������:��ȡPI�ź�Ƶ��ֵ
** �������:
** ��������: 
** *************************************************** */
UINT16 LibPiReadFrequency(UINT8 Channal)
{
	if(Channal<4)
	{
		return LibVarPiFrequency[Channal];
	}
	else
	{
		return 0;
	}
}
/* ******************************************************
** ��������:LibFunPiComputFrequency
** ��������:����PI�ź�Ƶ��ֵ
** �������:
** ��������: 
** *************************************************** */
void LibPiComputFrequency(void)
{
	UINT8 i,j;
	UINT32 VarData;	
	UINT16 VarSingalNum;	
	if(LibVarPiUpdateFlag>0)
	{
		LibVarPiUpdateFlag = 0;
		for(j=0;j<4;j++)
		{
			VarSingalNum = LibVarPiSampleTimeMS[j]/10;
			if(VarSingalNum<1){VarSingalNum = 1;}
			if(VarSingalNum>100){VarSingalNum = 100;}
			VarData = 0;
			LibTimerB0InterruptDisable();
			for(i=0;i<VarSingalNum;i++)
			{
				VarData += 	LibVarPiOrgData[j][i];
			}
			LibTimerB0InterruptEnable();
			VarData = VarData*1000;
			VarData = VarData/(VarSingalNum*10);
			LibVarPiFrequency[j] = (UINT16)VarData;		
		}
	}	
}
/* ******************************************************
** ��������:LibFunPiReset
** ��������:��ʼ��PI
** �������:
** ��������: 
** *************************************************** */
UINT8 LibPiReset(UINT8 Channal)
{
	#if DefineHardwareNewVersion
		if(Channal==0)
		{
			REG_TIMERA0_CNTR = 0;
			LibVarPiOverFlow[0] = 0;
		}
		else if(Channal==1)
		{
			REG_TIMERD0_CNTR = 0;
			LibVarPiOverFlow[1] = 0;
		}
		else if(Channal==2)
		{
			REG_TIMERD1_CNTR = 0;
			LibVarPiOverFlow[2] = 0;
		}
		else if(Channal==3)
		{
			REG_TIMERA1_CNTR = 0;
			LibVarPiOverFlow[3] = 0;
		}
		else
		{
			return 1;
		}
	#else
		if(Channal==0)
		{
			REG_TIMERD2_CNTR = 0;
			LibVarPiOverFlow[0] = 0;
		}
		else if(Channal==1)
		{
			REG_TIMERD0_CNTR = 0;
			LibVarPiOverFlow[1] = 0;
		}
		else if(Channal==2)
		{
			REG_TIMERD1_CNTR = 0;
			LibVarPiOverFlow[2] = 0;
		}
		else if(Channal==3)
		{
			REG_TIMERD3_CNTR = 0;
			LibVarPiOverFlow[3] = 0;
		}
		else
		{
			return 1;
		}
	#endif
	
	return 0;
}
/* ******************************************************
** ��������:LibFunPiInit
** ��������:��ʼ��PI
** �������:
** ��������: 
** *************************************************** */
void LibPiInit(void)
{
	#if DefineHardwareNewVersion
		//PI0:TIMERA0:TA0
		REG_TIMERA0_CTRL = 0;
		REG_TIMERA0_SCR = 0;
		REG_TIMERA0_COMSCR = 0;
		REG_TIMERA0_CNTR = 0;
		REG_TIMERA0_CTRL = 8192;
		LibVarPiOverFlow[0] = 0;
		//PI1:TIMERD0:TD0
		REG_TIMERD0_CTRL = 0;
		REG_TIMERD0_SCR = 0;
		REG_TIMERD0_COMSCR = 0;
		REG_TIMERD0_CNTR = 0;
		REG_TIMERD0_CTRL = 8192;
		LibVarPiOverFlow[1] = 0;
		//PI2:TIMERD1:TD1
		REG_TIMERD1_CTRL = 0;
		REG_TIMERD1_SCR = 0;
		REG_TIMERD1_COMSCR = 0;
		REG_TIMERD1_CNTR = 0;
		REG_TIMERD1_CTRL = 8704;
		LibVarPiOverFlow[2] = 0;
		//PI0:TIMERA1:TA1
		REG_TIMERA1_CTRL = 0;
		REG_TIMERA1_SCR = 0;
		REG_TIMERA1_COMSCR = 0;
		REG_TIMERA1_CNTR = 0;
		REG_TIMERA1_CTRL = 8704;
		LibVarPiOverFlow[3] = 0;
	#else
		//PI0:TIMERD2:TD2
		REG_TIMERD2_CTRL = 0;
		REG_TIMERD2_SCR = 0;
		REG_TIMERD2_COMSCR = 0;
		REG_TIMERD2_CNTR = 0;
		REG_TIMERD2_CTRL = 9216;
		LibVarPiOverFlow[0] = 0;
		//PI1:TIMERD0:TD0
		REG_TIMERD0_CTRL = 0;
		REG_TIMERD0_SCR = 0;
		REG_TIMERD0_COMSCR = 0;
		REG_TIMERD0_CNTR = 0;
		REG_TIMERD0_CTRL = 8192;
		LibVarPiOverFlow[1] = 0;
		//PI2:TIMERD1:TD1
		REG_TIMERD1_CTRL = 0;
		REG_TIMERD1_SCR = 0;
		REG_TIMERD1_COMSCR = 0;
		REG_TIMERD1_CNTR = 0;
		REG_TIMERD1_CTRL = 8704;
		LibVarPiOverFlow[2] = 0;
		//PI3:TIMERD3:TD3
		REG_TIMERD3_CTRL = 0;
		REG_TIMERD3_SCR = 0;
		REG_TIMERD3_COMSCR = 0;
		REG_TIMERD3_CNTR = 0;
		REG_TIMERD3_CTRL = 9728;
		LibVarPiOverFlow[3] = 0;
	#endif
}
/* *************************************************************** 
** File End
** ************************************************************ */
