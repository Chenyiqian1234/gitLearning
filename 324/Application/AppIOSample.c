#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
/**************************************************************
**函数名：FunIOSample()
**功能描述：IO端口输入采样与输出设置
**传入参数：无
**输出参数：无
**************************************************************/
 void FunIOSample(void)
{
	FunDiSample();//Di采样
	FunAiSample();//Ai采样
	FunDoSet();//置Do
	if(VarSysPowerOn>0)
	{
		VarDoBatteryRelay=1;//电源继电器	
	}
}

/**************************************************************
**函数名：FunDiSample()
**功能描述：Di采样
**传入参数：无
**输出参数：无
**************************************************************/
void FunDiSample()
{
	//DI检测

	VarDiTravelHighSpeed=LibGetValueDIH(1);	//pin14
	VarDiPilot=LibGetValueDIH(4);			//pin51
	VarDiLowSpeedEnable=LibGetValueDIH(0);	//pin13
	VarSysPowerOn=LibGetValueDIH(2);		//pin26

	VarDiAirFilterAlarm=LibGetValueDIL(2);	//pin24

	VarDiStop=LibGetValueDIH(5);			//pin52
	VarAiPilotSwitch=LibGetValueDIH(3);			//pin50
	
}

/**************************************************************
**函数名：FunAiSample()
**功能描述：Ai采样
**传入参数：无
**输出参数：无
**************************************************************/
void FunAiSample(void)
{
	UINT8 i;
	UINT32 temp_ulong;
	UINT32 temp_ulong1;
	//AI检测
	VarAiFuelVolume=LibGetAiRes(3);			//pin7，单位0.1R
	VarAiEngineDial=LibGetAiVoltage(0);		//pin4,单位mV
	VarAiPump1Pressure=LibGetAiCurrent(12);	//pin21,单位uA
	VarAiPump2Pressure=LibGetAiCurrent(6);	//pin10,单位uA

	
	
    VarAiHydraulicTemp=LibGetAiRes(1);		//pin5,单位0.1R	
	//读取PWM电流值
	VarValveCurrentNow = LibGetPwmCurrent(3); 		//pin66,PWM_3
	VarAssValveCurrentNow=LibGetPwmCurrent(11);     //辅具流量调节电磁阀当前电流，Pin80,PWM11
	VarHydraulicCoolingPumpValveCurrent = LibGetPwmCurrent(1); 		//pin39,PWM_1
	//系统电压
	VarSysVoltageMv = LibGetSystemVoltage();
	//充电报警
	if(VarSysVoltageMv-200<=VarSysVoltFilterLast) //当前电压小于之前电压，发动机没启动,||(VarEngineSpeedNow<300) 
	{
		VarDiCharge = 0x01;  //需要充电,电量不足
	}
	else
	{
		VarDiCharge = 0x00;
	}
	//表盘反馈位置
	VarAccDialPosiNow=VarAiEngineDial;
	//油量计算,每500ms计算一次
	if(LibTimer(6,1,500,1))
	{
		VarFuelComputeNum++;
		if(VarFuelComputeNum>100)
		{
			VarFuelComputeNum=100;
		}
		VarFuelVolume = FunFuelVolumeCompute(VarAiFuelVolume);
		for(i=99;i>0;i--)
		{
			VarFuelCompute[i]=VarFuelCompute[i-1];
		}
		VarFuelCompute[0]=VarFuelVolume;
		temp_ulong=0;
		for(i=0;i<100;i++)
		{
			temp_ulong += VarFuelCompute[i];
		}
		if(VarFuelComputeNum != 0)
		{
			VarFuelVolumeFilter=(UINT8)(temp_ulong/VarFuelComputeNum);
		}
	}
	//油量低报警
	if(VarFuelVolumeFilter<VarFuelLowAlarmLimit)
	{
		VarFuelLackAlarm = 1;
	}
	else
	{
		VarFuelLackAlarm = 0;
	}
	//油量传感器故障报警,
	if((VarAiFuelVolume<4)||(VarAiFuelVolume>10000))
	{
		VarFuelSensorError = 1;
	}
	else
	{
		VarFuelSensorError = 0;
	}
	//泵1传感器故障判断，计算泵1压力
	if((VarAiPump1Pressure<3000)||(VarAiPump1Pressure>25000))//传感器断开反馈220
	{
		VarP1PressureSensorEorror = 1;
	}
	else
	{
		VarP1PressureSensorEorror = 0;
	}
	VarP1Pressure=FunPressureCompute(VarAiPump1Pressure);
	for(i=19;i>0;i--)
	{
		VarP1PressureArray[i]=VarP1PressureArray[i-1];
	}
	VarP1PressureArray[0]=VarP1Pressure;
	temp_ulong=0;
	for(i=0;i<3;i++)
	{
		temp_ulong += VarP1PressureArray[i];
	}
	VarP1PressureFilter=(UINT16)(temp_ulong/3);
	//泵2传感器故障判断，计算泵2压力
	if((VarAiPump2Pressure<3000)||(VarAiPump2Pressure>25000))
	{
		VarP2PressureSensorEorror = 1;
	}
	else
	{
		VarP2PressureSensorEorror = 0;
	}
	VarP2Pressure = FunPressureCompute(VarAiPump2Pressure);
	for(i=19;i>0;i--)
	{
		VarP2PressureArray[i]=VarP2PressureArray[i-1];
	}
	VarP2PressureArray[0]=VarP2Pressure;
	temp_ulong=0;
	for(i=0;i<3;i++)
	{
		temp_ulong += VarP2PressureArray[i];
	}
	VarP2PressureFilter = (UINT16)(temp_ulong/3);
	//计算平均压力
	VarSysAveragePress = (UINT16)((VarP1Pressure+VarP2Pressure)>>1);
	//先导泵传感器故障判断，计算先导泵压力

	//计算斗杆大腔压力,单位bar

	for(i=19;i>0;i--)
	{
		VarPbPressureArray[i]=VarPbPressureArray[i-1];
	}
	VarPbPressureArray[0]=VarPbPressure;
	temp_ulong=0;
	for(i=0;i<20;i++)
	{
		temp_ulong += VarPbPressureArray[i];
	}

	//油门表盘故障判断
	if((VarAiEngineDial<400)||(VarAiEngineDial>4200))
	{
		VarDialSensorError = 1;
	}
	else
	{
		VarDialSensorError = 0;
	}
	//液压泵功率控制电磁比例阀故障判断
	if( (VarValveErrorTime1S>10)||
		((VarValveCurrentNow<30)&&(VarValvePwRatio>65000))
	  )
	{
		VarValveError = 1;
	}
	else
	{
		VarValveError = 0;
	}
	
		
		//液压油温计算,每300ms计算一次
	if(LibTimer(3,1,300,1))
	{
		VarHydraulicOilComputeNum++;
		if(VarHydraulicOilComputeNum>70)
		{
			VarHydraulicOilComputeNum=70;
		}
		VarHydraulicOilTemp = FunHydraulicOilTemCompute(VarAiHydraulicTemp);
		for(i=69;i>0;i--)
		{
			VarHydraulicOilCompute[i]=VarHydraulicOilCompute[i-1];
		}
		VarHydraulicOilCompute[0]=VarHydraulicOilTemp;
		temp_ulong=0;
		for(i=0;i<70;i++)
		{
			temp_ulong += VarHydraulicOilCompute[i];
		}
		if(VarHydraulicOilComputeNum != 0)
		{
			VarHydraulicOilTempFilter=(UINT8)(temp_ulong/VarHydraulicOilComputeNum);
		}
	}
	//液压油温高报警
	if(VarHydraulicOilTempFilter>90)//大于95报警
	{
		VarHydraulicOilHihgAlarm = 1;
	}
	else
	{
		VarHydraulicOilHihgAlarm = 0;
	}
	//液压油温传感器故障报警,正常范围200-2400,悬空时的Ai为18783
	if((VarAiHydraulicTemp<300)||((VarAiHydraulicTemp>60000)))
	{
		VarHydraulicOilTempSensorError = 1;
	}
	else
	{
		VarHydraulicOilTempSensorError = 0;
	}
}
/**************************************************************
**函数名：FunDoSet()
**功能描述：Do端口设置
**传入参数：无
**输出参数：无
**************************************************************/
void FunDoSet(void)
{
	//DO检测
	LibSetValueDOH(11,VarDoTravelHighSpeed);//pin46
	LibSetValueDOH(4,VarDoPilot);			//pin35
	LibSetValueDOH(13,VarDoSecondPressure);	//pin48
	LibSetValueDOH(7,VarDoBatteryRelay);	//pin42

	LibSetValueDOH(3,VarDoValveBreakPilot);	//pin34

	
	LibSetValueDOH(1,VarDoHydraulicCoolingPositiveValve); //pin32 液压冷却正/反转电磁阀
	LibSetValueDOH(6,VarDoBuzzerAlarm);	//pin37
	//LibSetValueDOL(1,VarDoAirFilterPump);	//pin41
	//LibSetValueDOL(1,0);	//pin41 2020/11/25上电空气清洗泵就得电，给视频记录仪供电
	LibSetValueDOH(10,VarDoFuelFilterPump);	//pin45
}

/**************************************************************
**函数名：FunPressureCompute()
**功能描述：根据压力传感器电流计算压力值
**传入参数：电流值(uA)
**输出参数：压力值(bar)
**************************************************************/
UINT16 FunPressureCompute(UINT16 VarAiPressure)
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
		Temp_Pressure = 400;
	}
	else
	{
		Temp_Pressure = (UINT16)(Temp_VarAiPressureMv*25-1000)/10;//40-200(0.1mA):0-400Bar
	}
	return(Temp_Pressure);
}

/**************************************************************
**函数名：FunLowerPressureCompute()
**功能描述：根据压力传感器电流计算压力值
**传入参数：电流值(uA)
**输出参数：压力值(bar)
**************************************************************/
UINT16 FunLowerPressureCompute(UINT16 VarAiPressure)
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
		Temp_Pressure = (UINT16)(Temp_VarAiPressureMv*10*3/8-150)/10;//40-200(0.1mA):0-60Bar
	}
	return(Temp_Pressure);
}

/**************************************************************
**函数名：FunFuelVolumeCompute()
**功能描述：根据燃油传感器电阻值计算燃油量
**传入参数：电阻值(0.1R)
**输出参数：燃油量(%)
**************************************************************/
UINT8 FunFuelVolumeCompute(UINT16 Res)
{
	UINT16 Temp_Fuel;
	VarResCompensation=Res*5;
	VarResCompensation=VarResCompensation/170;
	Res +=(UINT16)VarResCompensation;
	
	if(Res >= 1800)
	{
		Temp_Fuel = 100;
	}
	else if(Res <=100)
	{
		Temp_Fuel = 0;
	}
	else
	{
		Temp_Fuel = Res-100;
		Temp_Fuel = Temp_Fuel/17;
	}
	return((UINT8)Temp_Fuel);
}




/**************************************************************
**函数名：FunHydraulicOilTemCompute()
**功能描述：根据液压温度电阻值计算温度值
**传入参数：电阻值(0.1R)
**输出参数：温度(C)
**************************************************************/
UINT8 FunHydraulicOilTemCompute(UINT16 Res)
{


	
	
		UINT16 HydraulicOilTemp;
	
	if(Res>=1385)
	{
		HydraulicOilTemp = 100;
	}
	else if((Res<1385)&&((Res>=1366)))
	{
		HydraulicOilTemp = 95+((Res-1366)*(100-95))/(1385-1366);
	}
	else if((Res<1366)&&((Res>=1347)))
	{
		HydraulicOilTemp = 90+((Res-1347)*(95-90))/(1366-1347);
	}
	else if((Res<1347)&&((Res>=1328)))
	{
		HydraulicOilTemp = 85+((Res-1328)*(90-85))/(1366-1328);
	}
	else if((Res<1328)&&((Res>=1309)))
	{
		HydraulicOilTemp = 80+((Res-1309)*(85-80))/(1328-1309);
	}	
	else if((Res<1309)&&((Res>=1289)))
	{
		HydraulicOilTemp = 75+((Res-1289)*(80-75))/(1309-1289);
	}	
	else if((Res<1289)&&((Res>=1270)))
	{
		HydraulicOilTemp = 70+((Res-1270)*(75-70))/(1289-1270);
	}	
	else if((Res<1270)&&((Res>=1251)))
	{
		HydraulicOilTemp = 65+((Res-1251)*(70-65))/(1270-1251);
	}	
	else if((Res<1251)&&((Res>=1232)))
	{
		HydraulicOilTemp = 60+((Res-1232)*(65-60))/(1251-1232);
	}		
	else if((Res<1232)&&((Res>=1213)))
	{
		HydraulicOilTemp = 55+((Res-1213)*(60-55))/(1232-1213);
	}	
	else if((Res<1213)&&((Res>=1194)))
	{
		HydraulicOilTemp = 50+((Res-1194)*(55-50))/(1213-1194);
	}	
	else if((Res<1194)&&((Res>=1174)))
	{
		HydraulicOilTemp = 45+((Res-1174)*(50-45))/(1194-1174);
	}		
	else if((Res<1174)&&((Res>=1155)))
	{
		HydraulicOilTemp = 40+((Res-1155)*(45-40))/(1174-1155);
	}	
	else if((Res<1155)&&((Res>=1116)))
	{
		HydraulicOilTemp = 30+((Res-1116)*(40-30))/(1155-1116);
	}	
	else if((Res<1116)&&((Res>=1077)))
	{
		HydraulicOilTemp = 20+((Res-1077)*(30-20))/(1116-1077);
	}
	else
	{
		HydraulicOilTemp = 20;
	}
	return((UINT8)HydraulicOilTemp);
}
