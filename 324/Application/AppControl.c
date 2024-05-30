#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**函数名：FunSysSleep()
**功能描述：系统休眠
**传入参数：无
**输出参数：无
**************************************************************/
void FunSysSleep(void)
{
	UINT32 Ulong_Temp,Ulong_Temp2,Ulong_Temp3;
	BOOL VarBool1,VarBool2,VarBool3;
	VarBool1 = LibTimerTon(7,!VarSysPowerOn,30,&Ulong_Temp2);
	VarBool2 = LibTimerTon(3,!VarSysPowerOn,5000,&Ulong_Temp);//5S
	VarBool3 = LibTimerTon(13,!VarSysPowerOn,120000,&Ulong_Temp3);
	//机油压力低超过40S,关发动机,五十铃发动机有效
	if(VarEngineWorkErrorTime1S>40)
	{
		VarEngineNeedStopFlag =1;
	}
	else
	{
    	VarEngineNeedStopFlag =0;	
	}
	//钥匙开关关闭
	if(VarBool1)
	{
		//钥匙开关关闭后，节能部分阀置零，防止掉臂。
		VarDoDT7=0;
		VarDoDT1=0;
		VarDoDT2=0;
		VarDoDT8=0;
		//关闭DO,H_Bridge,PWM,+5V,+12V...
		LibSetValueDOH(11,0);	//pin46
		LibSetValueDOH(4,0);	//pin35
		LibSetValueDOH(13,0);	//pin48
		//油门调至最小
		VarCanEngineLevelSpeed=VarEngineLevelSpeed[0];
		
		//节能挖钥匙开关关闭后，DT5得电2分钟再失电
		VarDoDT5=1;//pin73 备用VarDoDT5
		
		
		//电源继电器延时5S关闭，之后系统休眠
		if( VarBool2 && (VarEngineSpeedNow<400) )
		{
			
			
			LibSetValueDOH(7,0);	//pin42,关闭系统电源
			LibSystem5vOutput(1);	//控制器+5V输出关闭
			LibSetPwmRatio(1,0);	//PWM输出关闭
			//保存GPS数据
			VarFlashGpsDataMasterNeedSaveFlag=1;
			VarFlashGpsDataBackupNeedSaveFlag=1;
			if(VarEngineStarted>0)//发动机启动过
			{
				//保存小时计数据
				VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
				VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
				VarFlashHourNeedSaveMainFlag=1;
				VarEngineStarted = 0;
			}
			FunFlashWriteData();//数据保存
			//中断开启
			LibIrqaEnable();
			LibIrqaEnable();
			LibMcuLedOutput(1);
			//再次判断钥匙开关电平信号
			if(LibGetValueDIH(2))
			{
			    LibSystemDelay1MS(5);
				if(LibGetValueDIH(2))
				{
					
					//重启
					LibSystemRestart();
				}
			}
		
		}
		
		if( VarBool3 && (VarEngineSpeedNow<400) )
		{
			LibSetValueDOH(0,0);	//pin31DT5关
	//	VarDoDT5=0;//pin73 备用VarDoDT5
		//中断开启
		LibIrqaEnable();
		LibIrqaEnable();
		LibMcuLedOutput(1);
		//再次判断钥匙开关电平信号
		if(LibGetValueDIH(2))
		{
		    LibSystemDelay1MS(5);
			if(LibGetValueDIH(2))
			{
				
				//重启
				LibSystemRestart();
			}
		}
		LibSystemSleep();
		
		}
		
	}
	else	
	{
		VarDoDT5=0;//pin73 备用VarDoDT5
	}
}
/**************************************************************
**函数名：AutoIdle()
**功能描述：自动怠速
**传入参数：无
**输出参数：无
**************************************************************/
void FunAutoIdle(void)

{
	//进入怠速以及怠速控制中
	if((VarCanAutoIdleEnable) //  //自动怠速使能
		&&(LibTimerGet1S()>4)  //已过了启动前几秒
		&&(VarAiPilotSwitch==0) //驾驶员无操作，先导压力开关为0
		&&(VarEngineSpeedNow>300)&&(!VarDiTravelHighSpeed)) //发动机已启动,行走压力开关关
	{
		if(!VarstartIdle)
		{
			VarIdleTimer=LibTimerGet1MS();
			VarstartIdle=TRUE;
		}
		else
		{
			if(LibTimerGet1MS()-VarIdleTimer>=3000)//3000
			{
				VarIdleState=2;
			}
			else if(LibTimerGet1MS()-VarIdleTimer>=1200) // 1200//开始进入怠速控制状态
			{
				VarIdleState=1;
				VarCurrentIdleDelay=TRUE;
			}
		}
	}
	//退出怠速
	else if(VarstartIdle==TRUE) 
	{
		VarstartIdle=FALSE;
		VarIdleState=0;
		VarIdleTimer=LibTimerGet1MS();
	}
	//延时电流上升
	else
	{
		if(LibTimerGet1MS()-VarIdleTimer>=2800)
			VarCurrentIdleDelay=FALSE;
	}
	
	
	//***************左手柄按钮一键怠速***********************
	if((VarDiLowSpeedEnableLast==0)&&(VarDiLowSpeedEnable>0))
	{
		if(VarButtonLowSpeedEnable>0)
		{
			VarButtonLowSpeedEnable=0;
		}
		else
		{
			VarButtonLowSpeedEnable=1;
		}
	}
	VarDiLowSpeedEnableLast=VarDiLowSpeedEnable;
}
/**************************************************************
**函数名：FunTemperatureCotrol()
**功能描述：发动机冷却水温过低与过高控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunTemperatureCotrol(void)
{
	//进入暖机状态
	if((VarCanEngineWaterTemp<25)
		&&(VarEngineSpeedNow>300)
		&&(VarEngineSpeedNow<1200)
		&&(VarEngineWarmDone==FALSE)
		&&(!VarEngineStartState))
	{
		VarEngineWarmState=TRUE;
		VarEngineWarmDone=TRUE;
		VarEngineWarmStartTime=LibTimerGet1S();
	}
	//暖机持续时间控制
	if(VarEngineWarmState&&((LibTimerGet1S()-VarEngineWarmStartTime)>15))
	{
		VarEngineWarmState=FALSE;
	}
	//进入冷却控制状态
	if( (VarCanEngineWaterTemp>102)&&(VarEngineSpeedNow>1500) )
	{
		VarEngineCoolState=TRUE;
	}
	//退出冷却控制
	if(VarCanEngineWaterTemp<100)
	{
		VarEngineCoolState=FALSE;
	}
}
/**************************************************************
**函数名：FunTravelSpeed()
**功能描述：行走高低速控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunTravelSpeed(void)
{
	if(  VarCanHighSpeedTravel>0 &&
	     VarEngineSpeedNow>300
	)
	{
		VarDoTravelHighSpeed=1;
	}
	else
	{
		VarDoTravelHighSpeed=0;
	}
/*	if((VarCanHighSpeedTravel!=VarCanHighSpeedTravelLast)||(VarTravelSpeedButton!=VarTravelSpeedButtonLast)
	&& VarEngineSpeedNow>300)
	{
		VarDoTravelHighSpeed=!VarDoTravelHighSpeed;
	}	
	VarCanHighSpeedTravelLast=VarCanHighSpeedTravel;
	VarTravelSpeedButtonLast=VarTravelSpeedButton;
*/
}
/**************************************************************
**函数名：FunSecondPressure()
**功能描述：二次增压控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunSecondPressure(void)
{
	//二次增压输出,S/H模式的情况
	if( ((VarCanSysHSLMode==0)||((VarCanSysHSLMode==1)))&&
	    (VarEngineSpeedNow>=1400)//1600
	)
	{
		if( (VarP1PressureFilter>300) || (VarP2PressureFilter>300) || (VarSysAveragePress>300))
		{
			VarDoSecondPressure = 1;
		}
		else if( (VarP1PressureFilter<280) && (VarP2PressureFilter<280) )
		{
			VarDoSecondPressure = 0;
		}
	}
	else if( (VarCanSysHSLMode==2) ||
	         (VarEngineSpeedNow<1350)//1550
	)
	{
		VarDoSecondPressure = 0;
	}
	//行走高速时，取消自动增压功能
/*	if(VarDiTravelHighSpeed>0)
	{
		VarDoSecondPressure = 0;
	}
	*/
}

/**************************************************************
**函数名：FunBuzzerAlarm()
**功能描述：蜂鸣器报警控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunBuzzerAlarm(void)
{
   if(VarSysPowerOn)
   {
       if ((VarDiStop)||(VarDiFastReversingSw))
        {
	       VarDoBuzzerAlarm=1;	   
        }
       else
        {
          VarDoBuzzerAlarm=0;
        }	
   }
   else
   {
        VarDoBuzzerAlarm=0;	
   }

}


/**************************************************************
**函数名：FunFuelAirFitlerControl()
**功能描述：空滤清洁与燃油过滤控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunFuelAirFitlerControl(void)
{
   
       if (VarAirFilterPump_Enable>0)
        {
	       VarDoAirFilterPump=0;	   
        }
       else
        {
          VarDoAirFilterPump=1;
        }
        
       if (VarFuelFilterPump_Enable>0)
        {
	       VarDoFuelFilterPump=1;	   
        }
       else
        {
          VarDoFuelFilterPump=0;
        }	


}

/**************************************************************
**函数名：FunSwitchValveControl()
**功能描述：开关阀控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunSwitchValveControl(void)
{
//	UINT32 Temp1_ET;
//	UINT32 Temp2_ET;
//	//雨刮高低速开关阀控制
//	VarWaterSprayOn = LibTimerTon(13,VarDoWaterSpray,3000,&Temp1_ET);//3S
//	VarWaterSprayOFF = LibTimerTon(14,!VarDoWaterSpray,3000,&Temp2_ET);//3S
//	if(VarWaterSprayOn)
//	{
//		VarDoWiper_1=1;
//		VarDoWiper_2=0;
//	}
//	else
//	{
//		switch(VarWiperButton)
//		{
//			case 0:
//				if(VarDiWiperResetSignal)
//				{
//					VarDoWiper_1=1;
//					VarDoWiper_2=0;
//				}
//				else
//				{
//					if(VarWaterSprayOFF)
//					{
//						VarDoWiper_1=0;
//						VarDoWiper_2=0;
//					}
//					else
//					{
//						VarDoWiper_1=VarDoWiper_1;
//						VarDoWiper_2=VarDoWiper_2;
//					}		
//				}
//				break;
//			case 1:
//				VarDoWiper_1=1;
//				VarDoWiper_2=0;
//				break;
//			case 2:
//				VarDoWiper_1=1;
//				VarDoWiper_2=1;
//				break;
//			default:break;
//		}
//	}
//	
//	
//	//洗涤开关阀控制
//	if(VarWaterSprayButton)
//	{
//		VarDoWaterSpray=1;
//	}
//	else
//	{
//		VarDoWaterSpray=0;
//	}
//	
//	//灯具开关控制
//	if(VarCautionLampButton)//警示灯
//	{
//		VarDoCautionLamp=1;
//	}
//	else
//	{
//		VarDoCautionLamp=0;
//	}
//	
//	if(VarCabinLamptButton)//驾驶室顶灯
//	{
//		VarDoCabinLamp=1;
//	}
//	else
//	{
//		VarDoCabinLamp=0;
//	}
//	
//	if(VarWorkLampButton)//工作灯
//	{
//		VarDoWorkLamp=1;
//	}
//	else
//	{
//		VarDoWorkLamp=0;
//	}
	
	//手动再生辅助负载电磁阀控制
	if(VarDoManualRegenrationLoadEnabled)
	{
		VarDoManualRegenrationLoad=1;
	}
	else
	{
		VarDoManualRegenrationLoad=0;
	}
}
/**************************************************************
**函数名：FunSpeedControl()
**功能描述：发动机转速控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunSpeedControl(void)
{

	   if (VarDialGrade>=9)
	   {
	     	VarCanSysHSLMode=0;
	   }
	   else if((VarDialGrade>=6)&&(VarDialGrade<9))
	   {
	   	    VarCanSysHSLMode=1;
	   }
	   else
	   {
	   	   	VarCanSysHSLMode=2;
	   }
		VarSpeedLevel=VarDialGrade;    // 表盘范围：1-10
		//转换成VarSpeedLevel:0-9
		if(VarSpeedLevel>0)
		{
			VarSpeedLevel -= 1;
		}
		if(VarSpeedLevel>9)
		{
			VarSpeedLevel = 9; 
		}
	  	//判断是否处于发动机启动前5秒，处于初启动状态，IN_START_STATE为TRUE
	  	if(LibTimerGet1S()>=5)
		{
			VarEngineStartState=FALSE;
		}
		else
		{
			VarEngineStartState=TRUE;	
		}
		//处于初启动状态或GPS锁转速，速度档位为0
	  	if (VarEngineStartState||VarGpsLockEnginePower)	  
	  	{
	  		VarSpeedLevel=0;
	  	}
	  	else
	  	{
	  	
	  
	  		    //AutoIdle
	  			if((VarIdleState==1)&&(VarSpeedLevel>=5))
			  	{
			  		VarSpeedLevel=(UINT8)(VarSpeedLevel-2);
			  	}
			  	else if(VarIdleState==2)
			  	{
			  		VarSpeedLevel=1;	
			  	}
			  	 if(VarBoomDownPressureFilter>5)
			  	 {
					 if(VarSpeedLevel>=8)
					 {
					  	 VarSpeedLevel=(UINT8)(VarSpeedLevel-3);				  						 
					 }
					 else if(VarSpeedLevel==7)
					 {
					  	 VarSpeedLevel=(UINT8)(VarSpeedLevel-2);				  						 
					 }
					 else if(VarSpeedLevel==6)
					 {
					  	 VarSpeedLevel=(UINT8)(VarSpeedLevel-1);				  						 
					 }
					 else 
					 {
						 VarSpeedLevel=(UINT8)(VarSpeedLevel);				  						 
					 }

			  	 }
			  	
	  			
	  			
			  	//暖机运行
			  	if(VarEngineWarmState) 
			  	{
			  		VarSpeedLevel=1;
			  	}
			  	//降温运行
			  	else if(VarEngineCoolState) 
			  	{
			  	    if(VarSpeedLevel>2)
			  	    {
			  	    	VarSpeedLevel=2;
			  	    }
			  	}
			  	//左手柄一键怠速运行
			  	else if(VarButtonLowSpeedEnable)
			  	{
			  		VarSpeedLevel =0;
			  	}
			  	//液压油高温时间2分钟、液压油温传感器异常处理
				else if((VarHydraulicOilTempCount>=400)||(VarHydraulicOilTempSensorError==1))
				{
					VarSpeedLevel =0;
				}
	  	}
	  	if(VarSpeedLevel>10)
	  	{
	  		VarSpeedLevel = 10;
	  	}
	  	if(VarSysSleepCommand)
	  	{
	  		VarSpeedLevel = 0;
	  	}
	  	
	  	
	    if(VarCanPumpMode)//转速提升到主泵额定转速
	    {
		    VarCanEngineLevelSpeed=1680;
	    }
	  	else if(VarCanEngineMode)//转速提升到发动机额定转速
	    {
		    VarCanEngineLevelSpeed=1850;
	    } 
	  	else
	  	{
	  	  	VarCanEngineLevelSpeed=VarEngineLevelSpeed[VarSpeedLevel];
	  	}
  
}
/**************************************************************
**函数名：FunAssistantSet()
**功能描述：辅具设置
**传入参数：无
**输出参数：无
**************************************************************/
void FunAssistantSet(void)
{
	//非辅具模式，退出
	if(VarCanSysHSLBKRMode<8)
	{
		VarDoValveBreakPilot=0;
		VarDoValvePressRegulate=0;
		VarProValveCurrentTarget=0;
		return;
	}
	//B-破碎器模式，液压破碎锤流量
	if(VarCanSysHSLBKRMode & 0x08)
	{
		VarDoValvePressRegulate = 0;
		VarDoValveBreakPilot = 0;
		if(VarDiPressureSwitch)
		{
			VarProValveCurrentTarget = (UINT16)((696.71-1.26*270*(float)(VarHydHammerFlow)/100)/2.1719);
		}
		else
		{
			VarProValveCurrentTarget = 0;	
		}
	}
	//K-液压剪模式,液压剪流量
	else if(VarCanSysHSLBKRMode & 0x10)
	{
		VarDoValvePressRegulate = 1;
		VarDoValveBreakPilot = 1;
		if(VarDiPressureSwitch)
		{
			VarProValveCurrentTarget = (UINT16)((696.71-1.26*270*(float)(VarHydSicissorsFlow)/100)/2.1719);
		}
		else
		{
			VarProValveCurrentTarget = 0;	
		}
	}
	//R-液压夯模式，液压夯流量
	else if(VarCanSysHSLBKRMode & 0x20)
	{
		VarDoValvePressRegulate = 1;
		VarDoValveBreakPilot = 1;
		if(VarDiPressureSwitch)
		{
			VarProValveCurrentTarget = (UINT16)((696.71-1.26*270*(float)(VarHydRamFlow)/100)/2.1719);
		}
		else
		{
			VarProValveCurrentTarget = 0;	
		}
	}
	//调用PID函数实现阀电流的闭环控制
	//待修改与验证
	//VarAssValvePwRatio = FunValveRatioComputePID(VarProValveCurrentTarget,VarAssValveCurrentNow,26,100,0);
	LibSetPwmRatio(11,0);
}






/**************************************************************
**函数名：FunHydraulicCoolingPumpCurrent()
**功能描述：液压冷却泵比例阀控制
**传入参数：无
**输出参数：无
**************************************************************/

void FunHydraulicCoolingPumpCurrent(void)
{ 	UINT8 Trigger;
	UINT32 Temp_ET;
	UINT8 Var_Enable1;
	UINT8 Var_Enable2;
	UINT8 Var_Enable3;
	UINT8 Var_Enable4;
	UINT8 N;
	
	//赋值，设置各档位风扇的最大电流值
	VarFANCurrent[0] = DefineFANCurrentSet0;
	VarFANCurrent[1] = DefineFANCurrentSet1;
	VarFANCurrent[2] = DefineFANCurrentSet2;
	VarFANCurrent[3] = DefineFANCurrentSet3;
	VarFANCurrent[4] = DefineFANCurrentSet4;
	VarFANCurrent[5] = DefineFANCurrentSet5;
	VarFANCurrent[6] = DefineFANCurrentSet6;
	VarFANCurrent[7] = DefineFANCurrentSet7;
	VarFANCurrent[8] = DefineFANCurrentSet8;
	VarFANCurrent[9] = DefineFANCurrentSet9;
	VarFANCurrent[10] = DefineFANCurrentSet10;
	
	 if(LibTimer(13,1,300,1))
	 {
		  if((VarHydraulicOilTempFilter>=95)&&(VarProHydraulicFANValveCurrentTarget<=150))//液压油高温持续时间计数
		  {
				VarHydraulicOilTempCount++;
		  }
		  else
		  {
				VarHydraulicOilTempCount=0;    
		  }        
	 }
	
	 if(VarHydraulicOilTempSensorError==1)//液压油温传感器故障报警时，风扇转速最大
	 {
		 VarProHydraulicFANValveCurrentTarget=150;
	 }
	 else
	 {
		  if(VarCanAccHydraulicCoolingFWD==0)
			 {
	
						if((VarHydraulicOilTempFilter<40))
							{
							 VarDoHydraulicCoolingPositiveValve=0;
							
							 VarProHydraulicFANValveCurrentTarget=600;//650	
							}
						else if((VarHydraulicOilTempFilter>=40)&&(VarHydraulicOilTempFilter<50))
							{
							   VarDoHydraulicCoolingPositiveValve=0;
							 
							 VarProHydraulicFANValveCurrentTarget=600;	//550
							}
						else if((VarHydraulicOilTempFilter>=50)&&(VarHydraulicOilTempFilter<55))
							{
								VarDoHydraulicCoolingPositiveValve=0;
					
								VarProHydraulicFANValveCurrentTarget=VarFANCurrent[VarCurrentLevel]+(VarFANCurrent[VarCurrentLevel]+VarCurrentLevel*10)*30/100;	
							}
						else if((VarHydraulicOilTempFilter>=55)&&(VarHydraulicOilTempFilter<60))
							{
								VarDoHydraulicCoolingPositiveValve=0;
								
							   VarProHydraulicFANValveCurrentTarget=VarFANCurrent[VarCurrentLevel]+(VarFANCurrent[VarCurrentLevel]+VarCurrentLevel*10)*25/100;	
							}
							
				
						else if((VarHydraulicOilTempFilter>=60)&&(VarHydraulicOilTempFilter<65))
						 
							{
							   VarDoHydraulicCoolingPositiveValve=0;
							
							   VarProHydraulicFANValveCurrentTarget=VarFANCurrent[VarCurrentLevel]+(VarFANCurrent[VarCurrentLevel]+VarCurrentLevel*10)*20/100;	
							}
						else if((VarHydraulicOilTempFilter>=65)&&(VarHydraulicOilTempFilter<70))
		
							{
								VarDoHydraulicCoolingPositiveValve=0;
						
								VarProHydraulicFANValveCurrentTarget=VarFANCurrent[VarCurrentLevel]+(VarFANCurrent[VarCurrentLevel]+VarCurrentLevel*10)*15/100;	
							}
							
						else if((VarHydraulicOilTempFilter>=70)&&(VarHydraulicOilTempFilter<75))
					
							{
								VarDoHydraulicCoolingPositiveValve=0;
						
								VarProHydraulicFANValveCurrentTarget=VarFANCurrent[VarCurrentLevel]+(VarFANCurrent[VarCurrentLevel]+VarCurrentLevel*10)*10/100;	
							}
						else if((VarHydraulicOilTempFilter>=75)&&(VarHydraulicOilTempFilter<80))
					
							{
								VarDoHydraulicCoolingPositiveValve=0;
						
								VarProHydraulicFANValveCurrentTarget=VarFANCurrent[VarCurrentLevel]+(VarFANCurrent[VarCurrentLevel]+VarCurrentLevel*10)*5/100;	
							}
						else if((VarHydraulicOilTempFilter>=80)&&(VarHydraulicOilTempFilter<85))
		
						   {
								VarDoHydraulicCoolingPositiveValve=0;
					
								VarProHydraulicFANValveCurrentTarget=VarFANCurrent[VarCurrentLevel];
							}
						else
						   {
								VarDoHydraulicCoolingPositiveValve=0;
							
							  VarProHydraulicFANValveCurrentTarget=150;	//100
							}
								  
			 }
						   

						 
			else
				{
					if(VarHydraulicFanBool==0)
					{
						VarProHydraulicFANValveCurrentTarget=200;	       		
					}
			
					
					if(VarEngineSpeedNow>400)	
					{
						Trigger=1;
						VarHydraulicFanBool=LibTimerTon(31,Trigger,60000,&Temp_ET);
					}
					else
					{
						Trigger=0;
						VarHydraulicFanBool=0;
						LibTimerTon(31,0,50,&Temp_ET);
					}
					
					if(VarHydraulicFanBool)//如果反转时间超过4.5分钟则让风扇先减速后停下来
					{
						if(VarProHydraulicFANValveCurrentTarget<650)
						{
							VarProHydraulicFANValveCurrentTarget+=5;
						}
						else
						{
							VarProHydraulicFANValveCurrentTarget=650;//600
							VarDoHydraulicCoolingPositiveValve=0;
					
						}
						
					}
					else
					{
						VarDoHydraulicCoolingPositiveValve=1;
				
					}
		
				}
		
	
	 }  
	 	    
}


/**************************************************************
**函数名：FunPumpCurrent()
**功能描述：液压泵功率控制
**传入参数：无
**输出参数：无
**************************************************************/
void FunPumpCurrent(void)
{

	UINT8 i,VarBool;
	UINT16 speed_key=100;
	UINT32 Temp_Ulong;
	UINT16	speed_key1;
	UINT16	speed_key2;
	//赋值，设置各档位初始电流值
	VarValveCurrent[0] = DefineValveCurrentSet0;
	VarValveCurrent[1] = DefineValveCurrentSet1;
	VarValveCurrent[2] = DefineValveCurrentSet2;
	VarValveCurrent[3] = DefineValveCurrentSet3;
	VarValveCurrent[4] = DefineValveCurrentSet4;
	VarValveCurrent[5] = DefineValveCurrentSet5;
	VarValveCurrent[6] = DefineValveCurrentSet6;
	VarValveCurrent[7] = DefineValveCurrentSet7;
	VarValveCurrent[8] = DefineValveCurrentSet8;
	VarValveCurrent[9] = DefineValveCurrentSet9;
	VarValveCurrent[10] = DefineValveCurrentSet10;
	//高原模式时,将高8档电流设置为基准值得90%
	if(VarCanHighlandMode>0)
	{
		for(i=3;i<11;i++)
		{
		  VarValveCurrent[i] = (UINT16)((VarValveCurrent[i]*9)/10);	
		}
	}
	//根据显示屏设置的功率点值对电流设置,所设置的功率点1-8对应所调节的档位3-11
	//VarPumpPowerParameter[i]=5对应电流基准值,小于5时1-2%;大于5时1-1%;
	for(i=0;i<8;i++)
	{
	  if(VarPumpPowerParameter[i]<5)
	  {
	  	VarValveCurrent[i+3] =(VarValveCurrent[i+3]*(100-(5-VarPumpPowerParameter[i])*2))/100;
	  }
	  else
	  {
	    VarValveCurrent[i+3] =(VarValveCurrent[i+3]*(100+(VarPumpPowerParameter[i]-5)*1))/100;	
	  }
	}

	//GPS锁泵功率,目标电流为1档	
	if(VarGpsLockPumpPower)
	{
		for(i=0;i<11;i++)
		{
			VarValveCurrent[i] = DefineValveCurrentSet0;
		}
		TempCurrentTarget=DefineValveCurrentSet0;
	}
	else
	{
		//根据压力计算各档位目标电流值				
		if ((VarEngineStartState>0) || 
			(VarIdleState>0) ||
			(VarSysSleepCommand>0) ||
			(VarEngineSpeedNow<100)
			)
		{
			VarValveCurrentTarget=0;
			TempCurrentTarget = 0;
			CurrentOffset=0;
		}
		else
		{
			//取驾驶员设定档位:0~9
			VarCurrentLevel = VarSpeedLevel;
			//AutoIdle
			if((VarIdleState==1)&&(VarSpeedLevel>=2))
			{
				VarCurrentLevel -= 2;
			}
			else if((VarIdleState==2)&&(VarSpeedLevel>=2))//为什么需要speedLevel>=2 ???
			{
				VarCurrentLevel = 0;	
			}
			//计算目标电流




	TempPressBigger = LibMaxUint16(VarP1PressureFilter,VarP2PressureFilter);

			if(LibTimer(9,1,10,1))
			{
				if((TempPressBigger<60)&&(VarDiTravelHighSpeed<=0))//驾驶员无操作，
				{
					if(VarLoadFreeStateTimer10Ms<65535)
					VarLoadFreeStateTimer10Ms++;
					VarLoadHeavyStateTimer10Ms=0;
					VarLoadMiddleStateTimer10Ms=0;
				}
				else if(TempPressBigger>310)
				{
					VarLoadFreeStateTimer10Ms=0;
					VarLoadMiddleStateTimer10Ms=0;//500;
					if(VarLoadHeavyStateTimer10Ms<65535)
					 VarLoadHeavyStateTimer10Ms++;
				}
				else 
				{
					VarLoadFreeStateTimer10Ms=0;
					VarLoadHeavyStateTimer10Ms=0;
					if(VarLoadMiddleStateTimer10Ms<65535)VarLoadMiddleStateTimer10Ms++;
				}
				
				
				
			}

			VarTempCureentTargetValue=VarValveCurrent[VarCurrentLevel];
		
			
	
				if(VarLoadFreeStateTimer10Ms>0)
				{
					VarTempCurrentTarget2 = 0;//初始动作时电流为0
					VarSpeedLowTimer10Ms=0;
					
				}
		
				else if(VarLoadHeavyStateTimer10Ms>5)
				{

					VarTempCurrentTarget2=200;	
				}
				
				else
				{
				
				
					speed_key1=(UINT16)(VarCanEngineLevelSpeed-VarCanEngineLevelSpeed*10/100);	//10%的掉速率
					speed_key2=(UINT16)(VarCanEngineLevelSpeed-VarCanEngineLevelSpeed*8/100);	//8%的掉速率

					if(LibTimer(10,1,10,1))
					{
						if(VarEngineSpeedNow>=speed_key2)//掉速小于8%
						{
							if(VarSpeedLowTimer10Ms<0xff) VarSpeedLowTimer10Ms++;
						}
						else
						{
							VarSpeedLowTimer10Ms=0;
						}
					}

					if(VarTempCurrentTarget2 < VarTempCureentTargetValue)
					{
						VarCurrentAddValue=2.5;				//压力>4MPa，电流以2的步长增加

					}
					VarCurrentReduceValue=0;//初始化为0
					
					if(VarEngineSpeedNow<=speed_key1)//掉速超过10%
					{
						VarCurrentAddValue = 0;//转速掉速超过10%时，电流保持不变不能上升
						if(VarTempCurrentTarget2 > VarTempCureentTargetValue*8/10)
						{
							VarCurrentReduceValue=5;//转速掉速超过10%且电流大于基准电流的80%时，电流以5的步长减少
						}
						
					}				
					else if(VarEngineSpeedNow<=speed_key2)//掉速超过8%小于10%
					{
						   if(VarTempCurrentTarget2 < VarTempCureentTargetValue*10/10)
							{
								VarCurrentAddValue=1;
							}
						
					}
					
					else if(VarSpeedLowTimer10Ms>50)//掉速<8%，持续时间超过500ms
					{
							if(VarTempCurrentTarget2 < VarTempCureentTargetValue*105/100)
							{
								VarCurrentAddValue=2;
							}
							
					}
					if((VarTempCurrentTarget2<VarTempCureentTargetValue)&&(VarCurrentAddValue>0))
					{
						VarTempCurrentTarget2 +=VarCurrentAddValue;  
					}
					else
					{
						if((VarCurrentReduceValue>0)&&(VarTempCurrentTarget2>VarCurrentReduceValue))
						{
							VarTempCurrentTarget2 -= VarCurrentReduceValue;
						}

					}
				}
			
	
			

			
			

		}
	}
	

	if(TempPressBigger>330)
	{

       VarTempCurrentTarget2=0;	
	}
	
	
	
		VarValveCurrentTarget=(UINT16)VarTempCurrentTarget2;
			
	
	//退出自动怠速延时上升
	if(VarCurrentIdleDelay)
	{
		VarValveCurrentTarget = 0;
	}
	//限值最大电流
	if(VarValveCurrentTarget>650)
	{
		VarValveCurrentTarget=650;
	}
	
	
	VarValvePwRatio = FunValveRatioComputePID(VarValveCurrentTarget,VarValveCurrentNow,26,100,0);
	LibSetPwmRatio(3,VarValvePwRatio);
	
		//......................DT3比例输出(液压冷却泵比例阀)..........................
	
	StructPwmDT3.PosLimit=50000;
	StructPwmDT3.NegLimit=0;
	StructPwmDT3.Kp=2.5;
	StructPwmDT3.Ki=2.5;
	StructPwmDT3.Kd=0;
	FunPID(VarHydraulicCoolingPumpValveCurrent,VarProHydraulicFANValveCurrentTarget,&StructPwmDT3,5,10,TRUE);
	//FunPID(VarHydraulicCoolingPumpValveCurrent,406,&StructPwmDT3,5,10,TRUE);//风扇噪声测试
	VarDt3PwRatio=(UINT16)(StructPwmDT3.Result);
	LibSetPwmRatio(1,VarDt3PwRatio);
}

/**************************************************************
**函数名：FunValveRatioComputePID()
**功能描述：比例阀的电流占空比PID计算:增量式PID
**传入参数：Current_Target-目标电流；
**输出参数：占空比
**************************************************************/
UINT16 FunValveRatioComputePID(UINT16 Current_Target,UINT16 Current_Now,UINT8 Kp,UINT8 Ki,UINT8 Kd)
{
	INT32 PID_Error;
	float PID_Kp,PID_Ki,PID_Kd;
	float D_u;
	PID_Kp = (float)Kp/(float)1;  PID_Ki = (float)Ki/(float)100;  PID_Kd = (float)Kd/(float)100;
	D_u = PID_Kp*x[0]+PID_Kd*x[1]+PID_Ki*x[2];
	D_Output=D_Last+D_u;
	//占空比输出限制
	if(D_Output>65535)
	{
		D_Output=65535;
	}
	if(D_Output<0)
	{
		D_Output=0;
	}
	PID_Error = (INT16)(Current_Target-Current_Now);
	D_Last = D_Output;
	x[0]=PID_Error-PID_Error_1;
	x[1]=PID_Error-2*PID_Error_1+PID_Error_2;
	x[2]=PID_Error;
	//PID_Error_2 = PID_Error_1;
	PID_Error_1 = PID_Error;
	return( (UINT16)D_Output );
}
/**************************************************************
**函数名：FunValveRatioComputePID_1()
**功能描述：比例阀的电流占空比PID计算:普通PID
**传入参数：Current_Target-目标电流；
**输出参数：占空比
**************************************************************/
UINT16 FunValveRatioComputePID_1(UINT16 Current_Target,UINT16 Current_Now,UINT8 Kp,UINT8 Ki,UINT8 Kd)
{
	INT16 PID_Error;
	float PID_Kp,PID_Ki,PID_Kd;
	PID_Kp = (float)Kp/(float)1;  PID_Ki = (float)Ki/(float)100;  PID_Kd = (float)Kd/(float)100;
	D_Output = PID_Kp*x[0]+PID_Kd*x[2]+PID_Ki*x[1];
	//占空比输出限制
	if(D_Output>65535)
	{
		D_Output=65535;
	}
	if(D_Output<0)
	{
		D_Output=0;
	}
	PID_Error = (INT16)(Current_Target-Current_Now);
	//设定死区为2mA
	if(LibAbsUint16(Current_Target,Current_Now)<2)
	{
		PID_Error = 0;
	}
	if((Current_Target<20)&&(Current_Now<20))//0~20mA电流检测不准,置偏差为0，避免偏差累加使响应速度降低
	{
		PID_Error = 0;	
	}
	x[0]=PID_Error;
	x[1]=PID_Error_1;
	x[2]=0;
	PID_Error_1 += PID_Error;
	//电流输出保护,不超过600mA
	if(Current_Now>600)
	{
		D_Output=0;
	}
	//	VarValveTargetLast = Current_Target;
	return( (UINT16)D_Output );
}

