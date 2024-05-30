#include "AppVar.h"
#include "AppFun.h"
#include "LibFunDefine.h"
/* ******************************************************
** ��������:FunSysWorkTimeCompute
** ��������:����Сʱ����������
** �������:��
** ���ز���:��
** *************************************************** */
void FunSysWorkTimeCompute(void)
{
	UINT8 VarStartBool,temp_uchar,VarBool_1,VarBool_2;
	UINT32 Password_1,UlongTemp_1,UlongTemp_2,UlongTemp_3;
	//������һ����������ʱ����㣬��λ:S
	if(VarEngineSpeedNow<400)
	{
		 VarStartBool= 0;
	}
	else
	{
		VarStartBool = 1;
		VarEngineStarted = 1;
	}
	if(LibTimer(8,VarStartBool,1000,1))
	{
		VarEngineWorkTime1S++;
		//��ű������쳣ʱ�����
		if(VarValveCurrentNow>700)
		{
			if(VarValveErrorTime1S<0xFFFF)
				VarValveErrorTime1S++;
		}
		else
			VarValveErrorTime1S=0;
		//����ѹ����ʱ���ۼ�
		if(VarCanEngineOilPreAlarm>0)
		{
			if(VarEngineWorkErrorTime1S<0xFF)
			{
				VarEngineWorkErrorTime1S++;
			}
		}
		else
		{
			VarEngineWorkErrorTime1S=0;
		}
	}
	//ʱ��ת��
	if(VarEngineWorkTime1S>59)
	{
		VarEngineWorkTime1M++;
		VarEngineWorkTime1S=0;
		if(VarEngineWorkTime1M%6 == 0) //ÿ��6���ӣ�����Сʱд��Flash
		{
			VarFlashHourNeedSaveMainFlag = 1;
			VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
			VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
		}
	}
	if(VarEngineWorkTime1M>59)
	{
		VarEngineWorkTime1H++;
		VarEngineWorkTime1M=0;
		//��ֹдFlashʱ��ת���źŷ��ͣ����·�����ת�ٲ��ȣ���Ϊ�ϵ�洢
		/*
		if( (VarEngineWorkTime1H<1000)||((VarEngineWorkTime1H%20==2)&&(VarEngineWorkTime1H>1000)) )
		{
			VarFlashHourNeedSaveMainFlag=1;
		}
		*/
	}
	VarBool_1 = LibTimerTon(4,VanEngineTimeSetPSDSendFlag,2000,&UlongTemp_1);//����2S
	if(VarBool_1>0)
	{	
		VanEngineTimeSetPSDSendFlag = 0;
		VanEngineTimeSetPSDoKFlag=0;
		LibTimerTon(4,0,2000,&UlongTemp_1);
		//�ж�Сʱ�����������Ƿ���ȷ
		temp_uchar = FunSystemPasswordComput(3,&Password_1,VarEngineWorkTime1H,VarEngineWorkTime1M,VarCanExcavatorId);
		if(temp_uchar==0)
		{
			if(VarCanEngineTimeSetPSD==Password_1)
			{
				VanEngineTimeSetPSDoKFlag=1;//����������ʱ������������ȷ
			}
			else
			{
				VanEngineTimeSetPSDoKFlag=0;
			}
		}
	}
	VarBool_1 = LibTimerTof(9,VanEngineTimeSetPSDSendFlag,60000,&UlongTemp_3);//60S��������Сʱ��ʱ��
	if(!VarBool_1)
	{
		VanEngineTimeSetPSDoKFlag=0;
	}
	VarBool_2 = LibTimerTon(8,VarCanEngineTimeSetFlag,2000,&UlongTemp_2);//ʱ�����÷��ͳ���2S
	if((VanEngineTimeSetPSDoKFlag>0)&&(VarBool_2>0))
	{
		VarCanEngineTimeSetPSDoK=0;
		VarEngineWorkTime1H = VarCanEngineTimeSetHour;
		VarFlashHourNeedSaveMainFlag = 1;//.......................test,201303025
		VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
		VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
		VanEngineTimeSetPSDoKFlag=0;
	}
}
/* *************************************************************** 
** File End
** ************************************************************ */
