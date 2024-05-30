#include "AppDefine.h"
UINT32 VarSysControlSerialID;//控制器编号
UINT8 VarCMCommunicationVersion=0;//通讯协议版本号
UINT8 VarExcavatorMonitorType;//显示屏类型
//DI
UINT8 VarDiAirFilterAlarm;	//空滤报警Di，低有效
UINT8 VarDiPreheat;			//预热Di，高有效，    **未用
UINT8 VarDiTravelHighSpeed;	//行走高速Di，高有效，**未用
UINT8 VarDiPilot;			//先导开关Di，高有效
UINT8 VarDiLowSpeedEnable;	//二次增压Di，高有效，**未用
UINT8 VarSysPowerOn;		//上电Di，高有效
UINT8 VarDiCharge;			//充电报警Di,计算得到
UINT8 VarDiPressureSwitch;  //辅具压力限值开关
//AI
UINT16 VarAiFuelVolume;		//油量电阻，0.1R
UINT16 VarAiEngineDial;		//表盘反馈,mV
UINT16 VarAiPump1Pressure;	//泵1传感器反馈,uA
UINT16 VarAiPump2Pressure;	//泵2传感器反馈,uA
UINT16 VarAiPilotSwitch;	//先导压力开关,DIH pin50
UINT16 VarAiAirFilter;		//空滤电阻,0.1R
//Do
UINT8 VarDoSecondPressure;	//二次增压输出电磁阀
UINT8 VarDoTravelHighSpeed;	//行走高速输出电磁阀
UINT8 VarDoBatteryRelay;	//系统电源继电器
UINT8 VarDoPilot;			//先导输出电磁阀
UINT8 VarDoEngineStopRelay;	//熄火马达电磁阀
UINT8 VarDoValveBreakPilot=0; //辅具液压阀
UINT8 VarDoValvePressRegulate=0;//辅具压力限制阀
//CAN
UINT8 VarSendDataID181[8];
UINT8 VarSendDataID281[8];
UINT8 VarSendDataID381[8];
UINT8 VarSendDataID481[8];
UINT8 VarSendDataID182[8];
UINT8 VarSendDataID282[8];
UINT8 VarSendDataID382[8];
//UINT8 VarSendDataID383[8];
//UINT8 VarSendDataID384[8];
//节能参数
UINT8 VarSendDataID236[8];
UINT8 VarSendDataID237[8];
UINT8 VarSendDataID238[8];
UINT8 VarSendDataID239[8];

UINT8 VarSendDataID187[8];
UINT8 VarSendDataID287[8];
UINT8 VarRecDataID116[8];  //节能参数
UINT8 VarRecDataID285[8];

UINT8 VarRecDataID385[8];
UINT8 VarRecDataID485[8];
UINT8 VarRecDataID585[8];
UINT8 VarRecDataID188[8];
UINT8 VarSendDataID387[8];
UINT8 VarSendDataID487[8];
UINT8 VarRecDataID666[8];
UINT8 VarSendDataID1A0[8];
UINT8 VarSendDataID1A1[8];
UINT8 VarSendDataID1A2[8];
UINT8 VarCanSendDataStep=0;
UINT8 VarCanSendDataGpsStep=0;
UINT8 VarCanGpsCancelCommand;	//GPS取消发送命令
UINT8 VarCanGpsCancelPSDoK;		//Gps取消密码对错返回值，1-正确;0-错误
UINT8 VarCanHighlandMode=0;     //0-普通模式，8-高原模式
//H Bridge
UINT8 VarAccMotorMoveDir=0;		//油门电机运动方向,0-停;1-缩;2-伸;3-刹
//System
UINT16 VarSysVoltageMv=0;		//系统电压，mV
UINT16 VarSysVoltFilterLast=0;

//NEW
UINT8 VarCanEngineOilPreAlarm=0;
UINT8 VarCanEngineDialPosi=0;
INT8 VarCanEngineTorque=0;
UINT16 VarCanEngineSpeed=0;
UINT16 VarCanEngineTargetSpeed=0;
UINT8 VarCanEngineWaterTemp=0;
UINT16 VarCanEngineOilPressure=0;
UINT16 VarCanEngineOilFlowRate=0;
UINT16 VarCanEngineAtmosPressrue=0;
INT16 VarCanEngineAirInTemp=0;
UINT16 VarCanEngineBoostPressrue=0;
INT16 VarCanEngineBoostTemp=0;
UINT16 VarCanEngineFuelWastageAll=0;
UINT8 VarCanSendEngineStep=0;
UINT8 VarRecDataID_0CF00300[8];
UINT8 VarRecDataID_0CF00400[8];
UINT8 VarRecDataID_18FEDF00[8];
UINT8 VarRecDataID_0x18FEEE00[8];
UINT8 VarRecDataID_0x18FEEF00[8];
UINT8 VarRecDataID_0x18FEF200[8];
UINT8 VarRecDataID_0x18FEF500[8];
UINT8 VarRecDataID_0x18FEF600[8];
UINT8 VarRecDataID_0x18FEF900[8];
UINT8 VarRecDataID_0x1CEBFF00[8];
UINT8 VarRecDataID_0x1CECFF00[8];
UINT8 VarRecDataID_0x18FECA00[8];
UINT8 VarSendDataID_0x0C0000E4[8];
UINT8 VarSendDataID_0x18FEE4E4[8];
UINT8 VarSendDataID_0x0C000003[8];
UINT8 VarSendDataID_0x18EA0021[8];
UINT8 VarSendDataID_0x18EA00F2[8];
UINT8 VarRecDataID_0x18ECFF00[8];//潍柴发动机单故障代码
UINT8 VarRecDataID_0x18EBFF00[8];//潍柴发动机多故障代码
UINT8 VarRecDataID_0x18FEE900[8];//五十铃油耗数据
UINT8 VarRecDataID_0x18FEB100[8];//五十铃小时计数据
UINT8 VarSendDataID0x18EA00FA[8];//五十铃小时计数据请求指令
UINT16 VarEngineAverageFuelYouHao;//平均油耗
UINT8 VarEngineNeedStopFlag=0;//机油压力低停机
//***************Control***********************
UINT8 VarDiLowSpeedEnableLast=0;
UINT16 VarEngineLevelSpeed[11];
UINT16 VarCanEngineLevelSpeed;
UINT8 VarButtonLowSpeedEnable=0;
UINT8 VarSetAccMotorCommand=0;		//开始标定命令
UINT16 VarSetAccMotorMoveDoneTime1Ms=0;
UINT16 VarSetAccMotorMoveCount=0;	//电机运动次数
UINT16 VarEngineTorque;
UINT16 VarAccMotorPosi[100]=
{
	0
};//电机历史位置
UINT16 VarEngineSpeed[100]=
{
	0
};//发动机历史转速值
UINT16 VarAccMotorPosiNow=0;		//电机位置反馈，mv
UINT16 VarAccDialPosiNow=0;			//表盘位置反馈,mV
UINT16 VarAccDialPosiLast=0;		//前一程序周期表盘位置值
UINT8 VarDialGrade=1;				//表盘档位值
UINT16 VarAccMotorPosiTarget=2000;	//电机目标位置
UINT16 VarAccMotorPosiSet[11];		//转速标定中得电机位置，11档
UINT16 VarAccMotorMoveTime1Ms=0;	//电机运动时间
UINT16 VarAccMotorStopTime1Ms=0;	//电机停止时间
UINT8 VarAccMotorMoveState=0;		//电机运动状态:1-单次运动中;0-单次运动结束
UINT32 VarAccMotorTimerLast=0;		//上一程序周期的系统时间，用以计算程序周期时间，进而计算电机运动剩余时间
UINT16 VarAccMotorPosiTargetLast=0;	//上程序电机目标位置，用于档位变化的判断及转速标定
UINT8 VarAccMotorStopJiggle=0;		//停止微动标志位，1-进入设定微动区域,停止运动;0-未进入设定微动区域
UINT8 VarEngineSpeedSetGradeTargetLast=0;//上程序周期标定目标档位，用于同一档位标定时间的计算
UINT8 VarTargetGradeSetState=0;			//单档位标定状态。1-在标定同一转速档位;0-标定的转速档位发生变化
UINT16 VarAccMotorMoveTimeExtra=0;		//电机运动额外增加时间，在标定中电机拉不动时增加的运动时间

UINT16 VarCanAccMotorPosiMaxLimit=4200;		//油门电机最大位置限制值
UINT16 VarCanAccMotorPosiMinLimit=1300;		//油门电机最小位置限制值

UINT8 VarCanAccDialSetCommand=0;		//油门表盘标定命令，来自显示屏
UINT8 VarAccDialPosiSetting=0;			//表盘标定状态，1-标定中
UINT32 VarAccDialPosiSetTimeLast=0;		//表盘上次标定时间
UINT8 VarCanAccDialSetCommandLast=0;	//上程序周期表盘标定命令
UINT8 VarDialSetSortLast=0;				//上次表盘标定类型
UINT16 VarAccDialPosiMax=0;				//表盘标定最大值
UINT16 VarAccDialPosiMin=0;				//表盘标定最小值
UINT8 VarCanEngineSpeedSet=0;			//转速标定命令，来自显示屏
UINT8 VarCanEngineSpeedSetLast=0;		//上程序转速标定命令，来自显示屏，上升沿做为标定开始命令
UINT8 VarEngineSpeedSetCommand=0;		//转速标定开始命令
UINT8 VarEngineSpeedSetState=0;			//转速标定状态，1-标定中
UINT8 VarEngineSpeedSetGradeTarget=0;	//转速目标标定档位
UINT16 VarEngineSpeedSet[11]=
{
	1000,1200,1350,1600,1800,1890,1980,2080,2150,2200,2250
};										//各档位设定的标定转速
UINT8 VarSetAutoMotorPosiOk=0;			//标定结束反馈,1-标定结束
UINT16 VarEngineSpeedNow=0;				//发动机当前转速
UINT16 VarEngineSpeedTarget=0;			//发动机目标转速，用于转速标定
UINT8 VanEngineTimeSetPSDSendFlag=0;		//发动机工作小时设置密码发送命令，来自显示屏
UINT8 VanEngineTimeSetPSDoKFlag=0;		//发动机工作小时设置密码对错反馈。1-密码正确，0-密码错误
//CAN
UINT8 VarCanAccDialPosiMinSet=0;		//表盘最小档位标定命令，来自显示屏
UINT8 VarCanAccDialPosiMaxSet=0;		//表盘最大档位标定命令，来自显示屏
UINT8 VarMoveTimes=0;					//电机微动次数

//AI转换为物理量相关变量定义
UINT8 VarFuelComputeNum=1;				//油量计算进行平均的基数
UINT16 VarFuelCompute[100]=
{
	0
};										//油量采样历史值
UINT8 VarFuelVolume=40;					//燃油量，未滤波
UINT8 VarFuelLackAlarm=0;				//燃油低报警
UINT8 VarFuelSensorError=0;				//燃油油位传感器故障
UINT8 VarWaterComputeNum=0;				//水温计算进行平均的基数
UINT16 VarWaterCompute[100]=
{
	0
};										//水温采样历史值
UINT8 VarWaterTemp=0;					//水温温度值，未滤波
UINT8 VarCanWaterHihgAlarm=0;			//水温高报警
UINT8 VarWaterTempSensorError=0;		//水温传感器故障
UINT8 VarP1PressureSensorEorror=0;		//泵1压力传感器故障
UINT16 VarP1PressureArray[20]=
{
	0
};										//泵1压力计算滤波数组
UINT16 VarP1Pressure=0;					//泵1压力，未滤波，单位bar
UINT8 VarP2PressureSensorEorror=0;		//泵2传感器故障
UINT8 VarPiPressureSensorEorror=0;      //先导泵压力传感器故障
UINT16 VarPiPressureArray[20]=
{
	0
};
UINT16 VarP2PressureArray[20]=
{
	0
};
UINT16 VarP2Pressure=0;					//泵2压力，未滤波，单位bar
//UINT16 VarPiPressure=0;                 //先导泵压力，未滤波，单位bar
UINT16 VarSysAveragePress=0;			//系统平均压力，单位bar
UINT16 VarP2PressureFilter=0;			//泵2压力，已滤波，单位bar
UINT16 VarP1PressureFilter=0;			//泵1压力，已滤波，单位bar	
UINT16 VarPiPressureFilter=0;			//先导压力，已滤波，单位bar
UINT8 VarDialSensorError=0;				//油门表盘反馈故障
UINT8 VarAccMotorSensorError=0;			//电机反馈故障
UINT8 VarFuelVolumeFilter=0;			//燃油油量，已滤波
UINT16 VarValveErrorTime1S=0;			//电磁阀故障累积时间，S
UINT8 VarEngineSpeedSensorError=0;		//转速传感器故障
UINT8 VarEngineWorkErrorTime1S=0;       //机油压力低累积时间，发动机工作开始计时
//*******
BOOL VarCanAutoIdleEnable = TRUE;		//自动怠速使能
UINT16 VarCanP1PressureIdleLimit=50;	//自动怠速开启压力
UINT16 VarCanP2PressureIdleLimit=50;	//自动怠速开启压力
BOOL VarstartIdle = TRUE;				//自动怠速开始标志量，TURE-进入自动怠速
UINT8 VarIdleState=0;					//怠速状态，1-怠速中
BOOL VarCurrentIdleDelay = FALSE;		//泵比例阀电流延时开启，TURE-应延时，此时阀电流为0
UINT32 VarIdleTimer=0;					//自动怠速状态判断计时器
//****
BOOL VarCanHighSpeedTravel=FALSE;		//行走高速使能，来自显示屏，TURE-行走高速使能
//***
UINT8 VarCanSysHSLBKRMode=2;			 //功率模式切换，H-S-L-B-K-R
UINT8 VarHydHammerFlow=0;                //液压锤流量值
UINT8 VarHydSicissorsFlow=0;             //液压剪流量值
UINT8 VarHydRamFlow=0;                   //液压夯流量值
UINT16 VarProValveCurrentTarget=0;       //液压辅具阀目标电流值
UINT8 VarPumpPowerParameter[8];          //液压泵功率点
//****
UINT8 VarSpeedLevel=0;					//发动机转速档位
BOOL VarEngineStartState;				//发动机开始上电状态，上电前5s-TURE
BOOL VarEngineWarmState=FALSE;			//发动机暖机状态，TURE-暖机中
BOOL VarEngineCoolState=FALSE;			//发动机冷机状态，TURE-冷机中
BOOL VarSysSleepCommand=FALSE;			//系统休眠命令
BOOL VarEngineWarmDone = FALSE;			//发动机暖机执行，用途：使发动机在一次启机中只暖机一次
UINT32 VarEngineWarmStartTime=0;		//发动机暖机时间控制计时器
UINT16 VarValveCurrent[11];				//各档位下设定的泵工作额定电流
UINT16 VarValveCurrentTarget=0;			//实际工作中的泵实际目标电流
UINT32 TempCurrentTarget=0;				//泵目标电流计算中间变量，根据压力值设定
UINT16 CurrentOffset=0;					//泵目标电流计算中间变量，根据转速变化设置
UINT8 VarCurrentLevel=0;				//泵电流档位
UINT16 VarValvePwRatio=0;				//阀电流控制中，PWM高电平量
UINT16 VarValveCurrentNow=0;			//液压泵电磁阀当前电流
UINT16 VarAssValveCurrentNow=0;          //辅具流量调节电磁阀当前电流
UINT8 VarValveRatioKp=0;				//阀电流PID控制中得Kp参数
UINT8 VarValveRatioKi=0;				//阀电流PID控制中得Ki参数
UINT8 VarValveRatioKd=0;				//阀电流PID控制中得Kd参数
INT32 x[3]=
{
	0
};										//阀电流PID控制中得比例，微分，积分量
float D_Output=0;						//阀电流PID计算得到的PWM高电平量
float D_Last=0;							//增量式PID中用到，本控制程序中未用
INT32 PID_Error_1=0;					//目标电流与实际电流制的差
INT16 PID_Error_2=0;					//偏差的累加
UINT8 VarValveError=0;					//电磁阀故障			
UINT8 VarCanEngineTimeSetFlag;			//发动机工作时间设置命令发送标志量
UINT8 VarCanEngineTimeSetPSDoK=0;		//发动机工作时间设置密码对错判断，1-密码正确；0-密码错误
UINT32 VarCanEngineTimeSetPSD;			//发动机工作时间设置密码
UINT16 VarCanEngineTimeSetHour;			//设置的发动机工作时间
UINT8 VarExcavatorEngineType=0;          //电喷发动机:0-康明斯，1-五十铃，2-潍柴
//****************GPS锁车相关参数***********************
UINT8 VarGpsLockState_A=0;			//Gps的A锁车状态
UINT8 VarCanGpsLockCommand_A=0;		//GPS的A锁车命令
UINT8 VarCanGpsCancel=0;			//GPS锁车取消命令，1-取消锁车
BOOL VarGpsLockWork_A=FALSE;		//GPS的A锁车，执行锁车判断变量，使挖掘机在A锁车后等到下次启机才执行锁车
UINT8 VarGpslockState_B=0;			//Gps的B锁车状态
UINT8 VarCanGpsLockCommand_B=0;		//GPS的B锁车命令
BOOL VarGpsLockWork_B=FALSE;		//GPS的B锁车，执行锁车判断变量，使挖掘机在A锁车后等到下次启机才执行锁车
UINT8 VarGpslockState_C=0;			//Gps的C锁车状态
UINT8 VarCanGpsLockCommand_C=0;		//GPS的C锁车命令
BOOL VarGpsLockWork_C=FALSE;		//GPS的C锁车，执行锁车判断变量，使挖掘机在A锁车后等到下次启机才执行锁车
UINT8 VarGpslockState_D=0;			//Gps的D锁车状态
UINT8 VarCanGpsLockCommand_D=0;		//GPS的D锁车命令
UINT8 VarGpsLockWork_D=0;			//GPS的D锁车，执行锁车判断变量，使挖掘机在A锁车后等到下次启机才执行锁车
UINT8 VarCanGpsHeartBeatLast=0;		//上程序周期GPS心跳状态
UINT8 VarCanGpsHeartBeat=0;			//本程序周期GPS心跳状态
UINT8 VarGpsCanNoBeat=0;			//GPS10s无心跳
UINT8 VarGpsCanErrorState=0;		//CAN总线故障状态判断量
BOOL VarGpsCanBusError=FALSE;		//GPS的CAN总线故障,10S无通讯
UINT8 VarCanBusLockCommand=0;		//GPS与控制器无通讯锁车命令
UINT8 VarCanBusLockState=0;			//CAN通讯故障锁车状态
UINT8 VarCan2MonthLockCommand=0;	//GPS2月无信号锁车命令
UINT8 VarCan2MonthLockState=0;		//GPS2月无信号锁车状态
UINT8 VarCanAntennaCut=0;			//GPS天线剪断判断量
UINT8 VarCanAntennaCutLockState=0;	//GPS天线剪断锁车状态
UINT8 VarCanAntennaCutLockCommand=0;//GPS天线剪断锁车命令
UINT8 VarCanUncoverLockCommand=0;	//GPS揭盖锁车命令
UINT8 VarCanUncoverLockState;		//GPS揭盖锁车状态
BOOL VarGpsLockEnginePower;			//GPS锁车所发动机功率
BOOL VarGpsLockPumpPower;			//GPS锁车所液压泵功率
UINT8 VarGpsSIMCardError;           //GPS设备的SIM卡故障
UINT8 VarCanSendGps1F1[8];
UINT8 VarCanSendGps1F2[8];
UINT8 VarCanSendGps1F3[8];
UINT8 VarCanSendGps1F4[8];
UINT8 VarCanSendGps1F5[8];
UINT8 VarCanSendGps1F6[8];
UINT8 VarCanSendGps1F7[8];
UINT8 VarCanSendGps1FC[8];
UINT8 VarCanSendGps1FD[8];
UINT32 VarCanGpsUnlockPSD;			//GPS2月锁车解锁密码
UINT8 VarCanSendGpsStep;			//用于发送CAN数据到GPS
UINT8 VarCanGpsRx1EF[8];
UINT8 VarCanGpsRx1FB[8];
UINT8 VarCanGpsRx1EE[8];
UINT8 VarCanGpsTemper;				//GPS温度
UINT32 VarGpsAntennaCut_Et=0;		//天线剪断已用时间
UINT32 VarGpsCanBusError_Et=0;		//CAN总线已故障时间
UINT8 VarCanGpsSendUnlockPSDFlag=0;	//发送Gps解锁密码标志量
BOOL VarCan2MonthLockCancel=0;		//GPS2月锁车取消
//******************FLASH********************
UINT8 VarFlashSysDateMasterNeedSaveFlag = 0;//主存储区系统参数需要保存标志位
UINT8 VarFlashSysDateBackupNeedSaveFlag = 0;//备份存储区系统参数需要保存标志位
UINT16 VarSysDataMasterCheckFlag;			//主存储区系统参数保存校验数据，保存一次加1
UINT16 VarSysDataBackupCheckFlag;			//备份存储区系统参数保存校验数据，保存一次加1
UINT8 VarFlashGpsDataMasterNeedSaveFlag=0;	//主存储区GPS数据需要保存标志位
UINT8 VarFlashGpsDataBackupNeedSaveFlag=0;	//备份存储区GPS数据需要保存标志位
UINT16 VarGpsDataMasterCheckFlag;			//主存储区GPS参数保存校验数据，保存一次加1
UINT16 VarGpsDataBackupCheckFlag;			//备份存储区GPS参数保存校验数据，保存一次加1
UINT32 VarCanGpsCacelPSD=0;					//Gps取消密码
UINT32 VarCanGpsUrgencyPSD=0;				//Gps紧急解锁密码
UINT8 VarCanGpsUrgencyCommand=0;			//Gps紧急解锁命令
UINT8 VarCanGpsUrgencyPSDoK=0;				//Gps紧急解锁密码判断，1-密码正确，0-密码错误
UINT8 VarCanGpsUrgencyState;				//GPS紧急解锁状态，1-紧急解锁中
//*******工作小时计*******
UINT16 VarEngineWorkTime1S;					//发动机工作时间Second
UINT32 VarEngineWorkTime1H;					//发动机工作时间Hour
UINT32 VarEngineWorkTime_Gps;				//Gps紧急解锁时发动机工作小时
UINT16 VarEngineWorkTime1M;					//发动机工作时间Min					
UINT8 VarFlashEngineWorkTimeMasterNeedSaveFlag;//主存储区发动机工作时间参数需要保存标志位
UINT8 VarFlashEngineWorkTimeBackupNeedSaveFlag;//备份存储区发动机工作时间参数需要保存标志位
UINT8 VarEngineStarted;							//发动机启机过，1-启机过，0-无启机
UINT16 VarEngineTimeMasterCheckFlag;			//主存储区发动机工作时间参数保存校验数据，保存一次加1
UINT16 VarEngineTimeBackupCheckFlag;			//备份存储区发动机工作时间参数保存校验数据，保存一次加1
UINT16 VarFlashEngineTimeMasterAdr;				//发动机工作小时保存主存储地址
UINT8 VarFlashEngineWorkTimeMasterNeedSaveFlagIndex;//发动机工作小时保存主存储区地址改变需保存标志量
UINT16 VarFlashEngineTimeBackupAdr;					//发动机工作小时保存备份存储地址
UINT8 VarFlashEngineWorkTimeBackupNeedSaveFlagIndex;//发动机工作小时保存备份存储区地址改变需保存标志量
UINT16 VarEngineTimeMasterCheckFlagIndex;			//主存储区发动机工作时间地址参数保存校验数据，保存一次加1
UINT16 VarEngineTimeBackupCheckFlagIndex;			//备份存储区发动机工作时间地址参数保存校验数据，保存一次加1
UINT8 VarFlashHourNeedSaveMainFlag=0;					//主存储区发动机工作时间需保存标志量
UINT16 VarFlashHourMainAdrCheckFlag=0;				//备份存储区发动机工作时间需保存标志量
//********8
UINT8 VarCanMonitorNeedBellAlarm;					//显示屏报警信号
UINT16 VarCanExcavatorType;							//挖掘机型号
UINT16 VarCanExcavatorId;							//挖掘机机号
UINT8 VarCanAlarmNoVoiceFlag;						//报警
UINT32 VarMonitorPassword;							//显示屏动态密码





UINT16 VarPbPressure;
UINT16 VarPbPressureArray[20];

//*******************电喷发动机故障代码相关****************************
UINT8 VarCanEngineNoDataFlag=0;
UINT8 VarCanEcmNoDataFlag=0;
UINT8 VarIsuzuFaultCodeSingle = 0;
UINT8 VarIsuzuFaultCodeMany = 0;
UINT32 VarIsuzuSPN[100]=
{
	0
};
UINT8 VarIsuzuFMI[100]=
{
	0
};
UINT16 VarIsuzuCodeNumber=0;
UINT8 VarIsuzuFault[100][8]=
{
	0
};
UINT8 VarIszuFaultSPNNumber=0;
UINT8 VarCanInFuelFilterAlarm=0;
UINT8 VarCanInOilPreLowAlarm=0;
UINT8 VarCanInPreBoostAlarm=0;
UINT8 VarCanInFuelTemAlarm=0;
UINT8 VarCanInWaterTempAlarm=0;
UINT8 VarCanInStopUrgency=0;
UINT8 VarCanInFeicheAlarm=0;
UINT8 VarCanInPreheat=0;

//Uart
//串口通讯相关变量
UINT8 VarUartDataSendFlag=0;
UINT8 LibSciReadData[100];
//**********8test************
UINT16 VarUartFaultCode;
UINT16 VarEngineFaultCode2;
UINT16 VarEngineFaultCode3;
UINT16 VarEngineFaultCode4;
UINT16 VarEngineFaultCode5;
UINT16 VarEngineFaultCode6;

UINT16 VarP1PressureFilterHistory[6]=
{
	0,0,0,0,0,0
};
BOOL  VarP1PressureUpFlag=FALSE;

UINT16 VarP2PressureFilterHistory[6]=
{
	0,0,0,0,0,0
};
BOOL  VarP2PressureUpFlag=FALSE;

UINT32 VarCANIsuzuTime[3]={0,0,0};



UINT8 VarPAccumAirSensorError=0;
UINT8 VarValveDT1Error=0;
UINT8 VarValveDT2Error=0;
UINT16 VarPAccumAirPressureBar=0;


UINT8 VarSendDataID_0x0CF00330[8];
UINT8 VarSendDataID_0x18FDCB30[8];

UINT16 TempPressBigger;

UINT16 VarLoadMiddleStateTimer10Ms;
UINT16 VarLoadHeavyStateTimer10Ms;
UINT16 VarTempCureentTargetValue;
UINT16 VarSpeedLowTimer10Ms;
float VarTempCurrentTarget2;
float VarCurrentAddValue;
UINT8 VarCurrentReduceValue;


UINT8 VarDiFastReversingSw;
UINT8 VarHydraulicOilComputeNum=0;		//液压油温计算进行平均的基数
UINT8 VarHydraulicOilTemp=0;			//液压油温采样历史值
UINT16 VarHydraulicOilCompute[100]=
{
	0
};
UINT8 VarHydraulicOilTempFilter=0;
UINT8 VarHydraulicOilHighAlarmLimit=0;
UINT8 VarHydraulicOilHihgAlarm=0;
UINT8 VarHydraulicOilTempSensorError=0;

UINT8 VarDoHydraulicCoolingPositiveValve;
UINT8 VarDoHydraulicCoolingReverseValve;

UINT16 VarAiHydraulicTemp;     //液压油温 电阻，0.1R
UINT16 VarProHydraulicFANValveCurrentTarget;

UINT16 VarHydraulicCoolingPumpValveCurrent;//液压冷却泵当前电流

UINT8 VarHydraulicFanBool=0;
UINT8 VarCanAccHydraulicCoolingFWD;
UINT16 VarFANCurrent[11]; 

UINT8 VarDiStop=0;
UINT8 VarDoBuzzerAlarm=0;
UINT8    VarDoAirFilterPump;
UINT8     VarDoFuelFilterPump;
UINT8    VarAirFilterPump_Enable;
UINT8    VarFuelFilterPump_Enable;

 //PIDparams StructPwmDT1;
 //PIDparams StructPwmDT2;
 PIDparams StructPwmDT3;
 PIDparams StructPwmDT4;
 PIDparams StructPwmDT5;
// UINT16 VarDt1PwRatio;
// UINT16 VarDt2PwRatio;
 UINT16 VarDt3PwRatio;
 UINT16 VarDt4PwRatio;
 UINT16 VarDt5PwRatio;
 
 UINT8 VarCanSysHSLMode;			 
 UINT8 VarCanSysBKRMode;
 UINT8 VarSendDataID_0x18EA0028[8];
 UINT8 VarRecDataID_0x18FEB300[8];
 
 UINT16 VarLoadFreeStateTimer10Ms;
 UINT16 VarLowEngineAirPressureBar=145;
 UINT8 VarLowEnginePressureFlag=0;
 UINT32 VarEngineFuelYouHao;
 UINT32 VarEngineSpeedWorkTome;
 UINT16 VarResCompensation;
 UINT8 VarMode1ChangeFlag=0;


 UINT8 VarCanPumpMode=0;//H+模式，发动机转速为泵的额定转速
 UINT8 VarCanEngineMode=0;//E模式，发动机转速为发动机的额定转速
 UINT8 VarValveCurrentTargetoffset;
 UINT16 VarHydraulicOilTempCount; //液压油高温时间计数

 FLOAT32 VarEngineFuelYouHaoInt;
 FLOAT32 VarEngineSpeedWorkTomeInt;
 UINT32 VarEngineSpeedWorkTomeEnd;
 UINT16 VarEngineSpeedWorkTomeTime;
 UINT32 VarEngineFuelYouHaoEnd;
 UINT32 VarYouHaoInit = 41065;//40804
 UINT32 VarWorkTimeInt = 11278;//11215
 FLOAT64 VarTemp1;
 FLOAT32 VarSub1;
 UINT16 VarEngineInstantFuelYouHao;//发动机瞬时油耗
 FLOAT32 VarEngineSpeedWorkTome1;
 FLOAT32 VarEngineFuelYouHao1;
 FLOAT32 VarEngineFuelYouHaoTemp;
 FLOAT32 VarEngineSpeedWorkTomeTemp;
 
 
 UINT8 VarSendDataID200[8];
 UINT8 VarSendDataID201[8];
 UINT8 VarSendDataID203[8];
 UINT8 VarSendDataID209[8];
 UINT8 VarSendDataID20A[8];
 UINT8 VarSendDataID20C[8];
 UINT8 VarSendDataID20D[8];
 UINT8 VarSendDataID20E[8];
 UINT8 VarSendDataID20F[8];
 UINT8 VarSendDataID210[8];
 UINT8 VarSendDataID211[8];
 UINT8 VarSendDataID212[8];
 UINT8 VarSendDataID215[8];
 UINT8 VarSendDataID216[8];
 UINT8 VarSendDataID217[8];
 UINT8 VarSendDataID218[8];
 UINT8 VarSendDataID220[8];
 UINT8 VarSendDataID221[8];
 UINT8 VarSendDataID222[8];
 UINT8 VarSendDataID224[8];
 UINT8 VarSendDataID227[8];
 UINT8 VarSendDataID22F[8];
 UINT8 VarSendDataID231[8];
 UINT8 VarSendDataID233[8];
 UINT8 VarSendDataID21E[8];
 UINT8 VarSendDataID216[8];
 UINT8 VarSendDataID218[8];
 UINT8 VarSendDataID2E1[8];
 UINT8 VarSendDataID2F0[8];
 UINT8 VarSendDataID2F1[8];
 
 //控制器接收GPS
 UINT8 VarRecDataID300[8];
 UINT8 VarRecDataID303[8];
 UINT8 VarRecDataID321[8];
 UINT8 VarRecDataID322[8];
 UINT8 VarRecDataID323[8];
 
 //控制器接收显示屏
 UINT8 VarRecDataID101[8];
 UINT8 VarRecDataID102[8];
 UINT8 VarRecDataID106[8];
 UINT8 VarRecDataID107[8];
 UINT8 VarRecDataID110[8];
 UINT8 VarRecDataID111[8];
 UINT8 VarRecDataID112[8];
 UINT8 VarRecDataID115[8];
 
 UINT16 GPSStateByte;	//
 UINT8 SimCardLostAlarm;	//拔卡报警
 BOOL GPSPlatformConnetState;	//GPS与平台连接状态，0-异常，1-正常
 BOOL GPSPlatformConnetState_Last=0;
 
 UINT8 VarAutoIdleSpeedGrade=1;
 UINT8 VarManualIdleSpeedGrade=1;
 UINT8 EscapeModeButton;
 BOOL b_115=0;
 BOOL PumpPowerParaSend;		//泵功率发送标志位
 UINT16 SignalNumber_115;//0x115消息序号
 UINT8 OderType_115=0;//命令类型，x1:动态请求，x2:密码发送，1x:无信号，2x:永久解锁，3x:紧急解锁
 UINT32 GPSUnlockPSD=0;
 UINT16 SignalNumber_2E1;//0x2E1消息序号
 UINT8 GPSLock_All_Enable=1;		//锁车总使能,1-启用，0-停用
 UINT8 GPSLock_Passive_Enable=1;	//被动锁车总使能,1-启用，0-停用
 UINT8 MonthNoSignalLock_Enable=1;	//盲区锁车使能,1-启用，0-停用
 UINT8 UncoverLock_Enable=1;		//拆盖锁车使能,1-启用，0-停用
 UINT8 CANSignalLostLock_Enable=1;	//总线锁车使能,1-启用，0-停用
 UINT8 SIMCardLostLock_Enable=1;	//拔卡锁车使能,1-启用，0-停用
 
 UINT16 VarAftertreatmentDOCIntakeTemp;//后处理尾气温度(DOC前)
 UINT16 VarAftertreatmentDOCOutletTemp;//后处理尾气温度(DOC后)
 UINT8 VarIntakeManifoldTemp; //进气歧管内温度
 UINT8 VarInterCoolInletTemp; //中冷器入口温度
 UINT16 VarCommonRailPressure; //共轨压力
 UINT16 VarAftertreatmentDPFDifferentialPressure;//DPF尾气压差UINT8 
 UINT8 VarDPFRegenerationStatus;//DPF再生状态
 UINT8 VarDPFTripStatus;
 UINT8 VarDPFPMAccumulationStatus;//DPF PM堆积状态
 UINT16 VarDPFModeL;//DPF模式
 UINT8 VarModeSelectionError;
 UINT8 VarDoManualRegenrationLoad; //手动再生辅助负载电磁阀
 UINT8 VarManualRegenerationButton;		// 11-手动再生按键
 UINT8 VarRegenerationInhibitButton; 	// 12-再生禁止
 BOOL VarCanGpsUnlockPSDOK;	//GPS2月锁车解锁密码状态
 UINT16 VarBKRFlowNowCurrent=0;//辅具流量调节电磁阀当前电流
 UINT8 VarGpsLockState_B=0;			//Gps的B锁车状态
 UINT8 VarGpsLockState_C=0;			//Gps的C锁车状态
 UINT8 VarGpsLockState_D=0;			//Gps的D锁车状态
 UINT8 GPSUnLockStep=0;
 UINT16 SignalNumber_2F1;//0x2F1消息序号
 UINT32 DynamicCode_H=0;
 UINT32 DynamicCode_L=0;
 UINT8 OderType_2F1=0;//命令类型，x1:动态请求，x2:密码发送，1x:无信号，2x:永久解锁，3x:紧急解锁
 UINT8 GPSPSDVerify; 
 
 /****GPSLock***/
 BOOL TimeAvailable_1=0;
 UINT8 TimeAvailable;	//时间有效位
 UINT8 NoSignalStart_Year=0;	//无信号开始时间，年
 UINT8 NoSignalStart_Month=0;//无信号开始时间，月
 UINT8 NoSignalStart_Day=0;	//无信号开始时间，日
 UINT8 NoSignalTotal_Day=0;	//无信号总时间，日
 UINT8 EmergencyStart_Year=0;//紧急解锁开始时间，年
 UINT8 EmergencyStart_Month=0;//紧急解锁开始时间，月
 UINT8 EmergencyStart_Day=0;	//紧急解锁开始时间，日
 UINT8 EmergencyStart_Hour=0;//紧急解锁开始时间，时
 UINT8 EmergencyUnlock_Hour=0;//紧急解锁总时间
 
 UINT8 VarRecDataID_0x18FFF900[8];
 UINT8 VarRecDataID0x18FEB100[8];
 UINT8 VarRecDataID0x18FEE900[8];
 UINT8 VarRecDataID_0x18FED900[8];
 UINT8 VarAutoRegenerationLamp=0;//自动再生中(绿灯常亮)
 UINT8 VarRecDataID_0x18FFF800[8];
 UINT8 VarManualRegenerationLamp=0;//手动再生灯:1-橙灯常亮;2-橙灯慢闪;3-橙灯快闪;
 UINT8 VarDoManualRegenrationLoadEnabled; //手动再生辅助负载电磁阀使能
 UINT8 VarRecDataID_0x18FF0300[8];
 UINT8 GPSLock_Enable_Initial;
 UINT16 BreakHammerFrequencyTimes;
 UINT8 VarCanGpsLockCommandLast_A=0;	
 UINT8 VarCanGpsLockCommandLast_B=0;
 UINT8 VarCanGpsLockCommandLast_C=0;	
 UINT8 VarCanGpsLockCommandLast_D=0;
 UINT8 ClockTime_Year;	//时钟时间，年
 UINT8 ClockTime_Month;	//时钟时间，月
 UINT8 ClockTime_Day;	//时钟时间，日
 UINT8 ClockTime_Hour;	//时钟时间，时
 BOOL TimeCompare_1=0;
 UINT16 OderType_115_Last=0;
 UINT16 SignalNumber_115_Last=0;
 UINT32 GPSUnlockPSD_Last=0;
 UINT32 PSD=0;
 BOOL b_48Test=0;
 UINT8 VarEngineStop=0;//发动机停机信号(锁车B)
 UINT8 flag=0;
 
