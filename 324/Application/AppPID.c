#include "AppVar.h"
#include "AppFun.h"

/* ******************************************************
** 函数名称:FunPID
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void FunClearPIDparams(PIDparams *Params)
{
	(*Params).Result = 0;
	(*Params).PosLimit = 0;
	(*Params).NegLimit = 0;
	(*Params).E = 0;
	(*Params).E1 = 0;
	(*Params).E2 = 0;
	(*Params).Kp = 0;
	(*Params).Ki = 0;
	(*Params).Kd = 0;
	(*Params).Count = 0;
}
/* ******************************************************
** 函数名称:FunPID
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
INT32 FunPID(INT32 MeasPoint,INT32 SetPoint,PIDparams *Params,INT32 Error,UINT32 Interval,BOOL Enable)
{	
	(*Params).Count++;
	if((*Params).Count < Interval)
	{
		return (*Params).Result;
	}
	if(Enable)
	{
		(*Params).E = SetPoint - MeasPoint;
		if((*Params).E<Error && (*Params).E>-Error)
		{
			(*Params).E = 0;
		}
		
		(*Params).Result += (*Params).Kp*((*Params).E-(*Params).E1) + (*Params).Ki*(*Params).E + (*Params).Kd*((*Params).E-2*(*Params).E1+(*Params).E2);
		
		if( (*Params).Result > (*Params).PosLimit )
		{
			(*Params).Result = (*Params).PosLimit;
		}
		else if( (*Params).Result < (*Params).NegLimit )
		{
			(*Params).Result = (*Params).NegLimit;
		}
		
		(*Params).E2 = (*Params).E1;
		(*Params).E1 = (*Params).E;
	}
	else
	{
		FunClearPIDparams(Params);
	}
	return (*Params).Result;
}
/* *************************************************************** 
** File End
** ************************************************************ */
