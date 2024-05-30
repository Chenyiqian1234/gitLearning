 #include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**��������FunPowerSaveControl()
**�������������۽���ģʽ�ж�
**�����������
**���������
**************************************************************/
void FunPowerSaveControl(void)
{

	//���۽���ģʽ�б�//�����������Ȳ�������
//	if(VarEngineSaveSensorFaultChangeModeFlag==1)
//	{
//		VarBoomWorkModeNow =8;
//	}
//	else
//	{
	VarBoomWorkModeNow = FunEnergySavingModeCheck();  	
//	}
	

	//���۽��ܿ���	
	switch(VarBoomWorkModeNow)
	{
		case 1:
			FunBoomEnergySavingMode_1();//���۽����½�
			break;
		case 2:
			FunBoomEnergySavingMode_2();//���ܴ������
			break;

		case 3:
			FunBoomEnergySavingMode_3();//���۽�������
			break;

		case 5:
			FunBoomEnergySavingMode_5();//������������
			break;
		case 6:
			FunBoomEnergySavingMode_6();//��λģʽ
			break;
		case 7:
			FunBoomEnergySavingMode_7();//֧��ģʽ
			break;
		case 8:
			FunBoomEnergySavingMode_8();//���۲�����ģʽ
			break;
		case 9:
			FunBoomEnergySavingMode_9();//йѹģʽ
			break;
		default:
			FunBoomEnergySavingMode_8();//���۲�����ģʽ
			break;
	}
	//��ת���ܿ���
	FunRatatorPowerSave();
	//��־������	
	if(VarBoomWorkModeNow!=1)
	{
		VarInMode1Flag=0;
	}
	
	//��������жϵ�λ
	if(VarDialGrade>=10)//10��
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
	
	//*********��ʱ��******************
	if(LibTimer(13,1,10,1))
	{
		//���뵽�����½�֧���ļ�ʱ��
		if((VarDiBoomDown)&&(VarBigSmallDifferentVale >= 50))
		{
			
			if(VarMode1KeepFlag10Ms<0xFFFF) VarMode1KeepFlag10Ms++;
		}
		else
		{
			VarMode1KeepFlag10Ms=0;
		}
		//���뵽����������ļ�ʱ��
		if((VarDiBoomUp) && (VarP2PressureFilter>=VarMode2InPutPress))//0111��330��Ϊ310��280��0118����ѹ����Ϊ��ǻѹ��
		{
			if(VarInMode3Timer10Ms<0xFFFF) VarInMode3Timer10Ms++;
		}
		else
		{
			VarInMode3Timer10Ms=0;
		}
		
		
		//����֧��ģʽ��ļ�ʱ��
		if(VarBoomWorkModeNow==7)
		{
			if(VarInMode7Timer10Ms<0xFFFF) VarInMode7Timer10Ms++;
		}
		else
		{
			VarInMode7Timer10Ms=0;
		}

/*		//����2ģʽ��ļ�ʱ��
		if(VarBoomWorkModeNow==2)
		{
			if(VarInMode2Timer10Ms<0xFFFF) VarInMode2Timer10Ms++;
		}
		else
		{
			VarInMode2Timer10Ms=0;
		}*/
		
		//����3ģʽ��ļ�ʱ��

		
		//����5ģʽ��ļ�ʱ��
		if(VarBoomWorkModeNow==5)
		{
			if(VarInMode5Timer10Ms<0xFFFF) VarInMode5Timer10Ms++;
		}
		else
		{
			VarInMode5Timer10Ms=0;
		}
		//����������ʱ��
		if (VarPAiBoomUpPressure>=20)
		{
			if(VarBoomUpTimer10Ms<0xFFFF) VarBoomUpTimer10Ms++;
		}
		else
		{
			VarBoomUpTimer10Ms=0;
		}
		//��λģʽ��ʱ��
		if ((!VarDiBoomUp) && (!VarDiBoomDown))
		{
			if(VarBoomUpDownTimer10Ms<0xFFFF) VarBoomUpDownTimer10Ms++;
		}
		else
		{
			VarBoomUpDownTimer10Ms=0;
		}
		
	/*	//��λģʽ֧��״̬�жϼ�ʱ��
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
		//����8ģʽ��ʱ��
		
		if(VarBoomWorkModeNow==8)
		{
			if(VarInMode8Timer10Ms<0xFFFF) VarInMode8Timer10Ms++;
		}
		else
		{
			VarInMode8Timer10Ms=0;
		}
		//�������ᣬ��ǻѹ������150bar��ʱ��
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
**��������FunPowerSaveControl()
**�������������۽���ģʽ�ж�
**�����������
**���������
**************************************************************/
UINT8 FunEnergySavingModeCheck()
{
	UINT8 ArmMode;
	VarBigSmallDifferentVale=(INT16)(VarBoomSmallPressureBar - VarBoomBigPressureBar);//���㶯�۴�Сǻѹ����ֵ
	
	

	
	
	//*******йѹģʽ�б�9ģʽ*******
	if(VarXieYaFlag)
	{
		//return(9);
		ArmMode=9;
	}
	else
	{
		if(VarBoomPowerSaveFlag)//���۽���ON
		{
			if(VarDiBoomUp)//��������
			{
				//���������ߵ��ٳ���1minִ�е�һ����۲�����
				if(VarRestarForEnginerFlag==1 )//ϵͳ����
				{
					
					
					VarInModeBoomUpFirstFlag=1;//�����һ����۲����ܱ�־
					if(VarInModeBoomUpFirstBackFlag==1)//�˳���һ����۲����ܱ�־
					{
					VarRestarForEnginerFlag=0;
					VarInModeBoomUpFirstBackFlag=0;
					}
					
					ArmMode=8;
					if(VarBoomBigPressureBar>150)
					{
						
						VarZhiCheJudgeTimerFlag=0;//�˳�֧��ģʽ
					}
					
				}
				else
				{   
			       
					//���֧����̧�����죬��������жϴ�ǻѹ��С��50bar���ǲ�����̧�ۣ�ֱ���ֱ�����λ���ǻѹ������150bar
					if((VarBoomBigPressureBar <= 50)||(VarAfterMode7Flag==1)) //����Сǻ��ȥ��ǻѹ��
					{
						ArmMode=8;
						VarAfterMode7Flag=1;
					//	if(VarBoomBigPressureBarTimer10Ms > 10)
						if(VarBoomBigPressureBar>150)
						{
							VarAfterMode7Flag=0;
							VarZhiCheJudgeTimerFlag=0;//�˳�֧��ģʽ
						}
						
					}
					else
					{
					//����ѹ������300bar���ҳ���300ms�е�5ģʽ��1��11�Ÿ�Ϊ330bar��200ms
						if(((VarPAccumPressureFilter>195) || (VarBoomSaveEngineUpInFlag==1) ) && (VarUpLowEngineFlag==0) )//��������ѹVarPAccumAirPressureBar
						{
							VarBoomSaveEngineUpInFlag=1;
							if(VarPAccumPressureFilter<190)//1��12��,160,165��Ϊ180,185
							{
								VarBoomSaveEngineUpInFlag=0;
							}
							if((VarInMode3Timer10Ms>=50)||(VarArmMode2Flag==1))
							{
								ArmMode=8;//���۽��ܴ�������
								VarArmMode2Flag=1;
							/*	if(TempPressBigger<=260)
								{
									VarArmMode2Flag=0;
								}
						*/
							}
							else
							{
								ArmMode=3;//3-���۽�������
							}
							
						}
						else
						{
							ArmMode=5;//5-������������
							VarUpLowEngineFlag=1;
						}
		
					}
				}
			}
			
			if(VarDiBoomDown)//�����½�
			{
				   //�жϸ��������ߵ��ٳ���1minִ�е�һ����۲����ܣ��������½�ʱ�˳�������ģʽ���ָ���������ģʽ�ж�
				//if(VarInModeBoomUpFirstFlag==1)
				if((VarInModeBoomUpFirstFlag==1)&&(VarPAccumPressureFilter>210))	
				{
						VarInModeBoomUpFirstFlag=0;
						VarInModeBoomUpFirstBackFlag=1;
					}
				
				

		//ɾ����ԭ�򣺹���DT�л�		//���֧�����±����죬�����±��жϴ�ǻѹ��С��50bar���ǲ������±ۣ�ֱ���ֱ�����λ���ǻѹ������150bar
		//		if((VarBoomBigPressureBar <= 50)||(VarAfterMode7BoomDownFlag==1)) //���۴�ǻѹ��
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
					//�����½������������ѹ�ĳ�ʼѹ������ѹ��ʼѹ��С��205,3��26�ո�Ϊ215bar���ܽ��붯�۽����½�ģʽ
						if((VarPAccumPressureFilter<215) || (VarBoomDowmFirstPAccumPressureFlag==1))
						{
							VarBoomDowmFirstPAccumPressureFlag=1;//�����½���һ�μ���ʼ��������ѹ��־λ

							//
							if((VarMode1KeepFlag10Ms>100)||(VarZhiCheJudgeTimerFlag==1))
							{
						
								ArmMode=7;//7-֧��ģʽ
								VarZhiCheJudgeTimerFlag=1;
							
					
							}
							else
							{
								ArmMode=1;//1-���۽����½�
							}
							
						}
						else
						{
							//return(8);//���۲�����ģʽ
							ArmMode=8;
						}
		//		}
				
	
				
				
			}
					
			if(!VarDiBoomUp &&!VarDiBoomDown)
			{	
				ArmMode=6;//6-��λģʽ
				VarUpLowEngineFlag=0;//
				
			}
			
		
		}
		else
		{
			//if(!VarDiBoomUp &&!VarDiBoomDown)
			//{	
		//	    ArmMode=6;//6-��λģʽ
		//	}
		//	else
		//	{
			//	return(8);//���۲�����ģʽ
				ArmMode=8;
		//	}
			
		}
	}
	
	
	return(ArmMode);
	
}
/**************************************************************
**��������FunBoomEnergySavingMode_1()
**�������������۽���ģʽ
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_1(void)  //
{
	
   //�ж��Ƿ����1ģʽ
	VarBoomEnergyMode1Flag=1;
		VarDoDT1=0;
		VarDoDT2=1;
		VarDoDT8=1;
    //��ʱ���Կ���DT8���
//    VarDT8PwmCurrentTarget=0;//2020��11��24���޸ģ���270��Ϊ0

}

/**************************************************************
**��������FunBoomEnergySavingMode_2()
**�������������ܴ������
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_2(void)  //
{
	
   
		VarDoDT1=1;
		VarDoDT2=1;
		VarDoDT8=1;
		VarDoDT7=1;//1.20��������1.18ע��ȥ��

   
}

/**************************************************************
**��������FunBoomEnergySavingMode_3()
**�������������۽���ģʽ
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_3(void)  //���۽�������
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
	//VarDoDT7=1;// 2020/7/10 ��0�ĵ�1


	
	VarLowEnginePressureFlag=0;
}

/**************************************************************
**��������FunBoomEnergySavingMode_5()
**�������������۽���ģʽ
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_5(void)  //������������
{

	VarDoDT7=1; //˫�ú���DT7=1
	
	 VarDoDT1=1;
	if(VarInMode5Timer10Ms>10)
	{
		VarDoDT2=0;
		VarDoDT8=0;

    }
	 

	VarLowEnginePressureFlag=0;
}
/**************************************************************
**��������FunBoomEnergySavingMode_6()
**�������������۽���ģʽ
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_6(void)  //��λģʽ
{
//	VarAfterMode7Flag=0;
	VarBoomEnergyMode1Flag=0;
	VarSaveEngineDT7Flag=0;
	
	//����ģʽ������ֱ���λ����2S���ϣ�DT1��DT2�رշ�ֹ���ܵ��ۣ�(2021.01.13�Ƿ�2s��رյ�ŷ���Ϊ�����رա�����λ���ۡ��ٴ���۵���?)
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
	
	VarBoomDowmFirstPAccumPressureFlag=0;//�����½���һ�μ���ʼ��������ѹ��־λ
	
	VarArmMode2Flag=0;
}
/**************************************************************
**��������FunBoomEnergySavingMode_7()
**�������������۽���ģʽ
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_7(void)  //֧��ģʽ
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
**��������FunBoomEnergySavingMode_8()
**�������������۽���ģʽ
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_8(void)  //���۲�����ģʽ
{
	//������ģʽ������ֱ���λ����1S���ϣ�DT1�رգ�����DT1
	
	      if((!VarBoomUpPressureSensorEorror) && (!VarBoomDownPressureSensorEorror) )//���������ȵ��Ͷ����½��ȵ�����������ʱ
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
**��������FunBoomEnergySavingMode_9()
**����������йѹģʽ
**�����������
**���������
**************************************************************/
void FunBoomEnergySavingMode_9(void)   //йѹģʽ
{
	VarDoDT1=1;
	VarDoDT2=1;
	VarDoDT8=1;
	VarLowEnginePressureFlag=0;
}
/**************************************************************
**��������FunRatatorPowerSave()
**������������ת����ģʽ
**�����������
**���������
**************************************************************/
void FunRatatorPowerSave(void)
{
	
	if((VarRatatorPowerSaveFlag)&&(!VarDiTreadPre)&&(VarPBucCapPressure<=280)&&(VarPBucketArmRodPressure<=280)&&(VarPBucketArmPressure<=280))//1����ת���ܿ���״̬ΪON��2������ѹ������ OFF��3��,4)(������ǻ�򶷸�Сǻ�򶷸˴�ǻС��280bar)
	{
		VarDoDT6=0;//DT6ʧ���
	}
	else
	{
		VarDoDT6=1;//DT6�õ�ر�
	}
	
}

/**************************************************************
**��������FunPowerSaveSpeedControl()
**�������������ܷ�����ת�ٿ���
**�����������
**���������
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
		
	  	
	if(VarBoomEnergyMode1Flag==1) //�����½�ת�ٵ������ƣ�1.13ȥ��ע�ͷ��ٴ����á����±���
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
}
/**************************************************************
**��������FunPowerSavePumpCurrentControl()
**�����������������õ�������
**�����������
**���������
**************************************************************/

void FunPowerSavePumpCurrentControl(void)
{
	UINT8 i,VarBool;
		UINT16 speed_key=100;
		UINT32 Temp_Ulong;
		UINT16	speed_key1;
		UINT16	speed_key2;
		//��ֵ�����ø���λ��ʼ����ֵ
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
						VarTempCurrentTarget2 = 0;//��ʼ����ʱ����Ϊ0
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
			if(VarPAiBoomUpPressure>5)
			{
				VarTempCurrentTarget2=330;//1.21��0��Ϊ
			}
			else
			{
				VarTempCurrentTarget2=0;	
			}
		}
			
			VarValveCurrentTarget=(UINT16)VarTempCurrentTarget2;
						
		//�˳��Զ�������ʱ����
		if(VarCurrentIdleDelay)
		{
			VarValveCurrentTarget = 0;
		}
		
		if((VarBoomEnergyMode1Flag==1)&&(TempPressBigger<180))//���۽����½�1ģʽ���� ����
		 {
			 
			// VarValveCurrentTarget=VarValveCurrent[VarCurrentLevel];//���۽����½�����Ϊ�õ�λ�Ļ�׼����
			VarValveCurrentTarget=650;
		 }
		//��ֵ������
		if(VarValveCurrentTarget>680)
		{
			VarValveCurrentTarget=680;
		}
		
	/*	if((VarBoomEnergyMode1Flag==1)&&(TempPressBigger<60))//���۽����½�1ģʽ���� ����
		 {
			 
			 VarValveCurrentTarget=VarValveCurrent[VarCurrentLevel];//���۽����½�����Ϊ�õ�λ�Ļ�׼����
		 }
		*/

		
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
