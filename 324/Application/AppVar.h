#include "AppDefine.h"
extern UINT32 VarSysControlSerialID;
extern UINT8 VarCMCommunicationVersion;
extern UINT8 VarExcavatorMonitorType;//显示屏类型
//DI
extern UINT8 VarDiAirFilterAlarm;
extern UINT8 VarDiPreheat;
extern UINT8 VarDiTravelHighSpeed;
extern UINT8 VarDiPilot;
extern UINT8 VarDiLowSpeedEnable;
extern UINT8 VarSysPowerOn;
extern UINT8 VarDiCharge;
extern UINT8 VarDiPressureSwitch;  //辅具压力限值开关
//AI
extern UINT16 VarAiFuelVolume;
extern UINT16 VarAiEngineDial;
extern UINT16 VarAiPump1Pressure;
extern UINT16 VarAiPump2Pressure;
extern UINT16 VarAiPilotSwitch;
extern UINT16 VarAiAirFilter;
//Do
extern UINT8 VarDoSecondPressure;
extern UINT8 VarDoTravelHighSpeed;
extern UINT8 VarDoBatteryRelay;
extern UINT8 VarDoPilot;
extern UINT8 VarDoEngineStopRelay;
extern UINT8 VarDoValveBreakPilot; //辅具液压阀
extern UINT8 VarDoValvePressRegulate;//辅具压力限制阀
//PI
//extern UINT16 VarPiEngineSpeed;
//CAN
extern UINT8 VarSendDataID181[8];
extern UINT8 VarSendDataID281[8];
extern UINT8 VarSendDataID381[8];
extern UINT8 VarSendDataID481[8];
extern UINT8 VarSendDataID182[8];
extern UINT8 VarSendDataID282[8];
extern UINT8 VarSendDataID382[8];
//extern UINT8 VarSendDataID383[8];
//extern UINT8 VarSendDataID384[8];
//节能参数
extern UINT8 VarSendDataID236[8];
extern UINT8 VarSendDataID237[8];
extern UINT8 VarSendDataID238[8];
extern UINT8 VarSendDataID239[8];

extern UINT8 VarSendDataID187[8];
extern UINT8 VarSendDataID287[8];
extern UINT8 VarRecDataID116[8];//节能参数
extern UINT8 VarSendDataID387[8];
extern UINT8 VarSendDataID487[8];
extern UINT8 VarSendDataID1A0[8];
extern UINT8 VarSendDataID1A1[8];
extern UINT8 VarSendDataID1A2[8];
extern UINT8 VarCanSendDataStep;
extern UINT8 VarCanSendDataGpsStep;
extern UINT8 VarCanGpsCancelCommand;
extern UINT8 VarCanGpsCancelPSDoK;
extern UINT8 VarCanHighlandMode;     //0-普通模式，8-高原模式
//H bridge
extern UINT8 VarAccMotorMoveDir;
//System
extern UINT16 VarSysVoltageMv;
extern UINT16 VarSysVoltFilterLast;
//NEW
extern UINT8 VarCanEngineOilPreAlarm;
extern UINT8 VarCanEngineDialPosi;
extern INT8 VarCanEngineTorque;
extern UINT16 VarCanEngineSpeed;
extern UINT16 VarCanEngineTargetSpeed;
extern UINT8 VarCanEngineWaterTemp;
extern UINT16 VarCanEngineOilPressure;
extern INT16 VarCanEngineAirInTemp;
extern UINT16 VarCanEngineOilFlowRate;
extern UINT16 VarCanEngineAtmosPressrue;
extern UINT16 VarCanEngineBoostPressrue;
extern INT16 VarCanEngineBoostTemp;
extern UINT16 VarCanEngineFuelWastageAll;
extern UINT8 VarCanSendEngineStep;
extern UINT8 VarRecDataID_0CF00300[8];
extern UINT8 VarRecDataID_0CF00400[8];
extern UINT8 VarRecDataID_18FEDF00[8];
extern UINT8 VarRecDataID_0x18FEEE00[8];
extern UINT8 VarRecDataID_0x18FEEF00[8];
extern UINT8 VarRecDataID_0x18FEF200[8];
extern UINT8 VarRecDataID_0x18FEF500[8];
extern UINT8 VarRecDataID_0x18FEF600[8];
extern UINT8 VarRecDataID_0x18FEF900[8];
extern UINT8 VarRecDataID_0x1CEBFF00[8];
extern UINT8 VarRecDataID_0x1CECFF00[8];
extern UINT8 VarRecDataID_0x18FECA00[8];
extern UINT8 VarSendDataID_0x0C0000E4[8];
extern UINT8 VarSendDataID_0x18FEE4E4[8];
extern UINT8 VarSendDataID_0x0C000003[8];
extern UINT8 VarSendDataID_0x18EA0021[8];
extern UINT8 VarSendDataID_0x18EA00F2[8];
extern UINT8 VarRecDataID_0x18ECFF00[8];
extern UINT8 VarRecDataID_0x18EBFF00[8];//潍柴发动机多故障代码
extern UINT8 VarRecDataID_0x18FEE900[8];//五十铃油耗数据
extern UINT8 VarRecDataID_0x18FEB100[8];
extern UINT8 VarSendDataID0x18EA00FA[8];
extern UINT16 VarEngineAverageFuelYouHao;
extern UINT8 VarEngineNeedStopFlag;//机油压力低停机
//***************Control***********************
extern UINT8 VarDiLowSpeedEnableLast;
extern UINT16 VarEngineLevelSpeed[11];
extern UINT16 VarCanEngineLevelSpeed;
extern UINT8 VarButtonLowSpeedEnable;
extern UINT8 VarSetAccMotorCommand;
extern UINT16 VarSetAccMotorMoveDoneTime1Ms;
extern UINT16 VarSetAccMotorMoveCount;
extern UINT16 VarEngineTorque;
extern UINT16 VarAccMotorPosi[100];
extern UINT16 VarEngineSpeed[100];
extern UINT16 VarAccMotorPosiNow;
extern UINT16 VarAccDialPosiNow;
extern UINT16 VarAccDialPosiLast;
extern UINT8 VarDialGrade;
extern UINT16 VarAccMotorPosiTarget;
extern UINT16 VarAccMotorPosiSet[10];
extern UINT16 VarAccMotorMoveTime1Ms;
extern UINT16 VarAccMotorStopTime1Ms;
extern UINT8 VarAccMotorMoveState;
extern UINT32 VarAccMotorTimerLast;
extern UINT16 VarAccMotorPosiTargetLast;
extern UINT8 VarAccMotorStopJiggle;
extern UINT8 VarEngineSpeedSetGradeTargetLast;
extern UINT8 VarTargetGradeSetState;
extern UINT16 VarAccMotorMoveTimeExtra;

extern UINT16 VarCanAccMotorPosiMaxLimit;
extern UINT16 VarCanAccMotorPosiMinLimit;

extern UINT8 VarCanAccDialSetCommand;
extern UINT8 VarAccDialPosiSetting;
extern UINT32 VarAccDialPosiSetTimeLast;
extern UINT8 VarCanAccDialSetCommandLast;
extern UINT8 VarDialSetSortLast;
extern UINT16 VarAccDialPosiMax;
extern UINT16 VarAccDialPosiMin;
extern UINT8 VarCanEngineSpeedSet;
extern UINT8 VarCanEngineSpeedSetLast;
extern UINT8 VarEngineSpeedSetCommand;
extern UINT8 VarEngineSpeedSetState;
extern UINT8 VarEngineSpeedSetGradeTarget;
extern UINT16 VarEngineSpeedSet[11];
extern UINT8 VarSetAutoMotorPosiOk;
extern UINT16 VarEngineSpeedNow;
extern UINT8 VanEngineTimeSetPSDSendFlag;
extern UINT8 VanEngineTimeSetPSDoKFlag;
//CAN
extern UINT8 VarCanAccDialPosiMinSet;
extern UINT8 VarCanAccDialPosiMaxSet;

//临时测试用
extern UINT8 VarMoveTimes;
extern UINT16 VarEngineSpeedTarget;

//AI转换为物理量相关变量定义
extern UINT8 VarFuelComputeNum;
extern UINT16 VarFuelCompute[100];
extern UINT8 VarFuelVolume;
extern UINT8 VarFuelLackAlarm;
extern UINT8 VarFuelSensorError;
extern UINT8 VarWaterComputeNum;
extern UINT16 VarWaterCompute[100];
extern UINT8 VarWaterTemp;
extern UINT8 VarCanWaterHihgAlarm;
extern UINT8 VarWaterTempSensorError;
extern UINT8 VarP1PressureSensorEorror;
extern UINT16 VarP1PressureArray[20];
extern UINT16 VarP1Pressure;
extern UINT8 VarP2PressureSensorEorror;
extern UINT16 VarP2PressureArray[20];
extern UINT16 VarP2Pressure;
//extern UINT16 VarPiPressure;
extern UINT16 VarSysAveragePress;
extern UINT16 VarP2PressureFilter;
extern UINT16 VarP1PressureFilter;
extern UINT16 VarPiPressureFilter;
extern UINT8 VarPiPressureSensorEorror;      //先导泵压力传感器故障
extern UINT16 VarPiPressureArray[20];
extern UINT8 VarDialSensorError;
extern UINT8 VarAccMotorSensorError;
extern UINT8 VarFuelVolumeFilter;
extern UINT16 VarValveErrorTime1S;
extern UINT8 VarEngineSpeedSensorError;
extern UINT8 VarEngineWorkErrorTime1S;
//*******
extern BOOL VarCanAutoIdleEnable;
extern UINT16 VarCanP1PressureIdleLimit;
extern UINT16 VarCanP2PressureIdleLimit;
extern BOOL VarstartIdle;
extern UINT8 VarIdleState;
extern UINT32 VarIdleTimer;
extern BOOL VarCurrentIdleDelay;
extern UINT8 VarPumpPowerParameter[8];          //液压泵功率点
//******
extern BOOL VarCanHighSpeedTravel;
//***
extern UINT8 VarCanSysHSLBKRMode;
extern UINT8 VarHydHammerFlow;                //液压锤流量值
extern UINT8 VarHydSicissorsFlow;             //液压剪流量值
extern UINT8 VarHydRamFlow;                   //液压夯流量值
extern UINT16 VarProValveCurrentTarget;       //液压辅具阀目标电流值
//****
extern UINT8 VarSpeedLevel;
extern BOOL VarEngineStartState;
extern BOOL VarEngineWarmState;
extern BOOL VarEngineCoolState;
extern BOOL VarSysSleepCommand;
extern BOOL VarEngineWarmDone;
extern UINT32 VarEngineWarmStartTime;
extern UINT16 VarValveCurrent[11];
extern UINT16 VarValveCurrentTarget;
extern UINT32 TempCurrentTarget;
extern UINT16 CurrentOffset;
extern UINT8 VarCurrentLevel;
extern UINT16 VarValvePwRatio;
extern UINT16 VarValveCurrentNow;
extern UINT16 VarAssValveCurrentNow;          //辅具流量调节电磁阀当前电流
extern UINT8 VarValveRatioKp;
extern UINT8 VarValveRatioKi;
extern UINT8 VarValveRatioKd;
extern INT32 x[3];
extern float D_Output;
extern float D_Last;
extern INT32 PID_Error_1;
extern INT16 PID_Error_2;
extern UINT8 VarValveError;
extern UINT8 VarCanEngineTimeSetFlag;
extern UINT8 VarCanEngineTimeSetPSDoK;
extern UINT32 VarCanEngineTimeSetPSD;
extern UINT16 VarCanEngineTimeSetHour;
extern UINT8 VarExcavatorEngineType;          //电喷发动机:0-康明斯，1-五十铃，2-潍柴
//****************GPS锁车相关参数***********************
extern UINT8 VarGpsLockState_A;
extern UINT8 VarCanGpsLockCommand_A;
extern UINT8 VarCanGpsCancel;
extern BOOL VarGpsLockWork_A;
extern UINT8 VarGpslockState_B;
extern UINT8 VarCanGpsLockCommand_B;
extern BOOL VarGpsLockWork_B;
extern UINT8 VarGpslockState_C;
extern UINT8 VarCanGpsLockCommand_C;
extern BOOL VarGpsLockWork_C;
extern UINT8 VarGpslockState_D;
extern UINT8 VarCanGpsLockCommand_D;
extern UINT8 VarGpsLockWork_D;
extern UINT8 VarCanGpsHeartBeatLast;
extern UINT8 VarCanGpsHeartBeat;
extern UINT8 VarGpsCanNoBeat;
extern UINT8 VarGpsCanErrorState;
extern BOOL VarGpsCanBusError;
extern UINT8 VarCanBusLockCommand;
extern UINT8 VarCanBusLockState;
extern UINT8 VarCan2MonthLockCommand;
extern UINT8 VarCan2MonthLockState;
extern UINT8 VarCanAntennaCut;
extern UINT8 VarCanAntennaCutLockState;
extern UINT8 VarCanAntennaCutLockCommand;
extern UINT8 VarCanUncoverLockCommand;
extern UINT8 VarCanUncoverLockState;
extern BOOL VarGpsLockEnginePower;
extern BOOL VarGpsLockPumpPower;
extern BOOL VarCan2MonthLockCancel;
extern UINT8 VarGpsSIMCardError;           //GPS设备的SIM卡故障
extern UINT8 VarCanSendGps1F1[8];
extern UINT8 VarCanSendGps1F2[8];
extern UINT8 VarCanSendGps1F3[8];
extern UINT8 VarCanSendGps1F4[8];
extern UINT8 VarCanSendGps1F5[8];
extern UINT8 VarCanSendGps1F6[8];
extern UINT8 VarCanSendGps1F7[8];
extern UINT8 VarCanSendGps1FC[8];
extern UINT8 VarCanSendGps1FD[8];
extern UINT32 VarCanGpsUnlockPSD;
extern UINT8 VarCanSendGpsStep;
extern UINT8 VarCanGpsRx1EF[8];
extern UINT8 VarCanGpsRx1FB[8];
extern UINT8 VarCanGpsRx1EE[8];
extern UINT8 VarCanGpsTemper;
extern UINT32 VarGpsAntennaCut_Et;
extern UINT32 VarGpsCanBusError_Et;
extern UINT8 VarCanGpsSendUnlockPSDFlag;
//******************FLASH********************
extern UINT8 VarFlashSysDateMasterNeedSaveFlag;
extern UINT8 VarFlashSysDateBackupNeedSaveFlag;
extern UINT16 VarSysDataMasterCheckFlag;
extern UINT16 VarSysDataBackupCheckFlag;
extern UINT8 VarFlashGpsDataMasterNeedSaveFlag;
extern UINT8 VarFlashGpsDataBackupNeedSaveFlag;
extern UINT16 VarGpsDataMasterCheckFlag;
extern UINT16 VarGpsDataBackupCheckFlag;
extern UINT32 VarCanGpsCacelPSD;
extern UINT32 VarCanGpsUrgencyPSD;
extern UINT8 VarCanGpsUrgencyCommand;
extern UINT8 VarCanGpsUrgencyPSDoK;
extern UINT8 VarCanGpsUrgencyState;
//*******工作小时计*******
extern UINT16 VarEngineWorkTime1S;
extern UINT32 VarEngineWorkTime1H;
extern UINT16 VarEngineWorkTime1M;
extern UINT32 VarEngineWorkTime_Gps;
extern UINT8 VarFlashEngineWorkTimeMasterNeedSaveFlag ;
extern UINT8 VarFlashEngineWorkTimeBackupNeedSaveFlag;
extern UINT8 VarEngineStarted;
extern UINT16 VarEngineTimeMasterCheckFlag;
extern UINT16 VarEngineTimeBackupCheckFlag;
extern UINT16 VarFlashEngineTimeMasterAdr;
extern UINT8 VarFlashEngineWorkTimeMasterNeedSaveFlagIndex;
extern UINT16 VarFlashEngineTimeBackupAdr;
extern UINT8 VarFlashEngineWorkTimeBackupNeedSaveFlagIndex;
extern UINT16 VarEngineTimeMasterCheckFlagIndex;
extern UINT16 VarEngineTimeBackupCheckFlagIndex;
extern UINT8 VarFlashHourNeedSaveMainFlag;
extern UINT16 VarFlashHourMainAdrCheckFlag;
//********8
extern UINT8 VarCanMonitorNeedBellAlarm;
extern UINT16 VarCanExcavatorType;
extern UINT16 VarCanExcavatorId;
extern UINT8 VarCanAlarmNoVoiceFlag;
extern UINT32 VarMonitorPassword;




extern UINT16 VarPbPressure;
extern UINT16 VarPbPressureArray[20];

//*******************电喷发动机故障代码相关****************************
extern UINT8 VarCanEngineNoDataFlag;
extern UINT8 VarCanEcmNoDataFlag;
extern UINT8 VarIsuzuFaultCodeSingle;
extern UINT8 VarIsuzuFaultCodeMany;
extern UINT32 VarIsuzuSPN[100];
extern UINT8 VarIsuzuFMI[100];
extern UINT16 VarIsuzuCodeNumber;
extern UINT8 VarIsuzuFault[100][8];
extern UINT8 VarIszuFaultSPNNumber;
extern UINT8 VarIszuFaultSPNNumber;
extern UINT8 VarCanInFuelFilterAlarm;
extern UINT8 VarCanInOilPreLowAlarm;
extern UINT8 VarCanInPreBoostAlarm;
extern UINT8 VarCanInFuelTemAlarm;
extern UINT8 VarCanInWaterTempAlarm;
extern UINT8 VarCanInStopUrgency;
extern UINT8 VarCanInFeicheAlarm;
extern UINT8 VarCanInPreheat;
//uart
extern UINT8 VarUartDataSendFlag;
extern UINT8 LibSciReadData[100];
//**************test***************
extern UINT16 VarUartFaultCode;
extern UINT16 VarEngineFaultCode2;
extern UINT16 VarEngineFaultCode3;
extern UINT16 VarEngineFaultCode4;
extern UINT16 VarEngineFaultCode5;
extern UINT16 VarEngineFaultCode6;

extern UINT16 VarP1PressureFilterHistory[6];
extern BOOL  VarP1PressureUpFlag;
extern UINT16 VarP2PressureFilterHistory[6];

extern UINT8 VarPAccumAirSensorError;
extern UINT8 VarValveDT1Error;
extern UINT8 VarValveDT2Error;
extern UINT16 VarPAccumAirPressureBar;//蓄能器气体压力值bar
extern BOOL  VarP2PressureUpFlag;

extern UINT32 VarCANIsuzuTime[3];

extern UINT8 VarSendDataID_0x0CF00330[8];
extern UINT8 VarSendDataID_0x18FDCB30[8];



extern UINT16 TempPressBigger;
extern UINT16 VarLoadFreeStateTimer10Ms;
extern UINT16 VarLoadMiddleStateTimer10Ms;
extern UINT16 VarLoadHeavyStateTimer10Ms;
extern UINT16 VarTempCureentTargetValue;
extern UINT16 VarSpeedLowTimer10Ms;
extern float VarTempCurrentTarget2;
extern float VarCurrentAddValue;


extern UINT8 VarDiFastReversingSw;
extern UINT8 VarHydraulicOilComputeNum;		//液压油温计算进行平均的基数
extern UINT8 VarHydraulicOilTemp;			//液压油温采样历史值
extern UINT16 VarHydraulicOilCompute[100];
extern UINT8 VarHydraulicOilTempFilter;
extern UINT8 VarHydraulicOilHighAlarmLimit;
extern UINT8 VarHydraulicOilHihgAlarm;
extern UINT8 VarHydraulicOilTempSensorError;

extern UINT8 VarDoHydraulicCoolingPositiveValve;
extern UINT8 VarDoHydraulicCoolingReverseValve;

extern UINT16 VarAiHydraulicTemp;     //液压油温 电阻，0.1R

extern UINT16 VarProHydraulicFANValveCurrentTarget;
extern UINT16 VarHydraulicCoolingPumpValveCurrent;//液压冷却泵当前电流

extern UINT8 VarCanAccHydraulicCoolingFWD;

extern UINT8 VarHydraulicFanBool;
extern UINT16 VarFANCurrent[11]; 


extern UINT8 VarDiStop;
extern UINT8 VarDoBuzzerAlarm;

extern UINT8    VarDoAirFilterPump;
extern UINT8    VarDoFuelFilterPump;
extern UINT8    VarAirFilterPump_Enable;
extern UINT8    VarFuelFilterPump_Enable;



//extern PIDparams StructPwmDT1;
//extern PIDparams StructPwmDT2;
extern PIDparams StructPwmDT3;
extern PIDparams StructPwmDT4;
extern PIDparams StructPwmDT5;
//extern UINT16 VarDt1PwRatio;
//extern UINT16 VarDt2PwRatio;
extern UINT16 VarDt3PwRatio;
extern UINT16 VarDt4PwRatio;
extern UINT16 VarDt5PwRatio;

 extern UINT8 VarCanSysHSLMode;			 
 extern UINT8 VarCanSysBKRMode;
 extern UINT8 VarSendDataID_0x18EA0028[8];
 extern UINT8 VarRecDataID_0x18FEB300[8];
 extern UINT8 VarCurrentReduceValue;
 
 extern UINT16 VarLowEngineAirPressureBar;
 extern UINT8 VarLowEnginePressureFlag;
 extern UINT32 VarEngineFuelYouHao;
 extern UINT32 VarEngineSpeedWorkTome;
 
 extern UINT16 VarResCompensation;//燃油校正中间变量
 extern UINT8 VarMode1ChangeFlag;

 
 extern UINT16 VarHydraulicOilTempCount; //液压油高温时间计数
 extern UINT8 VarCanPumpMode;//H+模式，发动机转速为泵的额定转速
 extern UINT8 VarCanEngineMode;//E模式，发动机转速为发动机的额定转速
 extern UINT8 VarValveCurrentTargetoffset;
 extern FLOAT32 VarEngineFuelYouHaoInt;
 extern FLOAT32 VarEngineSpeedWorkTomeInt;
 extern UINT32 VarEngineSpeedWorkTomeEnd;
 extern UINT16 VarEngineSpeedWorkTomeTime;
 extern UINT32 VarEngineFuelYouHaoEnd;
 extern UINT32 VarYouHaoInit;
 extern UINT32 VarWorkTimeInt;
 extern FLOAT64 VarTemp1;
 extern FLOAT32 VarSub1;
 extern UINT16 VarEngineInstantFuelYouHao;//发动机瞬时油耗
 extern FLOAT32 VarEngineSpeedWorkTome1;
 extern FLOAT32 VarEngineFuelYouHao1;
 extern FLOAT32 VarEngineFuelYouHaoTemp;
 extern FLOAT32 VarEngineSpeedWorkTomeTemp;
 
 
 extern UINT8 VarSendDataID200[8];
 extern UINT8 VarSendDataID201[8];
 extern UINT8 VarSendDataID203[8];
 extern UINT8 VarSendDataID209[8];
 extern UINT8 VarSendDataID20A[8];
 extern UINT8 VarSendDataID20C[8];
 extern UINT8 VarSendDataID20D[8];
 extern UINT8 VarSendDataID20E[8];
 extern UINT8 VarSendDataID20F[8];
 extern UINT8 VarSendDataID210[8];
 extern UINT8 VarSendDataID211[8];
 extern UINT8 VarSendDataID212[8];
 extern UINT8 VarSendDataID215[8];
 extern UINT8 VarSendDataID216[8];
 extern UINT8 VarSendDataID217[8];
 extern UINT8 VarSendDataID218[8];
 extern UINT8 VarSendDataID220[8];
 extern UINT8 VarSendDataID221[8];
 extern UINT8 VarSendDataID222[8];
 extern UINT8 VarSendDataID224[8];
 extern UINT8 VarSendDataID227[8];
 extern UINT8 VarSendDataID22F[8];
 extern UINT8 VarSendDataID231[8];
 extern UINT8 VarSendDataID233[8];
 extern UINT8 VarSendDataID21E[8];
 extern UINT8 VarSendDataID216[8];
 extern UINT8 VarSendDataID218[8];
 extern UINT8 VarSendDataID2E1[8];
 extern UINT8 VarSendDataID2F0[8];
 extern UINT8 VarSendDataID2F1[8];
 
 //控制器接收显示屏
 extern UINT8 VarRecDataID101[8];
 extern UINT8 VarRecDataID102[8];
 extern UINT8 VarRecDataID106[8];
 extern UINT8 VarRecDataID107[8];
 extern UINT8 VarRecDataID110[8];
 extern UINT8 VarRecDataID111[8];
 extern UINT8 VarRecDataID112[8];
 extern UINT8 VarRecDataID115[8];
 
 //控制器接收GPS
 extern UINT8 VarRecDataID300[8];
 extern UINT8 VarRecDataID303[8];
 extern UINT8 VarRecDataID321[8];
 extern UINT8 VarRecDataID322[8];
 extern UINT8 VarRecDataID323[8];
 
 extern UINT16 GPSStateByte;	//
 extern UINT8 SimCardLostAlarm;	//拔卡报警
 extern BOOL GPSPlatformConnetState;	//GPS与平台连接状态，0-异常，1-正常
 extern BOOL GPSPlatformConnetState_Last;
 
 extern UINT8 VarAutoIdleSpeedGrade;
 extern UINT8 VarManualIdleSpeedGrade;
 extern UINT8 EscapeModeButton;
 extern b_115;
 extern BOOL PumpPowerParaSend;
 extern UINT16 SignalNumber_115;//消息序号
 extern UINT8 OderType_115;
 extern UINT32 GPSUnlockPSD;
 extern UINT16 SignalNumber_2E1;//0x2E1消息序号
 extern UINT8 GPSLock_All_Enable;		//锁车总使能,1-启用，0-停用
 extern UINT8 GPSLock_Passive_Enable;	//被动锁车总使能,1-启用，0-停用
 extern UINT8 MonthNoSignalLock_Enable;	//盲区锁车使能,1-启用，0-停用
 extern UINT8 UncoverLock_Enable;		//拆盖锁车使能,1-启用，0-停用
 extern UINT8 CANSignalLostLock_Enable;	//总线锁车使能,1-启用，0-停用
 extern UINT8 SIMCardLostLock_Enable;	//拔卡锁车使能,1-启用，0-停用
 extern UINT16 VarAftertreatmentDOCIntakeTemp;//后处理尾气温度(DOC前)
 extern UINT16 VarAftertreatmentDOCOutletTemp;//后处理尾气温度(DOC后)
 extern UINT8 VarIntakeManifoldTemp; //进气歧管内温度
 extern UINT8 VarInterCoolInletTemp; //中冷器入口温度
 extern UINT16 VarCommonRailPressure; //共轨压力
 extern UINT16 VarAftertreatmentDPFDifferentialPressure;//DPF尾气压差
 extern UINT8 VarDPFRegenerationStatus;//DPF再生状态
 extern UINT8 VarDPFTripStatus;
 extern UINT8 VarDPFPMAccumulationStatus;//DPF PM堆积状态
 extern UINT16 VarDPFModeL;//DPF模式
 extern UINT8 VarModeSelectionError;
 extern UINT8 VarDoManualRegenrationLoad; //手动再生辅助负载电磁阀
 extern UINT8 VarManualRegenerationButton;		// 11-手动再生按键
 extern UINT8 VarRegenerationInhibitButton; 	// 12-再生禁止
 extern BOOL VarCanGpsUnlockPSDOK;
 extern UINT16 VarBKRFlowNowCurrent;//辅具流量调节电磁阀当前电流
 extern UINT8 VarGpsLockState_B;
 extern UINT8 VarGpsLockState_C;
 extern UINT8 VarGpsLockState_D;
 extern UINT8 GPSUnLockStep;
 extern UINT16 SignalNumber_2F1;
 extern UINT32 DynamicCode_H;
 extern UINT32 DynamicCode_L;
 extern UINT8 OderType_2F1;
 extern UINT8 GPSPSDVerify; 
 
 extern BOOL TimeAvailable_1;
 extern UINT8 TimeAvailable;//时间有效位
 extern UINT8 NoSignalStart_Year;	//无信号开始时间，年
 extern UINT8 NoSignalStart_Month;	//无信号开始时间，月
 extern UINT8 NoSignalStart_Day;		//无信号开始时间，日
 extern UINT8 NoSignalTotal_Day;	//无信号总时间，日
 extern UINT8 EmergencyStart_Year;//无信号开始时间，年
 extern UINT8 EmergencyStart_Month;//无信号开始时间，月
 extern UINT8 EmergencyStart_Day;	//无信号开始时间，日
 extern UINT8 EmergencyStart_Hour;//无信号开始时间，时
 extern UINT8 EmergencyUnlock_Hour;//紧急解锁总时间
 
 extern UINT8 VarRecDataID_0x18FFF900[8];
 extern UINT8 VarRecDataID0x18FEB100[8];
 extern UINT8 VarRecDataID0x18FEE900[8];
 extern UINT8 VarRecDataID_0x18FED900[8];
 extern UINT8 VarAutoRegenerationLamp;//自动再生中(绿灯常亮)
 extern UINT8 VarRecDataID_0x18FFF800[8];
 extern UINT8 VarManualRegenerationLamp;//手动再生灯:1-橙灯常亮;2-橙灯慢闪;3-橙灯快闪;
 extern UINT8 VarDoManualRegenrationLoadEnabled; //手动再生辅助负载电磁阀使能
 extern UINT8 VarRecDataID_0x18FF0300[8];
 extern UINT8 GPSLock_Enable_Initial;
 extern UINT16 BreakHammerFrequencyTimes;
 extern UINT8 VarCanGpsLockCommandLast_A;
 extern UINT8 VarCanGpsLockCommandLast_B;
 extern UINT8 VarCanGpsLockCommandLast_C;
 extern UINT8 VarCanGpsLockCommandLast_D;
 extern UINT8 ClockTime_Year;//时钟时间，年
 extern UINT8 ClockTime_Month;//时钟时间，月
 extern UINT8 ClockTime_Day;//时钟时间，日
 extern UINT8 ClockTime_Hour;	//时钟时间，时
 extern BOOL TimeCompare_1;
 extern UINT16 SignalNumber_115_Last;
 extern UINT16 OderType_115_Last;
 extern UINT32 GPSUnlockPSD_Last;
 extern UINT32 PSD;
 extern BOOL b_48Test;
 extern UINT8 VarEngineStop;//发动机停机信号(锁车B)
 extern UINT8 flag;
