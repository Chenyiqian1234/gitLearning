#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"

UINT8 VarDt1TestCounter = 0;
UINT16 VarDt1TestOutputCurrent=0;

/**************************************************************
**函数名：FunIOSample()
**功能描述：IO端口输入采样与输出设置
**传入参数：无
**输出参数：无
**************************************************************/
void FunPowerSaveIO(void)
{
	FunPowerSaveAiSample();//Ai采样
	FunPowerSaveDiSample();
	FunPowerSaveDoSet();   //置Do
	FunPowerSavePwmOutput();
}
/**************************************************************
**函数名：FunPwmOutput()
**功能描述:DT8控制
**传入参数：无
**输出参数：无
**************************************************************/

void FunPowerSavePwmOutput()
{	
	
	/*
	//......................DT8比例输出..........................
	StructPwmDT8.PosLimit=50000;
	StructPwmDT8.NegLimit=0;
	StructPwmDT8.Kp=2.5;//8
	StructPwmDT8.Ki=2.5;//3
	StructPwmDT8.Kd=0;//0.5
	
	FunPID(VarValveDT8CurrentNow,(UINT16)VarDT8PwmCurrentTarget,&StructPwmDT8,5,10,TRUE);
	
	VarDt8PwRatio = StructPwmDT8.Result;

	LibSetPwmRatio(4,VarDt8PwRatio);//pin67
	*/
}

/**************************************************************
**函数名：FunDiSample()
**功能描述：Di采样
**传入参数：无
**输出参数：无
**************************************************************/
void FunPowerSaveDiSample()
{
	VarDiTreadPre = VarDiTravelHighSpeed;	//行走压力开关；>0表示在行走，=0表示无行走  
	//压力开关
//	VarDiShangChe=LibGetValueDIH(3);//pin50
	VarDiDGNS=LibGetValueDIH(8);	//pin33
	VarDiDGWB=LibGetValueDIH(9);	//pin34
	VarDiCDDS=LibGetValueDIH(21);	//pin61
	VarDiCDWB=LibGetValueDIH(22);	//pin62
}

/**************************************************************
**函数名：FunAiSample()
**功能描述：Ai采样,AIR0~AIR5:0.1欧;AIR6~AIR13:1欧
**传入参数：无
**输出参数：无
**************************************************************/
void FunPowerSaveAiSample(void)
{
	//AI检测
	UINT8 i;
	UINT32 temp_ulong;
	double temp_double;
	UINT16 Temp_Uint;
	UINT32 temp_BoomSmallPre;
	UINT32 temp_AccumPre;
	UINT32 temp_AccumAirPre;
	
	VarAiBoomUpPressure = LibGetAiCurrent(4);	//pin8,动臂上升先导压力,单位uA
	VarAiBoomDownPressure = LibGetAiCurrent(5);	//pin9,动臂下降先导,单位uA	
	
	VarAiAccumPressure = LibGetAiCurrent(10);	//pin19,蓄能器压力,单位uA
	VarAiCBoomSmallPressure  = LibGetAiCurrent(11); //pin20,动臂小腔压力,单位uA
	VarAiCBucCapPressure  = LibGetAiCurrent(2); //pin6,铲斗大腔压力,单位uA
	
	VarAiCBoomBigPressure= LibGetAiCurrent(8); //pin16,动臂大腔,单位uA	
	VarAiCBucketArmPressure = LibGetAiCurrent(9); //pin17,斗杆大腔压力,单位uA	
	VarAiCBucketArmRodPressure = LibGetAiCurrent(13); //pin23,斗杆小腔压力,单位uA
	VarAiCPAccumAirSensor=LibGetAiCurrent(7);		//pin11,单位uA	蓄能器气压压力
			
	VarValveDT8CurrentNow=LibGetPwmCurrent(4);  //Pin67,电磁阀电流反馈 ,DT8,单位uA
	VarValveDT1CurrentNow=LibGetPwmCurrent(7);  //Pin70,电磁阀电流反馈,DT1,单位uA
	VarValveDT2CurrentNow=LibGetPwmCurrent(8);  //Pin71,电磁阀电流反馈,DT2,单位uA
	
	VarValveDT6CurrentNow=LibGetPwmCurrent(2);  //Pin40,电磁阀电流反馈,DT6,单位uA
	VarValveDT5CurrentNow=LibGetPwmCurrent(10);  //Pin73,电磁阀电流反馈,DT5,单位uA
	//Pin44,电磁阀电流反馈,DT7,单位uA，不能测出来，没有PWM电路
	
	
	
	
	/*	
	//DT1DOH输出，反馈电流值过大检测//DT1关VarValveDT1CurrentNow=18，DT1开VarValveDT1CurrentNow=1350左右
	if((VarDoDT1==1)&&(VarValveDT1CurrentNow<100))
	{
		VarValveDT1Error = 1;
		
	}
	if((VarDoDT1==1)&&(VarValveDT1CurrentNow>100))
	{
		VarValveDT1Error = 0;
	}
	//DT2DOH输出，反馈电流值过大检测
	if((VarDoDT2==1)&&(VarValveDT2CurrentNow<100))
	{
		VarValveDT2Error = 1;
	}
	if((VarDoDT2==1)&&(VarValveDT2CurrentNow>100))
	{
		VarValveDT2Error = 0;
	}	
	
	//DT6DOH输出，反馈电流值过大检测
	if((VarDoDT6==1)&&(VarValveDT6CurrentNow<100))
	{
		VarValveDT6Error = 1;
	}
	if((VarDoDT6==1)&&(VarValveDT6CurrentNow>100))
	{
		VarValveDT6Error = 0;
	}		
	//DT8DOH输出，反馈电流值过大检测
	if((VarDT8PwmCurrentTarget>20)&&(VarValveDT8CurrentNow<20))
	{
		VarValveDT8Error = 1;
	}
	if((VarDT8PwmCurrentTarget>20)&&(VarValveDT8CurrentNow>20))
	{
		VarValveDT8Error = 0;
	}
	//DT5DOH输出，反馈电流值过大检测  //需要做掉电保存
	if((VarDoDT5==1)&&(VarValveDT5CurrentNow<100))
	{
		VarValveDT5Error = 1;
	}
	if((VarDoDT5==1)&&(VarValveDT5CurrentNow>100))
	{
		VarValveDT5Error = 0;
	}	
	
	*/
	//蓄能器气压压力传感器故障	
	if((VarAiCPAccumAirSensor<3000)||(VarAiCPAccumAirSensor>25000))
	{
		VarPAccumAirSensorError = 1;
	}
	else
	{
		VarPAccumAirSensorError = 0;
	}
//蓄能器气压滤波
	for(i=50;i>0;i--)
	{
		VarAiPAccumAirArray[i]=VarAiPAccumAirArray[i-1];
	}
	VarAiPAccumAirArray[0]=VarAiCPAccumAirSensor;
	temp_ulong=0;
	for(i=0;i<50;i++)
	{
		temp_ulong += VarAiPAccumAirArray[i];
	}
	VarAiPAccumFilter=(UINT16)(temp_ulong/50);
	
//蓄能器气压校正
	
	temp_AccumAirPre=FunPressureCompute(VarAiPAccumFilter);
	if(temp_AccumAirPre>=6)
	{
	temp_AccumAirPre=((temp_AccumAirPre*990)-5704);
	temp_AccumAirPre=(temp_AccumAirPre/1000);
	}
	
	VarPAccumAirPressureBar=(UINT16)temp_AccumAirPre;//蓄能器气压最终显示，单位bar
	
	//蓄能器气压低报警
	if(VarPAccumAirPressureBar<=130)
	{
		VarAirPressureLowFlag=1;//蓄能器气压低报警
	}
	else
	{
		VarAirPressureLowFlag=0;
	}
	
	//斗杆大腔压力传感器故障判断
	if((VarAiCBucketArmPressure<3000)||(VarAiCBucketArmPressure>25000))
	{
		VarBucketArmPressureSensorEorror = 1;
	}
	else
	{
		VarBucketArmPressureSensorEorror = 0;
	}
	//斗杆小腔压力传感器故障判断
	if((VarAiCBucketArmRodPressure<3000)||(VarAiCBucketArmRodPressure>25000))
	{
		VarAiCBucketArmRodSensorEorror = 1;
	}
	else
	{
		VarAiCBucketArmRodSensorEorror = 0;
	}	
	
	//计算斗杆大腔压力,单位bar
	VarPBucketArmPressure = FunPressureCompute(VarAiCBucketArmPressure);
	//计算斗杆小腔压力,单位bar
	VarPBucketArmRodPressure = FunPressureCompute(VarAiCBucketArmRodPressure);
	//计算铲斗大腔压力,单位bar
	VarPBucCapPressure = FunPressureCompute(VarAiCBucCapPressure);
	//计算动臂上升先导压力,单位bar
	VarPAiBoomUpPressure = FunLowerPressureCompute(VarAiBoomUpPressure);
	//计算动臂下降先导，单位bar
	VarPAiBoomDownPressure = FunLowerPressureCompute(VarAiBoomDownPressure);

	
	

	
	
	//pin6,铲斗大腔压力传感器故障判断
	if((VarAiCBucCapPressure<3000)||(VarAiCBucCapPressure>25000))
	{
		VarAiCBucCapPressureSensorEorror = 1;
	}
	else
	{
		VarAiCBucCapPressureSensorEorror = 0;
	}
	
	
	

	//蓄能器压力计算，无滤波
	//先导泵传感器故障判断，计算先导泵压力
	if((VarAiAccumPressure<3000)||(VarAiAccumPressure>25000))
	{
		VarPAccumPressureSensorEorror = 1;//蓄能器压力传感器故障
	}
	else
	{
		VarPAccumPressureSensorEorror = 0;
	}
	temp_AccumPre = FunPressureCompute(VarAiAccumPressure);
	//蓄能器油压校正
	temp_AccumPre=((temp_AccumPre*1053)+1538);
	temp_AccumPre=(temp_AccumPre/1000);
	VarPAccumPressureFilter=(UINT16)temp_AccumPre;
	
	//检测动臂上升过程中的蓄能器压力最小值
	if(VarDiBoomUp)
	{
		if(VarPAccumPressureMin>VarPAccumPressureFilter)
		{
			VarPAccumPressureMin=VarPAccumPressureFilter;
		}
	}
	if(VarDiBoomDown)
	{
		VarPAccumPressureMin=500;
	}

	VarBoomDonwPilotFilter= FunPressureCompute3(VarBoomDonwPilot);//无用
	//蓄能器压力校准

	if((VarAiBoomUpPressure<3000)||(VarAiBoomUpPressure>25000))
	{
		VarBoomUpPressureSensorEorror = 1;//动臂上升压力传感器故障
	}
	else
	{
		VarBoomUpPressureSensorEorror = 0;
	}
	VarBoomUpPressureFilter = FunPressureCompute3(VarAiBoomUpPressure);//FunPressureCompute2
	if((VarAiBoomDownPressure<3000)||(VarAiBoomDownPressure>25000))
	{
		VarBoomDownPressureSensorEorror = 1;//动臂下降压力传感器故障
	}
	else
	{
		VarBoomDownPressureSensorEorror = 0;
	}
	//动臂下降先导压力
	VarBoomDownPressureFilter = FunPressureCompute3(VarAiBoomDownPressure);//FunPressureCompute3
	
	if((VarAiCBoomBigPressure<3000)||(VarAiCBoomBigPressure>25000))
	{
		VarBoomBigPressureSensorEorror = 1;//动臂大腔压力传感器故障
	}
	else
	{
		VarBoomBigPressureSensorEorror = 0;
	}
	VarBoomBigPressureBar=FunPressureCompute(VarAiCBoomBigPressure);
	//动臂大腔压力值修正
	if(VarBoomBigPressureBar>3)
	{
	 VarBoomBigPressureBar=VarBoomBigPressureBar-3;
	
	}
	
	if((VarAiCBoomSmallPressure<3000)||(VarAiCBoomSmallPressure>25000))
	{
		VarBoomSmallPressureSensorEorror = 1;//动臂小腔压力传感器故障
	}
	else
	{
		VarBoomSmallPressureSensorEorror = 0;
	}
	temp_BoomSmallPre=FunPressureCompute(VarAiCBoomSmallPressure);
	//动臂小腔压力值修正
	if(temp_BoomSmallPre>=2)
	{
	temp_BoomSmallPre=((temp_BoomSmallPre*1063)-1536);
	
	temp_BoomSmallPre=(temp_BoomSmallPre/1000);
	}
	VarBoomSmallPressureBar=(UINT16)temp_BoomSmallPre;
	
	
	
	
	//******************动臂上升、下降动作判断**********************
	if ((VarBoomUpPressureFilter>5)&&(VarBoomUpPressureFilter>VarBoomDownPressureFilter))     
	{
		VarDiBoomUp=1;
	}
	else 
	{
		VarDiBoomUp=0;
	}
	if((VarBoomDownPressureFilter>5)&&(VarBoomDownPressureFilter>VarBoomUpPressureFilter))     
	{
		VarDiBoomDown=1;
	}
	else 
	{
		VarDiBoomDown=0;
	}
		//*******************压力开关信号判别******************************
		if(VarDiDGNS||VarDiDGWB||VarDiCDDS||VarDiCDWB)
		{
			VarDiValveSwitchesFlag=1;
		}
		else
		{
			VarDiValveSwitchesFlag=0;
		}

}
/**************************************************************
**函数名：FunDoSet()
**功能描述：Do端口设置
**传入参数：无
**输出参数：无
**************************************************************/
void FunPowerSaveDoSet(void)
{
	//DO输出
	LibSetValueDOH(21,VarDoDT1);	//pin70
	LibSetValueDOH(22,VarDoDT2);	//pin71
//	LibSetValueDOH(18,VarDoDT8);	//pin67
	
	LibSetValueDOH(5,VarDoDT8);		//pin36，用变量DT8代替DT3,其他执行可不再更改
//	LibSetValueDOH(5,VarDoDT3);		//pin36 //
//	LibSetValueDOH(14,VarDoDT4);	//pin38,//备用


	
	LibSetValueDOH(0,VarDoDT5);	//pin31 
	LibSetValueDOH(16,VarDoDT6);	//pin40  DT6
	
		
	LibSetValueDOH(9,VarDoDT7);		//pin44
	LibSetValueDOH(23,1);	//pin72 备用VarDoDT9钥匙开关开输出0  VarDoDT9
	

	
	
	
}
/**************************************************************
**函数名：FunPressureCompute2()
**功能描述：根据压力传感器(0-10MPa)电流计算压力值
**传入参数：电流值(uA)
**输出参数：压力值(bar)
**************************************************************/
UINT16 FunPressureCompute2(UINT16 VarAiPressure)
{
	UINT16 Temp_Pressure;
	UINT16 Temp_VarAiPressureMv;
	Temp_VarAiPressureMv = VarAiPressure/100;
	if(Temp_VarAiPressureMv<40)
	{
		Temp_Pressure=0;
	}
	else if(Temp_VarAiPressureMv>200)
	{
		Temp_Pressure = 100;
	}
	else
	{
		Temp_Pressure = (UINT16)(Temp_VarAiPressureMv*5-200)/8;//40-200(0.1mA):0-100Bar
	}
	return(Temp_Pressure);
}
/**************************************************************
**函数名：FunPressureCompute3()
**功能描述：根据压力传感器(0-6MPa)电流计算压力值
**传入参数：电流值(uA)
**输出参数：压力值(bar)
**************************************************************/
UINT16 FunPressureCompute3(UINT16 VarAiPressure)
{
	UINT16 Temp_Pressure;
	UINT16 Temp_VarAiPressureMv;
	Temp_VarAiPressureMv = VarAiPressure/100;
	if(Temp_VarAiPressureMv<40)
	{
		Temp_Pressure=0;
	}
	else if(Temp_VarAiPressureMv>200)
	{
		Temp_Pressure = 60;
	}
	else
	{
		Temp_Pressure = (UINT16)(Temp_VarAiPressureMv*3-120)/8;//40-200(0.1mA):0-60Bar
	}
	return(Temp_Pressure);
}
