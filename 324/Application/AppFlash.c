/*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\
		----flash地址范围 0~0x3FFF(含)-----
	系 统 参 数:0x0000~0x07FF;
	Gps相关数据:0x0800~0x0FFF;
	工 作 时 间:0x1000~0x17FF;
	工作时间地址:0x1800~0x1FFF;
\*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\\*\*\*\*\*\*\*/
#include "AppFun.h"
#include "AppVar.h"
#include "AppDefine.h"
#include "LibFunDefine.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**函数名：FunFlashLoop()
**功能描述：Flash数据的保存
**传入参数：无
**输出参数：无
**************************************************************/
void FunFlashLoop(void)
{
	//save data to flash
	FunFlashWriteData();
}
/**************************************************************
**函数名：FunFlashInit()
**功能描述：初始化时从Flash读取数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunFlashInit(void)
{
	UINT8 i,Temp_8,error_1,error_2;
	UINT32 GetHourTime;
	//读系统参数
	for(i=0;i<5;i++)
	{
		Temp_8=FunFlashReadSysData(0x0000,0x0400,&VarSysDataMasterCheckFlag,&VarSysDataBackupCheckFlag);
		if(Temp_8>0)
		{
			break;
		}
	}
	//读GPS相关数据
	for(i=0;i<5;i++)
	{
		Temp_8=	FunFlashReadGpsData(0x0800,0x0C00,&VarGpsDataMasterCheckFlag,&VarGpsDataBackupCheckFlag);
		if(Temp_8>0)
		{
			break;
		}
	}
	//读发动机工作小时计地址
	FunFlashReadEngineTimeAdr(VarFlashEngineTimeMasterAdrIndexDef,VarFlashEngineTimeBackupAdrIndexDef,&VarEngineTimeMasterCheckFlagIndex,&VarEngineTimeBackupCheckFlagIndex);
	//读发动机工作小时
	for(i=0;i<5;i++)
	{
		error_1=FunFlashReadEngineWorkTime(VarFlashEngineTimeMasterAdr,VarFlashEngineTimeBackupAdr,&VarEngineTimeMasterCheckFlag,&VarEngineTimeBackupCheckFlag);
		if(error_1>0)
		{
			break;
		}
	}
	//读main区数据
	for(i=0;i<5;i++)
	{
		error_2=FunFlashReadEngineTimeMain(VarFlashHourMainAdrDef,&VarFlashHourMainAdrCheckFlag,&GetHourTime);
		if(error_2>0)
		{
			break;
		}
	}
	//主存储区与备份存储区都出错，读取main区备份时间
	if((error_1==0)&&(error_2>0))
	{
		VarEngineWorkTime1H = GetHourTime;
	}
	//读取空载转速值
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
**函数名：FunFlashWriteData()
**功能描述：向Flash写入数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunFlashWriteData(void)
{
	//保存系统参数
	FunFlashWriteSysDataCommand(0);
	FunFlashWriteSysDataCommand(1);
	//保存GPS相关数据
	FunFlashWriteGpsDataCommand(0);
	FunFlashWriteGpsDataCommand(1);
	//保存小时计
	FunFlashWriteWorkTimeCommand(0);
	FunFlashWriteWorkTimeCommand(1);
	//保存小时计数据地址索引
	FunFlashWtiteWorkTimeAdrCommand(0);
	FunFlashWtiteWorkTimeAdrCommand(1);
	//保存小时计main函数
	FunFlashWriteWorkTimeHourMainCommand();
}
/**************************************************************
**函数名：FunFlashWriteSysDataCommand()
**功能描述：向Flash写入系统参数数据:0x0000~0x7FFF
**传入参数：Sort=0:写入主存储区；Sort=1:写入备份存储区；
**输出参数：无
**************************************************************/
void FunFlashWriteSysDataCommand(UINT8 Sort)
{
	UINT8 i,Temp_Confirm=0;
	if(Sort==0)//写主存储区数据,地址:0x0000~0x03FF
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
	//写备份存储区数据,地址:0x0400~0x07FF
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
**函数名：FunFlashWriteSysData()
**功能描述：往Flash中写入系统参数：主存储区:0x0000~03FF;备份存储区:0x0400~07FF
**传入参数：无
**输出参数：无
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
	//数据
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
	WRITE_DATA[18] = VarBoomPowerSaveFlag;//动臂节能模式,回转节能模式,蓄能器泄压模式
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
	//数据保存
	Adress_Ini = DataAdrStart;
	Temp_8=LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],25);
	if(Temp_8>0) //校验正确，保存成功
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**函数名：FunFlashReadSysData()
**功能描述：从Flash读取系统参数数据
**传入参数：无
**输出参数：无
**************************************************************/
UINT8 FunFlashReadSysData(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
		UINT16 ReadMasterData[30],ReadBackupData[30];
		UINT16 i,Data_Ini;
		UINT32 Temp_32;
		UINT8 FlashMasterReadError,FlashBackupReadError;
		//校验主存储区域数据
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
	    		FlashMasterReadError=1;//主数据读取错误
	    	}
	    else
	    	{
	    		FlashMasterReadError=0;//主数据读取正确
	    	}
		//校验备份存储区域数据
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
	    		FlashBackupReadError=1;//主数据读取错误
	    	}
	    else
	    	{
	    		FlashBackupReadError=0;//主数据读取正确
	    	}
		//读主存储区域数据
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
			
			VarBoomPowerSaveFlag=ReadMasterData[18];//动臂节能模式,回转节能模式,蓄能器泄压模式
			VarRatatorPowerSaveFlag=ReadMasterData[19];
			VarXieYaFlag=ReadMasterData[20];
			
			(*MasterCheck_Flag) = ReadMasterData[0];
			return 1;

		}
		//读备份存储区域数据
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
			
			VarBoomPowerSaveFlag=ReadBackupData[18];//动臂节能模式,回转节能模式,蓄能器泄压模式
			VarRatatorPowerSaveFlag=ReadBackupData[19];
			VarXieYaFlag=ReadBackupData[20];
			
			(*BackupCheck_Flag) = ReadBackupData[0];
			return 1;
		}
		// 读存储器错误，加载默认值
		else
		{
			VarAccDialPosiMin = 1560;
			VarAccDialPosiMax = 3200;
			VarCanExcavatorId =0;
			VarCanExcavatorType=316;//470对应型号为316
			VarPumpPowerParameter[0] = 5;
			VarPumpPowerParameter[1] = 5;
			VarPumpPowerParameter[2] = 5;
			VarPumpPowerParameter[3] = 5;
			VarPumpPowerParameter[4] = 5;
			VarPumpPowerParameter[5] = 5;
			VarPumpPowerParameter[6] = 5;
			VarPumpPowerParameter[7] = 5;
			VarExcavatorMonitorType = 4;//默认SW显示屏
			VarCMCommunicationVersion = 6;//默认05版通讯协议版本05
			VarCanHighlandMode = 0;//默认非高原模式
			VarExcavatorEngineType = 0;//默认CUMMINS发动机
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
			(*MasterCheck_Flag) =0;
			(*BackupCheck_Flag) = 0;
			return 0;
		}
		
}
/**************************************************************
**函数名：FunFlashWriteGpsDate()
**功能描述：保存GPS相关数据:0x0800~0x0FFF
**传入参数：无
**输出参数：无
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

	//数据
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
	//数据保存
	Adress_Ini = DataAdrStart;
	Temp_8=LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],15);
	if(Temp_8>0) //校验正确，保存成功
		{ return 1;}
	else 
		{ return 0;}
}
/**************************************************************
**函数名：FunFlashWriteGpsDataCommand()
**功能描述：保存GPS相关数据:0x0800~0x0FFF
**传入参数：无
**输出参数：无
**************************************************************/
void FunFlashWriteGpsDataCommand(UINT8 Sort)
{
	UINT8 i,Temp_Confirm=0;
	if(Sort==0)//写主存储区数据,地址:0x0800~0x0BFF
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
	//写备份存储区数据,地址:0x0C00~0x0FFF
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
**函数名：FunFlashReadGpsData()
**功能描述：读取GPS相关数据:0x0800~0x0FFF
**传入参数：无
**输出参数：无
**************************************************************/
UINT8 FunFlashReadGpsData(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
	UINT16 ReadMasterData[30],ReadBackupData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError,FlashBackupReadError;
	
	//校验主存储区域数据
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
    		FlashMasterReadError=1;//主数据读取错误
    	}
    else
    	{
    		FlashMasterReadError=0;//主数据读取正确
    	}
	//校验备份存储区域数据
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
    		FlashBackupReadError=1;//备份数据读取错误
    	}
    else
    	{
    		FlashBackupReadError=0;//备份数据读取正确
    	}
	//读取主存储区数据
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
	//读取备份存储区数据
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
	//加载默认值
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
**函数名：FunFlashWriteWorkTimeCommand()
**功能描述：写工作小时入Flash,地址:0x1000~0x17FF
**传入参数：0：主存储区；1：备份存储区
**输出参数：
**************************************************************/
void FunFlashWriteWorkTimeCommand(UINT8 Sort)
{
	UINT8 i,Temp_Confirm=0;
	if(Sort==0)//写主存储区数据,地址:0x1000~0x13FF
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
			if(Temp_Confirm==0)//保存失败
			{
				VarFlashEngineTimeMasterAdr +=  0x000F;
				if( (VarFlashEngineTimeMasterAdr>VarFlashEngineTimeMasterAdrMax)||
				    (VarFlashEngineTimeMasterAdr<VarFlashEngineTimeMasterAdrDefault)
				  )
				  {
				  	VarFlashEngineTimeMasterAdr=VarFlashEngineTimeMasterAdrDefault;
				  }
				  VarFlashEngineWorkTimeMasterNeedSaveFlagIndex =1;//存储地址改变，需要保存
				  VarFlashEngineWorkTimeMasterNeedSaveFlag =1;
			}
		}
	}
	//写备份存储区数据,地址:0x1400~0x17FF
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
**函数名：FunFlashWriteEngineWorkTimeData()
**功能描述：保存发动机工作时间，地址:0x1000~0x17FF
**传入参数：无
**输出参数：无
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

	//数据
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
	//数据保存
	Adress_Ini = DataAdrStart;
	Temp_8=LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],12);
	if(Temp_8>0) //校验正确，保存成功
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**函数名：FunFlashReadEngineWorkTime()
**功能描述：读取工作小时计数据:0x1000~0x17FF
**传入参数：
**输出参数：无
**************************************************************/
UINT8 FunFlashReadEngineWorkTime(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
	UINT16 ReadMasterData[30],ReadBackupData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError,FlashBackupReadError;
	
	//校验主存储区域数据
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
    		FlashMasterReadError=1;//主数据读取错误
    	}
    else
    	{
    		FlashMasterReadError=0;//主数据读取正确
    	}
	//校验备份存储区域数据
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
    		FlashBackupReadError=1;//备份数据读取错误
    	}
    else
    	{
    		FlashBackupReadError=0;//备份数据读取正确
    	}
    //读取主存储区数据
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
	//读取备份存储区数据
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
	//装载默认数据
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
**函数名：FunFlashWtiteWorkTimeAdrCommand()
**功能描述：保存工作小时计地址
**传入参数：0:主存储区；1:备份存储区
**输出参数：无
**************************************************************/
void FunFlashWtiteWorkTimeAdrCommand(UINT8 Sort)
{
		UINT8 i,Temp_Confirm=0;
	if(Sort==0)//写主存储区数据,地址:0x1800~0x1BFF
	{
		if(VarFlashEngineWorkTimeMasterNeedSaveFlagIndex>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteEngineTimeAdr(0,&VarEngineTimeMasterCheckFlagIndex);//写主存储地址
				if(Temp_Confirm>0)
				{
					break;
				}
			}
			VarFlashEngineWorkTimeMasterNeedSaveFlagIndex=0;	
		}
	}
	//写备份存储区数据,地址:0x1C00~0x1FFF
	else if(Sort==1)
	{
		if(VarFlashEngineWorkTimeBackupNeedSaveFlagIndex>0)
		{
			for(i=0;i<5;i++)
			{
				Temp_Confirm = FunFlashWriteEngineTimeAdr(1,&VarEngineTimeBackupCheckFlagIndex);//写备份存储地址
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
**函数名：FunFlashWriteEngineTimeAdr()
**功能描述：保存发动机工作时间的存储地址，地址:0x1800~0x1FFF
**传入参数：无
**输出参数：无
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
		//数据
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
		//数据保存
		Adress_Ini = VarFlashEngineTimeMasterAdrIndexDef;//0x1800
		Temp_8 = LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],10);
	}
	else if(Sort==1)
	{
		WRITE_DATA[0] = (*Check_Flag);
		WRITE_DATA[1] = VarEngineWorkTimeDataIndexSort_ID;
		//数据
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
		//数据保存
		Adress_Ini = VarFlashEngineTimeBackupAdrIndexDef;//0x1C00
		Temp_8 = LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],10);
	}
	if(Temp_8>0) //校验正确，保存成功
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**函数名：FunFlashReadEngineTimeAdr()
**功能描述：读取发动机工作时间的存储地址，地址:0x1800~0x1FFF
**传入参数：无
**输出参数：无
**************************************************************/
void FunFlashReadEngineTimeAdr(UINT16 SysMasterAdr_Start,UINT16 SysBackupAdr_Start,UINT16 *MasterCheck_Flag,UINT16 *BackupCheck_Flag)
{
	UINT16 ReadMasterData[30],ReadBackupData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError,FlashBackupReadError;
	
	//校验主存储区域数据
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
    		FlashMasterReadError=1;//主数据读取错误
    	}
    else
    	{
    		FlashMasterReadError=0;//主数据读取正确
    	}
	//校验备份存储区域数据
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
    		FlashBackupReadError=1;//备份数据读取错误
    	}
    else
    	{
    		FlashBackupReadError=0;//备份数据读取正确
    	}
    //读取主存储区数据
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
	//读取备份存储区数据
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
**函数名：FunFlashWriteWorkTimeHourMainCommand()
**功能描述：小时计需要保存到main区时，进行保存
**传入参数：无
**输出参数：无
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
**函数名：FunFlashWriteHourMain()
**功能描述：写入工作时间(小时)到main区
**传入参数：DataAdrStart：存储开始地址；Check_Flag：返回值
**输出参数：1-保存成功;0-保存失败
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

	//数据
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
	//数据保存
	Adress_Ini = DataAdrStart;
	Temp_8 = LibFlashSetBlock(Adress_Ini,&WRITE_DATA[0],10);
	if(Temp_8>0) //校验正确，保存成功
		{ return 1; }
	else 
		{ return 0;}
}
/**************************************************************
**函数名：FunFlashReadEngineTimeMain()
**功能描述：读取main区保存的发动机工作时间
**传入参数：
**输出参数：
**************************************************************/
UINT8 FunFlashReadEngineTimeMain(UINT16 DataAdrStart,UINT16 *Check_Flag,UINT32 *GetHourTime)
{
	UINT16 ReadMasterData[30];
	UINT16 i,Data_Ini;
	UINT32 Temp_32;
	UINT8 FlashMasterReadError;
	
	//校验主存储区域数据
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
		FlashMasterReadError=1;//主数据读取错误
	}
    else
	{
		FlashMasterReadError=0;//主数据读取正确
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
**函数名：FunGetTwoWord()
**功能描述：读取Flash数据时，将两个字节的数据组合成一个四字节数据
**传入参数：Low16：低位；High16：高位
**输出参数：一个四字节的数据
**************************************************************/
UINT32 FunGetTwoWord(UINT16 Low16,UINT16 High16)
{
	UINT32 Temp32_1;
	Temp32_1 = High16;
	Temp32_1 = Temp32_1<<16;
	Temp32_1 = Temp32_1+Low16;
	return (Temp32_1);
}
