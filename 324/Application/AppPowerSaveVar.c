#include "AppDefine.h"
UINT16 VarAiBoomUpPressure;
UINT16 VarAiBoomDownPressure;

//节能
UINT8 VarDiBoomUp=0;
UINT8 VarDiBoomDown=0;
UINT8 VarDoDT1=0;
UINT8 VarDoDT2=0;
UINT8 VarDoDT3=0;//
UINT8 VarDoDT4=0;
UINT8 VarDoDT5=0;
UINT8 VarDoDT6=0;
UINT8 VarDoDT7=0;       //默认值更改
UINT8 VarDoDT8=0;  //GJ
UINT8 VarDoDT9=0;   //GJ
UINT8 VarBoomUpFlag=0;
UINT8 VarBoomDownFlag=0;
UINT16 VarAiAccumPressure=0;
UINT16 VarAiBoomPolePressure=0;
UINT16 VarPBoomPressureFilter=0;
UINT16 VarPAccumPressureFilter=0;
UINT8 VarBoomPowerSaveFlag=1;
UINT8 VarAccumDischargeFlag=0;
UINT8 VarRatatorPowerSaveFlag=1;
UINT8 VarDiTreadPre=1;
UINT16 FlagBoomUpPilot=0;
UINT16 FlagAll=0;
UINT16 VarBoomDonwPilot;//-GJ
UINT16 VarBoomDonwPilotFilter;//-GJ
BOOL BoomUpModeControlFlagLast = FALSE;
UINT8 Flag_test1=0;
UINT8 Flag_test2=0;
UINT16 VarValveDT8CurrentNow=0;			//DT8电磁阀当前电流
UINT16 VarValveDT1CurrentNow=0;			//DT1电磁阀当前电流
UINT16 VarValveDT2CurrentNow=0;			//DT2电磁阀当前电流
UINT16 VarValveDT6CurrentNow=0;         //DT6电磁阀当前电流
UINT16 VarValveDT5CurrentNow=0;
float VarValveCurrentTarget1=0;
UINT16 VarValveCurrentTarget2=0;
UINT16 VarBoomDownPressureFilter;
UINT16 VarBoomUpPressureFilter=0;
UINT16 VarAiCBucketArmPressure=0;//斗杆大腔压力传感器值
UINT16 VarPBucketArmPressure=0;	 //斗杆大腔压力，单位bar
UINT16 VarAiCBucketArmRodPressure=0;//斗杆小腔压力传感器值
UINT16 VarPBucketArmRodPressure=0;//斗杆小腔压力，单位bar
UINT16 VarPBucCapPressure=0;//铲斗大腔压力,单位bar
UINT16 VarPAiBoomUpPressure=0;////计算动臂上升先导压力,单位bar
UINT16 VarPAiBoomDownPressure=0;//计算动臂下降先导，单位bar


UINT8 VarDohStartupRelay=0;	
UINT8 VarDihEngineStart=0;
//
UINT8 a=0;
UINT8 Flag_DT1PWM=0;
UINT16 VarDt1PwRatio=0;
UINT16 VarDt2PwRatio=0;
UINT16 VarDt8PwRatio=0;
PIDparams StructPwmDT2;
PIDparams StructPwmDT8;

UINT16 VarAddValveCurrent1;

UINT8 flag_PWM_dt1=0;
UINT8 flag_PWMDT1=0;
UINT8 VarBoomWorkModeNow = 0;
UINT8 VarBoomWorkModeLast =0;
UINT32 Temp_ulong;  //计时器临时变量
UINT8 VarDiRatatoFlag;
UINT8 VarAccuDisFlag[20];

UINT8 VarTestFlag1;
UINT8 VarTestFlag2;

UINT8 VarDiBoomUpTimer100Ms=0;
UINT8 VarDoDT9Last;
UINT8 VarDoDT4DelayFlag;
UINT8 VarDoDT4DelayTimer100Ms;
UINT8 VarPumpCurrentPer;

UINT16 VarTravelStateTimer10MS;
UINT16 VarKongZaiTimer10Ms=0;
UINT16 VarPiDataHistory[100];
UINT16 VarFlashPiTargetLevel[12]=
{
	290,350,390,420,450,480,510,540,562,586,606,627	
};
UINT16 VarPiTargetLevel[12];
UINT8 VarPiTargetOkFlag[12]; 
UINT16 VarPiEngingSpeedHistory[10];
UINT32 VarPiEngineSpeedFilter;
UINT16 VarSpeedPointVal_1;
UINT16 VarSpeedPointVal_2;
UINT16 VarPiTarget;





UINT8 VarDataCal;

//20150929新加
UINT8 VarBoomWorkUpState=0;
UINT8 VarBoomUpPresLowState=0;

UINT8 VarZhiCheMode=0;
UINT8 VarAccuLowFlag=0;
UINT16 VarPAccumPressLowTimer10Ms=0;
UINT8 VarJieNengPrepaState=0;
UINT16 VarPAccumPressHighTimer10Ms=0;


UINT16 VarAiCBoomBigPressure=0;
UINT16 VarAiCBoomSmallPressure=0;
UINT16 VarAiCBucCapPressure=0;
UINT16 VarBoomBigPressureBar=0;
UINT16 VarBoomSmallPressureBar=0;
UINT8 VarFangNengStopCycle=0;

UINT16 VarBoomBigPressureBarHis[10];
UINT16 VarZhiCheJudgeTimer10Ms=0;
UINT16 VarTestUint16=0;
UINT8 VarXiKongFlag=0;

UINT8 VarBoomBigPreDowmFlag=0;
UINT8 VarBoomBigPreUpFlag=0;
UINT8 VarXiKongFlagLast=0;

UINT8 VarPaoTuFlag=0;
UINT8 VarNengLiangGouFlag=0;
UINT16 VarTimer10ms=0;

UINT8 VarDiBoomUpLast=0;
UINT16 VarBoomUpStartPAccumPre=0;

UINT8 VarBoomUpPressureSensorEorror=0;
UINT8 VarBoomDownPressureSensorEorror=0;
UINT8 VarPAccumPressureSensorEorror=0;
UINT8 VarBoomSmallPressureSensorEorror=0;
UINT8 VarBoomBigPressureSensorEorror=0;
UINT8 VarBucketArmPressureSensorEorror=0;
UINT8 VarAiCBucketArmRodSensorEorror=0;
UINT8 VarAiCBucCapPressureSensorEorror=0;
UINT8 VarDt1ValveError=0;
UINT8 VarDt2ValveError=0;
UINT16 VarPAccumPressureMin=500;
UINT16 VarPaccPreLowTimer10Ms=0;
UINT8 VarPaccmPresLowTimerStart=0;
UINT8 VarPaccPreLowFlag=0;

UINT8 	VarDoDT10=0;
UINT8	VarDoDT11=0;
UINT8	VarDoDT12=0;
UINT8 VarXieYaFlag=0;

UINT16 VarTestBoomUpDiCount=0;
//20170614新增
UINT16 VarPumpPressHeavyTimer10Ms=0;
UINT16 VarPumpPressMidTimer10Ms=0;
UINT8 VarInMode3Flag=0;
UINT16 VarMode3DT8OffDelayTimer10Ms=0;
UINT8 VarMode3DT8OffDelayFlag=0;
UINT8 VarReacordBoomUpFlagLast=0;
UINT8 VarMode3InEnable=0;
UINT8 VarBoomUpOpenAllFlag=0;
UINT8 VarBoomBigXiKongTimer10Ms;
UINT16 VarBoomBigNormalTimer10Ms=0;
BOOL VarReacordBoomUpFlag=FALSE;
UINT8 VarDT4MoveErrorTimes=0;
UINT8 VarInDt4Error=0;
UINT8 VarXiKongHappend=0;
UINT8 VarDt4OkTimes=0;
UINT16 VarDiBoomUpTimer10Ms=0;
UINT16 VarAiPAccumAirArray[50];
UINT16 VarAiPAccumFilter;
UINT16 VarPAccumP[5];
UINT8 VarRudeceFlag=0;
UINT8 VarBoomDownNormalModeFlag=0;
UINT8 VarBoomDownMoveFlag=0;
UINT16 VarUint16Test=0;
UINT8 VarBianGangNomarlFlag=0;
UINT16 VarBianGangNomarTimer10Ms=0;
UINT8 VarFlag1=0;
UINT8 VarFlag2=0;
UINT16 VarBoomMode12Timer10Ms=0;
UINT8 VarDaoChongFlag=0;
UINT16 VarDisChargePreMax=0;
UINT8 VarInChargePreMaxNeedCalFlag=0;
UINT16 VarInChargePreMaxCalTimer10Ms=0;
UINT16 VarTimeRecord_Hour=0;
UINT16 VarPAccumAirPreStart;
UINT8 VarPAccumAirPreStartFlag;





UINT16 VarPwmDT8CurrentTarget=0;
UINT8 VarZhiCheJudgeTimerFlag=0;
UINT16 VarInMode8Timer10Ms=0;
UINT16 VarBoomBigPressureBarTimer10Ms=0;
UINT16 VarInMode3Timer10Ms=0;
UINT16 VarInMode4Timer10Ms=0;
UINT16 VarInMode5Timer10Ms=0;
UINT16 VarInMode7Timer10Ms=0;
UINT16 VarSpeedLevel0Timer10Ms=0;
UINT8 VarDiValveSwitchesFlag=0;
UINT8 VarDiShangChe;//pin50
UINT8 VarDiDGNS;	//pin33
UINT8 VarDiDGWB;	//pin34
UINT8 VarDiCDDS;	//pin61
UINT8 VarDiCDWB;	//pin62
UINT8 VarInMode1Flag=0;

UINT8 VarSendDataID382Num=0;


UINT16 VarDT8PwmCurrentTarget=0;
INT16  VarBigSmallDifferentVale=0;
UINT8 VarUpLowEngineFlag=0;
UINT8 VarSDXYFlag=0;
UINT8 VarRestarForEnginerFlag=1;
UINT8 VarSpeedLevelEngineFlag=0;
UINT8 VarInModeBoomUpFirstFlag=0;
UINT8 VarInModeBoomUpFirstBackFlag=0;
UINT8 VarBoomSaveEngineUpInFlag=0;
UINT8 VarCanSendCanSaveStep=0;//can总线记录仪发送
UINT8 VarCanSendCanF11[8];
UINT8 VarCanSendCanF12[8];
UINT8 VarCanSendCanF13[8];
UINT8 VarCanSendCanF14[8];
UINT8 VarCanSendCanF15[8];
UINT8 VarCanSendCanF16[8];
UINT8 VarDelayTimeZhiCheFalg=0;
UINT16 VarMode1KeepFlag10Ms=0;
UINT16 VarBoomUpTimer10Ms=0;
UINT8 VarBoomUpTimerFlag=0;
UINT16 VarAiCPAccumAirSensor=0;
UINT8 VarAirPressureLowFlag=0;//蓄能器气压低报警
UINT8 VarBoomDowmFirstPAccumPressureFlag=0;//动臂下降第一次检测初始蓄能器油压标志位
UINT8 VarBoomEnergyMode1Flag=0;
UINT16 VarBoomUpDownTimer10Ms=0;//手柄中位计时器
UINT16 VarBoomUpDownZhiCheModeTimer10Ms=0;//手柄中位支车模式判断
//UINT8 VarSendDataID383Num=0;
UINT8 VarArmMode2Flag=0;//进入2模式的标志位
UINT8 VarAfterMode7Flag=0;//进入7模式支车后提臂不节能上升
UINT16 VarMode2InPutPress=0;//进入2模式分档位判断主泵压力
UINT8 VarCartridgeValveFaultFlag=0;//插装阀故障报警标志
UINT8 VarEngineSaveSensorFaultChangeModeFlag=0;//节能传感器故障进入不节能模式标志
UINT8 VarValveDT6Error=0;
UINT8 VarValveDT8Error=0;
UINT8 VarValveDT5Error=0;
UINT8 VarAfterMode7BoomDownFlag=0;
UINT8 VarSaveEngineDT7Flag=0;
