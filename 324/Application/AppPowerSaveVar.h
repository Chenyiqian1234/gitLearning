#include "AppDefine.h"

extern UINT16 VarAiBoomUpPressure;
extern UINT16 VarAiBoomDownPressure;

//SWE330节能项目另加变量
extern UINT8 VarDiBoomUp;//动臂上升
extern UINT8 VarDiBoomDown;//动臂下降
extern UINT8 VarDoDT1;
extern UINT8 VarDoDT2;
extern UINT8 VarDoDT3;
extern UINT8 VarDoDT4;
extern UINT8 VarDoDT5;
extern UINT8 VarDoDT6;
extern UINT8 VarDoDT7;
extern UINT8 VarDoDT8;  //GJ
extern UINT8 VarDoDT9;   //GJ
extern UINT8 VarBoomUpFlag;
extern UINT8 VarBoomDownFlag;
extern UINT16 VarAiAccumPressure;//pin19,蓄能器压力,单位uA
extern UINT16 VarAiBoomPolePressure;
extern UINT16 VarPAccumPressureFilter;
extern UINT16 VarPBoomPressureFilter;
extern UINT8 VarBoomPowerSaveFlag;//动臂节能模式
extern UINT8 VarAccumDischargeFlag;
extern UINT8 VarRatatorPowerSaveFlag;//回转节能模式
extern UINT8 VarDiTreadPre;
extern UINT16 FlagBoomUpPilot;  //GJ
extern UINT16 FlagAll;  //GJ
extern UINT16 VarBoomDonwPilot;  //GJ
extern UINT16 VarBoomDonwPilotFilter;  //GJ
extern BOOL BoomUpModeControlFlagLast; //GJ
extern UINT16 VarValveDT8CurrentNow;
extern UINT16 VarValveDT1CurrentNow;
extern UINT16 VarValveDT2CurrentNow;
extern UINT16 VarValveDT6CurrentNow;
extern UINT16 VarValveDT5CurrentNow;
extern UINT16 VarBoomDownPressureFilter;
extern UINT16 VarBoomUpPressureFilter;
extern UINT16 VarAiCBucketArmPressure;
extern UINT16 VarPBucketArmPressure;
extern UINT16 VarPBucketArmRodPressure;
extern UINT16 VarAiCBucketArmRodPressure;//斗杆大腔压力传感器值
extern UINT16 VarPBucCapPressure;
//extern UINT16 VarPAccumAirSensor;	 //蓄能器气压压力，单位bar
extern UINT16 VarPAiBoomUpPressure;////计算动臂上升先导压力,单位bar
extern UINT16 VarPAiBoomDownPressure;//计算动臂下降先导，单位bar

extern UINT8 VarDohStartupRelay;
extern UINT8 VarDihEngineStart;
//
extern UINT8 a;
extern UINT8 Flag_test1;
extern UINT8 Flag_test2;
extern UINT8 Flag_DT1PWM;
extern UINT8 flag_PWM_dt1;
extern UINT8 flag_PWMDT1;
extern float VarValveCurrentTarget1;
extern UINT16 VarValveCurrentTarget2;
extern UINT16 VarDt1PwRatio;
extern UINT16 VarDt2PwRatio;
extern UINT16 VarDt8PwRatio;
extern PIDparams StructPwmDT2;
extern PIDparams StructPwmDT8;

extern UINT16 VarAddValveCurrent1;
extern UINT32 Temp_ulong;
extern UINT8 VarBoomWorkModeNow;//动臂节能控制（1-9）模式
extern UINT8 VarBoomWorkModeLast;
extern UINT8 VarDiRatatoFlag;
extern UINT8 VarAccuDisFlag[20];
extern UINT8 VarTestFlag1;
extern UINT8 VarTestFlag2;

extern UINT8 VarDiBoomUpTimer100Ms;
extern UINT8 VarDoDT9Last;
extern UINT8 VarDoDT4DelayFlag;
extern UINT8 VarDoDT4DelayTimer100Ms;
extern UINT8 VarPumpCurrentPer;
extern UINT16 VarTravelStateTimer10MS;
extern UINT16 VarKongZaiTimer10Ms;
extern UINT16 VarPiDataHistory[100];
extern UINT16 VarFlashPiTargetLevel[12];
extern UINT16 VarPiTargetLevel[12];
extern UINT8 VarPiTargetOkFlag[12]; 
extern UINT16 VarPiEngingSpeedHistory[10];
extern UINT32 VarPiEngineSpeedFilter;
extern UINT16 VarSpeedPointVal_1;
extern UINT16 VarSpeedPointVal_2;
extern UINT16 VarPiTarget;





extern UINT8 VarDataCal;
extern UINT8 VarBoomWorkUpState;
extern  UINT8 VarBoomUpPresLowState;

extern UINT8 VarZhiCheMode;
extern UINT8 VarAccuLowFlag;
extern UINT16 VarPAccumPressLowTimer10Ms;
extern UINT8 VarJieNengPrepaState;
extern UINT16 VarPAccumPressHighTimer10Ms;

extern UINT16 VarAiCBoomBigPressure;
extern UINT16 VarAiCBoomSmallPressure;//pin20,动臂小腔压力,单位uA
extern UINT16 VarAiCBucCapPressure;
extern UINT16 VarBoomBigPressureBar;//动臂大腔压力值bar
extern UINT16 VarBoomSmallPressureBar;//动臂小腔压力值bar
extern UINT8 VarFangNengStopCycle;

extern UINT16 VarBoomBigPressureBarHis[10];

extern UINT16 VarTestUint16;
extern UINT16 VarZhiCheJudgeTimer10Ms;
extern UINT8 VarXiKongFlag;

extern UINT8 VarBoomBigPreDowmFlag;
extern UINT8 VarBoomBigPreUpFlag;
extern UINT8 VarXiKongFlagLast;
extern UINT8 VarPaoTuFlag;
extern UINT8 VarNengLiangGouFlag;
extern UINT16 VarTimer10ms;
extern UINT8 VarDiBoomUpLast;
extern UINT16 VarBoomUpStartPAccumPre;

extern UINT8 VarBoomUpPressureSensorEorror;
extern UINT8 VarBoomDownPressureSensorEorror;
extern UINT8 VarPAccumPressureSensorEorror;
extern UINT8 VarBoomSmallPressureSensorEorror;
extern UINT8 VarBoomBigPressureSensorEorror;
extern UINT8 VarBucketArmPressureSensorEorror;
extern UINT8 VarAiCBucketArmRodSensorEorror;
extern UINT8 VarAiCBucCapPressureSensorEorror;

extern UINT8 VarDt1ValveError;
extern UINT8 VarDt2ValveError;
extern UINT16 VarPAccumPressureMin;
extern UINT16 VarPaccPreLowTimer10Ms;
extern UINT8 VarPaccmPresLowTimerStart;
extern UINT8 VarPaccPreLowFlag;

extern UINT8 VarDoDT10;
extern UINT8 VarDoDT11;
extern UINT8 VarDoDT12;
extern UINT8 VarXieYaFlag;//蓄能器泄压模式
extern UINT16 VarTestBoomUpDiCount;

//20170614新增
extern UINT16 VarPumpPressHeavyTimer10Ms;
extern UINT16 VarPumpPressMidTimer10Ms;
extern UINT8 VarInMode3Flag;
extern UINT16 VarMode3DT8OffDelayTimer10Ms;
extern UINT8 VarMode3DT8OffDelayFlag;
extern UINT8 VarReacordBoomUpFlagLast;
extern UINT8 VarMode3InEnable;
extern UINT8 VarBoomUpOpenAllFlag;
extern UINT8 VarBoomBigXiKongTimer10Ms;
extern UINT16 VarBoomBigNormalTimer10Ms;
extern BOOL VarReacordBoomUpFlag;
extern UINT8 VarDT4MoveErrorTimes;
extern UINT8 VarInDt4Error;
extern UINT8 VarXiKongHappend;
extern UINT8 VarDt4OkTimes;
extern UINT16 VarDiBoomUpTimer10Ms;
extern UINT16 VarAiPAccumAirArray[50];
extern UINT16 VarAiPAccumFilter;
extern UINT16 VarPAccumP[5];
extern UINT8 VarRudeceFlag;
extern UINT8 VarBoomDownNormalModeFlag;
extern UINT8 VarBoomDownMoveFlag;
extern UINT16 VarUint16Test;
extern UINT8 VarBianGangNomarlFlag;
extern UINT16 VarBianGangNomarTimer10Ms;
extern UINT8 VarFlag1;
extern UINT8 VarFlag2;
extern UINT16 VarBoomMode12Timer10Ms;
extern UINT8 VarDaoChongFlag;

extern UINT16 VarDisChargePreMax;
extern UINT8 VarInChargePreMaxNeedCalFlag;
extern UINT16 VarInChargePreMaxCalTimer10Ms;
extern UINT16 VarTimeRecord_Hour;
extern UINT16 VarPAccumAirPreStart;
extern UINT8 VarPAccumAirPreStartFlag;

extern UINT16 VarPwmDT8CurrentTarget;
extern UINT8 VarZhiCheJudgeTimerFlag;
extern UINT16 VarInMode8Timer10Ms;
extern UINT16 VarInMode3Timer10Ms; 
extern UINT16 VarInMode4Timer10Ms;
extern UINT16 VarInMode5Timer10Ms;
extern UINT16 VarInMode7Timer10Ms;
extern UINT16 VarBoomBigPressureBarTimer10Ms;
extern UINT16 VarSpeedLevel0Timer10Ms;
extern UINT8 VarDiValveSwitchesFlag;
extern UINT8 VarDiShangChe;//pin50
extern UINT8 VarDiDGNS;	//pin33
extern UINT8 VarDiDGWB;	//pin34
extern UINT8 VarDiCDDS;	//pin61
extern UINT8 VarDiCDWB;	//pin62
extern UINT8 VarInMode1Flag;

extern UINT8 VarSendDataID382Num;


extern UINT16 VarDT8PwmCurrentTarget;
extern INT16  VarBigSmallDifferentVale;//动臂大小腔压力差值带符号
extern UINT8 VarUpLowEngineFlag;//动臂上升能量不足标志位
extern UINT8 VarSDXYFlag;//手动泄压标志，第一台耦合式节能挖机才有，后面不需要
extern UINT8 VarRestarForEnginerFlag;//节能部分判断系统重启
extern UINT8 VarSpeedLevelEngineFlag;//第一次提臂不节能标志怠速条件是否满足标志
extern UINT8 VarInModeBoomUpFirstFlag;//进入第一次提臂不节能标志
extern UINT8 VarInModeBoomUpFirstBackFlag;//退出第一次提臂不节能标志
extern UINT8 VarBoomSaveEngineUpInFlag;//动臂节能上升标志位
extern UINT8 VarCanSendCanSaveStep;//can总线记录仪发送
extern UINT8 VarCanSendCanF11[8];
extern UINT8 VarCanSendCanF12[8];
extern UINT8 VarCanSendCanF13[8];
extern UINT8 VarCanSendCanF14[8];
extern UINT8 VarCanSendCanF15[8];
extern UINT8 VarCanSendCanF16[8];
extern UINT8 VarDelayTimeZhiCheFalg;
extern UINT16 VarMode1KeepFlag10Ms;
extern UINT16 VarBoomUpTimer10Ms;
extern UINT8 VarBoomUpTimerFlag;
extern UINT16 VarAiCPAccumAirSensor;//单位uA	蓄能器气压压力
extern UINT8 VarAirPressureLowFlag;//蓄能器气压低报警
extern UINT8 VarBoomDowmFirstPAccumPressureFlag;//动臂下降第一次检测初始蓄能器油压标志位
extern UINT8 VarBoomEnergyMode1Flag;
extern UINT16 VarBoomUpDownTimer10Ms;
extern UINT16 VarBoomUpDownZhiCheModeTimer10Ms;
//extern UINT8 VarSendDataID383Num;
extern UINT8 VarArmMode2Flag;
extern UINT8 VarAfterMode7Flag;
extern UINT16 VarMode2InPutPress;//进入2模式分档位判断主泵压力
extern UINT8 VarCartridgeValveFaultFlag;//插装阀故障报警标志
extern UINT8 VarEngineSaveSensorFaultChangeModeFlag;//节能传感器故障进入不节能模式标志
extern UINT8 VarValveDT6Error;
extern UINT8 VarValveDT8Error;
extern UINT8 VarValveDT5Error;
extern UINT8 VarAfterMode7BoomDownFlag;
extern UINT8 VarSaveEngineDT7Flag;
