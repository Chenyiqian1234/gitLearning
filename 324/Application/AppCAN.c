#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppVar.h"
/**************************************************************
**��������FunCanDataDeal()
**����������CAN�������ݴ���������ʾ����GPS�뷢����MCU֮���ͨѶ
**�����������
**�����������
**************************************************************/
void FunCanDataDeal(void)
{
	//����������ʾ����GPS֮���ͨѶ
	FunCanDisplayGpsReceiveData();
	FunCanDisplayGpsPackSendData();
	FunCanDisplayGpsSendData();
	
	//�������뷢����MCU֮���ͨѶ
	FunCanReceiveEngineData();
	FunCanSendEngineDataPack();	
	FunCanSendEngineData();
}
/**************************************************************
**��������FunCanReceiveEngineData()
**�������������շ�����������������
**�����������
**�����������
**************************************************************/
void FunCanReceiveEngineData(void)
{
	UINT8 VarBool;
	UINT32 Temp_ulong;
	//���緢��������:0-����˹��1-��ʮ�壬2-Ϋ��	
	switch(VarExcavatorEngineType)
	{
		case 0:FunCanReceiveCumminsData();		//���շ�����ECU��CAN����
				FunWeiChaiFaultSPNCodeGet();
			//	FunCumminsFaultSPNCodeGet();	//���ϴ����ȡ
				FunCumminsFaultCodeDiagnose();	//�������
				break;  
		case 1:FunCanReceiveISUZUData();
				FunISUZUFaultSPNCodeGet();
				FunISUZUFaultCodeDiagnose();
				break;
		case 2:FunCanReceiveWeiChaiData();
				FunWeiChaiFaultSPNCodeGet();
				FunWeiChaiFaultCodeDiagnose();
				break;
		default:break;
	}
	//�������뷢����ͨѶ�����жϣ���ʱ10S�ж�
	VarBool = LibTimerTon(12,VarCanEngineNoDataFlag,10000,&Temp_ulong);
	if(VarBool)
	{
		VarCanEcmNoDataFlag =1;
	}
	else
	{
		VarCanEcmNoDataFlag =0;
	}
}
/**************************************************************
**��������FunCanSendEngineDataPack()
**������������Ϸ�����������������������
**�����������
**�����������
**************************************************************/
void FunCanSendEngineDataPack(void)
{
  switch(VarExcavatorEngineType)
  {
  	case 0:FunCanSendCumminsDataPack();break;
  	case 1:FunCanSendISUZUDataPack();break;
  	case 2:FunCanSendWeiChaiDataPack();break;
  	default:break;	
  }
}
/**************************************************************
**��������FunCanSendEngineData()
**��������������ϵ����ݷ�����������������
**�����������
**�����������
**************************************************************/
void FunCanSendEngineData(void)
{
	//CAN���ݷ���,ת�ٿ���10ms��������
	if(LibTimer(10,1,10,1))
	{
		VarCanSendEngineStep++;
		//���緢��������:0-����˹��1-��ʮ�壬2-Ϋ��	
		switch(VarExcavatorEngineType)
		{
			case 0:
			//	LibCan0SendData(13,0x0C000003,1,VarSendDataID_0x0C000003,8);break;//ת�ٿ���
			  //  LibCan0SendData(13,0x0CF00330,1,VarSendDataID_0x0CF00330,8);//���ȿ���
			    LibCan0SendData(13,0x18FDCB30,1,VarSendDataID_0x18FDCB30,8);break;//�����ʿ���

			case 1:
				
				if(VarEngineNeedStopFlag)//������ͣ������
				{
					LibCan0SendData(13,0x18FEE4E4,1,VarSendDataID_0x18FEE4E4,8);
				}
				else//������ת�ٿ���
				{
				    //LibCan0SendData(12,0x18EA0028,1,VarSendDataID_0x18EA0028,8);
					LibCan0SendData(13,0x0C0000E4,1,VarSendDataID_0x0C0000E4,8);
				}
			
		        LibCan0SendData(12,0x18EA00FA,1,VarSendDataID0x18EA00FA,8);//�򷢶���������������
				break;
			case 2:
			    LibCan0SendData(13,0x0C000003,1,VarSendDataID_0x0C000003,8);break;//ת�ٿ���
			default:break;

		}
	}
}
