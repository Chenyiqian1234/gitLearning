 #include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**函数名：FunPowerSaveControl()
**功能描述：动臂节能模式判断
**传入参数：无
**输出参数：
**************************************************************/
void FunPowerSaveControl(void)
{

	//动臂节能模式判别//传感器故障先不做控制
//	if(VarEngineSaveSensorFaultChangeModeFlag==1)
//	{
//		VarBoomWorkModeNow =8;
//	}
//	else
//	{
	VarBoomWorkModeNow = FunEnergySavingModeCheck();  	
//	}
	

	//动臂节能控制	
	switch(VarBoomWorkModeNow)
	{
		case 1:
			FunBoomEnergySavingMode_1();//动臂节能下降
			break;
		case 2:
			FunBoomEnergySavingMode_2();//节能大负载提臂
			break;

		case 3:
			FunBoomEnergySavingMode_3();//动臂节能上升
			break;

		case 5:
			FunBoomEnergySavingMode_5();//上升能量不足
			break;
		case 6:
			FunBoomEnergySavingMode_6();//中位模式
			break;
		case 7:
			FunBoomEnergySavingMode_7();//支车模式
			break;
		case 8:
			FunBoomEnergySavingMode_8();//动臂不节能模式
			break;
		case 9:
			FunBoomEnergySavingMode_9();//泄压模式
			break;
		default:
			FunBoomEnergySavingMode_8();//动臂不节能模式
			break;
	}
	//回转节能控制
	FunRatatorPowerSave();
	//标志量清零	
	if(VarBoomWorkModeNow!=1)
	{
		VarInMode1Flag=0;
	}
	
	//节能提臂判断档位
	if(VarDialGrade>=10)//10档
	{
		VarMode2InPutPress=320;//330
	}
	else if(VarDialGrade==9)
	{
		VarMode2InPutPress=315;//320
	}
	else
	{
		VarMode2InPutPress=305;//310
	}
	
	//*********定时器******************
	if(LibTimer(13,1,10,1))
	{
		//进入到动臂下降支车的计时器
		if((VarDiBoomDown)&&(VarBigSmallDifferentVale >= 50))
		{
			
			if(VarMode1KeepFlag10Ms<0xFFFF) VarMode1KeepFlag10Ms++;
		}
		else
		{
			VarMode1KeepFlag10Ms=0;
		}
		//进入到动臂上升后的计时器
		if((VarDiBoomUp) && (VarP2PressureFilter>=VarMode2InPutPress))//0111号330改为310，280；0118主泵压力改为大腔压力
		{
			if(VarInMode3Timer10Ms<0xFFFF) VarInMode3Timer10Ms++;
		}
		else
		{
			VarInMode3Timer10Ms=0;
		}
		
		
		//进入支车模式后的计时器
		if(VarBoomWorkModeNow==7)
		{
			if(VarInMode7Timer10Ms<0xFFFF) VarInMode7Timer10Ms++;
		}
		else
		{
			VarInMode7Timer10Ms=0;
		}

/*		//进入2模式后的计时器
		if(VarBoomWorkModeNow==2)
		{
			if(VarInMode2Timer10Ms<0xFFFF) VarInMode2Timer10Ms++;
		}
		else
		{
			VarInMode2Timer10Ms=0;
		}*/
		
		//进入3模式后的计时器

		
		//进入5模式后的计时器
		if(VarBoomWorkModeNow==5)
		{
			if(VarInMode5Timer10Ms<0xFFFF) VarInMode5Timer10Ms++;
		}
		else
		{
			VarInMode5Timer10Ms=0;
		}
		//动臂上升计时器
		if (VarPAiBoomUpPressure>=20)
		{
			if(VarBoomUpTimer10Ms<0xFFFF) VarBoomUpTimer10Ms++;
		}
		else
		{
			VarBoomUpTimer10Ms=0;
		}
		//中位模式计时器
		if ((!VarDiBoomUp) && (!VarDiBoomDown))
		{
			if(VarBoomUpDownTimer10Ms<0xFFFF) VarBoomUpDownTimer10Ms++;
		}
		else
		{
			VarBoomUpDownTimer10Ms=0;
		}
		
	/*	//中位模式支车状态判断计时器
		if(VarBoomBigPressureBar>VarBoomSmallPressureBar)
		{
			if ((!VarDiBoomUp) && (!VarDiBoomDown)&&((VarBoomBigPressureBar-VarBoomSmallPressureBar)>50))
			{
				if(VarBoomUpDownZhiCheModeTimer10Ms<0xFFFF) VarBoomUpDownZhiCheModeTimer10Ms++;
			}
			else
			{
				VarBoomUpDownZhiCheModeTimer10Ms=0;
			}
		}
		*/
		//进入8模式计时器
		
		if(VarBoomWorkModeNow==8)
		{
			if(VarInMode8Timer10Ms<0xFFFF) VarInMode8Timer10Ms++;
		}
		else
		{
			VarInMode8Timer10Ms=0;
		}
		//动臂上提，大腔压力大于150bar计时器
		if(VarBoomBigPressureBar>150)
		{
			if(VarBoomBigPressureBarTimer10Ms<0xFFFF) VarBoomBigPressureBarTimer10Ms++;
		}
		else
		{
			VarBoomBigPressureBarTimer10Ms=0;
		}
		
	
	}

}
/**************************************************************
**函数名：FunPowerSaveControl()
**功能描述：动臂节能模式判断
**传入参数：无
**输出参数：
**************************************************************/
UINT8 FunEnergySavingModeCheck()
{
	UINT8 ArmMode;
	VarBigSmallDifferentVale=(INT16)(VarBoomSmallPressureBar - VarBoomBigPressureBar);//计算动臂大小腔压力差值
	
	

	
	
	//*******泄压模式判别，9模式*******
	if(VarXieYaFlag)
	{
		//return(9);
		ArmMode=9;
	}
	else
	{
		if(VarBoomPowerSaveFlag)//动臂节能ON
		{
			if(VarDiBoomUp)//动臂上升
			{
				//刚启机或者怠速超过1min执行第一次提臂不节能
				if(VarRestarForEnginerFlag==1 )//系统重启
				{
					
					
					VarInModeBoomUpFirstFlag=1;//进入第一次提臂不节能标志
					if(VarInModeBoomUpFirstBackFlag==1)//退出第一次提臂不节能标志
					{
					VarRestarForEnginerFlag=0;
					VarInModeBoomUpFirstBackFlag=0;
					}
					
					ArmMode=8;
					if(VarBoomBigPressureBar>150)
					{
						
						VarZhiCheJudgeTimerFlag=0;//退出支车模式
					}
					
				}
				else
				{   
			       
					//解决支车后抬臂异响，节能提臂判断大腔压力小于50bar则是不节能抬臂，直到手柄回中位或大腔压力大于150bar
					if((VarBoomBigPressureBar <= 50)||(VarAfterMode7Flag==1)) //动臂小腔减去大腔压力
					{
						ArmMode=8;
						VarAfterMode7Flag=1;
					//	if(VarBoomBigPressureBarTimer10Ms > 10)
						if(VarBoomBigPressureBar>150)
						{
							VarAfterMode7Flag=0;
							VarZhiCheJudgeTimerFlag=0;//退出支车模式
						}
						
					}
					else
					{
					//主泵压力大于300bar并且持续300ms切到5模式，1月11号改为330bar，200ms
						if(((VarPAccumPressureFilter>195) || (VarBoomSaveEngineUpInFlag==1) ) && (VarUpLowEngineFlag==0) )//蓄能器气压VarPAccumAirPressureBar
						{
							VarBoomSaveEngineUpInFlag=1;
							if(VarPAccumPressureFilter<190)//1月12日,160,165改为180,185
							{
								VarBoomSaveEngineUpInFlag=0;
							}
							if((VarInMode3Timer10Ms>=50)||(VarArmMode2Flag==1))
							{
								ArmMode=8;//动臂节能大负载上升
								VarArmMode2Flag=1;
							/*	if(TempPressBigger<=260)
								{
									VarArmMode2Flag=0;
								}
						*/
							}
							else
							{
								ArmMode=3;//3-动臂节能上升
							}
							
						}
						else
						{
							ArmMode=5;//5-上升能量不足
							VarUpLowEngineFlag=1;
						}
		
					}
				}
			}
			
			if(VarDiBoomDown)//动臂下降
			{
				   //判断刚启机或者怠速超过1min执行第一次提臂不节能，当动臂下降时退出不节能模式，恢复正常节能模式判断
				//if(VarInModeBoomUpFirstFlag==1)
				if((VarInModeBoomUpFirstFlag==1)&&(VarPAccumPressureFilter>210))	
				{
						VarInModeBoomUpFirstFlag=0;
						VarInModeBoomUpFirstBackFlag=1;
					}
				
				

		//删除，原因：过多DT切换		//解决支车后下臂异响，节能下臂判断大腔压力小于50bar则是不节能下臂，直到手柄回中位或大腔压力大于150bar
		//		if((VarBoomBigPressureBar <= 50)||(VarAfterMode7BoomDownFlag==1)) //动臂大腔压力
		//		{
		//			ArmMode=8;
		//			VarAfterMode7BoomDownFlag=1;
		//			if(VarBoomBigPressureBar >= 150)
		//			{
		//				VarAfterMode7BoomDownFlag=0;
		//			}
					
		//		}
		//		else
		//		{
					//动臂下降检测蓄能器油压的初始压力，油压初始压力小于205,3月26日改为215bar才能进入动臂节能下降模式
						if((VarPAccumPressureFilter<215) || (VarBoomDowmFirstPAccumPressureFlag==1))
						{
							VarBoomDowmFirstPAccumPressureFlag=1;//动臂下降第一次检测初始蓄能器油压标志位

							//
							if((VarMode1KeepFlag10Ms>100)||(VarZhiCheJudgeTimerFlag==1))
							{
						
								ArmMode=7;//7-支车模式
								VarZhiCheJudgeTimerFlag=1;
							
					
							}
							else
							{
								ArmMode=1;//1-动臂节能下降
							}
							
						}
						else
						{
							//return(8);//动臂不节能模式
							ArmMode=8;
						}
		//		}
				
	
				
				
			}
					
			if(!VarDiBoomUp &&!VarDiBoomDown)
			{	
				ArmMode=6;//6-中位模式
				VarUpLowEngineFlag=0;//
				
			}
			
		
		}
		else
		{
			//if(!VarDiBoomUp &&!VarDiBoomDown)
			//{	
		//	    ArmMode=6;//6-中位模式
		//	}
		//	else
		//	{
			//	return(8);//动臂不节能模式
				ArmMode=8;
		//	}
			
		}
	}
	
	
	return(ArmMode);
	
}
/**************************************************************
**函数名：FunBoomEnergySavingMode_1()
**功能描述：动臂节能模式
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_1(void)  //
{
	
   //判断是否进入1模式
	VarBoomEnergyMode1Flag=1;
		VarDoDT1=0;
		VarDoDT2=1;
		VarDoDT8=1;
    //临时调试控制DT8输出
//    VarDT8PwmCurrentTarget=0;//2020年11月24日修改，由270改为0

}

/**************************************************************
**函数名：FunBoomEnergySavingMode_2()
**功能描述：节能大负载提臂
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_2(void)  //
{
	
   
		VarDoDT1=1;
		VarDoDT2=1;
		VarDoDT8=1;
		VarDoDT7=1;//1.20合流，将1.18注释去掉

   
}

/**************************************************************
**函数名：FunBoomEnergySavingMode_3()
**功能描述：动臂节能模式
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_3(void)  //动臂节能上升
{
	VarDoDT1=0;//
	VarDoDT2=1;//
	VarDoDT8=1;
	if((VarP2PressureFilter>=290)||(VarSaveEngineDT7Flag==1))//280
	{
		VarDoDT7=1;
		VarSaveEngineDT7Flag=1;
		if(VarP2PressureFilter<250)
		{
			VarSaveEngineDT7Flag=0;
		}
		
	}
	else
	{
		VarDoDT7=0;
	}
	//VarDoDT7=1;// 2020/7/10 从0改到1


	
	VarLowEnginePressureFlag=0;
}

/**************************************************************
**函数名：FunBoomEnergySavingMode_5()
**功能描述：动臂节能模式
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_5(void)  //上升能量不足
{

	VarDoDT7=1; //双泵合流DT7=1
	
	 VarDoDT1=1;
	if(VarInMode5Timer10Ms>10)
	{
		VarDoDT2=0;
		VarDoDT8=0;

    }
	 

	VarLowEnginePressureFlag=0;
}
/**************************************************************
**函数名：FunBoomEnergySavingMode_6()
**功能描述：动臂节能模式
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_6(void)  //中位模式
{
//	VarAfterMode7Flag=0;
	VarBoomEnergyMode1Flag=0;
	VarSaveEngineDT7Flag=0;
	
	//节能模式，如果手柄中位持续2S以上，DT1、DT2关闭防止节能掉臂，(2021.01.13是否将2s后关闭电磁阀改为立即关闭——中位掉臂、再次提臂掉臂?)
	if(VarDoDT1==1)
	{
		if(VarBoomUpDownTimer10Ms>=1)
		{
			VarDoDT1=0;
			VarDoDT2=0;
			VarDoDT8=0;
		}
	
	}
	else
	{
		if(VarBoomUpDownTimer10Ms>=200)
		{
			VarDoDT1=0;
			VarDoDT2=0;
			VarDoDT8=0;
		}
	}

	
	
	VarDoDT7=0;

	
	VarDT8PwmCurrentTarget=0;
	VarLowEnginePressureFlag=0;
	VarMode1ChangeFlag=0;
//	if(VarBoomUpDownZhiCheModeTimer10Ms>50)
//	{
//		VarZhiCheJudgeTimerFlag=0;
//	}
	
	VarBoomUpTimerFlag=0;
	
	VarBoomDowmFirstPAccumPressureFlag=0;//动臂下降第一次检测初始蓄能器油压标志位
	
	VarArmMode2Flag=0;
}
/**************************************************************
**函数名：FunBoomEnergySavingMode_7()
**功能描述：动臂节能模式
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_7(void)  //支车模式
{

	VarDoDT2=0;
	VarDoDT8=0;
	if(VarInMode7Timer10Ms>=40)//25
	{
	VarDoDT1=1;
	}
	
	
	
	VarDoDT7=0;
	VarDT8PwmCurrentTarget=0;
	

	VarLowEnginePressureFlag=0;
}
/**************************************************************
**函数名：FunBoomEnergySavingMode_8()
**功能描述：动臂节能模式
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_8(void)  //动臂不节能模式
{
	//不节能模式，如果手柄中位持续1S以上，DT1关闭，否则DT1
	
	      if((!VarBoomUpPressureSensorEorror) && (!VarBoomDownPressureSensorEorror) )//动臂上升先导和动臂下降先导传感器故障时
	      {
				if(VarBoomUpDownTimer10Ms>=1)
				{
						VarDoDT1=0;
				}
				else
				{
					  VarDoDT1=1;
				}
	      }
	      else
	      {
	    	  VarDoDT1=1;
	      }
		

	

	  	if(VarInMode8Timer10Ms>=10)
	  	{
	     VarDoDT2=0;
	     VarDoDT8=0;
	  	}
	     VarDoDT7=1;


	VarLowEnginePressureFlag=0;
	
	
}
/**************************************************************
**函数名：FunBoomEnergySavingMode_9()
**功能描述：泄压模式
**传入参数：无
**输出参数：
**************************************************************/
void FunBoomEnergySavingMode_9(void)   //泄压模式
{
	VarDoDT1=1;
	VarDoDT2=1;
	VarDoDT8=1;
	VarLowEnginePressureFlag=0;
}
/**************************************************************
**函数名：FunRatatorPowerSave()
**功能描述：回转节能模式
**传入参数：无
**输出参数：
**************************************************************/
void FunRatatorPowerSave(void)
{
	
	if((VarRatatorPowerSaveFlag)&&(!VarDiTreadPre)&&(VarPBucCapPressure<=280)&&(VarPBucketArmRodPressure<=280)&&(VarPBucketArmPressure<=280))//1）回转节能开关状态为ON，2）行走压力开关 OFF，3）,4)(铲斗大腔或斗杆小腔或斗杆大腔小于280bar)
	{
		VarDoDT6=0;//DT6失电打开
	}
	else
	{
		VarDoDT6=1;//DT6得电关闭
	}
	
}

/**************************************************************
**函数名：FunPowerSaveSpeedControl()
**功能描述：节能发动机转速控制
**传入参数：无
**输出参数：
**************************************************************/
void FunPowerSaveSpeedControl(void)
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
		
	  	
	if(VarBoomEnergyMode1Flag==1) //动臂下降转速单独控制，1.13去掉注释符再次启用——下臂慢
	{
	
		if((VarBoomSmallPressureBar>100)&&(VarBoomSmallPressureBar>VarBoomBigPressureBar))
		{
			VarCanEngineLevelSpeed=VarEngineLevelSpeed[VarSpeedLevel];
			
		}
		else
		{
			if(VarBoomDownPressureFilter<=10)
			{
				VarCanEngineLevelSpeed=VarEngineLevelSpeed[VarSpeedLevel];
			}
			else if((VarBoomDownPressureFilter>10)&&(VarBoomDownPressureFilter<=20))
			{
				VarCanEngineLevelSpeed=(VarEngineLevelSpeed[VarSpeedLevel]+((VarBoomDownPressureFilter-10)*10));					
			}
			else
			{
				VarCanEngineLevelSpeed=(VarEngineLevelSpeed[VarSpeedLevel]+100);
			}
		}
		
	}
	   else
	   {
	  	
 
 
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
}
/**************************************************************
**函数名：FunPowerSavePumpCurrentControl()
**功能描述：节能主泵电流控制
**传入参数：无
**输出参数：
**************************************************************/

void FunPowerSavePumpCurrentControl(void)
{
	UINT8 i,VarBool;
		UINT16 speed_key=100;
		UINT32 Temp_Ulong;
		UINT16	speed_key1;
		UINT16	speed_key2;
		//赋值，设置各档位初始电流值
		VarValveCurrent[0] = 0;
		VarValveCurrent[1] = 0;
		VarValveCurrent[2] = 0;
		VarValveCurrent[3] = 450;
		VarValveCurrent[4] = 520;
		VarValveCurrent[5] = 650;//550;
		VarValveCurrent[6] = 650;//580;
		VarValveCurrent[7] = 650;//600;
		VarValveCurrent[8] = 650;//620;
		VarValveCurrent[9] = 650;//620;
		VarValveCurrent[10] =650;// 620;
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
					if((TempPressBigger<60)&&(VarDiTravelHighSpeed<=0))
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

					//	VarTempCurrentTarget2=200;
					if(VarBoomWorkModeNow==3)
					{
						VarTempCurrentTarget2=650;
					}
					else
					{
						VarTempCurrentTarget2=200;
					}
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
			if(VarPAiBoomUpPressure>5)
			{
				VarTempCurrentTarget2=330;//1.21由0改为
			}
			else
			{
				VarTempCurrentTarget2=0;	
			}
		}
			
			VarValveCurrentTarget=(UINT16)VarTempCurrentTarget2;
						
		//退出自动怠速延时上升
		if(VarCurrentIdleDelay)
		{
			VarValveCurrentTarget = 0;
		}
		
		if((VarBoomEnergyMode1Flag==1)&&(TempPressBigger<180))//动臂节能下降1模式电流 控制
		 {
			 
			// VarValveCurrentTarget=VarValveCurrent[VarCurrentLevel];//动臂节能下降电流为该挡位的基准电流
			VarValveCurrentTarget=650;
		 }
		//限值最大电流
		if(VarValveCurrentTarget>680)
		{
			VarValveCurrentTarget=680;
		}
		
	/*	if((VarBoomEnergyMode1Flag==1)&&(TempPressBigger<60))//动臂节能下降1模式电流 控制
		 {
			 
			 VarValveCurrentTarget=VarValveCurrent[VarCurrentLevel];//动臂节能下降电流为该挡位的基准电流
		 }
		*/

		
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
