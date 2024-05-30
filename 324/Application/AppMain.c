#include "AppVar.h"
#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"

//LibTimer_1:CAN���ݷ�����ʾ��
//LibTimer_2:������LED����˸
//LibTimer_3:
//LibTimer_4:CAN���ݷ���GPS
//LibTimer_5:
//LibTimer_6:�������㶨ʱ����500ms����һ��
//LibTimer_7:�������أ�����SUNWARD
//LibTimer_8:����������ʱ���ۼ�
//LibTimer_10:CAN���͵�������MCU
//LibTimer_11:p1,p2ѹ���������

//LibTimerTon_1~12:����
/* *************************************************************** 
** AppMain
** ************************************************************ */
void AppMain(void) 
{ 
	FunUartReceiveData();
	FunUartSendData();
	//ϵͳ�ػ�����
	FunSysSleep();
	//������������
	FunIOSample();
	//���̱궨
	FunDialSpeedSet();
	//Flash��д
  	FunFlashLoop();
	//CANͨѶ
	FunCanDataDeal();
	//GPS��������
	FunControlGpsLock();
	//����Сʱ��
	FunSysWorkTimeCompute();
	//
	FunBuzzerAlarm();
	//
	FunHydraulicCoolingPumpCurrent();
	//
	FunFuelAirFitlerControl();
	
	//���ط�����
	FunSwitchValveControl();
	//���ܿ���
	FunPowerSaveIO();
	FunPowerSaveControl();
	FunPowerSaveFault();
	
	//����ϵͳ,�Ǳ��̱궨״̬
	if(VarAccDialPosiSetting==0)
	{
		if( (VarSysPowerOn>0)||(VarEngineSpeedNow>400) )
		{
			if(VarEngineSpeedNow>400)
			{
				//�Զ������ж�
				FunAutoIdle();
				//�¶���ؿ���
				FunTemperatureCotrol();
				//�����ٶ�
				FunTravelSpeed();

				//������ѹ
				FunSecondPressure();
				//��������
				FunAssistantSet();
				
				//������ת�ٿ���
				if(VarBoomPowerSaveFlag)//����
				{
					FunPowerSaveSpeedControl();
				}
				else//������
				{
					FunSpeedControl();
				}
				
				//�ù��ʿ���
				if(VarBoomPowerSaveFlag)//����
				{
					FunPowerSavePumpCurrentControl();
				}
				else//������
				{
					FunPumpCurrent();
				}
				
				
				
			}
			else
			{
				//Կ���ϵ磬������δ������ת�ٵ�����1��
				VarCanEngineLevelSpeed=VarEngineLevelSpeed[0];
			}
		}
	}	

	//�������У�LED����˸
	if(LibTimerGet1S()<5)
	{
		if(LibTimer(2,1,50,1))
		{
			LibMcuLedOutput(!LibFunMcuLedState());
		}
	}
	else
	{
		if(LibTimer(2,1,500,1))
		{
			LibMcuLedOutput(!LibFunMcuLedState());
		}
	}
}

/* *************************************************************** 
** File End
** ************************************************************ */
