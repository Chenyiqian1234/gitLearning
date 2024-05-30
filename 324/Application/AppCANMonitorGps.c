#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppVar.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**��������FunCanDisplayReceiveData()
**�����������������ʾ����GPS���յ�������
**�����������
**�����������
**************************************************************/
void FunCanDisplayGpsReceiveData(void)
{
	BOOL GPSLock_All_Enable_Last;		//������ʹ��,1-���ã�0-ͣ��
	BOOL GPSLock_Passive_Enable_Last;	//����������ʹ��,1-���ã�0-ͣ��
	BOOL MonthNoSignalLock_Enable_Last;	//ä������ʹ��,1-���ã�0-ͣ��
	BOOL UncoverLock_Enable_Last;		//�������ʹ��,1-���ã�0-ͣ��
	BOOL CANSignalLostLock_Enable_Last;	//��������ʹ��,1-���ã�0-ͣ��
	BOOL SIMCardLostLock_Enable_Last;	//�ο�����ʹ��,1-���ã�0-ͣ��
	UINT16 temp_uint;
	
//**********************************************���ݽ���*******************************************************************//
/**************************************************************
**����������CAN���������
**С��ģʽ�����ֽ���ǰ�����ֽ��ں�
**************************************************************/
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x18B<<<<<<<<<<<<<<<<<   
//	if(LibCan1ReceiveFlag(0))
//	{
//		LibCan1ReadReceiveData(0,VarRecDataID18B);
//		//Byte0
//		VarWorkLampButton=VarRecDataID18B[0];	
//		//Byte1
//		VarTravelSpeedButton=VarRecDataID18B[1];	
//		//Byte2
//		//Byte3
//		VarAutoIdleButton=VarRecDataID18B[3];
//		//Byte4
//		VarWiperButton=VarRecDataID18B[4];
//		//Byte5
//		VarWaterSprayButton=VarRecDataID18B[5];
//		//Byte6
//		VarCautionLampButton=VarRecDataID18B[6];
//		//Byte7
//		VarCabinLamptButton=VarRecDataID18B[7];
//	}
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x18C<<<<<<<<<<<<<<<<<
//	if(LibCan1ReceiveFlag(1))
//	{
//		LibCan1ReadReceiveData(1,VarRecDataID18C);
//		//Byte0
//		//Byte1
//		//Byte2
//		VarManualRegenerationButton=VarRecDataID18C[2];
//		//Byte3
//		VarRegenerationInhibitButton=VarRecDataID18C[3];
//		//Byte4
//		VarDialGrade=VarRecDataID18C[4];
//		if(VarDialGrade<1)
//		{
//			VarDialGrade=1;
//		}
//		else
//		{
//			VarDialGrade=VarDialGrade;
//		}		
//	}
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x09B<<<<<<<<<<<<<<<<<
//	if(LibCan1ReceiveFlag(2))
//	{
//		LibCan1ReadReceiveData(2,VarRecDataID09B);
//		//Byte0
//		VarPanelHeartbeat=VarRecDataID09B[0];
//	}
	
/**************************************************************
**������������ʾ������ CAN0
**���ģʽ�����ֽ���ǰ�����ֽ��ں�	
**************************************************************/	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x101<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(27))
	{
		LibCan0ReadReceiveData(27,VarRecDataID101);
		//Сʱ����������
		VarCanEngineTimeSetPSD = 0;
		VarCanEngineTimeSetPSD += VarRecDataID101[3];
		VarCanEngineTimeSetPSD = VarCanEngineTimeSetPSD<<8;
		VarCanEngineTimeSetPSD += VarRecDataID101[4];
		VarCanEngineTimeSetPSD = VarCanEngineTimeSetPSD<<8;
		VarCanEngineTimeSetPSD += VarRecDataID101[5];
		//����Сʱ����ֵ
		VarCanEngineTimeSetHour =0;
		VarCanEngineTimeSetHour += VarRecDataID101[6];
		VarCanEngineTimeSetHour = VarCanEngineTimeSetHour<<8;
		VarCanEngineTimeSetHour +=VarRecDataID101[7];
	}
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x102<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(16))
	{
		LibCan0ReadReceiveData(16,VarRecDataID102);
		//Byte6
		//bit0 GPS�������뿪ʼ����
		if( VarRecDataID102[6] & 0x01 )
		{
			VarCanGpsSendUnlockPSDFlag =1;
		}
		else
		{
			VarCanGpsSendUnlockPSDFlag = 0;
		}
	 
		//bit1 GPSȡ�����뿪ʼ����
		if( VarRecDataID102[6] & 0x02 )
		{
			VarCanGpsCancelCommand = 1;	
		}
		else
		{
			VarCanGpsCancelCommand = 0;
		}
		//bit2 ����Сʱ���������뿪ʼ����
		if( VarRecDataID102[6] & 0x04 )
		{
			VanEngineTimeSetPSDSendFlag = 1;
		}
		else
		{
			VanEngineTimeSetPSDSendFlag = 0;
		}
		//bit3 GPS�����������뿪ʼ����..
		if( VarRecDataID102[6] & 0x08 )
		{
			VarCanGpsUrgencyCommand = 1;
		}
		else
		{
			VarCanGpsUrgencyCommand = 0;
		}
		//bit4 ����Сʱ���÷���
		if( VarRecDataID102[6] & 0x10 )
		{
			VarCanEngineTimeSetFlag =1;
		}
		else
		{
			VarCanEngineTimeSetFlag =0;
		}
	}
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x106<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(17))
	{
		LibCan0ReadReceiveData(17,VarRecDataID106);
		//byte0-1 �ھ����ʾ�����ࣺ01-IC����02-��������03-Wachendorff����04-SW��
		if(VarExcavatorMonitorType!=VarRecDataID106[1])	
		{
			VarExcavatorMonitorType = VarRecDataID106[1];
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
		}
		//byte2-3 ����������ʾ����ͨѶЭ��汾:01-IC�ϰ棻02-IC�°棻03-�����;04-Wachendorff��;05-SW��1��
		if(VarCMCommunicationVersion!=VarRecDataID106[3])	
		{
			VarCMCommunicationVersion = VarRecDataID106[3];
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
		}
		//byte4-5/6-7 ��Wachendorff��ʾ���Ļ����ͺ��������ű���
		if(VarCMCommunicationVersion!=4)
		{
			//�����ͺ�
			temp_uint = VarRecDataID106[4];
			temp_uint = temp_uint<<8;
			temp_uint += VarRecDataID106[5];
			if(VarCanExcavatorType!=temp_uint)
			{
				VarCanExcavatorType = temp_uint;
				VarFlashSysDateMasterNeedSaveFlag=1;
				VarFlashSysDateBackupNeedSaveFlag=1;
			}
			//�������
			temp_uint = VarRecDataID106[6];
			temp_uint = temp_uint<<8;
			temp_uint += VarRecDataID106[7];
			if(VarCanExcavatorId!=temp_uint)
			{
				VarCanExcavatorId = temp_uint;
				VarFlashSysDateMasterNeedSaveFlag=1;
				VarFlashSysDateBackupNeedSaveFlag=1;
			}
		} 
	}
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x107<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(18))
	{
		LibCan0ReadReceiveData(18,VarRecDataID107);
		//byte4-5 ���緢��������
		VarExcavatorEngineType = VarRecDataID107[5];//���緢��������:0-����˹��1-��ʮ�壬2-Ϋ��3-�ֶ��֣�4-���⣻5-���		
	}
	
//	//>>>>>>>>>>>>>>>>>>>>>> ID=0x110<<<<<<<<<<<<<<<<<
//	if(LibCan0ReceiveFlag(19))
//	{
//		LibCan0ReadReceiveData(19,VarRecDataID110);
//		//Һѹ����������ֵ
//		VarHydHammerFlow = VarRecDataID110[0];
//		//Һѹ������ֵscissors
//		VarHydSicissorsFlow = VarRecDataID110[1];
//		//Һѹ������ֵ
//		VarHydRamFlow = VarRecDataID110[2];
//		//Һѹ������ѹ���趨ֵ
//		VarHydHammerPresure = VarRecDataID110[3];
//		//Һѹ��ѹ���趨ֵ
//		VarHydSicissorsPresure = VarRecDataID110[4];
//		//Һѹ��ѹ���趨ֵ
//		VarHydRamPresure = VarRecDataID110[5];
//	}
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x111<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(20))
	{
		LibCan0ReadReceiveData(20,VarRecDataID111);
		if( PumpPowerParaSend )	
		{
			if( (VarPumpPowerParameter[0] != VarRecDataID111[0])||
				(VarPumpPowerParameter[1] != VarRecDataID111[1])||
				(VarPumpPowerParameter[2] != VarRecDataID111[2])||
				(VarPumpPowerParameter[3] != VarRecDataID111[3])||
				(VarPumpPowerParameter[4] != VarRecDataID111[4])||
				(VarPumpPowerParameter[5] != VarRecDataID111[5])||
				(VarPumpPowerParameter[6] != VarRecDataID111[6])||
				(VarPumpPowerParameter[7] != VarRecDataID111[7])
			  )
			{
				VarPumpPowerParameter[0] = VarRecDataID111[0];  //�ò���1
				VarPumpPowerParameter[1] = VarRecDataID111[1];
				VarPumpPowerParameter[2] = VarRecDataID111[2];
				VarPumpPowerParameter[3] = VarRecDataID111[3];
				VarPumpPowerParameter[4] = VarRecDataID111[4];
				VarPumpPowerParameter[5] = VarRecDataID111[5];
				VarPumpPowerParameter[6] = VarRecDataID111[6];
				VarPumpPowerParameter[7] = VarRecDataID111[7];  //�ò���8
				VarFlashSysDateMasterNeedSaveFlag=1;//���ݱ���
				VarFlashSysDateBackupNeedSaveFlag=1;
			}
		} 
	}
	
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x112<<<<<<<<<<<<<<<<<
 	if(LibCan0ReceiveFlag(21))
	{
 		LibCan0ReadReceiveData(21,VarRecDataID112);
 		//Byte0
 		//bit0 ���̵�λ����
		if( VarRecDataID112[0] & 0x01 )
		{
		   VarCanAccDialPosiMinSet = 1;
		}
		else
		{
		   VarCanAccDialPosiMinSet = 0;
		}
		//bit1 ���̸�λ����
		if( VarRecDataID112[0] & 0x02 )
		{
		   VarCanAccDialPosiMaxSet = 1;
		}
		else
		{
		   VarCanAccDialPosiMaxSet = 0;
		}
		//bit2 �ù��ʷ��ͱ�־λ
		if( VarRecDataID112[0] & 0x04 )
		{
			PumpPowerParaSend = 1;
		}
		else
		{
			PumpPowerParaSend = 0;
		}
		//bit4
		if( VarRecDataID112[0] & 0x10 )
		{
		   VarCanAccHydraulicCoolingFWD = 0;//����0ʱҺѹ��ȴ����Ϊ��ת
		}
		else
		{
		   VarCanAccHydraulicCoolingFWD = 1;
		}		
		//Byte1,��ԭģʽ
		if( (VarRecDataID112[1] & 0x01)!=VarCanHighlandMode)
		{
			VarCanHighlandMode = (UINT8)(VarRecDataID112[1] & 0x01);
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
		}
		
		//Byte2,������ҵģʽ
		VarCanSysBKRMode = (UINT8)(VarRecDataID112[2]&0x07);	
		//Byte3
		//�����ֶ�/�Զ�ģʽ
//		if( VarRecDataID112[3] & 0x02 )
//		{
//			VarBrokenManual_AutoModel=1;//����1Ϊ�����Զ�ģʽ
//		}
//		else
//		{
//			VarBrokenManual_AutoModel=0;//����0Ϊ�����ֶ�ģʽ��Ĭ���ֶ�ģʽ
//		}
		//bit2,�������ģʽ
//		if( VarRecDataID112[3] & 0x04 )
//		{
//			VarBrokenConfluenceModel=1;
//		}
//		else
//		{
//			VarBrokenConfluenceModel=0;	
//		}
		//Byte4,bit2,�Զ�����
		if( VarRecDataID112[4] & 0x04 )
		{
//			AutoIdleMonitor = 1;
			VarCanAutoIdleEnable = 1;
		}	
		else
		{
//			AutoIdleMonitor = 0;
			VarCanAutoIdleEnable = 0;
		}
		//Byte4,bit3,���߸ߵ���
		if( VarRecDataID112[4] & 0x08 )
		{
			VarCanHighSpeedTravel = 1;
		}
		else
		{
			VarCanHighSpeedTravel = 0;
		}
		//Byte5�Զ����ٵ�λ����
		VarAutoIdleSpeedGrade=VarRecDataID112[5];
		//Byte6һ�����ٵ�λ����
		VarManualIdleSpeedGrade=VarRecDataID112[6];
		//Byte7,
		//bit0,��������
		if( VarRecDataID112[7] & 0x01 )
		{
		   VarAirFilterPump_Enable = 1;
		}
		else
		{
		   VarAirFilterPump_Enable = 0;
		}
		//bit1,ȼ�͹��˱�
		if( VarRecDataID112[7] & 0x02 )
		{
		   VarFuelFilterPump_Enable = 1;
		}
		else
		{
		   VarFuelFilterPump_Enable = 0;
		}
		//bit2,����ģʽ��ť
		if(VarRecDataID112[7] & 0x04)
		{
			EscapeModeButton = 1;
		}
		else
		{
			EscapeModeButton = 0;
		}
	}
	
 	//>>>>>>>>>>>>>>>>>>>>>> ID=0x115<<<<<<<<<<<<<<<<<
	b_115=LibCan0ReceiveFlag(22);
	if(LibCan0ReceiveFlag(22))
	{
		LibCan0ReadReceiveData(22,VarRecDataID115);
		SignalNumber_115 = VarRecDataID115[0];
		OderType_115 = VarRecDataID115[1];
		if (OderType_115==0x12 || OderType_115==0x22 || OderType_115==0x32) 
		{		
			GPSUnlockPSD = 0;
			GPSUnlockPSD += VarRecDataID115[2];
			GPSUnlockPSD = GPSUnlockPSD<<8;
			GPSUnlockPSD += VarRecDataID115[3];
			GPSUnlockPSD = GPSUnlockPSD<<8;
			GPSUnlockPSD += VarRecDataID115[4];
			GPSUnlockPSD = GPSUnlockPSD<<8;
			GPSUnlockPSD += VarRecDataID115[5];
		}
		else
		{
			GPSUnlockPSD = 0;
		}
	}
	
	// ����ID=0x185->101����116  ������1����0��
    if(LibCan0ReceiveFlag(19)) //����ͨ����Ҫ��
	{    		
    	LibCan0ReadReceiveData(19,VarRecDataID116);
		//���۽���ģʽ,��ת����ģʽ,������йѹģʽ
		//if(((VarRecDataID116[0] & 0x01)==0x01 )&& ((VarRecDataID116[0] & 0x08)==0x08))
    	if((VarRecDataID116[0] & 0x01)==0x01)
		{
		  if(VarBoomPowerSaveFlag != 1)
		  {
			VarBoomPowerSaveFlag=1;
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
		  }
		}
		if((VarRecDataID116[0] & 0x01)==0x0)
		{
			if(VarBoomPowerSaveFlag != 0)
			{
			VarBoomPowerSaveFlag=0;
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
			}
		}
			
		//if(((VarRecDataID116[0] & 0x02)==0x02 )&& ((VarRecDataID116[0] & 0x10)==0x10))
		if((VarRecDataID116[0] & 0x02)==0x02 )
		{
			if(VarRatatorPowerSaveFlag !=1)
			{
			VarRatatorPowerSaveFlag=1;
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
			}
		}
		if((VarRecDataID116[0] & 0x02)==0x0)
		{
			if(VarRatatorPowerSaveFlag !=0)
			{
			VarRatatorPowerSaveFlag=0;
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
			}
		}
		
		//if(((VarRecDataID116[0] & 0x04)==0x04 )&& ((VarRecDataID116[0] & 0x20)==0x20))
		if((VarRecDataID116[0] & 0x04)==0x04)
		{
			if(VarXieYaFlag !=1)
			{
			VarXieYaFlag=1;
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
			}
		}
		if((VarRecDataID116[0] & 0x04)==0x0)
		{
			if(VarXieYaFlag !=0)
			{
			VarXieYaFlag=0;
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
			}
		}
		
		
	}
	

	
/**************************************************************
**����������GPS���� CAN0 311��312
**���ģʽ�����ֽ���ǰ�����ֽ��ں�	
**************************************************************/	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x300<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(23))
	{
		VarCanGpsHeartBeat = LibCan0ReceiveFlag(23);
		LibCan0ReadReceiveData(23,VarRecDataID300);
		GPSStateByte = (VarRecDataID300[6]<<8);  //����±���
		GPSStateByte += VarRecDataID300[7];
		if (GPSStateByte & 0x40)//bit6 GPS����δ�ӻ򱻼���
		{
			VarCanAntennaCutLockCommand = 1;
		}
		else
		{
			VarCanAntennaCutLockCommand = 0;
		}
		if (GPSStateByte & 0x100)//bit8 ���Ǳ���
		{
			VarCanUncoverLockCommand = 1;
		}
		else
		{
			VarCanUncoverLockCommand = 0;
		}
		if (GPSStateByte & 0x200)//bit9 �ο�����    ����±���
		{
			SimCardLostAlarm = 1;
		}
		else
		{
			SimCardLostAlarm = 0;
		}
		if (GPSStateByte & 0x400)//bit10 ��Զ��ƽ̨����״̬  ����±���
		{
			GPSPlatformConnetState = 1;
		}
		else
		{
			GPSPlatformConnetState = 0;
		}
	}
	

	//>>>>>>>>>>>>>>>>>>>>>> ID=0x321<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(24))
	{
		LibCan0ReadReceiveData(24,VarRecDataID321);
		SignalNumber_2E1 = VarRecDataID321[0]*256 + VarRecDataID321[1];
		//��ǰ״̬��ֵ
		GPSLock_All_Enable_Last = GPSLock_All_Enable ;
		GPSLock_Passive_Enable_Last = GPSLock_Passive_Enable ;
		MonthNoSignalLock_Enable_Last = MonthNoSignalLock_Enable ;
		UncoverLock_Enable_Last = UncoverLock_Enable ;
		CANSignalLostLock_Enable_Last = CANSignalLostLock_Enable ;
		SIMCardLostLock_Enable_Last = SIMCardLostLock_Enable ;
		
		if (VarRecDataID321[3] & 0x01){
			GPSLock_All_Enable = 1;
		}
		else if(VarRecDataID321[4] & 0x01){
			GPSLock_All_Enable = 0;
		}
		if (VarRecDataID321[3] & 0x02){
			GPSLock_Passive_Enable = 1;
		}
		else if(VarRecDataID321[4] & 0x02){
			GPSLock_Passive_Enable = 0;
		}
		if (VarRecDataID321[3] & 0x04){
			MonthNoSignalLock_Enable = 1;
		}
		else if(VarRecDataID321[4] & 0x04){
			MonthNoSignalLock_Enable = 0;
		}
		if (VarRecDataID321[3] & 0x08){
			UncoverLock_Enable = 1;
		}
		else if(VarRecDataID321[4] & 0x08){
			UncoverLock_Enable = 0;
		}
		if (VarRecDataID321[3] & 0x10){
			CANSignalLostLock_Enable = 1;
		}
		else if(VarRecDataID321[4] & 0x10){
			CANSignalLostLock_Enable = 0;
		}
		if (VarRecDataID321[3] & 0x20){
			SIMCardLostLock_Enable = 1;
		}
		else if(VarRecDataID321[4] & 0x20){
			SIMCardLostLock_Enable = 0;
		}
		//ʹ��״̬�л�ʱ������
		if((GPSLock_All_Enable_Last != GPSLock_All_Enable)
		||(GPSLock_Passive_Enable_Last != GPSLock_Passive_Enable)
		||(MonthNoSignalLock_Enable_Last != MonthNoSignalLock_Enable)
		||(UncoverLock_Enable_Last != UncoverLock_Enable)
		||(CANSignalLostLock_Enable_Last != CANSignalLostLock_Enable)
		||(SIMCardLostLock_Enable_Last != SIMCardLostLock_Enable))
		{
			VarFlashGpsDataMasterNeedSaveFlag=1;
			VarFlashGpsDataBackupNeedSaveFlag=1;
		}
	}
	
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x322<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(25))
	{
		LibCan0ReadReceiveData(25,VarRecDataID322);
		SignalNumber_2E1 = VarRecDataID322[0]*256 + VarRecDataID322[1];
		if (VarRecDataID322[3] & 0x01)
		{
			VarCanGpsLockCommand_A = 1;
		}
		if (VarRecDataID322[3] & 0x02)
		{
			VarCanGpsLockCommand_B = 1;
		}
		if (VarRecDataID322[3] & 0x04)
		{
			VarCanGpsLockCommand_C = 1;
		}
		if (VarRecDataID322[3] & 0x08)
		{
			VarCanGpsLockCommand_D = 1;
		}
	}

	//>>>>>>>>>>>>>>>>>>>>>> ID=0x323<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(26))
	{
		LibCan0ReadReceiveData(26,VarRecDataID323);
		SignalNumber_2E1 = VarRecDataID323[0]*256 + VarRecDataID323[1];
		if (VarRecDataID323[3] & 0x01)
		{
			VarCanGpsLockCommand_A = 0;
		}
		if (VarRecDataID323[3] & 0x02)
		{
			VarCanGpsLockCommand_B = 0;
		}
		if (VarRecDataID323[3] & 0x04)
		{
			VarCanGpsLockCommand_C = 0;
		}
		if (VarRecDataID323[3] & 0x08)
		{
			VarCanGpsLockCommand_D = 0;
		}
	}
	
} 	
	
/**************************************************************
**��������FunCanDisplayGpsPackSendData()
**������������Ϸ�������ʾ����GPS������
**�����������
**�����������
**************************************************************/

void FunCanDisplayGpsPackSendData(void)
{
	UINT8 temp_uchar,i;
	UINT16 temp_uint16; 
	UINT32 Password_1;	
//**********************************************���ݷ���*******************************************************************//
/**************************************************************
**���������ݷ�����CAN�����
**С��ģʽ�����ֽ���ǰ�����ֽ��ں�	
**************************************************************/	
//	for(i=0;i<8;i++)
//	{
//		VarSendDataID19B[i] =0;
//	}
//	//>>>>>>>>>>>>>>>>>>>>>> ID=0x19B<<<<<<<<<<<<<<<<<
//	//Byte0
//	if(VarDoWorkLamp)
//	{
//		VarSendDataID19B[0] |= (UINT8)(1<<1); //bit1
//	}
//	
//	if(!VarDoTravelHighSpeed)
//	{
//		VarSendDataID19B[0] |= (UINT8)(1<<4); //bit4
//		VarSendDataID19B[0] |= (UINT8)(0<<6); //bit6
//	}
//	else
//	{
//		VarSendDataID19B[0] |= (UINT8)(0<<4); //bit4
//		VarSendDataID19B[0] |= (UINT8)(1<<6); //bit6
//	}
//	//Byte1
//	if(VarCanAutoIdleEnable)
//	{
//		VarSendDataID19B[1] |= (UINT8)(1<<5); //bit5
//	}
//	//Byte2
//	if(VarDoWiper_1 || VarDoWiper_2)
//	{
//		VarSendDataID19B[2] |= (UINT8)(1<<0); //bit0
//	}
//	
//	if(VarDoWiper_2)
//	{
//		VarSendDataID19B[2] |= (UINT8)(1<<2); //bit2
//	}
//	
//	if(VarDoWaterSpray)
//	{
//		VarSendDataID19B[2] |= (UINT8)(1<<5); //bit5
//	}
//	
//	//Byte3
//	if(VarDoCautionLamp)
//	{
//		VarSendDataID19B[3] |= (UINT8)(1<<1); //bit1
//	}
//
//	if(VarDoCabinLamp)
//	{
//		VarSendDataID19B[3] |= (UINT8)(1<<5); //bit5
//	}
//	//Byte5
//	if(VarManualRegenerationButton)
//	{
//		VarSendDataID19B[5] |= (UINT8)(1<<1); //bit1
//	}
//	
//	if(VarRegenerationInhibitButton)
//	{
//		VarSendDataID19B[5] |= (UINT8)(1<<5); //bit5
//	}

	/**************************************************************
	**���������ݷ�������ʾ�� CAN1 311��312
	**���ģʽ�����ֽ���ǰ�����ֽ��ں�	
	**************************************************************/	
	for(i=0;i<8;i++)
	{
		VarSendDataID200[i] =0;
		VarSendDataID201[i] =0;
		VarSendDataID203[i] =0;
		VarSendDataID209[i] =0;
		VarSendDataID20A[i] =0;
		VarSendDataID20C[i] =0;
		VarSendDataID20D[i] =0;
		VarSendDataID20E[i] =0;
		VarSendDataID20F[i] =0;
		VarSendDataID210[i] =0;
		VarSendDataID211[i] =0;
		VarSendDataID212[i] =0;
		VarSendDataID215[i] =0;
		VarSendDataID216[i] =0;
		VarSendDataID217[i] =0;
		VarSendDataID218[i] =0;
		VarSendDataID21E[i] =0;
		VarSendDataID220[i] =0;
		VarSendDataID221[i] =0;
		VarSendDataID222[i] =0;
		VarSendDataID224[i] =0;
		VarSendDataID227[i] =0;
		VarSendDataID22F[i] =0;
		VarSendDataID231[i] =0;
		VarSendDataID233[i] =0;
		VarSendDataID2F1[i] =0;
		VarSendDataID236[i] =0;
		VarSendDataID237[i] =0;
		VarSendDataID238[i] =0;
		VarSendDataID239[i] =0;
	}	
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x200 <<<<<<<<<<<<<<<<<
	VarSendDataID200[1] = (UINT8)(DefineHardwareVersion);
	VarSendDataID200[2] = (UINT8)(DefineSoftVersion);
	VarSendDataID200[3] = (UINT8)(VarCMCommunicationVersion);
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x201 <<<<<<<<<<<<<<<<<
	VarSendDataID201[0] = (UINT8)(VarP1PressureFilter>>8);	//P1ѹ��, bar
	VarSendDataID201[1] = (UINT8)(VarP1PressureFilter);
	VarSendDataID201[2] = (UINT8)(VarP2PressureFilter>>8);	//P2ѹ��,bar
	VarSendDataID201[3] = (UINT8)(VarP2PressureFilter);
	VarSendDataID201[4] = (UINT8)((VarSysVoltageMv/100)>>8);//ϵͳ��ѹ:0.1V
	VarSendDataID201[5] = (UINT8)(VarSysVoltageMv/100);
	VarSendDataID201[6] = VarFuelVolumeFilter; //ȼ����λ
	//VarSendDataID201[7]=VarDialGrade;	
	
	if(VarAccDialPosiNow>(VarAccDialPosiMax+120))//11��
 	{
		VarSendDataID201[7] = VarDialGrade+1; //���̵�λ
 	}
 	else
 	{
 		VarSendDataID201[7] = VarDialGrade; //���̵�λ

 	}  
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x203 <<<<<<<<<<<<<<<<<
	//VarSendDataID203[2] = (UINT8)(VarPiPressureFilter);	//�ȵ�ѹ��, bar 
	//VarSendDataID203[3] = (UINT8)(VarBrokenPiPressureFilter);//�����ȵ�ѹ��, bar
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x209  <<<<<<<<<<<<<<<<<
 	 VarSendDataID209[0] = (UINT8)(VarBoomBigPressureBar>>8 );//���۴�ǻѹ��ֵbar
 	 VarSendDataID209[1] = (UINT8)((VarBoomBigPressureBar));
 	 
 	 VarSendDataID209[2] =(UINT8) (VarBoomSmallPressureBar>>8 );//����Сǻѹ��ֵbar
 	 VarSendDataID209[3] =(UINT8)((VarBoomSmallPressureBar));
	
   	 VarSendDataID209[4] = 0;//����Сǻѹ��,��λbar
   	 VarSendDataID209[5] = 0;
   	 
   	 VarSendDataID209[6] = (UINT8)((VarPBucCapPressure>>8)&0xFF);//������ǻѹ��,��λbar
   	 VarSendDataID209[7] = (UINT8)(VarPBucCapPressure & 0xFF );
	
   	 
   	VarSendDataID20A[0] = (UINT8)((VarPBucketArmRodPressure>>8)&0xFF);//pin17,����Сǻѹ��ֵ��λbar
   	VarSendDataID20A[1] = (UINT8)(VarPBucketArmRodPressure & 0xFF );

   	VarSendDataID20A[2] = (UINT8)((VarPBucketArmPressure>>8)&0xFF);//pin23,���˴�ǻѹ��ֵ��λbar
   	VarSendDataID20A[3] = (UINT8)(VarPBucketArmPressure & 0xFF);
   	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20C  <<<<<<<<<<<<<<<<<
	if (VarCanSysHSLMode==0)
	{
		VarSendDataID20C[0] |= (UINT8)(1<<0); //bit0,Hģʽ
	}
	else if(VarCanSysHSLMode==1)
	{
		VarSendDataID20C[0] |= (UINT8)(1<<1); //bit1,Sģʽ
	}
	else 
	{
		VarSendDataID20C[0] |= (UINT8)(1<<2); //bit2,Lģʽ
	} 
	
	if(VarCanHighlandMode)
	{
		VarSendDataID20C[0] |= (UINT8)(1<<3); //bit3,��ԭģʽ
	}
	VarSendDataID20C[1] = (UINT8)(VarCanSysBKRMode & 0x07);	//0-2bit:BKRģʽ
	VarSendDataID20C[2] = (UINT8)(VarEngineWorkTime1H>>8);	//Сʱ
	VarSendDataID20C[3] = (UINT8)(VarEngineWorkTime1H);
	VarSendDataID20C[4] = (UINT8) VarEngineWorkTime1M;	//����
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20D  <<<<<<<<<<<<<<<<<
	VarSendDataID20D[2] = (UINT8)(VarEngineAverageFuelYouHao>>8);	//ƽ��ȼ������(L/h)�����ն����100
	VarSendDataID20D[3] = (UINT8)(VarEngineAverageFuelYouHao);
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20E  <<<<<<<<<<<<<<<<<
	VarSendDataID20E[0] = (UINT8)(VarEngineFuelYouHao>>24);	//���������ͺ�(L)�����ն����2
	VarSendDataID20E[1] = (UINT8)(VarEngineFuelYouHao>>16);
	VarSendDataID20E[2] = (UINT8)(VarEngineFuelYouHao>>8);
	VarSendDataID20E[3] = (UINT8)(VarEngineFuelYouHao);	
	
	VarSendDataID20E[4] = (UINT8)((VarEngineSpeedWorkTome/10)>>24);	//�������ܹ���ʱ��(h)�����ն����2
	VarSendDataID20E[5] = (UINT8)((VarEngineSpeedWorkTome/10)>>16);
	VarSendDataID20E[6] = (UINT8)((VarEngineSpeedWorkTome/10)>>8);
	VarSendDataID20E[7] = (UINT8)((VarEngineSpeedWorkTome/10));	
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20F  <<<<<<<<<<<<<<<<<
	VarSendDataID20F[2] = (UINT8)(VarAftertreatmentDOCIntakeTemp>>8);	
	VarSendDataID20F[3] = (UINT8)(VarAftertreatmentDOCIntakeTemp);
	VarSendDataID20F[4] = (UINT8)(VarAftertreatmentDOCOutletTemp>>8);	
	VarSendDataID20F[5] = (UINT8)(VarAftertreatmentDOCOutletTemp);
	VarSendDataID20F[6] = (UINT8)(VarCanEngineAirInTemp);  //�����¶ȣ����ն����40
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x210  <<<<<<<<<<<<<<<<<
	VarSendDataID210[1] = (UINT8)(VarCanEngineTorque);  //������Ť�ذٷֱȣ����ն����125
	VarSendDataID210[3] = (UINT8)(VarCanEngineBoostTemp); //��ѹ�¶ȣ����ն����40
	VarSendDataID210[4] = (UINT8)(VarIntakeManifoldTemp); //����������¶ȣ����ն����40
	VarSendDataID210[5] = (UINT8)(VarInterCoolInletTemp); //����������¶ȣ����ն����40
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x211  <<<<<<<<<<<<<<<<<
	VarSendDataID211[0] = (UINT8)(VarCanEngineOilPressure);  //����ѹ�������ն����4
	VarSendDataID211[2] = (UINT8)(VarCommonRailPressure>>8); //����ѹ�������ն����256
	VarSendDataID211[3] = (UINT8)(VarCommonRailPressure);
	VarSendDataID211[4] = (UINT8)(VarCanEngineAtmosPressrue); //����ѹ�������ն����0.5
	VarSendDataID211[5] = (UINT8)(VarCanEngineBoostPressrue); //��ѹѹ�������ն����2
	VarSendDataID211[6] = (UINT8)(VarAftertreatmentDPFDifferentialPressure>>8); 
	VarSendDataID211[7] = (UINT8)(VarAftertreatmentDPFDifferentialPressure);
	 
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x212  <<<<<<<<<<<<<<<<<
	VarSendDataID212[0] = (UINT8)(VarDPFRegenerationStatus);
	VarSendDataID212[1] = (UINT8)(VarDPFTripStatus);
	VarSendDataID212[2] = (UINT8)(VarDPFModeL>>8);
	VarSendDataID212[3] = (UINT8)(VarDPFModeL);
	VarSendDataID212[4] = (UINT8)(VarDPFPMAccumulationStatus);
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x215  <<<<<<<<<<<<<<<<<
	//Byte0
	if(VarFuelLackAlarm>0)
	{
		VarSendDataID215[0] |= 1<<0;  //bit0 �������㱨��
	}
	if(VarDiStop==1)
	{
		VarSendDataID215[0] |= 1<<1;  //bit1 ����ͣ������
	}
	if(VarHydraulicOilHihgAlarm)
	{
		VarSendDataID215[0] |= 1<<2;  //bit2 Һѹ���¸߱���
	}
	if(( VarCanEngineOilPreAlarm>0)||(VarEngineSpeedNow<400))
	{
		VarSendDataID215[0] |= 1<<4;  //bit4 ����ѹ���ͱ���
	}
	if(VarCanWaterHihgAlarm>0)
	{
		VarSendDataID215[0] |= 1<<5;  //bit5 ��ȴˮ�¸߱���
	}
	if(VarDiAirFilterAlarm==0)      //����Ч
	{
		VarSendDataID215[0] |= 1<<6;  //bit6 ���˶�������
	}
	if(VarDiCharge>0)
	{
		VarSendDataID215[0] |= 1<<7;  //bit7 ���ָʾ
	}
	//Byte1
	if(VarCanAutoIdleEnable>0)
	{
		VarSendDataID215[1] |= 1<<0;  //bit0 �Զ�����
	}
	if(VarButtonLowSpeedEnable)
	{
		VarSendDataID215[1] |= 1<<1;  //bit1 һ������
	}
	if(VarCanInPreheat>0)//Ԥ��DI
	{
		VarSendDataID215[7] |= 1<<2;  //bit2 Ԥ��	
	}
	if(VarEngineWarmState)
	{
		VarSendDataID215[1] |= 1<<3;  //bit3 ů������
	}
	if(VarDoTravelHighSpeed>0)
	{
		VarSendDataID215[1] |= 1<<4;  //bit4 ���߸ߵ���
	}
	if(VarModeSelectionError)
	{
		VarSendDataID215[1] |= 1<<5;  //bit5ģʽѡ�����
	}
/*
	//Byte2
	//bit0-2��������
    if(VarAutoRegenerationLamp)
    {
		VarSendDataID215[2] |= 1<<0;  //bit0-2:001 �Զ�������(�̵Ƴ���)
		VarSendDataID215[2] |= 0<<1;  
		VarSendDataID215[2] |= 0<<2;  
    }
    
    if(VarManualRegenerationLamp==1)
	{
		VarSendDataID215[2] |= 0<<0; //bit0-2:010 �ֶ���������(�ȵƳ���)
		VarSendDataID215[2] |= 1<<1;
		VarSendDataID215[2] |= 0<<2; 
	}
	else if(VarManualRegenerationLamp==2)
	{
		VarSendDataID215[2] |= 0<<0; //bit0-2:100 �ֶ�����������(�ȵ�����))
		VarSendDataID215[2] |= 0<<1;
		VarSendDataID215[2] |= 1<<2;
	}
	else if(VarManualRegenerationLamp==3)
	{
		VarSendDataID215[2] |= 0<<0; //bit0-2:110 �ֶ�����������(�ȵƿ���)
		VarSendDataID215[2] |= 1<<1;
		VarSendDataID215[2] |= 1<<2;
	}
	//bit4-5,��ʻԱ�����
	if(DriverWarningLamp==1) 
	{
		VarSendDataID215[2]|= (UINT8)1<<4;  //��ʻԱ����Ƴ�����bit4-5:01
		VarSendDataID215[2]|= (UINT8)0<<5;
	}
	else if(DriverWarningLamp==2) 
	{
		VarSendDataID215[2]|= (UINT8)0<<4;  //��ʻԱ�����������bit4-5:10
		VarSendDataID215[2]|= (UINT8)1<<5;
	}
	else if(DriverWarningLamp==3) 
	{
		VarSendDataID215[2]|= (UINT8)1<<4;  //��ʻԱ����ƿ�����bit4-5:11
		VarSendDataID215[2]|= (UINT8)1<<5;
	}
	//Byte5
	if(NoPowerLamp)
	{
		VarSendDataID215[5]|= (UINT8)1<<0;//bit0
	}
	if(EscapeModeLamp)
	{
		VarSendDataID215[5]|= (UINT8)1<<1;//bit1
	}
	if(EXHSystemLamp)
	{
		VarSendDataID215[5]|= (UINT8)1<<3;//bit3
	}
	if(AftertreatmentFailureLamp)
	{
		VarSendDataID215[5]|= (UINT8)1<<4;//bit4
	}
*/	
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x216  <<<<<<<<<<<<<<<<<
	VarSendDataID216[0] =(UINT8)(VarAiPump1Pressure/100);	//P1ѹ��AIֵ
	VarSendDataID216[1] =(UINT8)(VarAiPump2Pressure/100);	//P2ѹ��AIֵ
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x217  <<<<<<<<<<<<<<<<<
//    VarSendDataID217[0] =(UINT8)(VarAiBrokenPilotPressure/100); //�����ȵ�ѹ��AIֵ
//    VarSendDataID217[7] =(UINT8)(VarAiHydraulicTemp2/10); //Һѹ����2AIֵ

	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x218  <<<<<<<<<<<<<<<<<
    VarSendDataID218[4] =(UINT8)(VarAiHydraulicTemp/10); //Һѹ����AIֵ
    //VarSedDataID218n[5] =(UINT8)(VarAiPilotPressure/100); //�ȵ�ѹ��AIֵ   �ȵ�ѹ����������
    VarSendDataID218[6] =(UINT8)(VarAiFuelVolume/10);	//����������AIֵ
    
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x21E	<<<<<<<<<<<<<<<<<
    //Byte0
//    if(VarDoBrokenValve)
//    {
//		VarSendDataID21E[0]|= (UINT8)1<<2;//bit2���鴸���ط�
//    }
    //Byte1
    if(VarDoSecondPressure>0) 
	{
		VarSendDataID21E[1] |=  (UINT8)1<<0;//bit0 ������ѹ��
	}
	if(VarDoBatteryRelay>0)
	{
		VarSendDataID21E[1] |= (UINT8)1<<1;//bit1 �ϵ���ʱ���
	}
	if(VarDoPilot>0) 
	{
		VarSendDataID21E[1] |= (UINT8)1<<2;//bit2 �ȵ���ŷ�
	}
	if(VarDoTravelHighSpeed>0) 
	{
		VarSendDataID21E[1] |= (UINT8)1<<3;//bit3 ���߸ߵ��ٷ�
	}
	if(VarDoManualRegenrationLoad)
	{
		VarSendDataID21E[1] |= (UINT8)1<<5;//bit5 �ֶ������������ص�ŷ�
	}
//	if(VarDoBrokenConfluenceValve)
//	{
//		VarSendDataID21E[1] |= (UINT8)1<<6;//bit6 ��������ȵ���ŷ�
//	}
	//Byte2
	if(VarDiTravelHighSpeed>0) 
	{
		VarSendDataID21E[2] |= (UINT8)1<<0; // bit0 ����ѹ��H
	}	
	if(VarDiPilot>0) 
	{
		VarSendDataID21E[2] |= (UINT8)1<<1; // bit1 �ȵ�����H
	}
	if(VarDiLowSpeedEnable>0) 
	{
		VarSendDataID21E[2] |= (UINT8)1<<2; // bit2 һ�����ٿ���
	}
	if(VarManualRegenerationButton)
	{
		VarSendDataID21E[2] |= (UINT8)1<<3; // bit3 �ֶ���������
	}
	if(VarRegenerationInhibitButton)
	{
		VarSendDataID21E[2] |= (UINT8)1<<4; // bit4 ������ֹ����
	}
	if(VarDiStop==1)
	{
		VarSendDataID21E[2] |= (UINT8)1<<5; // bit5 ��ͣ����
	}
	//Byte3
    if(VarDoHydraulicCoolingPositiveValve==0)
    {
		VarSendDataID21E[3] |= (UINT8)1<<0; //bit0 ������ת
    }
    else
    {
		VarSendDataID21E[3] |= (UINT8)1<<0; //���ȷ�ת
    }
    if(VarDoAirFilterPump==0)
	{
    	VarSendDataID21E[3] |= (UINT8)1<<1;;//bit1,��������
	}    
	if(VarDoFuelFilterPump>0) 
	{
		VarSendDataID21E[3] |= (UINT8)1<<2;;//bit2�����͹��˱�
	} 
    if(VarCanAccHydraulicCoolingFWD==0)
    {
		VarSendDataID21E[3] |= (UINT8)1<<5; //bit5 ������ת
    }
    else
    {
		VarSendDataID21E[3] |= (UINT8)0<<5; 
    }
	//Byte7******��һ���Ƿ�������ư巢�͸���ʾ��������*******/
//    if(VarDoCabinLamp)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<0; //bit0 ��ʻ�Ҷ���	
//    }
//    if(VarDoWorkLamp)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<1; //bit1 ������	
//    }
//    if(VarDoCautionLamp)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<2; //bit2 ��ʾ��	
//    }
//    if(VarDoWiper_1&&(VarDoWiper_2==0))
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<5; //bit5 ���1��	
//    }
//    if(VarDoWiper_2)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<6; //bit6 ���2��	
//    }
//    if(VarDoWaterSpray)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<7; //bit7 ϴ��
//    }
    

	// >>>>>>>>>>>>>>>>>>>>>> ID=0x220	<<<<<<<<<<<<<<<<<
    if(VarCanGpsCancelPSDoK>0)
	{
		VarSendDataID220[0] |= 1<<0; //bit0  GPSȡ��������ȷ
	}
	if(VanEngineTimeSetPSDoKFlag>0)
	{
		VarSendDataID220[0] |= 1<<1; //bit1  Сʱ������������ȷ
	}	
	if(VarCanGpsUrgencyState>0)
	{
		VarSendDataID220[0] |= 1<<2;//bit2 GPS��������״̬	
	}
	if(VarCanGpsUnlockPSDOK)
	{
		VarSendDataID220[0] |= 1<<3;//bit3 GPS�ش�	
	}
	if(VarCanGpsUrgencyPSDoK)
	{
		VarSendDataID220[0] |= 1<<4; //bit4 GPS��������������ȷ
	}
	if(VarCanGpsCancel>0)
	{
		VarSendDataID220[0] |= 1<<5; //bit5 GPSȡ��״̬
	}
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x221	<<<<<<<<<<<<<<<<<
	VarSendDataID221[0] = VarRecDataID_0x18FEEE00[0];//ˮ��,���ն���Ҫ��40
	VarSendDataID221[1] = (UINT8)(VarHydraulicOilTempFilter);//Һѹ����1
	VarSendDataID221[2] = (UINT8)(VarEngineSpeedNow>>8); //������ת�ٸ��ֽ�
	VarSendDataID221[3] = (UINT8)(VarEngineSpeedNow); //������ת�����ֽ�
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x222	<<<<<<<<<<<<<<<<<
	VarSendDataID222[2] = (UINT8)(VarBKRFlowNowCurrent>>8); //�����������ڵ�ŷ���ǰ����
	VarSendDataID222[3] = (UINT8)(VarBKRFlowNowCurrent); 
	VarSendDataID222[4] = (UINT8)(VarHydraulicCoolingPumpValveCurrent>>8); //Һѹ��ȴ���ȵ�ŷ���ǰ����
	VarSendDataID222[5] = (UINT8)(VarHydraulicCoolingPumpValveCurrent); 
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x224	<<<<<<<<<<<<<<<<<
	if(VarValveCurrentNow<25)
	{
		temp_uint16=0;//����<25mA��ʾΪ0
	}
	else
	{
		temp_uint16=VarValveCurrentNow;
	}
	VarSendDataID224[4] =(UINT8)(temp_uint16>>8); //����������ֵ
	VarSendDataID224[5] =(UINT8)(temp_uint16);
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x227	<<<<<<<<<<<<<<<<<
	//VarSendDataID227[3] = (UINT8)(VarHydraulicOilTemp2Filter);//Һѹ����2

	// >>>>>>>>>>>>>>>>>>>>>> ID=0x22F	<<<<<<<<<<<<<<<<<
	//Byte0
	if((VarDialGrade>10) || (VarDialGrade==255))
	{
		VarSendDataID22F[0] |= 1<<0; //bit0 ���ű��̴������쳣
	}
	if(VarP1PressureSensorEorror>0)
	{
		VarSendDataID22F[0] |= 1<<1; //bit1 P1ѹ���������쳣
	}
	if(VarP2PressureSensorEorror>0)
	{
		VarSendDataID22F[0] |= 1<<2; //bit2 P2ѹ���������쳣
	}
	/*if(VarBrokenPiPressureSensorEorror>0)
	{
		VarSendDataID22F[0] |= 1<<3; //bit3 �����ȵ�ѹ���������쳣
	}
	*/
	if(VarFuelSensorError)
	{
		VarSendDataID22F[0] |= 1<<4; //bit4  �����������쳣����
	}
	if(VarPiPressureSensorEorror)
	{
		VarSendDataID22F[0] |= 1<<5; //bit5 �ȵ�ѹ���������쳣
	}
	//Byte1
	
	if(VarBoomUpPressureSensorEorror>0) 
	{
		VarSendDataID22F[1] |= (UINT8)1<<4;//bit4 b-up pre error//��������ѹ������������
	}

	if(VarBoomDownPressureSensorEorror>0) 
	{
		VarSendDataID22F[1] |= (UINT8)1<<5; // bit0 B-down.pre error �����½�ѹ������������
	}
	//Byte2
	
	if(VarBoomBigPressureSensorEorror>0) 
	{
		VarSendDataID22F[2] |= (UINT8)1; //bit2 b-rod.pre error ����Сǻѹ������������
	}
	if(VarBoomSmallPressureSensorEorror>0) //
	{
		VarSendDataID22F[2] |= (UINT8)1<<1; //bit3 b-cap pre error ���۴�ǻѹ������������
	}
	
	if(VarBucketArmPressureSensorEorror>0) //���˴�ǻ
	{
		VarSendDataID22F[2] |= (UINT8)1<<2; // bit0 Arm-cap Pre Error
	}
	if(VarAiCBucketArmRodSensorEorror>0) //����Сǻ
	{
		VarSendDataID22F[2] |= (UINT8)1<<3; // bit1  Arm-rod Pre Error
	}
    if(VarAiCBucCapPressureSensorEorror>0) 
	{
    	VarSendDataID22F[2] |= (UINT8)1<<4; //bit2  Buc-cap Pre Error
	}
	if(VarHydraulicOilTempSensorError)
	{
		VarSendDataID22F[2] |= 1<<6; //bit6 Һѹ���´������쳣
	}
	

//	if(VarHydraulicOilTemp2SensorError)
//	{
//		VarSendDataID22F[2] |= 1<<7; //bit7 Һѹ���´�����1�쳣
//	}
	//Byte3
	if(VarValveError>0)
	{
		VarSendDataID22F[3] |= 1<<1; //bit1 �ù��ʿ��Ʊ������쳣
	}
	if(VarCanEcmNoDataFlag)
	{
		VarSendDataID22F[3] |= 1<<5;//bit5 ECM�������ͨѶ����
	}
	//Byte4
	if(VarGpsCanBusError)
	{
		VarSendDataID22F[4] |= 1<<4;//bit4 GPS�������ͨѶ����
	}
	
// >>>>>>>>>>>>>>>>>>>>>> ID=0x231	<<<<<<<<<<<<<<<<<
	//Byte0
	if(VarGpsLockWork_A)
	{
		VarSendDataID231[0] |= 1<<0;//bit0 A����״̬(ʵ������)
	}
	if(VarGpsLockWork_B)
	{
		VarSendDataID231[0] |= 1<<1;//bit1 B����״̬(ʵ������)
	}
	if(VarGpsLockWork_C)
	{
		VarSendDataID231[0] |= 1<<2;//bit2 C����״̬(ʵ������)
	}
	if(VarGpsLockWork_D)
	{
		VarSendDataID231[0] |= 1<<3;//bit3 D����״̬(ʵ������)
	}
	if(VarGpsLockState_A)
	{
		VarSendDataID231[0] |= 1<<5;//bit5 A����ָ��״̬(�յ�����ָ���)
	}
	if(VarGpsLockState_B)
	{
		VarSendDataID231[0] |= 1<<6;//bit6 B����ָ��״̬(�յ�����ָ���)
	}
	if(VarGpsLockState_C)
	{
		VarSendDataID231[0] |= 1<<7;//bit7 C����ָ��״̬(�յ�����ָ���)
	}
	//Byte1
	if(VarGpsLockState_D)
	{
		VarSendDataID231[1] |= 1<<0;//bit0 D����ָ��״̬(�յ�����ָ���)
	}
	//Byte2
	if( VarCan2MonthLockState )
	{
		VarSendDataID231[2] |= 0x01; //bit0 G005 ä������
	}
	if( VarCanUncoverLockState )
	{
		VarSendDataID231[2] |= 0x02; //bit1 G007 �������
	}
	if( VarCanBusLockState )
	{
		VarSendDataID231[2] |= 0x04; //bit2 G008 ��������
	}
	if( VarGpsSIMCardError )
	{
		VarSendDataID231[2] |= 0x08; //bit3 G009 SIM������
	}
	if( VarCanAntennaCutLockState )
	{
		VarSendDataID231[2] |= 0x10; //bit4 G006 ���߶Ͽ�����
	}
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x233	<<<<<<<<<<<<<<<<<
	temp_uchar = FunSystemPasswordComput(4,&Password_1,VarEngineWorkTime1H,VarEngineWorkTime1M,VarCanExcavatorId);
	if(temp_uchar==0)
	{
		VarMonitorPassword = Password_1;
	}
	//byte2~4:�û���������
	VarSendDataID233[0] = (UINT8)(VarMonitorPassword>>16);
	VarSendDataID233[1] = (UINT8)(VarMonitorPassword>>8);
	VarSendDataID233[2] = (UINT8)(VarMonitorPassword); 
	
	//�������汾��ϢSWCV-ABC-DE-FGH
	//ABC-222
	temp_uint16 = DefExcavatorEngineType*100+DefineHardwareVersion;//A:2-���緢����
	VarSendDataID233[3] = (UINT8)(temp_uint16>>8);     //Ӳ���汾BC��22-sw������2��
	VarSendDataID233[4] = (UINT8)temp_uint16;
	//DE
	VarSendDataID233[5] = (UINT8)VarCMCommunicationVersion; //ͨѶЭ��汾��
	//FGH 
	VarSendDataID233[6] = (UINT8)(DefineSoftVersion>>8);     //��������汾    
	VarSendDataID233[7] = (UINT8)DefineSoftVersion;
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x2F1	<<<<<<<<<<<<<<<<<
	if (GPSUnLockStep==1)
	{
		VarSendDataID2F1[0] = SignalNumber_2F1;
		VarSendDataID2F1[1] = OderType_2F1;
		VarSendDataID2F1[2] = (UINT8)(DynamicCode_H>>16);
		VarSendDataID2F1[3] = (UINT8)(DynamicCode_H>>8);
		VarSendDataID2F1[4] = (UINT8)(DynamicCode_H); 
		VarSendDataID2F1[5] = (UINT8)(DynamicCode_L>>16);
		VarSendDataID2F1[6] = (UINT8)(DynamicCode_L>>8);
		VarSendDataID2F1[7] = (UINT8)(DynamicCode_L); 
	}
	else if(GPSUnLockStep==3)
	{
		VarSendDataID2F1[0] = SignalNumber_2F1;
		VarSendDataID2F1[1] = OderType_2F1;
		VarSendDataID2F1[2] = GPSPSDVerify;
	}
	
	//������ʾ ID236
	if(VarAirPressureLowFlag>0)//��������ѹ�ͱ���
	{
		VarSendDataID236[0] |= (UINT8)1<<0;  //bit0	
	}
	
    if(VarPAccumPressureSensorEorror>0) 
	{
		VarSendDataID236[0] |= (UINT8)1<<1; // bit1  ac.pre error ������ѹ������������
	}
	
	if(VarPAccumAirSensorError>0)
	{
		VarSendDataID236[0] |= (UINT8)1<<2;  //bit2	atoms.pre error //��������ѹѹ������������	
	}
	
	VarSendDataID236[0] |= (UINT8)0<<3;  //bit3	��תѹ��1����������	
	VarSendDataID236[0] |= (UINT8)0<<4;  //bit4	��תѹ��2����������
	
    if(VarCartridgeValveFaultFlag>0) //��װ������
    {
    	VarSendDataID236[0] |= (UINT8)1<<5; // bit0 Error
    }
    VarSendDataID236[0] |= (UINT8)0<<6;  //DT1 Error	
    VarSendDataID236[0] |= (UINT8)0<<7;  //DT2 Error
    
    VarSendDataID236[1]=0;//DT3-DT10 Error
    
    VarSendDataID236[2] |= (UINT8)0; //DT11 Error
    VarSendDataID236[2] |= (UINT8)0<<1; //DT12 Error
	if((VarBoomDownPressureSensorEorror>0) ||(VarBoomSmallPressureSensorEorror>0) ) 
	{
		VarSendDataID236[2] |= (UINT8)1<<2; //�ȵ�ѹ�����ع���
	}
	
	
	//������ʾ ID237
    VarSendDataID237[0] = VarBoomWorkModeNow;//���۽��ܿ��ƣ�1-9��ģʽ
	if(VarBoomPowerSaveFlag>0) 
	{
		VarSendDataID237[1] |= (UINT8)1;//bit0 b.mode����ֵ 
	}
	if(VarRatatorPowerSaveFlag>0) 
	{
		VarSendDataID237[1] |= (UINT8)1<<1;//bit1 R.mode����ֵ
	}
	if(VarXieYaFlag>0) 
	{
		VarSendDataID237[1] |= (UINT8)1<<2;//bit2 AC.decompre����ֵ
	}

	if(VarPAiBoomUpPressure>5)
	{
		VarSendDataID237[1] |= (UINT8)(1<<3);  //bit3	//���㶯�������ȵ�ѹ�����أ�����0.5MpaΪ����
	}
  
	if(VarPAiBoomDownPressure>5)
	{
		VarSendDataID237[1] |= (UINT8)(1<<4);  //bit4	//���㶯���½��ȵ�ѹ�����أ�����0.5MpaΪ����
	}
	
	if( VarDoDT1>0)
	{
		VarSendDataID237[1] |= (UINT8)(1<<5);  //bit7	DT1
	}
	   	
	if(VarDoDT2>0) 
	{
		VarSendDataID237[1] |= (UINT8)(1<<6); // bit0 DT2
	}
	
	if(VarDoDT5>0) 
	{
		VarSendDataID237[2] |= (UINT8)1; //bit0 DT5
	}
	
	if(VarDoDT7>0)
	{
		VarSendDataID237[2] |= (UINT8)(1<<1);  //bit1 DT7	
	}
	
	if(VarDoDT6>0)
	{
		VarSendDataID237[2] |= (UINT8)(1<<2);  //bit2 DT6
	}
	
	if(VarDoDT3>0) 
	{
		VarSendDataID237[2] |= (UINT8)1<<3; // bit3 DT3
	}
	
	if(VarDoDT4>0) 
	{
		VarSendDataID237[2] |= (UINT8)1<<4; //bit4 DT4
	}
  
	if(VarDoDT9>0)
	{
		VarSendDataID237[2] |= (UINT8)(1<<5);  //bit5 DT9
	}
	
	VarSendDataID237[2] |= (UINT8)(0<<6);  //bit6 DT10

	if(VarPAiBoomUpPressure>5 || VarPAiBoomDownPressure>5)
	{
		VarSendDataID237[2] |= (UINT8)(1<<7);  //bit7 �ȵ�ѹ������	
	}
  
	//������ʾ ID238
 	VarSendDataID238[0] = (UINT8)(VarPAccumPressureFilter>>8 );//pin19,������ѹ��ֵ��λbar
 	VarSendDataID238[1] = (UINT8)((VarPAccumPressureFilter));  

 	VarSendDataID238[2] = (UINT8)(VarPAccumAirPressureBar>>8 );//��������ѹѹ������λbar
 	VarSendDataID238[3] = (UINT8)((VarPAccumAirPressureBar));  
 	
 	VarSendDataID238[4] = 0;//��תѹ��1
 	VarSendDataID238[5] = 0; 
 	
 	VarSendDataID238[6] = 0;//��תѹ��2
 	VarSendDataID238[7] = 0; 
 	
	//������ʾ ID239
 	VarSendDataID239[0] = (UINT8)(VarDoDT8>>8  );//DT8��������ֵVarValveDT8CurrentNow
    VarSendDataID239[1] = (UINT8)((VarDoDT8));
    
 	VarSendDataID239[2] = 0; //DT11����ֵ
    VarSendDataID239[3] = 0;
    
 	VarSendDataID239[4] = 0; //DT12����ֵ
    VarSendDataID239[5] = 0;
	
/**************************************************************
**���������ݷ�����GPS
**���ģʽ�����ֽ���ǰ�����ֽ��ں�	
**************************************************************/	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x2E1	<<<<<<<<<<<<<<<<<
	//Զ��ƽ̨Ӧ��byte0-1��Ӧ��ID��byte2-3��Ӧ����ϢSN

	if(LibCan0ReceiveFlag(26))
	{
		VarSendDataID2E1[0] = (UINT8)(0x323>>8);
		VarSendDataID2E1[1] = (UINT8)(0x323);
		VarSendDataID2E1[2] = (UINT8)(SignalNumber_2E1>>8);
		VarSendDataID2E1[3] = (UINT8)(SignalNumber_2E1);
	}
	else if(LibCan0ReceiveFlag(25))
	{
		VarSendDataID2E1[0] = (UINT8)(0x322>>8);
		VarSendDataID2E1[1] = (UINT8)(0x322);
		VarSendDataID2E1[2] = (UINT8)(SignalNumber_2E1>>8);
		VarSendDataID2E1[3] = (UINT8)(SignalNumber_2E1);
	}
	else if(LibCan0ReceiveFlag(24))
	{
		VarSendDataID2E1[0] = (UINT8)(0x321>>8);
		VarSendDataID2E1[1] = (UINT8)(0x321);
		VarSendDataID2E1[2] = (UINT8)(SignalNumber_2E1>>8);
		VarSendDataID2E1[3] = (UINT8)(SignalNumber_2E1);
	}

	// >>>>>>>>>>>>>>>>>>>>>> ID=0x2F0	<<<<<<<<<<<<<<<<<
	VarSendDataID2F0[0] = VarFuelVolumeFilter; //ȼ����λ��0-100.0xFF��ʾ��Ч����λ%
	VarSendDataID2F0[1] = 255;//���٣�0xFF��ʾ��Ч����λ0.1km/h
	VarSendDataID2F0[2] = 255;
/**************************************************************
**���������ݷ�������¼��
**С��ģʽ	
**************************************************************/		
	//Can���߼�¼��ֵ��ʼ��Ϊ��
	for(i=0;i<8;i++)
	{
		VarCanSendCanF11[i] = 0;
		VarCanSendCanF12[i] = 0;
		VarCanSendCanF13[i] = 0;
		VarCanSendCanF14[i] = 0;
		VarCanSendCanF15[i] = 0;
		
	}
	//0x511
	VarCanSendCanF11[0] = (UINT8)(VarPAiBoomUpPressure); 
	VarCanSendCanF11[1] = (UINT8)(VarPAiBoomUpPressure>>8);//�����ȵ�ѹ��
	VarCanSendCanF11[2] = (UINT8)(VarPAiBoomDownPressure);   //��λbar
	VarCanSendCanF11[3] = (UINT8)(VarPAiBoomDownPressure>>8);	//�½��ȵ�ѹ��
	VarCanSendCanF11[4] = (UINT8)VarPAccumPressureFilter;
	VarCanSendCanF11[5] = (UINT8)(VarPAccumPressureFilter>>8);	//��������ѹ
	VarCanSendCanF11[6] = (UINT8)(VarPAccumAirPressureBar); //  ��������ѹ
	VarCanSendCanF11[7] = (UINT8)(VarPAccumAirPressureBar>>8);
	//0x512
	VarCanSendCanF12[0] = (UINT8)(VarDoDT1); 
	VarCanSendCanF12[1] = (UINT8)(VarDoDT2);
	VarCanSendCanF12[2] = (UINT8)(VarDoDT3);   
	VarCanSendCanF12[3] = (UINT8)(VarDoDT4);	
	VarCanSendCanF12[4] = (UINT8)(VarDoDT5);
	VarCanSendCanF12[5] = (UINT8)(VarDoDT6);	
	VarCanSendCanF12[6] = (UINT8)(VarDoDT7);
	VarCanSendCanF12[7] = (UINT8)(VarDoDT8);

	//
	//0x513

	VarCanSendCanF13[0] = (UINT8)(VarBoomBigPressureBar); 
	VarCanSendCanF13[1] = (UINT8)(VarBoomBigPressureBar>>8);//���۴�ǻ
	VarCanSendCanF13[2] = (UINT8)(VarBoomSmallPressureBar);   
	VarCanSendCanF13[3] = (UINT8)(VarBoomSmallPressureBar>>8);	//����Сǻ
	VarCanSendCanF13[4] = (UINT8)(VarPBucketArmPressure);
	VarCanSendCanF13[5] = (UINT8)(VarPBucketArmPressure>>8);	//���˴�ǻ
	VarCanSendCanF13[6] = (UINT8)(VarPBucketArmRodPressure);
	VarCanSendCanF13[7] = (UINT8)(VarPBucketArmRodPressure>>8);//����Сǻ
	
	//ox514
	
	VarCanSendCanF14[0] = (UINT8)(VarBoomWorkModeNow); //����ģʽ
	VarCanSendCanF14[1] = (UINT8)(0);
	VarCanSendCanF14[2] = (UINT8)(VarEngineSpeedNow);   
	VarCanSendCanF14[3] = (UINT8)(VarEngineSpeedNow>>8);	//������ת��
	VarCanSendCanF14[4] = (UINT8)(VarP1PressureFilter);
	VarCanSendCanF14[5] = (UINT8)(VarP1PressureFilter>>8);	//P1
	VarCanSendCanF14[6] = (UINT8)(VarP2PressureFilter);
	VarCanSendCanF14[7] = (UINT8)(VarP2PressureFilter>>8);//P2
	
	//0x515
	VarCanSendCanF15[0] = (UINT8)(VarPBucCapPressure); //������ǻѹ��
	VarCanSendCanF15[1] = (UINT8)(VarPBucCapPressure>>8);//
	VarCanSendCanF15[2] = (UINT8)(VarDiTreadPre);   //����ѹ������
	VarCanSendCanF15[3] = (UINT8)(0);	//
	VarCanSendCanF15[4] = (UINT8)(VarRecDataID_0x18FFF800[3]-125);//������Ť�ذٷֱ�
	VarCanSendCanF15[5] = (UINT8)(0);	//
	VarCanSendCanF15[6] = (UINT8)(VarRecDataID_0x18FEF200[0]);//��ʱ����˲ʱ�ͺ�
	VarCanSendCanF15[7] = (UINT8)(VarRecDataID_0x18FEF200[1]);//
	
	//0x516
	VarCanSendCanF16[0] = (UINT8)(VarRecDataID_0x18FEE900[4]); //��ʮ�巢�����ۼ��ͺģ���λ��0.5L�����ֽ�
	VarCanSendCanF16[1] = (UINT8)(VarRecDataID_0x18FEE900[5]);//
	VarCanSendCanF16[2] = (UINT8)(VarRecDataID_0x18FEE900[6]);   //
	VarCanSendCanF16[3] = (UINT8)(VarRecDataID_0x18FEE900[7]);	//��ʮ�巢�����ۼ��ͺģ���λ��0.5L�����ֽ�
	VarCanSendCanF16[4] = (UINT8)(0);//
	VarCanSendCanF16[5] = (UINT8)(0);	//
	VarCanSendCanF16[6] = (UINT8)(0);
	VarCanSendCanF16[7] = (UINT8)(0);//
	
}
	
/**************************************************************
**��������FunCanDisplaySendData()
**����������������������ʾ����GPS
**�����������
**�����������
**************************************************************/
void FunCanDisplayGpsSendData(void)
{	
	//CAN0���ݷ�����GPS����ʾ�� 311��312
	if(LibTimer(1,1,20,1))
	{
		VarCanSendDataGpsStep++;
		switch(VarCanSendDataGpsStep)
		{
			case 1:
				LibCan0SendData(14,0x200,0,VarSendDataID200,8);
				break;
			case 2:
				LibCan0SendData(14,0x201,0,VarSendDataID201,8);
				break;
			case 3:
				LibCan0SendData(14,0x203,0,VarSendDataID203,8);
				break;
			case 4:
				LibCan0SendData(14,0x209,0,VarSendDataID209,8);
				break;
			case 5:
				LibCan0SendData(14,0x20A,0,VarSendDataID20A,8);
				break;
			case 6:
				LibCan0SendData(14,0x20C,0,VarSendDataID20C,8);
				break;				
			case 7:
				LibCan0SendData(14,0x20D,0,VarSendDataID20D,8);
				break;
			case 8:
				LibCan0SendData(14,0x20E,0,VarSendDataID20E,8);
				break;
			case 9:
				LibCan0SendData(14,0x20F,0,VarSendDataID20F,8);
				break;
			case 10:
				LibCan0SendData(14,0x210,0,VarSendDataID210,8);
				break;
			case 11:
				LibCan0SendData(14,0x211,0,VarSendDataID211,8);
				break;
			case 12:
				LibCan0SendData(14,0x212,0,VarSendDataID212,8);
				break;			
			case 13:
				LibCan0SendData(14,0x215,0,VarSendDataID215,8);
				break;
			case 14:
				LibCan0SendData(14,0x216,0,VarSendDataID216,8);
				break;
			case 15:
				LibCan0SendData(14,0x217,0,VarSendDataID217,8);
				break;
			case 16:
				LibCan0SendData(14,0x218,0,VarSendDataID218,8);
				break;
			case 17:
				LibCan0SendData(14,0x21E,0,VarSendDataID21E,8);
				break;
			case 18:
				LibCan0SendData(14,0x220,0,VarSendDataID220,8);
				break;
			case 19:
				LibCan0SendData(14,0x221,0,VarSendDataID221,8);
				break;
			case 20:
				LibCan0SendData(14,0x222,0,VarSendDataID222,8);
				break;
			case 21:
				LibCan0SendData(14,0x224,0,VarSendDataID224,8);
				break;
			case 22:
				LibCan0SendData(14,0x227,0,VarSendDataID227,8);
				break;
			case 23:
				LibCan0SendData(14,0x22F,0,VarSendDataID22F,8);
				break;
			case 24:
				LibCan0SendData(14,0x231,0,VarSendDataID231,8);
				break;
			case 25:
				LibCan0SendData(14,0x233,0,VarSendDataID233,8);
				break;
			case 26:
				LibCan0SendData(14,0x236,0,VarSendDataID236,8);
				break;
			case 27:
				LibCan0SendData(14,0x237,0,VarSendDataID237,8);
				break;
			case 28:
				LibCan0SendData(14,0x238,0,VarSendDataID238,8);
				break;
			case 29:
				LibCan0SendData(14,0x239,0,VarSendDataID239,8);
				break;
			case 30:
				if (GPSUnLockStep==1 || GPSUnLockStep==3)
				{
					LibCan0SendData(14,0x2F1,0,VarSendDataID2F1,8);
				}
				break;
			default:
				VarCanSendDataGpsStep=0;
				break;
		}
	}
	


	//CAN0���ݷ���GPS	 311��312
	if(LibTimer(4,1,30,1))
	{
		VarCanSendGpsStep++;
		switch(VarCanSendGpsStep)
		{
			case 1:
				LibCan0SendData(14,0x2E1,0,VarSendDataID2E1,8);
				break;
			case 2:
				LibCan0SendData(14,0x2F0,0,VarSendDataID2F0,8);
				break;
			default:
				VarCanSendGpsStep=0;
				break;
		}
	}

	//CAN���ݷ�����CAN�������
//	if(LibTimer(17,1,20,1))
//	{
//		LibCan1SendData(13,0x19B,0,VarSendDataID19B,8);
//	}
	

	//can0���ݷ����ݼ�¼�� 311��312
	if(LibTimer(14,1,10,1))
	{
		VarCanSendCanSaveStep++;
		switch(VarCanSendCanSaveStep)
		{
			case 1:
				LibCan0SendData(11,0x511,0,VarCanSendCanF11,8);
				break;
			case 2:
				LibCan0SendData(11,0x512,0,VarCanSendCanF12,8);
				break;
			case 3:
				LibCan0SendData(11,0x513,0,VarCanSendCanF13,8);
				break;
			case 4:
				LibCan0SendData(11,0x514,0,VarCanSendCanF14,8);
				break;
			case 5:
				LibCan0SendData(11,0x515,0,VarCanSendCanF15,8);
				break;
			case 6:
				LibCan0SendData(11,0x516,0,VarCanSendCanF16,8);
				break;
			default:
				VarCanSendCanSaveStep=0;
				break;	
		}
	}

		
		
		/*LibCan0SendData(32,0x511,0,VarCanSendCanF11,8);
		LibCan0SendData(33,0x512,0,VarCanSendCanF12,8);
		LibCan0SendData(34,0x513,0,VarCanSendCanF13,8);
		LibCan0SendData(35,0x514,0,VarCanSendCanF14,8);
		LibCan0SendData(36,0x515,0,VarCanSendCanF15,8);
		LibCan0SendData(37,0x516,0,VarCanSendCanF16,8);
	}*/
		
}

