/*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\
		----flash��ַ��Χ 0~0x3FFF(��)-----
	ϵ ͳ �� ��:0x0000~0x07FF;
	Gps�������:0x0800~0x0FFF;
	�� �� ʱ ��:0x1000~0x17FF;
	����ʱ���ַ:0x1800~0x1FFF;
\*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\*/
#include "AppFun.h"
#include "AppVar.h"
#include "AppDefine.h"
#include "LibFunDefine.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**��������FunFlashLoop()
**����������Flash���ݵı���
**�����������
**�����������
**************************************************************/
void FunFlashLoop(void)
{
	//save data to flash
	FunFlashWriteData();
}
/**************************************************************
**��������FunFlashInit()
**������������ʼ��ʱ��Flash��ȡ����
**�����������
**�����������
**************************************************************/
void FunFlashInit(void)
{
	UINT8 i,Temp_8,error_1,error_2;
	UINT32 GetHourTime;
	//��ϵͳ����
	for(i=0;i<5;i++)
	{
		Temp_8=FunFlashReadSysData(0x0000,0x0400,&VarSysDataMasterCheckFlag,&VarSysDataBackupCheckFlag);
		if(Temp_8>0)
		{
			break;
		}
	}
	//��GPS�������
	for(i=0;i<5;i++)
	{
		Temp_8=	FunFlashReadGpsData(0x0800,0x0C00,&VarGpsDataMasterCheckFlag,&VarGpsDataBackupCheckFlag);
		if(Temp_8>0)
		{
			break;
		}
	}
	//������������Сʱ�Ƶ�ַ
	FunFlashReadEngineTimeAdr(VarFlashEngineTimeMasterAdrIndexDef,VarFlashEngineTimeBackupAdrIndexDef,&VarEngineTimeMasterCheckFlagIndex,&VarEngineTimeBackupCheckFlagIndex);
	//������������Сʱ
	for(i=0;i<5;i++)
	{
		error_1=FunFlashReadEngineWorkTime(VarFlashEngineTimeMasterAdr,VarFlashEngineTimeBackupAdr,&VarEngineTimeMasterCheckFlag,&VarEngineTimeBackupCheckFlag);
		if(error_1>0)
		{
			break;
		}
	}
	//��main������
	for(i=0;i<5;i++)
	{
		error_2=FunFlashReadEngineTimeMain(VarFlashHourMainAdrDef,&VarFlashHourMainAdrCheckFlag,&GetHourTime);
		if(error_2>0)
		{
			break;
		}
	}
	//���洢���뱸�ݴ洢����������ȡmain������ʱ��
	if((error_1==0)&&(error_2>0))
	{
		VarEngineWorkTime1H = GetHourTime;
	}
	//��ȡ����ת��ֵ
		VarEngineLevelSpeed[0] = DefineEngineSpeedSet0;
		VarEngineLevelSpeed[1] = DefineEngineSpeedSet1;
		VarEngineLevelSpeed[2] = DefineEngineSpeedSet2;
		VarEngineLevelSpeed[3] = DefineEngineSpeedSet3;
		VarEngineLevelSpeed[4] = DefineEngineSpeedSet4;
		VarEngineLevelSpeed[5] = DefineEngineSpeedSet5;
		VarEngineLevelSpeed[6] = DefineEngineSpeedSet6;
		VarEngineLevelSpeed[7] = DefineEngineSpeedSet7;
		VarEngineLevelSpeed[8] = DefineEngineSpeedSet8;
		VarEngineLevelSpeed[9] = DefineEngineSpeedSet9;
		VarEngineLevelSpeed[10] = DefineEngineSpeedSet10;
}
/**************************************************************
**��������FunFlashWriteData()
**������������Flashд������
**�����������
**�����������
**************************************************************/
void FunFlashWriteData(void)
{
	//����ϵͳ����
	FunFlashWriteSysDataCommand(0);
	FunFlashWriteSysDataCommand(1);
	//����GPS�������
	FunFlashWriteGpsDataCommand(0);
	FunFlashWriteGpsDataCommand(1);
	//����Сʱ��
	FunFlashWriteWorkTimeCommand(0);
	FunFlashWriteWorkTimeCommand(1);
	//����Сʱ�����ݵ�ַ����
	FunFlashWtiteWorkTimeAdrCommand(0);
	FunFlashWtiteWorkTimeAdrCommand(1);
	//����Сʱ��main����
	FunFlashWriteWorkTimeHourMainCommand();
}
/**************************************************************
**��������FunFlashWriteSysDataCommand()
**������������Flashд��ϵͳ��������:0x0000~0x7FFF
**���������Sort=0:д�����洢����Sort=1:д�뱸�ݴ洢����
**�����������
**************************************************************/
void FunFlashWriteSysDataCommand(UINT8 Sort)
{
	UINT8 i,Temp_Confirm=0;
	if(Sort==0)//д���洢������,��ַ:0x0000~0x03FF
	{
		if(VarFlashSysDateMasterNeedSaveFlag>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteSysData(0x0000,&VarSysDataMasterCheckFlag);
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashSysDateMasterNeedSaveFlag=0;	
		}
	}
	//д���ݴ洢������,��ַ:0x0400~0x07FF
	else if(Sort==1)
	{
		if(VarFlashSysDateBackupNeedSaveFlag>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteSysData(0x0400,&VarSysDataBackupCheckFlag);
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashSysDateBackupNeedSaveFlag=0;	
		}
	}	
}
/**************************************************************
**��������FunFlashWriteSysData()
**������������Flash��д��ϵͳ���������洢��:0x0000~03FF;���ݴ洢��:0x0400~07FF
**�����������
**�����������
**************************************************************/
UINT8 FunFlashWriteSysData(UINT16 DataAdrStart,UINT16 *Check_Flag)
{
	UINT8 Temp_8;
	UINT16 i,WRITE_DATA[30];
	UINT16 Adress_Ini,Temp_16=0;
	UINT32 Temp_32=0;
	
	if((*Check_Flag)<65535) (*Check_Flag)++;
		else (*Check_Flag)=0;

	WRITE_DATA[0] = (*Check_Flag);
	WRITE_DATA[1] = VarSysParaDataSort_ID;
	//����
	WRITE_DATA[2] = VarPumpPowerParameter[0];
	WRITE_DATA[3] = VarPumpPowerParameter[1];
	WRITE_DATA[4] = VarPumpPowerParameter[2];
	WRITE_DATA[5] = VarPumpPowerParameter[3];
	WRITE_DATA[6] = VarPumpPowerParameter[4];
	WRITE_DATA[7] = VarPumpPowerParameter[5];
	WRITE_DATA[8] = VarPumpPowerParameter[6];
	WRITE_DATA[9] = VarPumpPowerParameter[7];		
	WRITE_DATA[10] = VarExcavatorMonitorType;		
	WRITE_DATA[11] = VarCMCommunicationVersion;
	WRITE_DATA[12] = VarCanHighlandMode;
	WRITE_DATA[13] = VarAccDialPosiMin;
	WRITE_DATA[14] = VarAccDialPosiMax;
	WRITE_DATA[15] = VarCanExcavatorId;
	WRITE_DATA[16] = VarCanExcavatorType;
	WRITE_DATA[17] = VarExcavatorEngineType;
	WRITE_DATA[18] = VarBoomPowerSaveFlag;//���۽���ģʽ,��ת����ģʽ,������йѹģʽ
	WRITE_DATA[19] = VarRatatorPowerSaveFlag;
	WRITE_DATA[20] = VarXieYaFlag;
	WRITE_DATA[21] = 0;	
	
	Temp_32=0;
	for(i=2;i<22;i++)
	{
		Temp_32 +=WRITE_DATA[i];
	}
	WRITE_DATA[22] = (UINT16)Temp_32;
	WRITE_DATA[23] = (UINT16)(Temp_32>>16);
	WRITE_DATA[24] = (*Check_Flag);
	//���ݱ���
	Adress_Ini = DataAdrStart;
	Temp_8=LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],25);
	if(Temp_8>0) //У����ȷ������ɹ�
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**��������FunFlashReadSysData()
**������������Flash��ȡϵͳ��������
**�����������
**�����������
**************************************************************/
UINT8 FunFlashReadSysData(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
		UINT16 ReadMasterData[30],ReadBackupData[30];
		UINT16 i,Data_Ini;
		UINT32 Temp_32;
		UINT8 FlashMasterReadError,FlashBackupReadError;
		//У�����洢��������
		Data_Ini= SysMasterAdr_Start;
		LibFlashGetBlock(Data_Ini,&ReadMasterData[0],25);
		Temp_32=0;
		for(i=2;i<22;i++)
		{
			Temp_32 += ReadMasterData[i];
		}
		if( (ReadMasterData[0] != ReadMasterData[24])||
	    	(ReadMasterData[1] !=VarSysParaDataSort_ID)||
	    	(Temp_32 != FunGetTwoWord(ReadMasterData[22],ReadMasterData[23]))
	      )
	    	{
	    		FlashMasterReadError=1;//�����ݶ�ȡ����
	    	}
	    else
	    	{
	    		FlashMasterReadError=0;//�����ݶ�ȡ��ȷ
	    	}
		//У�鱸�ݴ洢��������
		Data_Ini= SysBackupAdr_Start;
		LibFlashGetBlock(Data_Ini,&ReadBackupData[0],25);
		Temp_32=0;
		for(i=2;i<22;i++)
		{
			Temp_32 += ReadBackupData[i];
		}
		if( (ReadBackupData[0] != ReadBackupData[24])||
	    	(ReadBackupData[1] !=VarSysParaDataSort_ID)||
	    	(Temp_32 != FunGetTwoWord(ReadBackupData[22],ReadBackupData[23]))
	      )
	    	{
	    		FlashBackupReadError=1;//�����ݶ�ȡ����
	    	}
	    else
	    	{
	    		FlashBackupReadError=0;//�����ݶ�ȡ��ȷ
	    	}
		//�����洢��������
		if(FlashMasterReadError==0)
		{					
			VarPumpPowerParameter[0] = (UINT8)ReadMasterData[2];
			VarPumpPowerParameter[1] = (UINT8)ReadMasterData[3];
			VarPumpPowerParameter[2] = (UINT8)ReadMasterData[4];
			VarPumpPowerParameter[3] = (UINT8)ReadMasterData[5];
			VarPumpPowerParameter[4] = (UINT8)ReadMasterData[6];
			VarPumpPowerParameter[5] = (UINT8)ReadMasterData[7];
			VarPumpPowerParameter[6] = (UINT8)ReadMasterData[8];
			VarPumpPowerParameter[7] = (UINT8)ReadMasterData[9];
			VarExcavatorMonitorType = (UINT8)ReadMasterData[10];
			VarCMCommunicationVersion = (UINT8)ReadMasterData[11];
			VarCanHighlandMode = (UINT8)ReadMasterData[12];
			VarAccDialPosiMin = ReadMasterData[13];
			VarAccDialPosiMax = ReadMasterData[14];
			VarCanExcavatorId = ReadMasterData[15];
			VarCanExcavatorType =ReadMasterData[16];
			VarExcavatorEngineType = (UINT8)ReadMasterData[17];
			
			VarBoomPowerSaveFlag=ReadMasterData[18];//���۽���ģʽ,��ת����ģʽ,������йѹģʽ
			VarRatatorPowerSaveFlag=ReadMasterData[19];
			VarXieYaFlag=ReadMasterData[20];
			
			(*MasterCheck_Flag) = ReadMasterData[0];
			return 1;

		}
		//�����ݴ洢��������
		else if(FlashBackupReadError == 0)
		{		
			VarPumpPowerParameter[0] = (UINT8)ReadBackupData[2];
			VarPumpPowerParameter[1] = (UINT8)ReadBackupData[3];
			VarPumpPowerParameter[2] = (UINT8)ReadBackupData[4];
			VarPumpPowerParameter[3] = (UINT8)ReadBackupData[5];
			VarPumpPowerParameter[4] = (UINT8)ReadBackupData[6];
			VarPumpPowerParameter[5] = (UINT8)ReadBackupData[7];
			VarPumpPowerParameter[6] = (UINT8)ReadBackupData[8];
			VarPumpPowerParameter[7] = (UINT8)ReadBackupData[9];
			VarExcavatorMonitorType = (UINT8)ReadBackupData[10];
			VarCMCommunicationVersion = (UINT8)ReadBackupData[11];
			VarCanHighlandMode = (UINT8)ReadBackupData[12];
			VarAccDialPosiMin = ReadBackupData[13];
			VarAccDialPosiMax = ReadBackupData[14];
			VarCanExcavatorId = ReadBackupData[15];
			VarCanExcavatorType =ReadBackupData[16];
			VarExcavatorEngineType = (UINT8)ReadBackupData[17];
			
			VarBoomPowerSaveFlag=ReadBackupData[18];//���۽���ģʽ,��ת����ģʽ,������йѹģʽ
			VarRatatorPowerSaveFlag=ReadBackupData[19];
			VarXieYaFlag=ReadBackupData[20];
			
			(*BackupCheck_Flag) = ReadBackupData[0];
			return 1;
		}
		// ���洢�����󣬼���Ĭ��ֵ
		else
		{
			VarAccDialPosiMin = 1560;
			VarAccDialPosiMax = 3200;
			VarCanExcavatorId =0;
			VarCanExcavatorType=316;//470��Ӧ�ͺ�Ϊ316
			VarPumpPowerParameter[0] = 5;
			VarPumpPowerParameter[1] = 5;
			VarPumpPowerParameter[2] = 5;
			VarPumpPowerParameter[3] = 5;
			VarPumpPowerParameter[4] = 5;
			VarPumpPowerParameter[5] = 5;
			VarPumpPowerParameter[6] = 5;
			VarPumpPowerParameter[7] = 5;
			VarExcavatorMonitorType = 4;//Ĭ��SW��ʾ��
			VarCMCommunicationVersion = 6;//Ĭ��05��ͨѶЭ��汾05
			VarCanHighlandMode = 0;//Ĭ�ϷǸ�ԭģʽ
			VarExcavatorEngineType = 0;//Ĭ��CUMMINS������
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
			(*MasterCheck_Flag) =0;
			(*BackupCheck_Flag) = 0;
			return 0;
		}
		
}
/**************************************************************
**��������FunFlashWriteGpsDate()
**��������������GPS�������:0x0800~0x0FFF
**�����������
**�����������
**************************************************************/
UINT8 FunFlashWriteGpsData(UINT16 DataAdrStart,UINT16 *Check_Flag)
{
	UINT8 Temp_8;
	UINT16 i,WRITE_DATA[30];
	UINT16 Adress_Ini,Temp_16=0;
	UINT32 Temp_32=0;

	if((*Check_Flag)<65535) (*Check_Flag)++;
	else (*Check_Flag)=0;

	WRITE_DATA[0] = (*Check_Flag);
	WRITE_DATA[1] = VarGpsParaDataSort_ID;

	//����
	WRITE_DATA[2] = VarGpsLockState_A;
	WRITE_DATA[3] = VarGpsLockState_B;
	WRITE_DATA[4] = VarGpsLockState_C;
	WRITE_DATA[5] = VarGpsLockState_D;
	WRITE_DATA[6] = VarCanGpsUrgencyState;
	WRITE_DATA[7] = VarCanGpsCancel;
	WRITE_DATA[8] = VarCanGpsLockCommand_A;
	WRITE_DATA[9] = VarCanGpsLockCommand_B;
	WRITE_DATA[10] = VarCanGpsLockCommand_C;
	WRITE_DATA[11] = VarCanGpsLockCommand_D;
	
	WRITE_DATA[12] = (UINT8)GPSLock_All_Enable ;
	WRITE_DATA[13] = (UINT8)GPSLock_Passive_Enable ;
	WRITE_DATA[14] = (UINT8)MonthNoSignalLock_Enable ;
	WRITE_DATA[15] = (UINT8)UncoverLock_Enable ;
	WRITE_DATA[16] = (UINT8)CANSignalLostLock_Enable ;
	WRITE_DATA[17] = (UINT8)SIMCardLostLock_Enable ;
	
	WRITE_DATA[18] = (UINT8)VarCan2MonthLockState;
	WRITE_DATA[19] = NoSignalStart_Year;
	WRITE_DATA[20] = NoSignalStart_Month;
	WRITE_DATA[21] = NoSignalStart_Day;
	
	WRITE_DATA[22] = EmergencyStart_Year;
	WRITE_DATA[23] = EmergencyStart_Month;
	WRITE_DATA[24] = EmergencyStart_Day;
	WRITE_DATA[25] = EmergencyStart_Hour;
	
	WRITE_DATA[26] = GPSLock_Enable_Initial;
	
	Temp_32 = 0;
	for(i=2;i<12;i++)
	{
		Temp_32 +=WRITE_DATA[i];
	}
	WRITE_DATA[12] = (UINT16)Temp_32;
	WRITE_DATA[13] = (UINT16)(Temp_32>>16);
	WRITE_DATA[14] = (*Check_Flag);
	//���ݱ���
	Adress_Ini = DataAdrStart;
	Temp_8=LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],15);
	if(Temp_8>0) //У����ȷ������ɹ�
		{ return 1;}
	else 
		{ return 0;}
}
/**************************************************************
**��������FunFlashWriteGpsDataCommand()
**��������������GPS�������:0x0800~0x0FFF
**�����������
**�����������
**************************************************************/
void FunFlashWriteGpsDataCommand(UINT8 Sort)
{
	UINT8 i,Temp_Confirm=0;
	if(Sort==0)//д���洢������,��ַ:0x0800~0x0BFF
	{
		if(VarFlashGpsDataMasterNeedSaveFlag>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteGpsData(0x0800,&VarGpsDataMasterCheckFlag);
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashGpsDataMasterNeedSaveFlag=0;	
		}
	}
	//д���ݴ洢������,��ַ:0x0C00~0x0FFF
	else if(Sort==1)
	{
		if(VarFlashGpsDataBackupNeedSaveFlag>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteGpsData(0x0C00,&VarGpsDataBackupCheckFlag);
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashGpsDataBackupNeedSaveFlag=0;	
		}
	}
}
/**************************************************************
**��������FunFlashReadGpsData()
**������������ȡGPS�������:0x0800~0x0FFF
**�����������
**�����������
**************************************************************/
UINT8 FunFlashReadGpsData(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
	UINT16 ReadMasterData[30],ReadBackupData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError,FlashBackupReadError;
	
	//У�����洢��������
	Data_Ini= SysMasterAdr_Start;
	//LibFlashGetBlock(Data_Ini,&ReadMasterData[0],15);
	LibFlashGetBlock(Data_Ini,&ReadMasterData[0],29);	
	Temp_32=0;
	//for(i=2;i<12;i++)
	for(i=2;i<26;i++)
	{
		Temp_32 += ReadMasterData[i];
	}
	/*
	if( (ReadMasterData[0] != ReadMasterData[14])||
    	(ReadMasterData[1] !=VarGpsParaDataSort_ID)||
    	(Temp_32 != FunGetTwoWord(ReadMasterData[12],ReadMasterData[13]))
      )
      */
    if( (ReadMasterData[0] != ReadMasterData[28])||
		(ReadMasterData[1] !=VarGpsParaDataSort_ID)||
		(Temp_32 != FunGetTwoWord(ReadMasterData[26],ReadMasterData[27]))
	  )
    	{
    		FlashMasterReadError=1;//�����ݶ�ȡ����
    	}
    else
    	{
    		FlashMasterReadError=0;//�����ݶ�ȡ��ȷ
    	}
	//У�鱸�ݴ洢��������
	Data_Ini= SysBackupAdr_Start;
	//LibFlashGetBlock(Data_Ini,&ReadBackupData[0],15);
	LibFlashGetBlock(Data_Ini,&ReadBackupData[0],29);
	Temp_32=0;
	//for(i=2;i<12;i++)
	for(i=2;i<26;i++)
	{
		Temp_32 += ReadBackupData[i];
	}
	/*if( (ReadBackupData[0] != ReadBackupData[14])||
    	(ReadBackupData[1] !=VarGpsParaDataSort_ID)||
    	(Temp_32 != FunGetTwoWord(ReadBackupData[12],ReadBackupData[13]))
      )
      */
    if( (ReadBackupData[0] != ReadBackupData[28])||
		(ReadBackupData[1] !=VarGpsParaDataSort_ID)||
		(Temp_32 != FunGetTwoWord(ReadBackupData[26],ReadBackupData[27]))
	  )
    	{
    		FlashBackupReadError=1;//�������ݶ�ȡ����
    	}
    else
    	{
    		FlashBackupReadError=0;//�������ݶ�ȡ��ȷ
    	}
	//��ȡ���洢������
	if(FlashMasterReadError==0)
	{
		VarGpsLockWork_A = (UINT8)ReadMasterData[2];
		VarGpsLockWork_B = (UINT8)ReadMasterData[3];
		VarGpsLockWork_C = (UINT8)ReadMasterData[4];
		VarGpsLockWork_D = (UINT8)ReadMasterData[5];
		VarCanGpsUrgencyState = (UINT8)ReadMasterData[6];
		VarCanGpsCancel = (UINT8)ReadMasterData[7];
		VarCanGpsLockCommand_A = (UINT8)ReadMasterData[8]; 
		VarCanGpsLockCommand_B = (UINT8)ReadMasterData[9]; 
		VarCanGpsLockCommand_C = (UINT8)ReadMasterData[10]; 
        VarCanGpsLockCommand_D = (UINT8)ReadMasterData[11]; 
        
        GPSLock_All_Enable = (UINT8)ReadMasterData[12];
		GPSLock_Passive_Enable = (UINT8)ReadMasterData[13];
		MonthNoSignalLock_Enable = (UINT8)ReadMasterData[14];
		UncoverLock_Enable = (UINT8)ReadMasterData[15];
		CANSignalLostLock_Enable = (UINT8)ReadMasterData[16];
		SIMCardLostLock_Enable = (UINT8)ReadMasterData[17];
		VarCan2MonthLockState = (UINT8)ReadMasterData[18];
		NoSignalStart_Year = (UINT8)ReadMasterData[19];
		NoSignalStart_Month = (UINT8)ReadMasterData[20];
		NoSignalStart_Day = (UINT8)ReadMasterData[21];
		
		EmergencyStart_Year = (UINT8)ReadMasterData[22];
		EmergencyStart_Month = (UINT8)ReadMasterData[23];
		EmergencyStart_Day = (UINT8)ReadMasterData[24];
		EmergencyStart_Hour = (UINT8)ReadMasterData[25];
		(*MasterCheck_Flag) = ReadMasterData[0];
		return 1;
	}
	//��ȡ���ݴ洢������
	else if(FlashBackupReadError==0)
	{
		
		VarGpsLockWork_A = (UINT8)ReadBackupData[2];
		VarGpsLockWork_B = (UINT8)ReadBackupData[3];
		VarGpsLockWork_C = (UINT8)ReadBackupData[4];
		VarGpsLockWork_D = (UINT8)ReadBackupData[5];
		VarCanGpsUrgencyState = (UINT8)ReadBackupData[6];
		VarCanGpsCancel = (UINT8)ReadBackupData[7];
		VarCanGpsLockCommand_A = (UINT8)ReadBackupData[8]; 
		VarCanGpsLockCommand_B = (UINT8)ReadBackupData[9]; 
		VarCanGpsLockCommand_C = (UINT8)ReadBackupData[10]; 
        VarCanGpsLockCommand_D = (UINT8)ReadBackupData[11]; 
        
        GPSLock_All_Enable = (UINT8)ReadBackupData[12];
		GPSLock_Passive_Enable = (UINT8)ReadBackupData[13];
		MonthNoSignalLock_Enable = (UINT8)ReadBackupData[14];
		UncoverLock_Enable = (UINT8)ReadBackupData[15];
		CANSignalLostLock_Enable = (UINT8)ReadBackupData[16];
		SIMCardLostLock_Enable = (UINT8)ReadBackupData[17];
		VarCan2MonthLockState = (UINT8)ReadBackupData[18];
		NoSignalStart_Year = (UINT8)ReadBackupData[19];
		NoSignalStart_Month = (UINT8)ReadBackupData[20];
		NoSignalStart_Day = (UINT8)ReadBackupData[21];
		
		EmergencyStart_Year = (UINT8)ReadBackupData[22];
		EmergencyStart_Month = (UINT8)ReadBackupData[23];
		EmergencyStart_Day = (UINT8)ReadBackupData[24];
		EmergencyStart_Hour = (UINT8)ReadBackupData[25];
		(*BackupCheck_Flag) = ReadBackupData[0];
		return 1;
	}
	//����Ĭ��ֵ
	else
	{
		VarGpsLockWork_A = 0;
		VarGpsLockWork_B = 0;
		VarGpsLockWork_C = 0;
		VarGpsLockWork_D = 0;
		VarCanGpsUrgencyState=0;
		VarCanGpsCancel=0;
		VarCanGpsLockCommand_A=0;
		VarCanGpsLockCommand_B=0;
		VarCanGpsLockCommand_C=0;
		VarCanGpsLockCommand_D=0;
		
	    GPSLock_All_Enable = 1;
		GPSLock_Passive_Enable = 1;
		MonthNoSignalLock_Enable = 1;
		UncoverLock_Enable = 1;
		CANSignalLostLock_Enable = 1;
		SIMCardLostLock_Enable = 1;
		VarCan2MonthLockState = 0;
		NoSignalStart_Year = 0;
		NoSignalStart_Month = 0;
		NoSignalStart_Day = 0;
		
		EmergencyStart_Year = 0;
		EmergencyStart_Month = 0;
		EmergencyStart_Day = 0;
		EmergencyStart_Hour = 0;
		(*MasterCheck_Flag) =0;
		(*BackupCheck_Flag) =0;
		return 0;
	}
}
/**************************************************************
**��������FunFlashWriteWorkTimeCommand()
**����������д����Сʱ��Flash,��ַ:0x1000~0x17FF
**���������0�����洢����1�����ݴ洢��
**���������
**************************************************************/
void FunFlashWriteWorkTimeCommand(UINT8 Sort)
{
	UINT8 i,Temp_Confirm=0;
	if(Sort==0)//д���洢������,��ַ:0x1000~0x13FF
	{
		if(VarFlashEngineWorkTimeMasterNeedSaveFlag>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteEngineWorkTimeData(VarFlashEngineTimeMasterAdr,&VarEngineTimeMasterCheckFlag);
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashEngineWorkTimeMasterNeedSaveFlag=0;	
			if(Temp_Confirm==0)//����ʧ��
			{
				VarFlashEngineTimeMasterAdr +=  0x000F;
				if( (VarFlashEngineTimeMasterAdr>VarFlashEngineTimeMasterAdrMax)||
				    (VarFlashEngineTimeMasterAdr<VarFlashEngineTimeMasterAdrDefault)
				  )
				  {
				  	VarFlashEngineTimeMasterAdr=VarFlashEngineTimeMasterAdrDefault;
				  }
				  VarFlashEngineWorkTimeMasterNeedSaveFlagIndex =1;//�洢��ַ�ı䣬��Ҫ����
				  VarFlashEngineWorkTimeMasterNeedSaveFlag =1;
			}
		}
	}
	//д���ݴ洢������,��ַ:0x1400~0x17FF
	else if(Sort==1)
	{
		if(VarFlashEngineWorkTimeBackupNeedSaveFlag>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteEngineWorkTimeData(VarFlashEngineTimeBackupAdr,&VarEngineTimeBackupCheckFlag);
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashEngineWorkTimeBackupNeedSaveFlag=0;	
			if(Temp_Confirm==0)
			{
			VarFlashEngineTimeBackupAdr +=  0x000F;
			if( (VarFlashEngineTimeBackupAdr>VarFlashEngineTimeBackupAdrMax)||
				(VarFlashEngineTimeBackupAdr<VarFlashEngineTimeBackupAdrDefault)
		      )
			{
				VarFlashEngineTimeBackupAdr=VarFlashEngineTimeBackupAdrDefault;
			}
				VarFlashEngineWorkTimeBackupNeedSaveFlagIndex =1;
				VarFlashEngineWorkTimeBackupNeedSaveFlag =1;
			}
		}
	}
}
/**************************************************************
**��������FunFlashWriteEngineWorkTimeData()
**�������������淢��������ʱ�䣬��ַ:0x1000~0x17FF
**�����������
**�����������
**************************************************************/
UINT8 FunFlashWriteEngineWorkTimeData(UINT16 DataAdrStart,UINT16 *Check_Flag)
{
	UINT8 Temp_8;
	UINT16 i,WRITE_DATA[12];
	UINT16 Adress_Ini,Temp_16=0;
	UINT32 Temp_32=0;

	if((*Check_Flag)<65535) (*Check_Flag)++;
	else (*Check_Flag)=0;

	WRITE_DATA[0] = (*Check_Flag);
	WRITE_DATA[1] = VarEngineWorkTimeDataSort_ID;

	//����
	WRITE_DATA[2] = (UINT16)(VarEngineWorkTime1H);
	WRITE_DATA[3] = (UINT16)(VarEngineWorkTime1H>>16);
	WRITE_DATA[4] = VarEngineWorkTime1M;
	WRITE_DATA[5] = VarEngineWorkTime1S;
	WRITE_DATA[6] = (UINT16)(VarEngineWorkTime_Gps);
	WRITE_DATA[7] = (UINT16)(VarEngineWorkTime_Gps>>16);
	WRITE_DATA[8] = BreakHammerFrequencyTimes;
	Temp_32 = 0;
	for(i=2;i<9;i++)
	{
		Temp_32 +=WRITE_DATA[i];
	}
	WRITE_DATA[9] = (UINT16)Temp_32;
	WRITE_DATA[10] = (UINT16)(Temp_32>>16);
	WRITE_DATA[11] = (*Check_Flag);
	//���ݱ���
	Adress_Ini = DataAdrStart;
	Temp_8=LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],12);
	if(Temp_8>0) //У����ȷ������ɹ�
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**��������FunFlashReadEngineWorkTime()
**������������ȡ����Сʱ������:0x1000~0x17FF
**���������
**�����������
**************************************************************/
UINT8 FunFlashReadEngineWorkTime(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
	UINT16 ReadMasterData[30],ReadBackupData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError,FlashBackupReadError;
	
	//У�����洢��������
	Data_Ini= SysMasterAdr_Start;
	LibFlashGetBlock(Data_Ini,&ReadMasterData[0],12);
	Temp_32=0;
	for(i=2;i<9;i++)
	{
		Temp_32 += ReadMasterData[i];
	}
	if( (ReadMasterData[0] != ReadMasterData[11])||
    	(ReadMasterData[1] !=VarEngineWorkTimeDataSort_ID)||
    	(Temp_32 != FunGetTwoWord(ReadMasterData[9],ReadMasterData[10]))
      )
    	{
    		FlashMasterReadError=1;//�����ݶ�ȡ����
    	}
    else
    	{
    		FlashMasterReadError=0;//�����ݶ�ȡ��ȷ
    	}
	//У�鱸�ݴ洢��������
	Data_Ini= SysBackupAdr_Start;
	LibFlashGetBlock(Data_Ini,&ReadBackupData[0],12);
	Temp_32=0;
	for(i=2;i<9;i++)
	{
		Temp_32 += ReadBackupData[i];
	}
	if( (ReadBackupData[0] != ReadBackupData[11])||
    	(ReadBackupData[1] !=VarEngineWorkTimeDataSort_ID)||
    	(Temp_32 != FunGetTwoWord(ReadBackupData[9],ReadBackupData[10]))
      )
    	{
    		FlashBackupReadError=1;//�������ݶ�ȡ����
    	}
    else
    	{
    		FlashBackupReadError=0;//�������ݶ�ȡ��ȷ
    	}
    //��ȡ���洢������
	if(FlashMasterReadError==0)
	{
		VarEngineWorkTime1H = FunGetTwoWord(ReadMasterData[2],ReadMasterData[3]);
		VarEngineWorkTime1M = ReadMasterData[4];
		VarEngineWorkTime1S = ReadMasterData[5];
		VarEngineWorkTime_Gps = FunGetTwoWord(ReadMasterData[6],ReadMasterData[7]);
		BreakHammerFrequencyTimes = ReadMasterData[8];
		(*MasterCheck_Flag) = ReadMasterData[0];
		return 1;
	}
	//��ȡ���ݴ洢������
	else if(FlashBackupReadError==0)
	{
		VarEngineWorkTime1H = FunGetTwoWord(ReadBackupData[2],ReadBackupData[3]);
		VarEngineWorkTime1M = ReadBackupData[4];
		VarEngineWorkTime1S = ReadBackupData[5];
		VarEngineWorkTime_Gps = FunGetTwoWord(ReadBackupData[6],ReadBackupData[7]);
		BreakHammerFrequencyTimes = ReadMasterData[8];
		(*BackupCheck_Flag) = ReadBackupData[0];
		return 1;
	}
	//װ��Ĭ������
	else
	{
		VarEngineWorkTime1H = 0;
		VarEngineWorkTime1M = 0;
		VarEngineWorkTime1S = 0;
		VarEngineWorkTime_Gps =0;
		BreakHammerFrequencyTimes = 0;
		(*MasterCheck_Flag)=0;
		(*BackupCheck_Flag)=0;
		return 0;
	}
}
/**************************************************************
**��������FunFlashWtiteWorkTimeAdrCommand()
**�������������湤��Сʱ�Ƶ�ַ
**���������0:���洢����1:���ݴ洢��
**�����������
**************************************************************/
void FunFlashWtiteWorkTimeAdrCommand(UINT8 Sort)
{
		UINT8 i,Temp_Confirm=0;
	if(Sort==0)//д���洢������,��ַ:0x1800~0x1BFF
	{
		if(VarFlashEngineWorkTimeMasterNeedSaveFlagIndex>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteEngineTimeAdr(0,&VarEngineTimeMasterCheckFlagIndex);//д���洢��ַ
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashEngineWorkTimeMasterNeedSaveFlagIndex=0;	
		}
	}
	//д���ݴ洢������,��ַ:0x1C00~0x1FFF
	else if(Sort==1)
	{
		if(VarFlashEngineWorkTimeBackupNeedSaveFlagIndex>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteEngineTimeAdr(1,&VarEngineTimeBackupCheckFlagIndex);//д���ݴ洢��ַ
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashEngineWorkTimeBackupNeedSaveFlagIndex=0;	
		}
	}
}
/**************************************************************
**��������FunFlashWriteEngineTimeAdr()
**�������������淢��������ʱ��Ĵ洢��ַ����ַ:0x1800~0x1FFF
**�����������
**�����������
**************************************************************/
UINT8 FunFlashWriteEngineTimeAdr(UINT8 Sort,UINT16 *Check_Flag)
{
	UINT8 Temp_8=0;
	UINT16 i,WRITE_DATA[10];
	UINT16 Adress_Ini,Temp_16=0;
	UINT32 Temp_32=0;

	if((*Check_Flag)<65535) (*Check_Flag)++;
	else (*Check_Flag)=0;

    if(Sort==0)
    {
		WRITE_DATA[0] = (*Check_Flag);
		WRITE_DATA[1] = VarEngineWorkTimeDataIndexSort_ID;
		//����
		WRITE_DATA[2] = VarFlashEngineTimeMasterAdr;
		WRITE_DATA[3] = 0;
		WRITE_DATA[4] = 0;
		WRITE_DATA[5] = 0;
		WRITE_DATA[6] = 0;
		Temp_32 = 0;
		for(i=2;i<7;i++)
		{
			Temp_32 +=WRITE_DATA[i];
		}
		WRITE_DATA[7] = (UINT16)Temp_32;
		WRITE_DATA[8] = (UINT16)(Temp_32>>16);
		WRITE_DATA[9] = (*Check_Flag);
		//���ݱ���
		Adress_Ini = VarFlashEngineTimeMasterAdrIndexDef;//0x1800
		Temp_8 = LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],10);
	}
	else if(Sort==1)
	{
		WRITE_DATA[0] = (*Check_Flag);
		WRITE_DATA[1] = VarEngineWorkTimeDataIndexSort_ID;
		//����
		WRITE_DATA[2] = VarFlashEngineTimeBackupAdr;
		WRITE_DATA[3] = 0;
		WRITE_DATA[4] = 0;
		WRITE_DATA[5] = 0;
		WRITE_DATA[6] = 0;
		Temp_32 = 0;
		for(i=2;i<7;i++)
		{
			Temp_32 +=WRITE_DATA[i];
		}
		WRITE_DATA[7] = (UINT16)Temp_32;
		WRITE_DATA[8] = (UINT16)(Temp_32>>16);
		WRITE_DATA[9] = (*Check_Flag);
		//���ݱ���
		Adress_Ini = VarFlashEngineTimeBackupAdrIndexDef;//0x1C00
		Temp_8 = LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],10);
	}
	if(Temp_8>0) //У����ȷ������ɹ�
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**��������FunFlashReadEngineTimeAdr()
**������������ȡ����������ʱ��Ĵ洢��ַ����ַ:0x1800~0x1FFF
**�����������
**�����������
**************************************************************/
void FunFlashReadEngineTimeAdr(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
	UINT16 ReadMasterData[30],ReadBackupData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError,FlashBackupReadError;
	
	//У�����洢��������
	Data_Ini= SysMasterAdr_Start;	
	LibFlashGetBlock(Data_Ini,&ReadMasterData[0],10);
	Temp_32=0;
	for(i=2;i<7;i++)
	{
		Temp_32 += ReadMasterData[i];
	}
	if( (ReadMasterData[0] != ReadMasterData[9])||
    	(ReadMasterData[1] !=VarEngineWorkTimeDataIndexSort_ID)||
    	(Temp_32 != FunGetTwoWord(ReadMasterData[7],ReadMasterData[8]))
      )
    	{
    		FlashMasterReadError=1;//�����ݶ�ȡ����
    	}
    else
    	{
    		FlashMasterReadError=0;//�����ݶ�ȡ��ȷ
    	}
	//У�鱸�ݴ洢��������
	Data_Ini= SysBackupAdr_Start;
	LibFlashGetBlock(Data_Ini,&ReadBackupData[0],10);	
	Temp_32=0;
	for(i=2;i<7;i++)
	{
		Temp_32 += ReadBackupData[i];
	}
	if( (ReadBackupData[0] != ReadBackupData[9])||
    	(ReadBackupData[1] !=VarEngineWorkTimeDataIndexSort_ID)||
    	(Temp_32 != FunGetTwoWord(ReadBackupData[7],ReadBackupData[8]))
      )
    	{
    		FlashBackupReadError=1;//�������ݶ�ȡ����
    	}
    else
    	{
    		FlashBackupReadError=0;//�������ݶ�ȡ��ȷ
    	}
    //��ȡ���洢������
	if(FlashMasterReadError==0)
	{
		VarFlashEngineTimeMasterAdr = ReadMasterData[2];
		(*MasterCheck_Flag) = ReadMasterData[0];
		if( (VarFlashEngineTimeMasterAdr>VarFlashEngineTimeMasterAdrMax)||
			(VarFlashEngineTimeMasterAdr<VarFlashEngineTimeMasterAdrDefault)
	      )
		{
			VarFlashEngineTimeMasterAdr=VarFlashEngineTimeMasterAdrDefault;
			VarFlashEngineWorkTimeMasterNeedSaveFlagIndex =1 ;
		}
	}
	else
	{
		VarFlashEngineTimeMasterAdr=VarFlashEngineTimeMasterAdrDefault;
		VarFlashEngineWorkTimeMasterNeedSaveFlagIndex =1 ;
	}
	//��ȡ���ݴ洢������
    if(FlashBackupReadError==0)
	{
		VarFlashEngineTimeBackupAdr = ReadBackupData[2];
		(*BackupCheck_Flag) = ReadBackupData[0];
		if( (VarFlashEngineTimeBackupAdr>VarFlashEngineTimeBackupAdrMax)||
		(VarFlashEngineTimeBackupAdr<VarFlashEngineTimeBackupAdrDefault)
		)
		{
			VarFlashEngineTimeBackupAdr=VarFlashEngineTimeBackupAdrDefault;
			VarFlashEngineWorkTimeBackupNeedSaveFlagIndex =1;
		}
	}
	else
	{
		VarFlashEngineTimeBackupAdr=VarFlashEngineTimeBackupAdrDefault;
		VarFlashEngineWorkTimeBackupNeedSaveFlagIndex =1;	
		(*MasterCheck_Flag)=0;
		(*BackupCheck_Flag)=0;
	}
}
/**************************************************************
**��������FunFlashWriteWorkTimeHourMainCommand()
**����������Сʱ����Ҫ���浽main��ʱ�����б���
**�����������
**�����������
**************************************************************/
void FunFlashWriteWorkTimeHourMainCommand(void)
{
	UINT8 i,Temp_8;
	if(VarFlashHourNeedSaveMainFlag>0)
	{
		VarFlashHourNeedSaveMainFlag = 0;
		for(i=0;i<3;i++)
		{
			Temp_8 = FunFlashWriteHourMain(VarFlashHourMainAdrDef,&VarFlashHourMainAdrCheckFlag);
			if(Temp_8>0)
			{
				break;
			}
		}
	}	
}
/**************************************************************
**��������FunFlashWriteHourMain()
**����������д�빤��ʱ��(Сʱ)��main��
**���������DataAdrStart���洢��ʼ��ַ��Check_Flag������ֵ
**���������1-����ɹ�;0-����ʧ��
**************************************************************/
UINT8 FunFlashWriteHourMain(UINT16 DataAdrStart,UINT16 *Check_Flag)
{
	UINT8 Temp_8;
	UINT16 i,WRITE_DATA[10];
	UINT16 Adress_Ini,Temp_16=0;
	UINT32 Temp_32=0;

	if((*Check_Flag)<65535) (*Check_Flag)++;
	else (*Check_Flag)=0;

	WRITE_DATA[0] = (*Check_Flag);
	WRITE_DATA[1] = VarEngineWorkTimeHourMainSort_ID;

	//����
	WRITE_DATA[2] = (UINT16)(VarEngineWorkTime1H);
	WRITE_DATA[3] = (UINT16)(VarEngineWorkTime1H>>16);
	WRITE_DATA[4] = 0;
	WRITE_DATA[5] = 0;
	WRITE_DATA[6] = 0;
	Temp_32 = 0;
	for(i=2;i<7;i++)
	{
		Temp_32 +=WRITE_DATA[i];
	}
	WRITE_DATA[7] = (UINT16)Temp_32;
	WRITE_DATA[8] = (UINT16)(Temp_32>>16);
	WRITE_DATA[9] = (*Check_Flag);
	//���ݱ���
	Adress_Ini = DataAdrStart;
	Temp_8 = LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],10);
	if(Temp_8>0) //У����ȷ������ɹ�
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**��������FunFlashReadEngineTimeMain()
**������������ȡmain������ķ���������ʱ��
**���������
**���������
**************************************************************/
UINT8 FunFlashReadEngineTimeMain(UINT16 DataAdrStart,UINT16 *Check_Flag,UINT32 *GetHourTime)
{
	UINT16 ReadMasterData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError;
	
	//У�����洢��������
	Data_Ini= DataAdrStart;
	LibFlashGetBlock(Data_Ini,&ReadMasterData[0],10);
	Temp_32=0;
	for(i=2;i<7;i++)
	{
		Temp_32 += ReadMasterData[i];
	}
	if( (ReadMasterData[0] != ReadMasterData[9])||
    	(ReadMasterData[1] !=VarEngineWorkTimeHourMainSort_ID)||
    	(Temp_32 != FunGetTwoWord(ReadMasterData[7],ReadMasterData[8]))
      )
	{
		FlashMasterReadError=1;//�����ݶ�ȡ����
	}
    else
	{
		FlashMasterReadError=0;//�����ݶ�ȡ��ȷ
	}
    if(FlashMasterReadError==0)
    {
    	(*GetHourTime) = FunGetTwoWord(ReadMasterData[2],ReadMasterData[3]);
    	(*Check_Flag) = ReadMasterData[0];
    	return 1;
    }
    else
    {
    	(*Check_Flag)=0;
    	return 0;
    }
}
/**************************************************************
**��������FunGetTwoWord()
**������������ȡFlash����ʱ���������ֽڵ�������ϳ�һ�����ֽ�����
**���������Low16����λ��High16����λ
**���������һ�����ֽڵ�����
**************************************************************/
UINT32 FunGetTwoWord(UINT16 Low16,UINT16 High16)
{
	UINT32 Temp32_1;
	Temp32_1 = High16;
	Temp32_1 = Temp32_1<<16;
	Temp32_1 = Temp32_1+Low16;
	return (Temp32_1);
}
