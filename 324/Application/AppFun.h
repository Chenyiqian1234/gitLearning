#include "AppDefine.h"
//主循环函数定义
void FunControlGpsLock(void);
void FunAutoIdle(void);
void FunTemperatureCotrol(void);
void FunTravelSpeed(void);
void FunSecondPressure(void);
void FunSpeedControl(void);
void FunPumpCurrent(void);
void FunSysSleep(void);
void FunSysWorkTimeCompute(void);
void FunAssistantSet(void);

//CAN与显示屏通讯
void FunCanDataDeal(void);
void FunCanDisplayGpsPackSendData(void);
void FunCanDisplayGpsSendData(void);
void FunCanDisplayGpsReceiveData(void);

void FunCanReceiveEngineData(void);
void FunCanSendCumminsDataPack(void);
void FunCanSendEngineDataPack(void);
void FunCanSendWeiChaiDataPack(void);
void FunCanSendISUZUDataPack(void);

void FunCanSendEngineData(void);
void FunCanReceiveCumminsData(void);
void FunCanReceiveISUZUData(void);
void FunCanReceiveWeiChaiData(void);

//标定相关
void FunDialSpeedSet(void);
void FunDialSet(UINT8);
UINT8 FunDialGradeCal(UINT16,UINT16);
void FunFlashWtiteWorkTimeAdrCommand(UINT8);

//IO端口采样与设置
void FunIOSample(void);
void FunDiSample(void);	//Di采样
void FunAiSample(void);	//Ai采样
void FunDoSet(void);	//置Do
void FunRatoteCotrol(void);
//Flash读取相关函数
void FunFlashLoop(void);
void FunFlashInit(void);	 //Flash的初始化
void FunFlashWriteData(void);//Flash写数据
UINT8 FunFlashWriteGpsData(UINT16 DataAdrStart,UINT16 *Check_Flag);//保存GPS数据
//从Flash中读取GPS数据
UINT8 FunFlashReadGpsData(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag);
UINT32 FunGetTwoWord(UINT16 Low16,UINT16 High16);
UINT8 FunFlashWriteSysData(UINT16 Adr_Start,UINT16 *Check_Flag);
void FunFlashWriteSysDataCommand(UINT8 Sort);
void FunFlashWriteSysDataCommand(UINT8 Sort);
void FunFlashWriteGpsDataCommand(UINT8 Sort);
void FunFlashWriteGpsDataCommand(UINT8 Sort);
UINT8 FunFlashReadSysData(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag);
void FunFlashWriteWorkTimeCommand(UINT8 Sort);
UINT8 FunFlashWriteEngineWorkTimeData(UINT16 DataAdrStart,UINT16 *Check_Flag);
UINT8 FunFlashReadEngineWorkTime(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag);
UINT8 FunFlashWriteEngineTimeAdr(UINT8 Sort,UINT16 *Check_Flag);
void FunFlashReadEngineTimeAdr(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag);
void FunFlashWriteWorkTimeHourMainCommand(void);
UINT8 FunFlashWriteHourMain(UINT16 Adr_Start,UINT16 *Check_Flag);
UINT8 FunFlashReadEngineTimeMain(UINT16 DataAdrStart,UINT16 *Check_Flag,UINT32 *GetHourTime);
//泵的压力计算
UINT16 FunPressureCompute(UINT16 VarAiPressure);
//发动机冷却水温计算
UINT8 FunWaterTemCompute(UINT16 Res);
//燃油量计算
UINT8 FunFuelVolumeCompute(UINT16 Res);
//电磁比例阀的占空比PID计算,只加入比例、积分环节
UINT16 FunValveRatioComputePID(UINT16 Current_Target,UINT16 Current_Now,UINT8 Kp,UINT8 Ki,UINT8 Kd);
UINT16 FunValveRatioComputePID_1(UINT16 Current_Target,UINT16 Current_Now,UINT8 Kp,UINT8 Ki,UINT8 Kd);
//Sort:0-发动机工作时间清零密码，1-GPS取消密码，2-紧急解锁密码，3-发动机工作小时设置密码，4-显示屏密码,返回0-读取成功
UINT8 FunSystemPasswordComput(UINT8 Sort,UINT32 *Password_1,UINT32 WorkTime_H,UINT16 WorkTime_M,UINT32 Machine_ID);
//发动机故障诊断
void FunISUZUFaultCodeDiagnose(void);
void FunISUZUFaultSPNCodeGet(void);
void FunCumminsFaultSPNCodeGet(void);
void FunCumminsFaultCodeDiagnose(void);
void FunWeiChaiFaultSPNCodeGet(void);
void FunWeiChaiFaultCodeDiagnose(void);

//串口通讯相关程序
void FunUartReceiveData(void);
void FunUartSendData(void);
void FunUartSendDataDiDo(void);
void FunUartSendDataFuju(void);
void FunUartSendDataAI(void);
void FunUartSendDataExcavator(void);
void FunUartSendDataBiaoding(void);
void FunUartSendDataGps(void);
void FunUartSendDataFlash(void);
void FunUartSendDataSpeed(void);



UINT16 FunLowerPressureCompute(UINT16 VarAiPressure);


//液压油温计算

UINT8 FunHydraulicOilTemCompute(UINT16 Res);

void FunHydraulicCoolingPumpCurrent(void);


void FunClearPIDparams(PIDparams *Params);
INT32 FunPID(INT32 MeasPoint,INT32 SetPoint,PIDparams *Params,INT32 Error,UINT32 Interval,BOOL Enable);

void FunBuzzerAlarm(void);
void FunFuelAirFitlerControl(void);
void FunSwitchValveControl(void);

BOOL IsLeap(UINT16 year);
BOOL IsTimeAvailable(UINT16 year,UINT16 month, UINT16 day,UINT8 hour);
UINT16 DayInYear(UINT16 year, UINT16 month, UINT16 day);
UINT16 DaysBetween2Date(UINT16 year1, UINT16 month1, UINT16 day1,UINT16 year2, UINT16 month2, UINT16 day2);
UINT16 HoursBetween2Date(UINT16 year1, UINT16 month1, UINT16 day1,UINT8 hour1, UINT16 year2, UINT16 month2, UINT16 day2, UINT8 hour2);
BOOL TimeCompare(UINT16 year1, UINT16 month1, UINT16 day1,UINT8 hour1, UINT16 year2, UINT16 month2, UINT16 day2, UINT8 hour2);

