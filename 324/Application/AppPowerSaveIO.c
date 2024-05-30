#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"

UINT8 VarDt1TestCounter = 0;
UINT16 VarDt1TestOutputCurrent=0;

/**************************************************************
**��������FunIOSample()
**����������IO�˿�����������������
**�����������
**�����������
**************************************************************/
void FunPowerSaveIO(void)
{
	FunPowerSaveAiSample();//Ai����
	FunPowerSaveDiSample();
	FunPowerSaveDoSet();   //��Do
	FunPowerSavePwmOutput();
}
/**************************************************************
**��������FunPwmOutput()
**��������:DT8����
**�����������
**�����������
**************************************************************/

void FunPowerSavePwmOutput()
{	
	
	/*
	//......................DT8�������..........................
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
**��������FunDiSample()
**����������Di����
**�����������
**�����������
**************************************************************/
void FunPowerSaveDiSample()
{
	VarDiTreadPre = VarDiTravelHighSpeed;	//����ѹ�����أ�>0��ʾ�����ߣ�=0��ʾ������  
	//ѹ������
//	VarDiShangChe=LibGetValueDIH(3);//pin50
	VarDiDGNS=LibGetValueDIH(8);	//pin33
	VarDiDGWB=LibGetValueDIH(9);	//pin34
	VarDiCDDS=LibGetValueDIH(21);	//pin61
	VarDiCDWB=LibGetValueDIH(22);	//pin62
}

/**************************************************************
**��������FunAiSample()
**����������Ai����,AIR0~AIR5:0.1ŷ;AIR6~AIR13:1ŷ
**�����������
**�����������
**************************************************************/
void FunPowerSaveAiSample(void)
{
	//AI���
	UINT8 i;
	UINT32 temp_ulong;
	double temp_double;
	UINT16 Temp_Uint;
	UINT32 temp_BoomSmallPre;
	UINT32 temp_AccumPre;
	UINT32 temp_AccumAirPre;
	
	VarAiBoomUpPressure = LibGetAiCurrent(4);	//pin8,���������ȵ�ѹ��,��λuA
	VarAiBoomDownPressure = LibGetAiCurrent(5);	//pin9,�����½��ȵ�,��λuA	
	
	VarAiAccumPressure = LibGetAiCurrent(10);	//pin19,������ѹ��,��λuA
	VarAiCBoomSmallPressure  = LibGetAiCurrent(11); //pin20,����Сǻѹ��,��λuA
	VarAiCBucCapPressure  = LibGetAiCurrent(2); //pin6,������ǻѹ��,��λuA
	
	VarAiCBoomBigPressure= LibGetAiCurrent(8); //pin16,���۴�ǻ,��λuA	
	VarAiCBucketArmPressure = LibGetAiCurrent(9); //pin17,���˴�ǻѹ��,��λuA	
	VarAiCBucketArmRodPressure = LibGetAiCurrent(13); //pin23,����Сǻѹ��,��λuA
	VarAiCPAccumAirSensor=LibGetAiCurrent(7);		//pin11,��λuA	��������ѹѹ��
			
	VarValveDT8CurrentNow=LibGetPwmCurrent(4);  //Pin67,��ŷ��������� ,DT8,��λuA
	VarValveDT1CurrentNow=LibGetPwmCurrent(7);  //Pin70,��ŷ���������,DT1,��λuA
	VarValveDT2CurrentNow=LibGetPwmCurrent(8);  //Pin71,��ŷ���������,DT2,��λuA
	
	VarValveDT6CurrentNow=LibGetPwmCurrent(2);  //Pin40,��ŷ���������,DT6,��λuA
	VarValveDT5CurrentNow=LibGetPwmCurrent(10);  //Pin73,��ŷ���������,DT5,��λuA
	//Pin44,��ŷ���������,DT7,��λuA�����ܲ������û��PWM��·
	
	
	
	
	/*	
	//DT1DOH�������������ֵ������//DT1��VarValveDT1CurrentNow=18��DT1��VarValveDT1CurrentNow=1350����
	if((VarDoDT1==1)&&(VarValveDT1CurrentNow<100))
	{
		VarValveDT1Error = 1;
		
	}
	if((VarDoDT1==1)&&(VarValveDT1CurrentNow>100))
	{
		VarValveDT1Error = 0;
	}
	//DT2DOH�������������ֵ������
	if((VarDoDT2==1)&&(VarValveDT2CurrentNow<100))
	{
		VarValveDT2Error = 1;
	}
	if((VarDoDT2==1)&&(VarValveDT2CurrentNow>100))
	{
		VarValveDT2Error = 0;
	}	
	
	//DT6DOH�������������ֵ������
	if((VarDoDT6==1)&&(VarValveDT6CurrentNow<100))
	{
		VarValveDT6Error = 1;
	}
	if((VarDoDT6==1)&&(VarValveDT6CurrentNow>100))
	{
		VarValveDT6Error = 0;
	}		
	//DT8DOH�������������ֵ������
	if((VarDT8PwmCurrentTarget>20)&&(VarValveDT8CurrentNow<20))
	{
		VarValveDT8Error = 1;
	}
	if((VarDT8PwmCurrentTarget>20)&&(VarValveDT8CurrentNow>20))
	{
		VarValveDT8Error = 0;
	}
	//DT5DOH�������������ֵ������  //��Ҫ�����籣��
	if((VarDoDT5==1)&&(VarValveDT5CurrentNow<100))
	{
		VarValveDT5Error = 1;
	}
	if((VarDoDT5==1)&&(VarValveDT5CurrentNow>100))
	{
		VarValveDT5Error = 0;
	}	
	
	*/
	//��������ѹѹ������������	
	if((VarAiCPAccumAirSensor<3000)||(VarAiCPAccumAirSensor>25000))
	{
		VarPAccumAirSensorError = 1;
	}
	else
	{
		VarPAccumAirSensorError = 0;
	}
//��������ѹ�˲�
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
	
//��������ѹУ��
	
	temp_AccumAirPre=FunPressureCompute(VarAiPAccumFilter);
	if(temp_AccumAirPre>=6)
	{
	temp_AccumAirPre=((temp_AccumAirPre*990)-5704);
	temp_AccumAirPre=(temp_AccumAirPre/1000);
	}
	
	VarPAccumAirPressureBar=(UINT16)temp_AccumAirPre;//��������ѹ������ʾ����λbar
	
	//��������ѹ�ͱ���
	if(VarPAccumAirPressureBar<=130)
	{
		VarAirPressureLowFlag=1;//��������ѹ�ͱ���
	}
	else
	{
		VarAirPressureLowFlag=0;
	}
	
	//���˴�ǻѹ�������������ж�
	if((VarAiCBucketArmPressure<3000)||(VarAiCBucketArmPressure>25000))
	{
		VarBucketArmPressureSensorEorror = 1;
	}
	else
	{
		VarBucketArmPressureSensorEorror = 0;
	}
	//����Сǻѹ�������������ж�
	if((VarAiCBucketArmRodPressure<3000)||(VarAiCBucketArmRodPressure>25000))
	{
		VarAiCBucketArmRodSensorEorror = 1;
	}
	else
	{
		VarAiCBucketArmRodSensorEorror = 0;
	}	
	
	//���㶷�˴�ǻѹ��,��λbar
	VarPBucketArmPressure = FunPressureCompute(VarAiCBucketArmPressure);
	//���㶷��Сǻѹ��,��λbar
	VarPBucketArmRodPressure = FunPressureCompute(VarAiCBucketArmRodPressure);
	//���������ǻѹ��,��λbar
	VarPBucCapPressure = FunPressureCompute(VarAiCBucCapPressure);
	//���㶯�������ȵ�ѹ��,��λbar
	VarPAiBoomUpPressure = FunLowerPressureCompute(VarAiBoomUpPressure);
	//���㶯���½��ȵ�����λbar
	VarPAiBoomDownPressure = FunLowerPressureCompute(VarAiBoomDownPressure);

	
	

	
	
	//pin6,������ǻѹ�������������ж�
	if((VarAiCBucCapPressure<3000)||(VarAiCBucCapPressure>25000))
	{
		VarAiCBucCapPressureSensorEorror = 1;
	}
	else
	{
		VarAiCBucCapPressureSensorEorror = 0;
	}
	
	
	

	//������ѹ�����㣬���˲�
	//�ȵ��ô����������жϣ������ȵ���ѹ��
	if((VarAiAccumPressure<3000)||(VarAiAccumPressure>25000))
	{
		VarPAccumPressureSensorEorror = 1;//������ѹ������������
	}
	else
	{
		VarPAccumPressureSensorEorror = 0;
	}
	temp_AccumPre = FunPressureCompute(VarAiAccumPressure);
	//��������ѹУ��
	temp_AccumPre=((temp_AccumPre*1053)+1538);
	temp_AccumPre=(temp_AccumPre/1000);
	VarPAccumPressureFilter=(UINT16)temp_AccumPre;
	
	//��⶯�����������е�������ѹ����Сֵ
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

	VarBoomDonwPilotFilter= FunPressureCompute3(VarBoomDonwPilot);//����
	//������ѹ��У׼

	if((VarAiBoomUpPressure<3000)||(VarAiBoomUpPressure>25000))
	{
		VarBoomUpPressureSensorEorror = 1;//��������ѹ������������
	}
	else
	{
		VarBoomUpPressureSensorEorror = 0;
	}
	VarBoomUpPressureFilter = FunPressureCompute3(VarAiBoomUpPressure);//FunPressureCompute2
	if((VarAiBoomDownPressure<3000)||(VarAiBoomDownPressure>25000))
	{
		VarBoomDownPressureSensorEorror = 1;//�����½�ѹ������������
	}
	else
	{
		VarBoomDownPressureSensorEorror = 0;
	}
	//�����½��ȵ�ѹ��
	VarBoomDownPressureFilter = FunPressureCompute3(VarAiBoomDownPressure);//FunPressureCompute3
	
	if((VarAiCBoomBigPressure<3000)||(VarAiCBoomBigPressure>25000))
	{
		VarBoomBigPressureSensorEorror = 1;//���۴�ǻѹ������������
	}
	else
	{
		VarBoomBigPressureSensorEorror = 0;
	}
	VarBoomBigPressureBar=FunPressureCompute(VarAiCBoomBigPressure);
	//���۴�ǻѹ��ֵ����
	if(VarBoomBigPressureBar>3)
	{
	 VarBoomBigPressureBar=VarBoomBigPressureBar-3;
	
	}
	
	if((VarAiCBoomSmallPressure<3000)||(VarAiCBoomSmallPressure>25000))
	{
		VarBoomSmallPressureSensorEorror = 1;//����Сǻѹ������������
	}
	else
	{
		VarBoomSmallPressureSensorEorror = 0;
	}
	temp_BoomSmallPre=FunPressureCompute(VarAiCBoomSmallPressure);
	//����Сǻѹ��ֵ����
	if(temp_BoomSmallPre>=2)
	{
	temp_BoomSmallPre=((temp_BoomSmallPre*1063)-1536);
	
	temp_BoomSmallPre=(temp_BoomSmallPre/1000);
	}
	VarBoomSmallPressureBar=(UINT16)temp_BoomSmallPre;
	
	
	
	
	//******************�����������½������ж�**********************
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
		//*******************ѹ�������ź��б�******************************
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
**��������FunDoSet()
**����������Do�˿�����
**�����������
**�����������
**************************************************************/
void FunPowerSaveDoSet(void)
{
	//DO���
	LibSetValueDOH(21,VarDoDT1);	//pin70
	LibSetValueDOH(22,VarDoDT2);	//pin71
//	LibSetValueDOH(18,VarDoDT8);	//pin67
	
	LibSetValueDOH(5,VarDoDT8);		//pin36���ñ���DT8����DT3,����ִ�пɲ��ٸ���
//	LibSetValueDOH(5,VarDoDT3);		//pin36 //
//	LibSetValueDOH(14,VarDoDT4);	//pin38,//����


	
	LibSetValueDOH(0,VarDoDT5);	//pin31 
	LibSetValueDOH(16,VarDoDT6);	//pin40  DT6
	
		
	LibSetValueDOH(9,VarDoDT7);		//pin44
	LibSetValueDOH(23,1);	//pin72 ����VarDoDT9Կ�׿��ؿ����0  VarDoDT9
	

	
	
	
}
/**************************************************************
**��������FunPressureCompute2()
**��������������ѹ��������(0-10MPa)��������ѹ��ֵ
**�������������ֵ(uA)
**���������ѹ��ֵ(bar)
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
**��������FunPressureCompute3()
**��������������ѹ��������(0-6MPa)��������ѹ��ֵ
**�������������ֵ(uA)
**���������ѹ��ֵ(bar)
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
