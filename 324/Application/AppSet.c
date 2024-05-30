#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
/**************************************************************
**函数名：Fun_Set_Loop()
**功能描述：标定油门表盘与各档位下对应的转速值
**传入参数：无
**输出参数：无
**************************************************************/
void FunDialSpeedSet(void)
{
	UINT8 VarAccDialPosiSetSort;
	//油门表盘最小值、最大值标定
	if((VarCanAccDialPosiMinSet==1)&&(VarCanAccDialPosiMaxSet==0))
	{
		VarAccDialPosiSetSort=1;//标定最小值
	}
	else if((VarCanAccDialPosiMinSet==0)&&(VarCanAccDialPosiMaxSet==1))
	{
		VarAccDialPosiSetSort=2;//标定最大值
	}
	else
	{
		VarAccDialPosiSetSort=0;
	}
	VarCanAccDialSetCommand=VarAccDialPosiSetSort;
	if(VarAccDialPosiSetSort>0)
	{
		FunDialSet(VarAccDialPosiSetSort);	
	}
	VarDialSetSortLast=VarAccDialPosiSetSort;
	VarCanAccDialSetCommandLast=VarCanAccDialSetCommand;
	//取驾驶员设定档位, 运算后范围0-9
	VarDialGrade = FunDialGradeCal(VarAccDialPosiMin,VarAccDialPosiMax);//VarAccDialPosiMax
}
 /**************************************************************
**函数名：Fun_Set_Acc_Dial_Max()
**功能描述：标定油门表盘的最大档位或最小档位
**传入参数：Set_Sort— ==1：标定最小档位./==2：标定最大档位
**输出参数：无
**************************************************************/
void FunDialSet(UINT8 Set_Sort)
{
	//无标定命令，则不进行标定
	if(VarCanAccDialSetCommand==0)
	{
		VarAccDialPosiSetting=0;
	}
	//上升沿触发进行标定，且当前处于非标定状态，上电时间超过5S
	if(	(VarCanAccDialSetCommand>0)&&
		(VarCanAccDialSetCommandLast==0)&&
		(VarAccDialPosiSetting==0)&&
    	(LibTimerGet1S()-5>0 ))
	{
		VarAccDialPosiSetting=1;
	}
	//正在设置模式中
	if(VarAccDialPosiSetting==1)
	{
		if(Set_Sort==1)
		{
			VarAccDialPosiMin=VarAccDialPosiNow;
		}
		else if(Set_Sort==2)
		{
			VarAccDialPosiMax=VarAccDialPosiNow;
		}
		VarFlashSysDateMasterNeedSaveFlag = 1;//数据需要保存
		VarFlashSysDateBackupNeedSaveFlag = 1;
		VarAccDialPosiSetting=0;//标定完毕
		VarDialSetSortLast=Set_Sort;
		VarAccDialPosiSetTimeLast=LibTimerGet1S();
	}
}
/**************************************************************
**函数名：Fun_Dial_Grade_Cal()
**功能描述：标定油门表盘的档位
**传入参数：Dial_Limit_1—油门表盘第一档值；Dial_Limit_2—油门表盘第十档值；
**输出参数：当前档位值
**************************************************************/
UINT8 FunDialGradeCal(UINT16 Dial_Limit_1,UINT16 Dial_Limit_2)
{
	UINT8 Dial_Grade_Now;
	UINT16 Dial_Grade_Band;
	if(LibAbsUint16(VarAccDialPosiNow,VarAccDialPosiLast)<15)
	return(VarDialGrade);
	VarAccDialPosiLast=VarAccDialPosiNow;
	
	if(Dial_Limit_1<Dial_Limit_2)
	{
		Dial_Grade_Band=(UINT16)( (Dial_Limit_2-Dial_Limit_1)/18 );
		if(VarAccDialPosiNow<(Dial_Limit_1+Dial_Grade_Band))
		{
			Dial_Grade_Now=1;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+3*Dial_Grade_Band))
		{
			Dial_Grade_Now=2;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+5*Dial_Grade_Band))
		{
			Dial_Grade_Now=3;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+7*Dial_Grade_Band))
		{
			Dial_Grade_Now=4;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+9*Dial_Grade_Band))
		{
			Dial_Grade_Now=5;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+11*Dial_Grade_Band))
		{
			Dial_Grade_Now=6;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+13*Dial_Grade_Band))
		{
			Dial_Grade_Now=7;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+15*Dial_Grade_Band))
		{
			Dial_Grade_Now=8;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+17*Dial_Grade_Band))
		{
			Dial_Grade_Now=9;
		}
		else 
		{
			Dial_Grade_Now=10;
		}
	}
	else 
	{
		Dial_Grade_Band=(UINT16)( (Dial_Limit_1-Dial_Limit_2)/18);
		if(VarAccDialPosiNow>(Dial_Limit_1-Dial_Grade_Band))
		{
			Dial_Grade_Now=1;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-3*Dial_Grade_Band))
		{
			Dial_Grade_Now=2;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-5*Dial_Grade_Band))
		{
			Dial_Grade_Now=3;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-7*Dial_Grade_Band))
		{
			Dial_Grade_Now=4;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-9*Dial_Grade_Band))
		{
			Dial_Grade_Now=5;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-11*Dial_Grade_Band))
		{
			Dial_Grade_Now=6;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-13*Dial_Grade_Band))
		{
			Dial_Grade_Now=7;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-15*Dial_Grade_Band))
		{
			Dial_Grade_Now=8;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-17*Dial_Grade_Band))
		{
			Dial_Grade_Now=9;
		}
		else 
		{
			Dial_Grade_Now=10;
		}
	}	
	return(Dial_Grade_Now);
}
