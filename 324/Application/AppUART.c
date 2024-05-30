#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**函数名：FunUartReceiveData()
**功能描述：接收串口数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunUartReceiveData(void)
{
	UINT16 VarDataLenth,i;
//	UINT8 LibSciReadData[100];
	VarDataLenth= LibSciReceiveDataLenth();
	for(i=0;i<VarDataLenth;i++)
	{
		LibSciReadData[i]=LibSciReadReceiveData();
	}
	if((LibSciReadData[0]==99)&&(LibSciReadData[1]==115))//cs
	{
      if(LibSciReadData[2]>47)
      {
      	VarUartDataSendFlag=(UINT8)(LibSciReadData[2]-48);
      }
	}
}
/**************************************************************
**函数名：FunUartSendData()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/
void FunUartSendData(void)
{
	if(1)
	{    	
		if(LibTimer(7,1,1000,1))
		{
		//	VarUartDataSendFlag++;
			switch(VarUartDataSendFlag)
			{
				case 1:FunUartSendDataDiDo();break;
				case 2:FunUartSendDataAI();break;
				case 3:FunUartSendDataExcavator();break;
				case 4:FunUartSendDataBiaoding();break;
				case 5:FunUartSendDataFuju();break;
				case 6:FunUartSendDataGps();break;
				case 7:FunUartSendDataFlash();break;
				case 8:FunUartSendDataSpeed();break;				
/*				case 9:LibSciSendNumUint16(VarAiCBucketArmPressure,1,0);
						LibSciSendByte(0x20);
						LibSciSendNumUint16(VarPBucketArmPressure,1,0);
						LibSciSendByte(0x20);
						LibSciSendNumUint8(VarRatatorPowerSaveFlag,1,0);
						LibSciSendByte(0x20);
						LibSciSendNumUint8(VarDoDT6,1,0);
						break;*/
				default:break;
			}
		}
	}	
}
/**************************************************************
**函数名：FunUartSendDataDiDo()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/
void FunUartSendDataDiDo(void)
{
	LibSciSendString((UINT8*)"AIC.IN");//cs1   电流输入值
/*	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);//系统压力
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiPilotSwitch,1,0);//先导压力开关0
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);//高低速0
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//目标电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//实际电流值
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiPilotSwitch,1,0);//先导压力开关0
	//LibSciSendByte(0x20);
	//LibSciSendNumUint8(VarDiTravelHighSpeed,1,0);//先导压力开关0
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAiBoomDownPressure,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDoDT5,1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveDT5CurrentNow,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveDT5Error,1,0);
	*/
		
	/*
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiPilotSwitch,1,0);//先导压力开关0
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomUpPressureFilter,1,0);//动臂上升先导
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomDownPressureFilter,1,0);//动臂下降先导
	/*
	LibSciSendString((UINT8*)"***");
	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);//较大的压力
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP2PressureFilter,1,0);//P2压力
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);//P1压力
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomWorkModeNow,1,0);//模式
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiBoomUp,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiBoomDown,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSpeedLevel,1,0);//挡位
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//发动机转速

	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//小腔压力	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomBigPressureBar,1,0);//大腔压力*/
	

	
		
		/*
	
	
	
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanEngineTorque,1,0);//扭矩
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//发动机转速
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//目标电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//实际电流值
	LibSciSendByte(0x20);
	
	
	
	/*LibSciSendByte(0x20);
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(123,1,0);//小腔压力	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(456,1,0);//大腔压力bar
/*	
	

		
	
	
	/*	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarBoomWorkModeNow,1,0);//模式
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiBoomDown,1,0);//动臂下降
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//小腔压力	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomBigPressureBar,1,0);//大腔压力
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarZhiCheJudgeTimerFlag,1,0);//支车模式标志
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiValveSwitchesFlag,1,0);//压力开关	
	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarUpLowEngineFlag,1,0);//能量不足上升标志位
	*/

	
	/*LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//主泵目标电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//主泵实际电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[0],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[1],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[2],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[3],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[4],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[5],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[6],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[7],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[8],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[9],1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrent[10],1,0);//

	
	/*
	
	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarCanEngineTorque,1,0);//扭矩百分比
		LibSciSendByte(0x20);
				LibSciSendNumUint16(VarCanEngineWaterTemp,1,0);//水温
				LibSciSendByte(0x20);
							LibSciSendNumUint16(VarHydraulicOilTempFilter,1,0);//液压油温	
	
	
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPwmDT8CurrentTarget,1,0);

	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveDT8CurrentNow,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDt8PwRatio,1,0);
	
	
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomUpPressure,1,0);//pin8,动臂上升先导压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomDownPressure,1,0);//pin9,动臂下降先导,单位uA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiAccumPressure,1,0);//pin19,蓄能器压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBoomSmallPressure,1,0);//pin20,动臂小腔压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBucCapPressure,1,0);//pin6,铲斗大腔压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBoomBigPressure,1,0);//pin16,动臂大腔,单位uA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBucketArmPressure,1,0);//pin17,斗杆大腔压力,单位uA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBucketArmRodPressure,1,0);//pin23,斗杆小腔压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCPAccumAirSensor,1,0);//pin11,单位uA	蓄能器气压压力	
	*/
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAiBoomUpPressure,1,0);//pin8,动臂上升先导压力,单位uA
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAiBoomDownPressure,1,0);//pin9,动臂下降先导,单位uA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiAccumPressure,1,0);//pin19,蓄能器压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAccumPressureFilter,1,0);//pin19,蓄能器压力,单位uA
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//pin20,动臂小腔压力,单位uA
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarPBucCapPressure,1,0);//pin6,铲斗大腔压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBoomBigPressure,1,0);//pin16,动臂大腔,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomBigPressureBar,1,0);//pin16,动臂大腔,单位uA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPBucketArmPressure,1,0);//pin17,斗杆大腔压力,单位uA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//pin23,斗杆小腔压力,单位uA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAccumAirPressureBar,1,0);//pin11,单位uA	蓄能器气压压力	

		
	
}
/**************************************************************
**函数名：FunUartSendDataAI()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/
void FunUartSendDataAI(void)
{
	LibSciSendString((UINT8*)"AiPwm");//cs2
	//202004
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDoTravelHighSpeed,1,0);//
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAirPressureLowFlag,1,0);////节能传感器故障进入不节能模式标志
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAirPressureLowFlag,1,0);////节能传感器故障进入不节能模式标志
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(flag,1,0);////节能传感器故障进入不节能模式标志
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//转换后
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSpeedLevel,1,0);//气压
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanEngineSpeed,1,0);//实际
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAirPressureLowFlag,1,0);////动臂大腔压力传感器故障
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarP2PressureFilter,1,0);//
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarDoDT7,1,0);////节能传感器故障进入不节能模式标志
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16((VarRecDataID_0CF00400[2]-125),1,0);//


	

/*	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomUpPressure,1,0);//动臂上升先导压力电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAiBoomUpPressure,1,0);//动臂上升先导压力值bar
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomDownPressure,1,0);//动臂下降先导压力电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAiBoomDownPressure,1,0);//动臂下降先导压力值bar	
	
	*/

	
	

	

}
/**************************************************************
**函数名：FunUartSendData()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/
void FunUartSendDataBiaoding(void)
{
	LibSciSendString((UINT8*)"DI");//Cs4
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiDGNS,1,0);//开关斗杆内收
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiDGWB,1,0);//开关斗杆外摆
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiCDDS,1,0);//开关铲斗内收
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiCDWB,1,0);//开关铲斗外摆
	LibSciSendString((UINT8*)"Do");
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarBoomWorkModeNow,1,0);//模式VarBoomWorkModeNow
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDoDT1,1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDoDT2,1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDoDT3,1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDoDT4,1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDoDT6,1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDoDT7,1,0);//
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAccumPressureFilter,1,0);//
	
	
}
/**************************************************************
**函数名：FunUartSendDataExcavator()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/
void FunUartSendDataExcavator(void)
{
	    LibSciSendString((UINT8*)"SysData");//CS3
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarCanAutoIdleEnable,1,0);//自动怠速使能
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarAiPilotSwitch,1,0);//VarAiPilotSwitch
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarEngineSpeedNow,1,0);//动臂上升压力
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);//动臂下降压力bar	
	
		
		
	    
	    /*LibSciSendByte(0x20);
	    LibSciSendNumUint8(VarBoomWorkModeNow,1,0);//模式VarBoomWorkModeNow
	    
	    LibSciSendByte(0x20);
	        LibSciSendNumUint16(VarRestarForEnginerFlag,1,0);//启机标志位
	       	LibSciSendByte(0x20);
	        LibSciSendNumUint16(VarSpeedLevel0Timer10Ms,1,0);//计时器
	       LibSciSendByte(0x20);
	        LibSciSendNumUint16(VarSpeedLevelEngineFlag,1,0);//怠速节能部分标志位	
		       LibSciSendByte(0x20);
		        LibSciSendNumUint16(VarInModeBoomUpFirstFlag,1,0);//1
		        LibSciSendByte(0x20);
		  LibSciSendNumUint16(VarInModeBoomUpFirstBackFlag,1,0);//1
		  LibSciSendByte(0x20);
		  LibSciSendNumUint16(VarDiBoomUp,1,0);//1动臂上升
	     LibSciSendByte(0x20);
		 LibSciSendNumUint16(VarBoomUpPressureFilter,1,0);//
	     LibSciSendByte(0x20);
		 LibSciSendNumUint16(VarBoomDownPressureFilter,1,0);//		    				     		        
	    
	    /*
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarPAccumAirPressureBar,1,0);//蓄能器气体压力VarPAccumAirPressureBar
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarPAccumPressureFilter,1,0);//蓄能器压力
    	
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarLowEngineAirPressureBar,1,0);//蓄能器压力下降第一次接收值
    	LibSciSendByte(0x20);
		LibSciSendNumUint8(VarDoDT7,1,0);//
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarP1Pressure,1,0);//
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarP2Pressure,1,0);//
    	   /* 	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarCanExcavatorType,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarCanExcavatorId,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16((UINT16)VarEngineWorkTime1H,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint8((UINT8)VarEngineWorkTime1M,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint8(VarCMCommunicationVersion,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendString((UINT8*)"***");
    	LibSciSendByte(0x20);
    	LibSciSendNumUint8(VarCanEngineWaterTemp,1,0);
	    LibSciSendByte(0x20);
    	LibSciSendNumUint8(VarFuelVolumeFilter,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarEngineSpeedNow,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarCanEngineTorque,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarP1PressureFilter,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarP2PressureFilter,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarPiPressureFilter,1,0);
    	LibSciSendByte(0x20);
    	LibSciSendString((UINT8*)"***");
	    LibSciSendByte(0x20);
		LibSciSendNumUint16(VarAccDialPosiMin,1,0);
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarAccDialPosiMax,1,0);
		LibSciSendByte(0x20);
		LibSciSendNumUint8(VarExcavatorEngineType,1,0);
		LibSciSendByte(0x20);
    	LibSciSendByte(0x0D);
    	LibSciSendByte(0x0A);*/
}
/**************************************************************
**函数名：FunUartSendDataGps()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/
void FunUartSendDataGps(void)
{
	LibSciSendString((UINT8*)"Gps");
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanGpsHeartBeat,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanGpsLockCommand_A,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarGpsLockWork_A,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanGpsLockCommand_B,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarGpsLockWork_B,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanGpsLockCommand_C,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarGpsLockWork_C,1,1);
	LibSciSendByte(0x20);
	LibSciSendString((UINT8*)"***");
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanGpsLockCommand_D,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarGpsLockWork_D,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCan2MonthLockState,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanAntennaCutLockState,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanUncoverLockState,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanBusLockState,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanGpsCancel,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarCanGpsUrgencyState,1,1);
	LibSciSendByte(0x20);
	LibSciSendNumUint16((UINT16)VarEngineWorkTime_Gps,1,1);
	LibSciSendByte(0x20);
	LibSciSendByte(0x0D);
	LibSciSendByte(0x0A);
}
	
/**************************************************************
**函数名：FunUartSendDataFuju()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/	
void FunUartSendDataFuju(void)  //cs5
{
	LibSciSendString((UINT8*)"Fuju");
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanHighSpeedTravel,1,0);//行走高低速
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//发动机当前转速
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDoTravelHighSpeed,1,0);//行走高低速电磁阀输出
	
	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarAirFilterPump_Enable,1,0);//空气泵
		LibSciSendByte(0x20);
			LibSciSendNumUint16(VarDoAirFilterPump,1,0);//输出
		
	
	
	

	
	
	
	
	//	LibSciSendByte(0x20);
	//		LibSciSendNumUint16(VarPiPressureFilter,1,0);//先导压力
/*			LibSciSendByte(0x20);
					LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);//行走高速
	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarEngineSpeedNow,1,0);//发动机转速
	
		
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSpeedLevel,1,0);//发动机转速挡位
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCurrentLevel,1,0);//泵电流挡位
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDialGrade,1,0);//表盘挡位值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);//泵1压力
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);//泵2压力
	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);//泵1泵2压力较大的一个值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarTempCureentTargetValue,1,0);//额定电流直接赋值的中间电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16((VarTempCurrentTarget2),1,0);//中间计算电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//目标电流值
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//反馈电流值	
	
	/*
	LibSciSendString((UINT8*)"Fuju");
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[0],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[1],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[2],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[3],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[4],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[5],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[6],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPumpPowerParameter[7],1,0);
	LibSciSendByte(0x20);
	LibSciSendString((UINT8*)"***");
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarHydHammerFlow,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarHydSicissorsFlow,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarHydRamFlow,1,0);
	LibSciSendByte(0x20);//VarProValveCurrentTarget
	LibSciSendNumUint16(VarProValveCurrentTarget,1,0);
	LibSciSendByte(0x20);//VarDoValvePressRegulate
	LibSciSendNumUint8(VarDoValvePressRegulate,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDoValveBreakPilot,1,0);
	LibSciSendByte(0x20);
	LibSciSendByte(0x0D);
	LibSciSendByte(0x0A);
	*/
}
/**************************************************************
**函数名：FunUartSendDataFlash()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/	
void FunUartSendDataFlash(void)
{
	LibSciSendString((UINT8*)"Flash");
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSysDataMasterCheckFlag,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSysDataBackupCheckFlag,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarGpsDataMasterCheckFlag,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarGpsDataBackupCheckFlag,1,0);
	
	LibSciSendByte(0x20);
	LibSciSendString((UINT8*)"***");
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineTimeMasterCheckFlag,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineTimeBackupCheckFlag,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineTimeMasterCheckFlagIndex,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineTimeBackupCheckFlagIndex,1,0);
	
	LibSciSendByte(0x20);
	LibSciSendString((UINT8*)"***");
	LibSciSendNumUint16(VarFlashHourMainAdrCheckFlag,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarFlashEngineTimeMasterAdr,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarFlashEngineTimeBackupAdr,1,0);
	LibSciSendByte(0x20);
	LibSciSendByte(0x20);
	LibSciSendByte(0x0D);
	LibSciSendByte(0x0A);
}
/**************************************************************
**函数名：FunUartSendDataFlash()
**功能描述：通过串口发送系统参数
**传入参数：无
**输出参数：无
**************************************************************/	
void FunUartSendDataSpeed(void)
{
	LibSciSendString((UINT8*)"CumminsDiag");//cs8
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDoSecondPressure,1,0);//二次增压DO输出	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanSysHSLMode,1,0);//bit0,H模式bit1,S模式bit2,L模式
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);	////发动机当前转速
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP2PressureFilter,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSysAveragePress,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);	//行走压力开关DIH
	
	
	
	
	/*LibSciSendByte(0x20);
	LibSciSendNumUint16(VarIsuzuFaultCodeSingle,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarIsuzuFaultCodeMany,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarIsuzuCodeNumber,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarUartFaultCode,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineFaultCode2,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineFaultCode3,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineFaultCode4,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineFaultCode5,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineFaultCode6,1,0);
	
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[0],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[1],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[2],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[3],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[4],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[5],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[6],1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarRecDataID_0x18ECFF00[7],1,0);*/
	LibSciSendByte(0x20);
	LibSciSendByte(0x0D);
	LibSciSendByte(0x0A);
}
