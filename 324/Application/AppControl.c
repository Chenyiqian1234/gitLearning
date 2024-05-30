#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**��������FunSysSleep()
**����������ϵͳ����
**�����������
**�����������
**************************************************************/
void FunSysSleep(void)
{
	UINT32 Ulong_Temp,Ulong_Temp2,Ulong_Temp3;
	BOOL VarBool1,VarBool2,VarBool3;
	VarBool1 = LibTimerTon(7,!VarSysPowerOn,30,&Ulong_Temp2);
	VarBool2 = LibTimerTon(3,!VarSysPowerOn,5000,&Ulong_Temp);//5S
	VarBool3 = LibTimerTon(13,!VarSysPowerOn,120000,&Ulong_Temp3);
	//����ѹ���ͳ���40S,�ط�����,��ʮ�巢������Ч
	if(VarEngineWorkErrorTime1S>40)
	{
		VarEngineNeedStopFlag =1;
	}
	else
	{
    	VarEngineNeedStopFlag =0;	
	}
	//Կ�׿��عر�
	if(VarBool1)
	{
		//Կ�׿��عرպ󣬽��ܲ��ַ����㣬��ֹ���ۡ�
		VarDoDT7=0;
		VarDoDT1=0;
		VarDoDT2=0;
		VarDoDT8=0;
		//�ر�DO,H_Bridge,PWM,+5V,+12V...
		LibSetValueDOH(11,0);	//pin46
		LibSetValueDOH(4,0);	//pin35
		LibSetValueDOH(13,0);	//pin48
		//���ŵ�����С
		VarCanEngineLevelSpeed=VarEngineLevelSpeed[0];
		
		//������Կ�׿��عرպ�DT5�õ�2������ʧ��
		VarDoDT5=1;//pin73 ����VarDoDT5
		
		
		//��Դ�̵�����ʱ5S�رգ�֮��ϵͳ����
		if( VarBool2 && (VarEngineSpeedNow<400) )
		{
			
			
			LibSetValueDOH(7,0);	//pin42,�ر�ϵͳ��Դ
			LibSystem5vOutput(1);	//������+5V����ر�
			LibSetPwmRatio(1,0);	//PWM����ر�
			//����GPS����
			VarFlashGpsDataMasterNeedSaveFlag=1;
			VarFlashGpsDataBackupNeedSaveFlag=1;
			if(VarEngineStarted>0)//������������
			{
				//����Сʱ������
				VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
				VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
				VarFlashHourNeedSaveMainFlag=1;
				VarEngineStarted = 0;
			}
			FunFlashWriteData();//���ݱ���
			//�жϿ���
			LibIrqaEnable();
			LibIrqaEnable();
			LibMcuLedOutput(1);
			//�ٴ��ж�Կ�׿��ص�ƽ�ź�
			if(LibGetValueDIH(2))
			{
			    LibSystemDelay1MS(5);
				if(LibGetValueDIH(2))
				{
					
					//����
					LibSystemRestart();
				}
			}
		
		}
		
		if( VarBool3 && (VarEngineSpeedNow<400) )
		{
			LibSetValueDOH(0,0);	//pin31DT5��
	//	VarDoDT5=0;//pin73 ����VarDoDT5
		//�жϿ���
		LibIrqaEnable();
		LibIrqaEnable();
		LibMcuLedOutput(1);
		//�ٴ��ж�Կ�׿��ص�ƽ�ź�
		if(LibGetValueDIH(2))
		{
		    LibSystemDelay1MS(5);
			if(LibGetValueDIH(2))
			{
				
				//����
				LibSystemRestart();
			}
		}
		LibSystemSleep();
		
		}
		
	}
	else	
	{
		VarDoDT5=0;//pin73 ����VarDoDT5
	}
}
/**************************************************************
**��������AutoIdle()
**�����������Զ�����
**�����������
**�����������
**************************************************************/
void FunAutoIdle(void)

{
	//���뵡���Լ����ٿ�����
	if((VarCanAutoIdleEnable) //  //�Զ�����ʹ��
		&&(LibTimerGet1S()>4)  //�ѹ�������ǰ����
		&&(VarAiPilotSwitch==0) //��ʻԱ�޲������ȵ�ѹ������Ϊ0
		&&(VarEngineSpeedNow>300)&&(!VarDiTravelHighSpeed)) //������������,����ѹ�����ع�
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
			else if(LibTimerGet1MS()-VarIdleTimer>=1200) // 1200//��ʼ���뵡�ٿ���״̬
			{
				VarIdleState=1;
				VarCurrentIdleDelay=TRUE;
			}
		}
	}
	//�˳�����
	else if(VarstartIdle==TRUE) 
	{
		VarstartIdle=FALSE;
		VarIdleState=0;
		VarIdleTimer=LibTimerGet1MS();
	}
	//��ʱ��������
	else
	{
		if(LibTimerGet1MS()-VarIdleTimer>=2800)
			VarCurrentIdleDelay=FALSE;
	}
	
	
	//***************���ֱ���ťһ������***********************
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
**��������FunTemperatureCotrol()
**������������������ȴˮ�¹�������߿���
**�����������
**�����������
**************************************************************/
void FunTemperatureCotrol(void)
{
	//����ů��״̬
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
	//ů������ʱ�����
	if(VarEngineWarmState&&((LibTimerGet1S()-VarEngineWarmStartTime)>15))
	{
		VarEngineWarmState=FALSE;
	}
	//������ȴ����״̬
	if( (VarCanEngineWaterTemp>102)&&(VarEngineSpeedNow>1500) )
	{
		VarEngineCoolState=TRUE;
	}
	//�˳���ȴ����
	if(VarCanEngineWaterTemp<100)
	{
		VarEngineCoolState=FALSE;
	}
}
/**************************************************************
**��������FunTravelSpeed()
**�������������߸ߵ��ٿ���
**�����������
**�����������
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
**��������FunSecondPressure()
**����������������ѹ����
**�����������
**�����������
**************************************************************/
void FunSecondPressure(void)
{
	//������ѹ���,S/Hģʽ�����
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
	//���߸���ʱ��ȡ���Զ���ѹ����
/*	if(VarDiTravelHighSpeed>0)
	{
		VarDoSecondPressure = 0;
	}
	*/
}

/**************************************************************
**��������FunBuzzerAlarm()
**������������������������
**�����������
**�����������
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
**��������FunFuelAirFitlerControl()
**�������������������ȼ�͹��˿���
**�����������
**�����������
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
**��������FunSwitchValveControl()
**�������������ط�����
**�����������
**�����������
**************************************************************/
void FunSwitchValveControl(void)
{
//	UINT32 Temp1_ET;
//	UINT32 Temp2_ET;
//	//��θߵ��ٿ��ط�����
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
//	//ϴ�ӿ��ط�����
//	if(VarWaterSprayButton)
//	{
//		VarDoWaterSpray=1;
//	}
//	else
//	{
//		VarDoWaterSpray=0;
//	}
//	
//	//�ƾ߿��ؿ���
//	if(VarCautionLampButton)//��ʾ��
//	{
//		VarDoCautionLamp=1;
//	}
//	else
//	{
//		VarDoCautionLamp=0;
//	}
//	
//	if(VarCabinLamptButton)//��ʻ�Ҷ���
//	{
//		VarDoCabinLamp=1;
//	}
//	else
//	{
//		VarDoCabinLamp=0;
//	}
//	
//	if(VarWorkLampButton)//������
//	{
//		VarDoWorkLamp=1;
//	}
//	else
//	{
//		VarDoWorkLamp=0;
//	}
	
	//�ֶ������������ص�ŷ�����
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
**��������FunSpeedControl()
**����������������ת�ٿ���
**�����������
**�����������
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
		VarSpeedLevel=VarDialGrade;    // ���̷�Χ��1-10
		//ת����VarSpeedLevel:0-9
		if(VarSpeedLevel>0)
		{
			VarSpeedLevel -= 1;
		}
		if(VarSpeedLevel>9)
		{
			VarSpeedLevel = 9; 
		}
	  	//�ж��Ƿ��ڷ���������ǰ5�룬���ڳ�����״̬��IN_START_STATEΪTRUE
	  	if(LibTimerGet1S()>=5)
		{
			VarEngineStartState=FALSE;
		}
		else
		{
			VarEngineStartState=TRUE;	
		}
		//���ڳ�����״̬��GPS��ת�٣��ٶȵ�λΪ0
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
			  	
	  			
	  			
			  	//ů������
			  	if(VarEngineWarmState) 
			  	{
			  		VarSpeedLevel=1;
			  	}
			  	//��������
			  	else if(VarEngineCoolState) 
			  	{
			  	    if(VarSpeedLevel>2)
			  	    {
			  	    	VarSpeedLevel=2;
			  	    }
			  	}
			  	//���ֱ�һ����������
			  	else if(VarButtonLowSpeedEnable)
			  	{
			  		VarSpeedLevel =0;
			  	}
			  	//Һѹ�͸���ʱ��2���ӡ�Һѹ���´������쳣����
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
	  	
	  	
	    if(VarCanPumpMode)//ת�����������öת��
	    {
		    VarCanEngineLevelSpeed=1680;
	    }
	  	else if(VarCanEngineMode)//ת���������������ת��
	    {
		    VarCanEngineLevelSpeed=1850;
	    } 
	  	else
	  	{
	  	  	VarCanEngineLevelSpeed=VarEngineLevelSpeed[VarSpeedLevel];
	  	}
  
}
/**************************************************************
**��������FunAssistantSet()
**������������������
**�����������
**�����������
**************************************************************/
void FunAssistantSet(void)
{
	//�Ǹ���ģʽ���˳�
	if(VarCanSysHSLBKRMode<8)
	{
		VarDoValveBreakPilot=0;
		VarDoValvePressRegulate=0;
		VarProValveCurrentTarget=0;
		return;
	}
	//B-������ģʽ��Һѹ���鴸����
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
	//K-Һѹ��ģʽ,Һѹ������
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
	//R-Һѹ��ģʽ��Һѹ������
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
	//����PID����ʵ�ַ������ıջ�����
	//���޸�����֤
	//VarAssValvePwRatio = FunValveRatioComputePID(VarProValveCurrentTarget,VarAssValveCurrentNow,26,100,0);
	LibSetPwmRatio(11,0);
}






/**************************************************************
**��������FunHydraulicCoolingPumpCurrent()
**����������Һѹ��ȴ�ñ���������
**�����������
**�����������
**************************************************************/

void FunHydraulicCoolingPumpCurrent(void)
{ 	UINT8 Trigger;
	UINT32 Temp_ET;
	UINT8 Var_Enable1;
	UINT8 Var_Enable2;
	UINT8 Var_Enable3;
	UINT8 Var_Enable4;
	UINT8 N;
	
	//��ֵ�����ø���λ���ȵ�������ֵ
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
		  if((VarHydraulicOilTempFilter>=95)&&(VarProHydraulicFANValveCurrentTarget<=150))//Һѹ�͸��³���ʱ�����
		  {
				VarHydraulicOilTempCount++;
		  }
		  else
		  {
				VarHydraulicOilTempCount=0;    
		  }        
	 }
	
	 if(VarHydraulicOilTempSensorError==1)//Һѹ���´��������ϱ���ʱ������ת�����
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
					
					if(VarHydraulicFanBool)//�����תʱ�䳬��4.5�������÷����ȼ��ٺ�ͣ����
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
**��������FunPumpCurrent()
**����������Һѹ�ù��ʿ���
**�����������
**�����������
**************************************************************/
void FunPumpCurrent(void)
{

	UINT8 i,VarBool;
	UINT16 speed_key=100;
	UINT32 Temp_Ulong;
	UINT16	speed_key1;
	UINT16	speed_key2;
	//��ֵ�����ø���λ��ʼ����ֵ
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
	//��ԭģʽʱ,����8����������Ϊ��׼ֵ��90%
	if(VarCanHighlandMode>0)
	{
		for(i=3;i<11;i++)
		{
		  VarValveCurrent[i] = (UINT16)((VarValveCurrent[i]*9)/10);	
		}
	}
	//������ʾ�����õĹ��ʵ�ֵ�Ե�������,�����õĹ��ʵ�1-8��Ӧ�����ڵĵ�λ3-11
	//VarPumpPowerParameter[i]=5��Ӧ������׼ֵ,С��5ʱ1-2%;����5ʱ1-1%;
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

	//GPS���ù���,Ŀ�����Ϊ1��	
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
		//����ѹ���������λĿ�����ֵ				
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
			//ȡ��ʻԱ�趨��λ:0~9
			VarCurrentLevel = VarSpeedLevel;
			//AutoIdle
			if((VarIdleState==1)&&(VarSpeedLevel>=2))
			{
				VarCurrentLevel -= 2;
			}
			else if((VarIdleState==2)&&(VarSpeedLevel>=2))//Ϊʲô��ҪspeedLevel>=2 ???
			{
				VarCurrentLevel = 0;	
			}
			//����Ŀ�����




	TempPressBigger = LibMaxUint16(VarP1PressureFilter,VarP2PressureFilter);

			if(LibTimer(9,1,10,1))
			{
				if((TempPressBigger<60)&&(VarDiTravelHighSpeed<=0))//��ʻԱ�޲�����
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
					VarTempCurrentTarget2 = 0;//��ʼ����ʱ����Ϊ0
					VarSpeedLowTimer10Ms=0;
					
				}
		
				else if(VarLoadHeavyStateTimer10Ms>5)
				{

					VarTempCurrentTarget2=200;	
				}
				
				else
				{
				
				
					speed_key1=(UINT16)(VarCanEngineLevelSpeed-VarCanEngineLevelSpeed*10/100);	//10%�ĵ�����
					speed_key2=(UINT16)(VarCanEngineLevelSpeed-VarCanEngineLevelSpeed*8/100);	//8%�ĵ�����

					if(LibTimer(10,1,10,1))
					{
						if(VarEngineSpeedNow>=speed_key2)//����С��8%
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
						VarCurrentAddValue=2.5;				//ѹ��>4MPa��������2�Ĳ�������

					}
					VarCurrentReduceValue=0;//��ʼ��Ϊ0
					
					if(VarEngineSpeedNow<=speed_key1)//���ٳ���10%
					{
						VarCurrentAddValue = 0;//ת�ٵ��ٳ���10%ʱ���������ֲ��䲻������
						if(VarTempCurrentTarget2 > VarTempCureentTargetValue*8/10)
						{
							VarCurrentReduceValue=5;//ת�ٵ��ٳ���10%�ҵ������ڻ�׼������80%ʱ��������5�Ĳ�������
						}
						
					}				
					else if(VarEngineSpeedNow<=speed_key2)//���ٳ���8%С��10%
					{
						   if(VarTempCurrentTarget2 < VarTempCureentTargetValue*10/10)
							{
								VarCurrentAddValue=1;
							}
						
					}
					
					else if(VarSpeedLowTimer10Ms>50)//����<8%������ʱ�䳬��500ms
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
			
	
	//�˳��Զ�������ʱ����
	if(VarCurrentIdleDelay)
	{
		VarValveCurrentTarget = 0;
	}
	//��ֵ������
	if(VarValveCurrentTarget>650)
	{
		VarValveCurrentTarget=650;
	}
	
	
	VarValvePwRatio = FunValveRatioComputePID(VarValveCurrentTarget,VarValveCurrentNow,26,100,0);
	LibSetPwmRatio(3,VarValvePwRatio);
	
		//......................DT3�������(Һѹ��ȴ�ñ�����)..........................
	
	StructPwmDT3.PosLimit=50000;
	StructPwmDT3.NegLimit=0;
	StructPwmDT3.Kp=2.5;
	StructPwmDT3.Ki=2.5;
	StructPwmDT3.Kd=0;
	FunPID(VarHydraulicCoolingPumpValveCurrent,VarProHydraulicFANValveCurrentTarget,&StructPwmDT3,5,10,TRUE);
	//FunPID(VarHydraulicCoolingPumpValveCurrent,406,&StructPwmDT3,5,10,TRUE);//������������
	VarDt3PwRatio=(UINT16)(StructPwmDT3.Result);
	LibSetPwmRatio(1,VarDt3PwRatio);
}

/**************************************************************
**��������FunValveRatioComputePID()
**�����������������ĵ���ռ�ձ�PID����:����ʽPID
**���������Current_Target-Ŀ�������
**���������ռ�ձ�
**************************************************************/
UINT16 FunValveRatioComputePID(UINT16 Current_Target,UINT16 Current_Now,UINT8 Kp,UINT8 Ki,UINT8 Kd)
{
	INT32 PID_Error;
	float PID_Kp,PID_Ki,PID_Kd;
	float D_u;
	PID_Kp = (float)Kp/(float)1;  PID_Ki = (float)Ki/(float)100;  PID_Kd = (float)Kd/(float)100;
	D_u = PID_Kp*x[0]+PID_Kd*x[1]+PID_Ki*x[2];
	D_Output=D_Last+D_u;
	//ռ�ձ��������
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
**��������FunValveRatioComputePID_1()
**�����������������ĵ���ռ�ձ�PID����:��ͨPID
**���������Current_Target-Ŀ�������
**���������ռ�ձ�
**************************************************************/
UINT16 FunValveRatioComputePID_1(UINT16 Current_Target,UINT16 Current_Now,UINT8 Kp,UINT8 Ki,UINT8 Kd)
{
	INT16 PID_Error;
	float PID_Kp,PID_Ki,PID_Kd;
	PID_Kp = (float)Kp/(float)1;  PID_Ki = (float)Ki/(float)100;  PID_Kd = (float)Kd/(float)100;
	D_Output = PID_Kp*x[0]+PID_Kd*x[2]+PID_Ki*x[1];
	//ռ�ձ��������
	if(D_Output>65535)
	{
		D_Output=65535;
	}
	if(D_Output<0)
	{
		D_Output=0;
	}
	PID_Error = (INT16)(Current_Target-Current_Now);
	//�趨����Ϊ2mA
	if(LibAbsUint16(Current_Target,Current_Now)<2)
	{
		PID_Error = 0;
	}
	if((Current_Target<20)&&(Current_Now<20))//0~20mA������ⲻ׼,��ƫ��Ϊ0������ƫ���ۼ�ʹ��Ӧ�ٶȽ���
	{
		PID_Error = 0;	
	}
	x[0]=PID_Error;
	x[1]=PID_Error_1;
	x[2]=0;
	PID_Error_1 += PID_Error;
	//�����������,������600mA
	if(Current_Now>600)
	{
		D_Output=0;
	}
	//	VarValveTargetLast = Current_Target;
	return( (UINT16)D_Output );
}

