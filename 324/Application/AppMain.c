#include "AppVar.h"
#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"

//LibTimer_1:CAN数据发送显示屏
//LibTimer_2:控制器LED灯闪烁
//LibTimer_3:
//LibTimer_4:CAN数据发送GPS
//LibTimer_5:
//LibTimer_6:油量计算定时器，500ms计算一次
//LibTimer_7:串口下载，发送SUNWARD
//LibTimer_8:发动机工作时间累加
//LibTimer_10:CAN发送到发动机MCU
//LibTimer_11:p1,p2压力上升检测

//LibTimerTon_1~12:已用
/* *************************************************************** 
** AppMain
** ************************************************************ */
void AppMain(void) 
{ 
	FunUartReceiveData();
	FunUartSendData();
	//系统关机休眠
	FunSysSleep();
	//输入采样与输出
	FunIOSample();
	//表盘标定
	FunDialSpeedSet();
	//Flash读写
  	FunFlashLoop();
	//CAN通讯
	FunCanDataDeal();
	//GPS锁车控制
	FunControlGpsLock();
	//工作小时计
	FunSysWorkTimeCompute();
	//
	FunBuzzerAlarm();
	//
	FunHydraulicCoolingPumpCurrent();
	//
	FunFuelAirFitlerControl();
	
	//开关阀控制
	FunSwitchValveControl();
	//节能控制
	FunPowerSaveIO();
	FunPowerSaveControl();
	FunPowerSaveFault();
	
	//控制系统,非表盘标定状态
	if(VarAccDialPosiSetting==0)
	{
		if( (VarSysPowerOn>0)||(VarEngineSpeedNow>400) )
		{
			if(VarEngineSpeedNow>400)
			{
				//自动怠速判断
				FunAutoIdle();
				//温度相关控制
				FunTemperatureCotrol();
				//行走速度
				FunTravelSpeed();

				//二次增压
				FunSecondPressure();
				//辅具设置
				FunAssistantSet();
				
				//发动机转速控制
				if(VarBoomPowerSaveFlag)//节能
				{
					FunPowerSaveSpeedControl();
				}
				else//不节能
				{
					FunSpeedControl();
				}
				
				//泵功率控制
				if(VarBoomPowerSaveFlag)//节能
				{
					FunPowerSavePumpCurrentControl();
				}
				else//不节能
				{
					FunPumpCurrent();
				}
				
				
				
			}
			else
			{
				//钥匙上电，发动机未启动，转速档调至1档
				VarCanEngineLevelSpeed=VarEngineLevelSpeed[0];
			}
		}
	}	

	//程序运行，LED灯闪烁
	if(LibTimerGet1S()<5)
	{
		if(LibTimer(2,1,50,1))
		{
			LibMcuLedOutput(!LibFunMcuLedState());
		}
	}
	else
	{
		if(LibTimer(2,1,500,1))
		{
			LibMcuLedOutput(!LibFunMcuLedState());
		}
	}
}

/* *************************************************************** 
** File End
** ************************************************************ */
