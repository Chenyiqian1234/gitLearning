#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**��������FunUartReceiveData()
**�������������մ�������
**�����������
**�����������
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
**��������FunUartSendData()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
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
**��������FunUartSendDataDiDo()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
**************************************************************/
void FunUartSendDataDiDo(void)
{
	LibSciSendString((UINT8*)"AIC.IN");//cs1   ��������ֵ
/*	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);//ϵͳѹ��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiPilotSwitch,1,0);//�ȵ�ѹ������0
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);//�ߵ���0
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//Ŀ�����ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//ʵ�ʵ���ֵ
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiPilotSwitch,1,0);//�ȵ�ѹ������0
	//LibSciSendByte(0x20);
	//LibSciSendNumUint8(VarDiTravelHighSpeed,1,0);//�ȵ�ѹ������0
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
	LibSciSendNumUint16(VarAiPilotSwitch,1,0);//�ȵ�ѹ������0
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomUpPressureFilter,1,0);//���������ȵ�
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomDownPressureFilter,1,0);//�����½��ȵ�
	/*
	LibSciSendString((UINT8*)"***");
	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);//�ϴ��ѹ��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP2PressureFilter,1,0);//P2ѹ��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);//P1ѹ��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomWorkModeNow,1,0);//ģʽ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiBoomUp,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiBoomDown,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSpeedLevel,1,0);//��λ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//������ת��

	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//Сǻѹ��	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomBigPressureBar,1,0);//��ǻѹ��*/
	

	
		
		/*
	
	
	
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanEngineTorque,1,0);//Ť��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//������ת��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//Ŀ�����ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//ʵ�ʵ���ֵ
	LibSciSendByte(0x20);
	
	
	
	/*LibSciSendByte(0x20);
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(123,1,0);//Сǻѹ��	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(456,1,0);//��ǻѹ��bar
/*	
	

		
	
	
	/*	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarBoomWorkModeNow,1,0);//ģʽ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiBoomDown,1,0);//�����½�
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//Сǻѹ��	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomBigPressureBar,1,0);//��ǻѹ��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarZhiCheJudgeTimerFlag,1,0);//֧��ģʽ��־
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiValveSwitchesFlag,1,0);//ѹ������	
	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarUpLowEngineFlag,1,0);//��������������־λ
	*/

	
	/*LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//����Ŀ�����ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//����ʵ�ʵ���ֵ
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
		LibSciSendNumUint16(VarCanEngineTorque,1,0);//Ť�ذٷֱ�
		LibSciSendByte(0x20);
				LibSciSendNumUint16(VarCanEngineWaterTemp,1,0);//ˮ��
				LibSciSendByte(0x20);
							LibSciSendNumUint16(VarHydraulicOilTempFilter,1,0);//Һѹ����	
	
	
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPwmDT8CurrentTarget,1,0);

	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveDT8CurrentNow,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDt8PwRatio,1,0);
	
	
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomUpPressure,1,0);//pin8,���������ȵ�ѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomDownPressure,1,0);//pin9,�����½��ȵ�,��λuA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiAccumPressure,1,0);//pin19,������ѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBoomSmallPressure,1,0);//pin20,����Сǻѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBucCapPressure,1,0);//pin6,������ǻѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBoomBigPressure,1,0);//pin16,���۴�ǻ,��λuA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBucketArmPressure,1,0);//pin17,���˴�ǻѹ��,��λuA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBucketArmRodPressure,1,0);//pin23,����Сǻѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCPAccumAirSensor,1,0);//pin11,��λuA	��������ѹѹ��	
	*/
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAiBoomUpPressure,1,0);//pin8,���������ȵ�ѹ��,��λuA
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAiBoomDownPressure,1,0);//pin9,�����½��ȵ�,��λuA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiAccumPressure,1,0);//pin19,������ѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAccumPressureFilter,1,0);//pin19,������ѹ��,��λuA
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//pin20,����Сǻѹ��,��λuA
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarPBucCapPressure,1,0);//pin6,������ǻѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiCBoomBigPressure,1,0);//pin16,���۴�ǻ,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomBigPressureBar,1,0);//pin16,���۴�ǻ,��λuA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPBucketArmPressure,1,0);//pin17,���˴�ǻѹ��,��λuA	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarBoomSmallPressureBar,1,0);//pin23,����Сǻѹ��,��λuA
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAccumAirPressureBar,1,0);//pin11,��λuA	��������ѹѹ��	

		
	
}
/**************************************************************
**��������FunUartSendDataAI()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
**************************************************************/
void FunUartSendDataAI(void)
{
	LibSciSendString((UINT8*)"AiPwm");//cs2
	//202004
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDoTravelHighSpeed,1,0);//
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAirPressureLowFlag,1,0);////���ܴ��������Ͻ��벻����ģʽ��־
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAirPressureLowFlag,1,0);////���ܴ��������Ͻ��벻����ģʽ��־
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(flag,1,0);////���ܴ��������Ͻ��벻����ģʽ��־
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//ת����
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSpeedLevel,1,0);//��ѹ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanEngineSpeed,1,0);//ʵ��
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarAirPressureLowFlag,1,0);////���۴�ǻѹ������������
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarP2PressureFilter,1,0);//
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16(VarDoDT7,1,0);////���ܴ��������Ͻ��벻����ģʽ��־
	//LibSciSendByte(0x20);
	//LibSciSendNumUint16((VarRecDataID_0CF00400[2]-125),1,0);//


	

/*	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomUpPressure,1,0);//���������ȵ�ѹ������ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAiBoomUpPressure,1,0);//���������ȵ�ѹ��ֵbar
	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarAiBoomDownPressure,1,0);//�����½��ȵ�ѹ������ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarPAiBoomDownPressure,1,0);//�����½��ȵ�ѹ��ֵbar	
	
	*/

	
	

	

}
/**************************************************************
**��������FunUartSendData()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
**************************************************************/
void FunUartSendDataBiaoding(void)
{
	LibSciSendString((UINT8*)"DI");//Cs4
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiDGNS,1,0);//���ض�������
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiDGWB,1,0);//���ض������
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiCDDS,1,0);//���ز�������
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarDiCDWB,1,0);//���ز������
	LibSciSendString((UINT8*)"Do");
	LibSciSendByte(0x20);
	LibSciSendNumUint8(VarBoomWorkModeNow,1,0);//ģʽVarBoomWorkModeNow
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
**��������FunUartSendDataExcavator()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
**************************************************************/
void FunUartSendDataExcavator(void)
{
	    LibSciSendString((UINT8*)"SysData");//CS3
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarCanAutoIdleEnable,1,0);//�Զ�����ʹ��
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarAiPilotSwitch,1,0);//VarAiPilotSwitch
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarEngineSpeedNow,1,0);//��������ѹ��
		LibSciSendByte(0x20);
		LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);//�����½�ѹ��bar	
	
		
		
	    
	    /*LibSciSendByte(0x20);
	    LibSciSendNumUint8(VarBoomWorkModeNow,1,0);//ģʽVarBoomWorkModeNow
	    
	    LibSciSendByte(0x20);
	        LibSciSendNumUint16(VarRestarForEnginerFlag,1,0);//������־λ
	       	LibSciSendByte(0x20);
	        LibSciSendNumUint16(VarSpeedLevel0Timer10Ms,1,0);//��ʱ��
	       LibSciSendByte(0x20);
	        LibSciSendNumUint16(VarSpeedLevelEngineFlag,1,0);//���ٽ��ܲ��ֱ�־λ	
		       LibSciSendByte(0x20);
		        LibSciSendNumUint16(VarInModeBoomUpFirstFlag,1,0);//1
		        LibSciSendByte(0x20);
		  LibSciSendNumUint16(VarInModeBoomUpFirstBackFlag,1,0);//1
		  LibSciSendByte(0x20);
		  LibSciSendNumUint16(VarDiBoomUp,1,0);//1��������
	     LibSciSendByte(0x20);
		 LibSciSendNumUint16(VarBoomUpPressureFilter,1,0);//
	     LibSciSendByte(0x20);
		 LibSciSendNumUint16(VarBoomDownPressureFilter,1,0);//		    				     		        
	    
	    /*
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarPAccumAirPressureBar,1,0);//����������ѹ��VarPAccumAirPressureBar
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarPAccumPressureFilter,1,0);//������ѹ��
    	
    	LibSciSendByte(0x20);
    	LibSciSendNumUint16(VarLowEngineAirPressureBar,1,0);//������ѹ���½���һ�ν���ֵ
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
**��������FunUartSendDataGps()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
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
**��������FunUartSendDataFuju()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
**************************************************************/	
void FunUartSendDataFuju(void)  //cs5
{
	LibSciSendString((UINT8*)"Fuju");
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanHighSpeedTravel,1,0);//���߸ߵ���
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);//��������ǰת��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDoTravelHighSpeed,1,0);//���߸ߵ��ٵ�ŷ����
	
	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarAirFilterPump_Enable,1,0);//������
		LibSciSendByte(0x20);
			LibSciSendNumUint16(VarDoAirFilterPump,1,0);//���
		
	
	
	

	
	
	
	
	//	LibSciSendByte(0x20);
	//		LibSciSendNumUint16(VarPiPressureFilter,1,0);//�ȵ�ѹ��
/*			LibSciSendByte(0x20);
					LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);//���߸���
	LibSciSendByte(0x20);
		LibSciSendNumUint16(VarEngineSpeedNow,1,0);//������ת��
	
		
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSpeedLevel,1,0);//������ת�ٵ�λ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCurrentLevel,1,0);//�õ�����λ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDialGrade,1,0);//���̵�λֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);//��1ѹ��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);//��2ѹ��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(TempPressBigger,1,0);//��1��2ѹ���ϴ��һ��ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarTempCureentTargetValue,1,0);//�����ֱ�Ӹ�ֵ���м����ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16((VarTempCurrentTarget2),1,0);//�м�������ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentTarget,1,0);//Ŀ�����ֵ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarValveCurrentNow,1,0);//��������ֵ	
	
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
**��������FunUartSendDataFlash()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
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
**��������FunUartSendDataFlash()
**����������ͨ�����ڷ���ϵͳ����
**�����������
**�����������
**************************************************************/	
void FunUartSendDataSpeed(void)
{
	LibSciSendString((UINT8*)"CumminsDiag");//cs8
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDoSecondPressure,1,0);//������ѹDO���	
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarCanSysHSLMode,1,0);//bit0,Hģʽbit1,Sģʽbit2,Lģʽ
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarEngineSpeedNow,1,0);	////��������ǰת��
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP1PressureFilter,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarP2PressureFilter,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarSysAveragePress,1,0);
	LibSciSendByte(0x20);
	LibSciSendNumUint16(VarDiTravelHighSpeed,1,0);	//����ѹ������DIH
	
	
	
	
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
