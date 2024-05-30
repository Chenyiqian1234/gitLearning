#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "swGpsPrivate.h"
#include "stdlib.h"
/* ***************************************************************
**
** 函数名称: FunControlGpsLock
** 功能描述: GPS相关控制
**
******************************************************************/
void FunControlGpsLock(void)
{
	BOOL Step3CountStart,Step3CountStop,TimeAvailabe_Judge=0,Time_Longer;
	UINT8 VarBool1,temp_uchar,VarBool2;
	UINT32 Password_1;
	UINT32 Ulong_Temp1,Ulong_Temp2;
	UINT32 TonGpsCanError_Et;
	UINT16 Year_1,Year_2,Month_1,Month_2,Day_1,Day_2,Hour_1,Hour_2,Days,Hours;
	UINT32 code_1_H=9999,code_2_H=765432,code_1_L=8888,code_2_L=6790;
	
	//使能初始化
	if(GPSLock_Enable_Initial==0)
	{
		GPSLock_All_Enable = 1;	
		GPSLock_Passive_Enable = 1;
		MonthNoSignalLock_Enable = 1;
		UncoverLock_Enable = 1;
		CANSignalLostLock_Enable = 1;
		SIMCardLostLock_Enable = 1;
		
		GPSLock_Enable_Initial = 1;
		VarFlashGpsDataMasterNeedSaveFlag=1;
		VarFlashGpsDataBackupNeedSaveFlag=1;		
	}
	
	
	//GPS锁车命令下发时，写入一次Flash
	if((VarCanGpsLockCommand_A != VarCanGpsLockCommandLast_A)||(VarCanGpsLockCommand_B != VarCanGpsLockCommandLast_B)
	||(VarCanGpsLockCommand_C != VarCanGpsLockCommandLast_C)||(VarCanGpsLockCommand_D != VarCanGpsLockCommandLast_D))	
	{
		VarFlashGpsDataMasterNeedSaveFlag=1;
		VarFlashGpsDataBackupNeedSaveFlag=1;
	}
	
	//A锁车
	if(	VarCanGpsLockCommand_A>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_A=TRUE;
	}
	else
	{
		VarGpsLockState_A = FALSE;//VarGpsLockWork_A
		VarGpsLockWork_A = FALSE;
	}
	VarCanGpsLockCommandLast_A = VarCanGpsLockCommand_A;
	//B锁车
	if(	VarCanGpsLockCommand_B>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_B=TRUE;
	}
	else
	{
		VarGpsLockState_B = FALSE;//VarGpsLockWork_B
		VarGpsLockWork_B = FALSE;
	}
	VarCanGpsLockCommandLast_B = VarCanGpsLockCommand_B;
	//C锁车
	if(	VarCanGpsLockCommand_C>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_C=TRUE;
	}
	else
	{
		VarGpsLockState_C = FALSE;//VarGpsLockWork_C
		VarGpsLockWork_C = FALSE;
	}
	VarCanGpsLockCommandLast_C = VarCanGpsLockCommand_C;
	//D锁车
	if(	VarCanGpsLockCommand_D>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_D=TRUE;
	}
	else
	{
		VarGpsLockState_D = FALSE;//VarGpsLockWork_D
		VarGpsLockWork_D = FALSE;
	}
	VarCanGpsLockCommandLast_D = VarCanGpsLockCommand_D;
	//10秒内心跳信号无变化，认为can总线故障，延时5分钟后锁车。
	//if(	VarCanGpsHeartBeatLast == VarCanGpsHeartBeat)	
	if(	VarCanGpsHeartBeat==0)
	{
		VarGpsCanNoBeat = 1;
	}
	else
	{
		VarGpsCanNoBeat = 0;	
	}
	VarGpsCanErrorState = LibTimerTon(9,VarGpsCanNoBeat,30000,&TonGpsCanError_Et);//30S
	if(VarGpsCanErrorState)
	{
		VarGpsCanBusError = TRUE;
	}
	else
	{
		VarGpsCanBusError = FALSE;
	}
	VarCanBusLockCommand = LibTimerTon(10,VarGpsCanBusError,30000,&VarGpsCanBusError_Et);//5min,3......	
	if((VarCanGpsCancel==0 && VarCanGpsUrgencyState==0)&&
	VarCanBusLockCommand>0
	)
	{
		
		VarCanBusLockState=1;
	}
	else
	{
		VarCanBusLockState=0;
	}
	if (VarCanGpsCancel==1 || VarCanGpsUrgencyState==1) VarGpsCanBusError = FALSE;
	
	
	//天线被拆延时20秒锁车
	VarCanAntennaCut = LibTimerTon(11,VarCanAntennaCutLockCommand,20000,&VarGpsAntennaCut_Et);
	if(VarCanAntennaCut>0 &&
	(VarCanGpsCancel==0 && VarCanGpsUrgencyState==0))
	{
		VarCanAntennaCutLockState=1;
	}
	else
	{
		VarCanAntennaCutLockState=0;
	}
	
	//拆盖即时锁车
	if(VarCanUncoverLockCommand>0 &&
	(VarCanGpsCancel==0 && VarCanGpsUrgencyState==0))
	{
		VarCanUncoverLockState=1;
	}
	else
	{
		VarCanUncoverLockState=0;
	}
	
	TimeAvailabe_Judge= IsTimeAvailable((ClockTime_Year+2000),ClockTime_Month,ClockTime_Day,ClockTime_Hour);
	TimeAvailable_1=TimeAvailabe_Judge;
	
	//无信号锁车
	if(GPSPlatformConnetState==0)//无信号
	{	
		if (VarCan2MonthLockState==1){
			;//已是无信号锁车状态则不再判断
		
		//无信号总时长未超过60天，时间有效
		}else if (TimeAvailable==1 && TimeAvailabe_Judge==1){
			Year_1 = NoSignalStart_Year+2000;//年仅发送最后两位
			Month_1 = NoSignalStart_Month;
			Day_1 = NoSignalStart_Day;
			Year_2 = ClockTime_Year+2000;//年仅发送最后两位
			Month_2 = ClockTime_Month;
			Day_2 = ClockTime_Day;
			Time_Longer=TimeCompare(Year_1,Month_1,Day_1,0,Year_2,Month_2,Day_2,0);
			TimeCompare_1=Time_Longer;
			if (NoSignalStart_Year==0 || NoSignalStart_Month==0 ||NoSignalStart_Day==0||Time_Longer==0){
				//无信号初始时间无效时，保存当前年月日，累计时间清零
				NoSignalStart_Year = ClockTime_Year;
				NoSignalStart_Month = ClockTime_Month;
				NoSignalStart_Day = ClockTime_Day;
				NoSignalTotal_Day = 0;
				//'时间保存'
				VarFlashGpsDataMasterNeedSaveFlag=1;
				VarFlashGpsDataBackupNeedSaveFlag=1;
			}
			if (NoSignalTotal_Day==0){//上电一次只计算一次间隔时间，此变量初始化为0
				Year_1 = NoSignalStart_Year+2000;//年仅发送最后两位
				Month_1 = NoSignalStart_Month;
				Day_1 = NoSignalStart_Day;
				Year_2 = ClockTime_Year+2000;//年仅发送最后两位
				Month_2 = ClockTime_Month;
				Day_2 = ClockTime_Day;
				Days = DaysBetween2Date(Year_1,Month_1,Day_1,Year_2,Month_2,Day_2);
				if (Days==0) NoSignalTotal_Day=1;
				else if(Days>60) NoSignalTotal_Day=60;
			}
			//无信号总时长超过60天
			if (NoSignalTotal_Day>=60){	
				//'状态保存'
				if(VarCan2MonthLockState==0){
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
					VarCan2MonthLockState = 1;
				}
			}
		}
	//有信号，锁车状态，无信号时间不为0		
	}else {
		if(((NoSignalTotal_Day!=0)||(VarCan2MonthLockState==1))&& GPSPlatformConnetState == 1){	
			//锁车状态解除，累计时间清零
			VarCan2MonthLockState = 0;
			NoSignalStart_Year = 0;
			NoSignalStart_Month = 0;
			NoSignalStart_Day = 0;
			NoSignalTotal_Day = 0;
			//'状态时间保存'
			VarFlashGpsDataMasterNeedSaveFlag=1;
			VarFlashGpsDataBackupNeedSaveFlag=1;
		} 
	}
	
	
	//锁车使能控制
	//GPSLock_All_Enable=0;
	if (GPSLock_All_Enable==0)//总使能
	{
		VarGpsLockState_A = 0;
		VarGpsLockState_B = 0;
		VarGpsLockState_C = 0;
		VarGpsLockState_D = 0;
		VarGpsCanBusError = FALSE;
		VarCanBusLockState=0;
		VarCanAntennaCutLockState=0;
		VarCanUncoverLockState=0;
		VarCan2MonthLockState=0;
	}
	if(GPSLock_Passive_Enable==0)//被动锁车总使能
	{
		VarGpsCanBusError = FALSE;
		VarCanBusLockState=0;
		VarCanAntennaCutLockState=0;
		VarCanUncoverLockState=0;
		VarCan2MonthLockState=0;
	}
	if(MonthNoSignalLock_Enable==0)//盲区锁车使能
	{
		VarCan2MonthLockState=0;
	}
	if(UncoverLock_Enable==0)//拆盖锁车使能
	{
		VarCanUncoverLockState=0;
	}
	if(CANSignalLostLock_Enable==0)//总线锁车使能
	{
		VarGpsCanBusError = FALSE;
		VarCanBusLockState=0;
	}
	if(SIMCardLostLock_Enable==0)//拔卡锁车使能
	{
		//VarCan2MonthLockState = 0;//SIM卡异常无锁车
	}
	
	//密码判断
	//计时前置
	if (GPSUnLockStep==3) Step3CountStart=1;
	else Step3CountStart=0;
	Step3CountStop = LibTimerTon(5,Step3CountStart,6000,&Ulong_Temp1);
	
	//当命令序号不同时，重新启动密码判断流程
	if ((SignalNumber_115 != SignalNumber_115_Last)||((OderType_115&0x30) != (OderType_115_Last&0x30))){
		GPSUnLockStep = 0;
	}
	//判断步骤
	switch (GPSUnLockStep){
	case 0:	
		if (OderType_115==0x11 || OderType_115==0x21 || OderType_115==0x31){
			code_1_H=VarSysVoltageMv;
			code_2_H=rand();
			code_1_L=VarAiFuelVolume;
			code_2_L=rand();
			OderType_2F1 = OderType_115;
			SignalNumber_2F1 = SignalNumber_115;
			OderType_115_Last = OderType_115;
			SignalNumber_115_Last = SignalNumber_115;
			DynamicCode_H = caculateCodeH(code_1_H,code_2_H);
			DynamicCode_L = caculateCodeL(code_1_L,code_2_L);
			GPSUnLockStep = 1;//收到动态码请求，计算动态码，保存命令序号，进入步骤1
		}
		else{//清零
			DynamicCode_H = 0;
			DynamicCode_L = 0;
			break;
		}
	case 1:	
		if (OderType_115==0x12 || OderType_115==0x22 || OderType_115==0x32){
			GPSUnLockStep = 2;//当接收到显示屏发送密码后停止发送，进入步骤2
		}
		else break;	//发送动态码
	case 2://2.接收交互密码，校验密码结果
		//密码状态清零
		VarCanGpsCancelPSDoK=0;
		VarCanGpsUnlockPSDOK=0;
		VarCanGpsUrgencyPSDoK=0;
		GPSUnlockPSD_Last=GPSUnlockPSD;
		//0x12：无信号锁车解除
		if (OderType_115==0x12){
			GPSUnLockStep = 3;
			OderType_2F1 = 0x12;
			Password_1 = swNetworklessUnlock(DynamicCode_H,DynamicCode_L,1);
			PSD =Password_1;
			if (GPSUnlockPSD==Password_1){
				VarCanGpsUnlockPSDOK=1;
				if(VarCan2MonthLockState==1){
					VarCan2MonthLockState=0;
					//保存当前年月日，累计时间清零
					if(TimeAvailable==1 && TimeAvailabe_Judge==1){
						NoSignalStart_Year = ClockTime_Year;
						NoSignalStart_Month = ClockTime_Month;
						NoSignalStart_Day = ClockTime_Day;					
					}else{
						NoSignalStart_Year = 0;
						NoSignalStart_Month = 0;
						NoSignalStart_Day = 0;			
					}
					NoSignalTotal_Day = 0;
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}
			}
			GPSPSDVerify = VarCanGpsUnlockPSDOK;
		}
		//0x22：锁车功能永久解除
		else if (OderType_115==0x22)
		{
			GPSUnLockStep = 3;
			OderType_2F1 = 0x22;
			Password_1 = swGpsPermanentCancel(DynamicCode_H,DynamicCode_L,1);
			PSD =Password_1;
			if (GPSUnlockPSD==Password_1){
				//密码正确执行
				VarCanGpsCancelPSDoK=1;
				if(VarCanGpsCancel==0){
					VarCanGpsCancel=1;
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}
			}else if(GPSUnlockPSD==4321){
				//恢复密码，显示正确
				VarCanGpsCancelPSDoK=1;
				if(VarCanGpsCancel==1){
					VarCanGpsCancel=0;
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}	
			}
			GPSPSDVerify = VarCanGpsCancelPSDoK;
		}
		//0x32：紧急解除
		else if(OderType_115==0x32){
			GPSUnLockStep = 3;
			OderType_2F1 = 0x32;
			Password_1 = swEmergentUnlock(DynamicCode_H, DynamicCode_L,1);
			PSD =Password_1;
			if (GPSUnlockPSD==Password_1){
				//密码正确执行
				VarCanGpsUrgencyPSDoK=1;
				if(VarCanGpsUrgencyState==0){
					VarCanGpsUrgencyState=1;
					if(TimeAvailable==1 && TimeAvailabe_Judge==1){
						EmergencyStart_Year = ClockTime_Year;
						EmergencyStart_Month = ClockTime_Month;
						EmergencyStart_Day = ClockTime_Day;	
						EmergencyStart_Hour = ClockTime_Hour;	
					}else{
						EmergencyStart_Year = 0;
						EmergencyStart_Month = 0;
						EmergencyStart_Day = 0;		
						EmergencyStart_Hour = 0;
					}
					//保存GPS数据
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
					//保存小时计数据
					VarEngineWorkTime_Gps = VarEngineWorkTime1H;
					VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
					VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
				}
			//恢复密码，显示正确
			}else if(GPSUnlockPSD==4321){
				VarCanGpsUrgencyPSDoK=1;
				if(VarCanGpsUrgencyState>0){
					VarCanGpsUrgencyState=0;
					EmergencyUnlock_Hour=0;
					EmergencyStart_Year = ClockTime_Year;
					EmergencyStart_Month = ClockTime_Month;
					EmergencyStart_Day = ClockTime_Day;	
					EmergencyStart_Hour = ClockTime_Hour;
					//保存GPS数据
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}
			}
			GPSPSDVerify = VarCanGpsUrgencyPSDoK;//密码状态赋值
		}else{
			GPSPSDVerify = 0;//密码状态清零
			break;//显示屏未发送密码则不发送密码判断状态
		}
	case 3://发送密码正确/错误状态
		//同一密码界面接收到新密码后，回到步骤2
		if ((OderType_115==OderType_2F1)&&(GPSUnlockPSD_Last!=GPSUnlockPSD)) GPSUnLockStep = 2;
		//当不同命令的序号恰巧相同时，返回步骤0
		else if (OderType_115!=OderType_2F1) GPSUnLockStep = 0;
		//进入步骤3开始计时，6s后进入步骤4
		else if (Step3CountStop==1){
			LibTimerTon(5,0,6000,&Ulong_Temp1);//计时清除
			GPSUnLockStep = 4;
		}
		else break;
	case 4://等待发送新密码或退出界面不再通讯
		//同一密码界面接收到新密码后回到密码判断步骤
		if ((OderType_115==OderType_2F1)&&(GPSUnlockPSD_Last!=GPSUnlockPSD)) GPSUnLockStep = 2;
		break;
	default:break;
	}

	//Gps紧急解锁时间起作用时间为48小时
	//总线状态正常且数据有效时，使用GPS发送时间计算48小时
	if((TimeAvailable==1 && TimeAvailabe_Judge==1)&&(VarCanGpsUrgencyState>0)&&(VarGpsCanErrorState==0)){
		b_48Test=1;
		if(EmergencyUnlock_Hour==0){
			Year_1 = EmergencyStart_Year+2000;//年仅发送最后两位
			Month_1 = EmergencyStart_Month;
			Day_1 = EmergencyStart_Day;
			Hour_1=EmergencyStart_Hour;
			Year_2 = ClockTime_Year+2000;//年仅发送最后两位
			Month_2 = ClockTime_Month;
			Day_2 = ClockTime_Day;
			Hour_2=ClockTime_Hour;
			Time_Longer=TimeCompare(Year_1,Month_1,Day_1,Hour_1,Year_2,Month_2,Day_2,Hour_2);
			if (EmergencyStart_Year==0 || EmergencyStart_Month==0 ||EmergencyStart_Day==0||Time_Longer==0){
				EmergencyStart_Year = ClockTime_Year;
				EmergencyStart_Month = ClockTime_Month;
				EmergencyStart_Day = ClockTime_Day;	
				EmergencyStart_Hour = ClockTime_Hour;	
				//保存GPS数据
				VarFlashGpsDataMasterNeedSaveFlag=1;
				VarFlashGpsDataBackupNeedSaveFlag=1;
			}
			//重新赋值
			Year_1 = EmergencyStart_Year+2000;//年仅发送最后两位
			Month_1 = EmergencyStart_Month;
			Day_1 = EmergencyStart_Day;
			Hour_1=EmergencyStart_Hour;
			Hours=HoursBetween2Date(Year_1,Month_1,Day_1,Hour_1,Year_2,Month_2,Day_2,Hour_2);
			if (Hours==0) EmergencyUnlock_Hour=1;
			else if(Hours>48) EmergencyUnlock_Hour=48;
			else EmergencyUnlock_Hour=Hours;
		}
		if(EmergencyUnlock_Hour>=48){
			VarCanGpsUrgencyState=0;//GPS紧急解除取消
			EmergencyStart_Year = 0;
			EmergencyStart_Month = 0;
			EmergencyStart_Day = 0;		
			EmergencyStart_Hour = 0;
			//保存GPS数据
			VarFlashGpsDataMasterNeedSaveFlag=1;
			VarFlashGpsDataBackupNeedSaveFlag=1;
		}
	}
	//总线状态不正常等其他无法使用GPS时间时，使用工作小时计算48小时
	if((VarEngineWorkTime1H>VarEngineWorkTime_Gps+48)&&(VarCanGpsUrgencyState>0))
	{
		VarCanGpsUrgencyState=0;//GPS紧急解除取消
		//保存GPS数据
		VarFlashGpsDataMasterNeedSaveFlag=1;
		VarFlashGpsDataBackupNeedSaveFlag=1;
	}
	
	//------------------执行锁车--------------------
	if(VarCanGpsCancel==0 && VarCanGpsUrgencyState==0)//如果未屏蔽GPS锁车
	{
		if(VarGpsLockWork_C&&(!VarGpsLockWork_D))    //C锁车锁发动机功率
		{
			VarGpsLockEnginePower=TRUE;
			VarGpsLockPumpPower=FALSE;
		}
		else if((!VarGpsLockWork_C)&&VarGpsLockWork_D)//D锁车锁泵功率
		{
			VarGpsLockPumpPower=TRUE;
			VarGpsLockEnginePower=FALSE;	
		}
		else if( (VarGpsLockWork_C&&VarGpsLockWork_D)//自锁车锁转速与功率
			||VarCan2MonthLockState
			||VarCanUncoverLockState
			||VarCanBusLockState
			||VarCanAntennaCutLockState)
		{
			VarGpsLockEnginePower=TRUE;
			VarGpsLockPumpPower=TRUE;
		}
		else
		{
			VarGpsLockEnginePower=FALSE;
			VarGpsLockPumpPower=FALSE;
		}		
	}
	else
	{
		VarGpsLockEnginePower=FALSE;
		VarGpsLockPumpPower=FALSE;
	}
	//A锁车，锁先导
	if( ((VarCanGpsCancel==1 || VarCanGpsUrgencyState==1)||(!VarGpsLockWork_A)) &&
		(VarSysPowerOn>0) &&
		(VarDiPilot>0))
	{
		VarDoPilot=1;
	}
	else
	{
		VarDoPilot=0;
	}
	
	//B锁车，锁发动机停机
	if( ((VarCanGpsCancel==1 && VarCanGpsUrgencyState==1)||(!VarGpsLockWork_B))
		&&VarSysPowerOn)//B锁车，锁发动机，发动机停机
	{
		VarEngineStop=0;
	}
	else
	{
		VarEngineStop=1; 
	}

}

/* ***************************************************************
**
** 函数名称: IsLeap
** 功能描述: 判断一个年份是否为闰年
**
******************************************************************/
BOOL IsLeap(UINT16 year)
{
   return ((year % 4 ==0 && year % 100 !=0)|| year % 400 ==0) ;
}
/* ***************************************************************
**
** 函数名称: DayInYear
** 功能描述: 根据给定的日期，求出它在该年的第几天
**
******************************************************************/
UINT16 DayInYear(UINT16 year, UINT16 month, UINT16 day)
{
    //int _day = 0;
	UINT16 i;
	UINT16 DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeap(year))
        DAY[1] = 29;
    for(i=0; i<month - 1; ++i)
    {
        day += DAY[i];
    }
    return day;
}
/* ***************************************************************
**
** 函数名称: DaysBetween2Date
** 功能描述: 根据给定的日期，求出两日期的差值
**
******************************************************************/
UINT16 DaysBetween2Date(UINT16 year1, UINT16 month1, UINT16 day1,UINT16 year2, UINT16 month2, UINT16 day2)
{
	UINT16 d1,d2,d3;
	UINT16 Year_Temp,Month_Temp,Day_Temp;
	UINT16 year;
	//年月相同
	if(year1 == year2 && month1 == month2)
	{
		return (day1 > day2) ? (day1 - day2) : (day2 - day1);
      
	//如果年相同
	}else if(year1 == year2)
	{
    	
         d1 = DayInYear(year1, month1, day1);
         d2 = DayInYear(year2, month2, day2);
         return (d1 > d2) ? (d1 - d2) : (d2 - d1);
      
     //年月都不相同
     }else{
         //确保year1年份比year2早
         if(year1 > year2){
             //swop进行两个值的交换
        	Year_Temp = year1;
        	Month_Temp = month1;
        	Day_Temp = day1;
        	year1 = year2;
        	month1 = month2;
        	day1 = day2;
        	year2 = Year_Temp;
        	month2 = Month_Temp;
        	day2 = Day_Temp;
         }  
         if(IsLeap(year1))
			d1 = 366 - DayInYear(year1,month1, day1); //取得这个日期在该年还于下多少天
         else
			d1 = 365 - DayInYear(year1,month1, day1);
         d2 = DayInYear(year2,month2,day2); //取得在当年中的第几天
         d3 = 0;
         for( year= year1 + 1; year < year2; year++)
         {
			if(IsLeap(year))
				d3 += 366;
			else
				d3 += 365;
         }
         return d1 + d2 + d3;
     }
}
/* ***************************************************************
**
** 函数名称: HoursBetween2Date
** 功能描述: 根据给定的日期，求出小时差值
**
******************************************************************/
UINT16 HoursBetween2Date(UINT16 year1, UINT16 month1, UINT16 day1,UINT8 hour1, UINT16 year2, UINT16 month2, UINT16 day2, UINT8 hour2)
{
	BOOL Exchanged=0;
	UINT16 d1,d2,d3;
	UINT16 Year_Temp,Month_Temp,Day_Temp;
	UINT16 year;
	INT16 Days;
	INT32 Hours;
	//年月相同
	if(year1 == year2 && month1 == month2)
	{
		Days = day2 - day1;
	
	//如果年相同
	}else if(year1 == year2)
	{
		d1 = DayInYear(year1, month1, day1);
		d2 = DayInYear(year2, month2, day2);
		Days = d2 - d1;
	
	//年月都不相同
	}else{
		//确保year1年份比year2早
		if(year1 > year2)
		{
			//swop进行两个值的交换
			Year_Temp = year1;
			Month_Temp = month1;
			Day_Temp = day1;
			year1 = year2;
			month1 = month2;
			day1 = day2;
			year2 = Year_Temp;
			month2 = Month_Temp;
			day2 = Day_Temp;
			Exchanged = 1;
		}
			
		if(IsLeap(year1))
			d1 = 366 - DayInYear(year1,month1, day1); //取得这个日期在该年还于下多少天
		else
			d1 = 365 - DayInYear(year1,month1, day1);
		d2 = DayInYear(year2,month2,day2); //取得在当年中的第几天
		d3 = 0;
		for( year= year1 + 1; year < year2; year++)
		{
			if(IsLeap(year))
				d3 += 366;
			else
				d3 += 365;
		}
		if(Exchanged==1)
			Days = -(d1 + d2 + d3);
		else
			Days = d1 + d2 + d3;
	}
	Hours=24*Days+hour2-hour1;
	if(Hours>65535 || Hours< -65535)
	{
		Hours=65535;
	}
	if(Hours>=0) return Hours;
	else return -Hours;
			
}
/* ***************************************************************
**
** 函数名称: IsTimeAvailable
** 功能描述: 根据给定的日期，求出它在该年的第几天
**
******************************************************************/
BOOL IsTimeAvailable(UINT16 year,UINT16 month,UINT16 day,UINT8 hour)
{
	UINT16 DAY_1[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	UINT16 DAY_2[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	if(year==0 || month==0 || day==0) 	return 0 ;
	if(month>12 || hour>24)	return 0 ;
	if(IsLeap(year)){
		if(day>DAY_2[month])	return 0 ;
	}else{
		if(day>DAY_1[month])	return 0 ;
	}
	return 1 ;
}
/* ***************************************************************
**
** 函数名称: TimeCompare
** 功能描述: 两日期比较，1早于2输出1,2早于1输出0
**
******************************************************************/
BOOL TimeCompare(UINT16 year1, UINT16 month1, UINT16 day1,UINT8 hour1, UINT16 year2, UINT16 month2, UINT16 day2, UINT8 hour2)
{
	UINT16 d1,d2,d3;
	UINT16 Year_Temp,Month_Temp,Day_Temp;
	UINT16 year;
	//年月日相同
	if(year1 == year2 && month1 == month2 && day1==day2){
		if(hour2>=hour1) return 1;
		else return 0;
	//年月相同	
	}else if(year1 == year2 && month1 == month2){
		if(day2>=day1) return 1;
		else return 0;
	//如果年相同
	}else if(year1 == year2)
	{	
		if(month2>=month1) return 1;
		else return 0;
	 //年月日都不相同
	 }else{
		 //确保year1年份比year2早
		 if(year2 > year1) return 1;
		 else return 0;		 
	 }
}
