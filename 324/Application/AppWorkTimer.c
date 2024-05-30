#include "AppVar.h"
#include "AppFun.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:FunSysWorkTimeCompute
** 功能描述:工作小时计算与清零
** 传入参数:无
** 返回参数:无
** *************************************************** */
void FunSysWorkTimeCompute(void)
{
	UINT8 VarStartBool,temp_uchar,VarBool_1,VarBool_2;
	UINT32 Password_1,UlongTemp_1,UlongTemp_2,UlongTemp_3;
	//发动机一次启机工作时间计算，单位:S
	if(VarEngineSpeedNow<400)
	{
		 VarStartBool= 0;
	}
	else
	{
		VarStartBool = 1;
		VarEngineStarted = 1;
	}
	if(LibTimer(8,VarStartBool,1000,1))
	{
		VarEngineWorkTime1S++;
		//电磁比例阀异常时间计算
		if(VarValveCurrentNow>700)
		{
			if(VarValveErrorTime1S<0xFFFF)
				VarValveErrorTime1S++;
		}
		else
			VarValveErrorTime1S=0;
		//机油压力低时间累加
		if(VarCanEngineOilPreAlarm>0)
		{
			if(VarEngineWorkErrorTime1S<0xFF)
			{
				VarEngineWorkErrorTime1S++;
			}
		}
		else
		{
			VarEngineWorkErrorTime1S=0;
		}
	}
	//时间转化
	if(VarEngineWorkTime1S>59)
	{
		VarEngineWorkTime1M++;
		VarEngineWorkTime1S=0;
		if(VarEngineWorkTime1M%6 == 0) //每隔6分钟，工作小时写入Flash
		{
			VarFlashHourNeedSaveMainFlag = 1;
			VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
			VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
		}
	}
	if(VarEngineWorkTime1M>59)
	{
		VarEngineWorkTime1H++;
		VarEngineWorkTime1M=0;
		//防止写Flash时无转速信号发送，导致发动机转速不稳，改为断电存储
		/*
		if( (VarEngineWorkTime1H<1000)||((VarEngineWorkTime1H%20==2)&&(VarEngineWorkTime1H>1000)) )
		{
			VarFlashHourNeedSaveMainFlag=1;
		}
		*/
	}
	VarBool_1 = LibTimerTon(4,VanEngineTimeSetPSDSendFlag,2000,&UlongTemp_1);//持续2S
	if(VarBool_1>0)
	{	
		VanEngineTimeSetPSDSendFlag = 0;
		VanEngineTimeSetPSDoKFlag=0;
		LibTimerTon(4,0,2000,&UlongTemp_1);
		//判断小时计设置密码是否正确
		temp_uchar = FunSystemPasswordComput(3,&Password_1,VarEngineWorkTime1H,VarEngineWorkTime1M,VarCanExcavatorId);
		if(temp_uchar==0)
		{
			if(VarCanEngineTimeSetPSD==Password_1)
			{
				VanEngineTimeSetPSDoKFlag=1;//发动机工作时间设置密码正确
			}
			else
			{
				VanEngineTimeSetPSDoKFlag=0;
			}
		}
	}
	VarBool_1 = LibTimerTof(9,VanEngineTimeSetPSDSendFlag,60000,&UlongTemp_3);//60S内须设置小时计时间
	if(!VarBool_1)
	{
		VanEngineTimeSetPSDoKFlag=0;
	}
	VarBool_2 = LibTimerTon(8,VarCanEngineTimeSetFlag,2000,&UlongTemp_2);//时间设置发送持续2S
	if((VanEngineTimeSetPSDoKFlag>0)&&(VarBool_2>0))
	{
		VarCanEngineTimeSetPSDoK=0;
		VarEngineWorkTime1H = VarCanEngineTimeSetHour;
		VarFlashHourNeedSaveMainFlag = 1;//.......................test,201303025
		VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
		VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
		VanEngineTimeSetPSDoKFlag=0;
	}
}
/* *************************************************************** 
** File End
** ************************************************************ */
