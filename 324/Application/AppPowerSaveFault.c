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
**��������FunPowerSaveFault()
**�������������ܹ����жϱ���
**�����������
**���������
**************************************************************/
void FunPowerSaveFault(void)
{
	//���ܴ��������Ͻ��벻����ģʽ
	if(
	(VarBoomUpPressureSensorEorror == 1)||//��������ѹ������������
	(VarBoomDownPressureSensorEorror == 1)||//�����½�ѹ������������
	(VarBoomBigPressureSensorEorror == 1)||//���۴�ǻѹ������������
	(VarBoomSmallPressureSensorEorror == 1)||//����Сǻѹ������������
	(VarPAccumPressureSensorEorror == 1)||//��������ѹ����������
	(VarAirPressureLowFlag==1)||//��������ѹ�ͱ���
	(VarP1PressureSensorEorror == 1)||//P1�ô���������
	(VarP2PressureSensorEorror == 1)//P2�ô���������
	)
	{
		VarEngineSaveSensorFaultChangeModeFlag=1;//���ܴ��������Ͻ��벻����ģʽ��־
	}
	else
	{
		VarEngineSaveSensorFaultChangeModeFlag=0;
	}
		
		
	//���������ϱ���
	
	VarPAccumAirSensorError == 1;//��������ѹѹ������������
	VarBucketArmPressureSensorEorror == 1;//���˴�ǻѹ�������������ж�
	VarAiCBucketArmRodSensorEorror == 1;//����Сǻѹ�������������ж�
	VarAiCBucCapPressureSensorEorror == 1; //������ǻѹ�������������ж�

	
	
	
	
	//��ŷ����ϱ���
	VarValveDT1Error == 1;
	VarValveDT2Error == 1;
	VarValveDT6Error == 1;
	VarValveDT8Error == 1;
	VarValveDT5Error == 1;
	//DT7û��
	
	//��װ������
	if((VarBoomDownPressureFilter>5)&&(VarBoomBigPressureBar>300)&&(VarBoomSmallPressureBar>300))
	{
		VarCartridgeValveFaultFlag=1;
	}
	else
	{
		VarCartridgeValveFaultFlag=0;
	}
	
	
	
	
	
	
	
	
}


