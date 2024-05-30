#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibTimerTof
** 功能描述:定时器
** 传入参数:
** 返回数据: 
** *************************************************** */
BOOL LibTimerTof(UINT8 Channal,BOOL In,UINT32 Pt,UINT32 *Et)
{
	UINT8 Q=1;
	if(Channal<32)
	{
		if(In>0)
		{
			Q = 1;
			LibVarTofEnable &= ~(1L<<Channal);
			LibVarTofEt[Channal] = 0;
		}
		else
		{
			if(LibVarTofEt[Channal]>=Pt)
			{
				Q= 0;
				LibVarTofEt[Channal] = Pt;
			}
			LibVarTofEnable |= (1L<<Channal);
		}
		*Et = LibVarTofEt[Channal];
	}
	return Q;
}
/* ******************************************************
** 函数名称:LibTimerTon
** 功能描述:定时器
** 传入参数:
** 返回数据: 
** *************************************************** */
BOOL LibTimerTon(UINT8 Channal,BOOL In,UINT32 Pt,UINT32 *Et)
{
	UINT8 Q=0;
	if(Channal<32)
	{
		if(In==0)
		{
			Q = 0;
			LibVarTonEnable &= ~(1L<<Channal);
			LibVarTonEt[Channal] = 0;
		}
		else
		{
			if(LibVarTonEt[Channal]>=Pt)
			{
				Q= 1;
				LibVarTonEt[Channal] = Pt;
			}
			LibVarTonEnable |= (1L<<Channal);
		}
		*Et = LibVarTonEt[Channal];
	}
	return Q;
}
/* ******************************************************
** 函数名称:LibTimer
** 功能描述:定时器
** 传入参数:
** 返回数据: 
** *************************************************** */
BOOL LibTimer(UINT8 Channal,BOOL Trigger,UINT32 Time,BOOL Signal)
{
	UINT8 Result=0;
	if(Channal<40)
	{
		switch(Trigger)
		{
			case 0:
				//低电平触发
				if(LivVarTimeTriggerLast[Channal]!=0 || Signal!=0)
				{
					LibVarTimer[Channal] = 0;
				}
				Result = 0;
				while(LibVarTimer[Channal]>=Time)
				{
					LibVarTimer[Channal] -= Time;
					Result = 1;
				}
				break;
			case 1:
				//高电平触发
				if(LivVarTimeTriggerLast[Channal]!=1 || Signal!=1)
				{
					LibVarTimer[Channal] = 0;
				}
				Result = 0;
				while(LibVarTimer[Channal]>=Time)
				{
					LibVarTimer[Channal] -= Time;
					Result = 1;
				}
				break;
			case 2:
				//上升沿触发
				if(LivVarTimeTriggerLast[Channal]!=2)
				{
					LibVarTimer[Channal] = 0;
					LibVarTimeEdgeStart[Channal] = 0;
				}
				
				if(LibVarTimeEdgeStart[Channal]==0)
				{
					LibVarTimer[Channal] = 0;
				}
				
				if(Signal>0 && LibVarTimeSignalLast[Channal]==0)
				{
					LibVarTimeEdgeStart[Channal] = 1;
				}
				
				Result = 0;
				while(LibVarTimer[Channal]>=Time)
				{
					LibVarTimer[Channal] -= Time;
					LibVarTimeEdgeStart[Channal] = 0;
					Result = 1;
				}
				break;
			case 3:
				//下降沿
				if(LivVarTimeTriggerLast[Channal]!=3)
				{
					LibVarTimer[Channal] = 0;
					LibVarTimeEdgeStart[Channal] = 0;
				}
				
				if(LibVarTimeEdgeStart[Channal]==0)
				{
					LibVarTimer[Channal] = 0;
				}
				
				if(Signal==0 && LibVarTimeSignalLast[Channal]>0)
				{
					LibVarTimeEdgeStart[Channal] = 1;
				}
				
				Result = 0;
				while(LibVarTimer[Channal]>=Time)
				{
					LibVarTimer[Channal] -= Time;
					LibVarTimeEdgeStart[Channal] = 0;
					Result = 1;
				}
				break;				
			default:
				Result = 0;
		}
		LivVarTimeTriggerLast[Channal] = Trigger;
		LibVarTimeSignalLast[Channal] = Signal;		
	}
	return Result;
}
/* *************************************************************** 
** File End
** ************************************************************ */
