/*
 * AppPowerSaveFault.c
 *
 *  Created on: Dec 17, 2020
 *      Author: Sean
 */

#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**函数名：FunPowerSaveFault()
**功能描述：节能故障判断报警
**传入参数：无
**输出参数：
**************************************************************/
void FunPowerSaveFault(void)
{
	//节能传感器故障进入不节能模式
	if(
	(VarBoomUpPressureSensorEorror == 1)||//动臂上升压力传感器故障
	(VarBoomDownPressureSensorEorror == 1)||//动臂下降压力传感器故障
	(VarBoomBigPressureSensorEorror == 1)||//动臂大腔压力传感器故障
	(VarBoomSmallPressureSensorEorror == 1)||//动臂小腔压力传感器故障
	(VarPAccumPressureSensorEorror == 1)||//蓄能器油压传感器故障
	(VarAirPressureLowFlag==1)||//蓄能器气压低报警
	(VarP1PressureSensorEorror == 1)||//P1泵传感器故障
	(VarP2PressureSensorEorror == 1)//P2泵传感器故障
	)
	{
		VarEngineSaveSensorFaultChangeModeFlag=1;//节能传感器故障进入不节能模式标志
	}
	else
	{
		VarEngineSaveSensorFaultChangeModeFlag=0;
	}
		
		
	//传感器故障报警
	
	VarPAccumAirSensorError == 1;//蓄能器气压压力传感器故障
	VarBucketArmPressureSensorEorror == 1;//斗杆大腔压力传感器故障判断
	VarAiCBucketArmRodSensorEorror == 1;//斗杆小腔压力传感器故障判断
	VarAiCBucCapPressureSensorEorror == 1; //铲斗大腔压力传感器故障判断

	
	
	
	
	//电磁阀故障报警
	VarValveDT1Error == 1;
	VarValveDT2Error == 1;
	VarValveDT6Error == 1;
	VarValveDT8Error == 1;
	VarValveDT5Error == 1;
	//DT7没有
	
	//插装阀故障
	if((VarBoomDownPressureFilter>5)&&(VarBoomBigPressureBar>300)&&(VarBoomSmallPressureBar>300))
	{
		VarCartridgeValveFaultFlag=1;
	}
	else
	{
		VarCartridgeValveFaultFlag=0;
	}
	
	
	
	
	
	
	
	
}


