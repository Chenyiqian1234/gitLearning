#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppVar.h"
#include "AppPowerSaveVar.h"
/**************************************************************
**函数名：FunCanDisplayReceiveData()
**功能描述：处理从显示屏、GPS接收到的数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanDisplayGpsReceiveData(void)
{
	BOOL GPSLock_All_Enable_Last;		//锁车总使能,1-启用，0-停用
	BOOL GPSLock_Passive_Enable_Last;	//被动锁车总使能,1-启用，0-停用
	BOOL MonthNoSignalLock_Enable_Last;	//盲区锁车使能,1-启用，0-停用
	BOOL UncoverLock_Enable_Last;		//拆盖锁车使能,1-启用，0-停用
	BOOL CANSignalLostLock_Enable_Last;	//总线锁车使能,1-启用，0-停用
	BOOL SIMCardLostLock_Enable_Last;	//拔卡锁车使能,1-启用，0-停用
	UINT16 temp_uint;
	
//**********************************************数据接收*******************************************************************//
/**************************************************************
**控制器接收CAN总面板数据
**小端模式，低字节在前，高字节在后
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
**控制器接收显示屏数据 CAN0
**大端模式，高字节在前，低字节在后	
**************************************************************/	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x101<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(27))
	{
		LibCan0ReadReceiveData(27,VarRecDataID101);
		//小时计设置密码
		VarCanEngineTimeSetPSD = 0;
		VarCanEngineTimeSetPSD += VarRecDataID101[3];
		VarCanEngineTimeSetPSD = VarCanEngineTimeSetPSD<<8;
		VarCanEngineTimeSetPSD += VarRecDataID101[4];
		VarCanEngineTimeSetPSD = VarCanEngineTimeSetPSD<<8;
		VarCanEngineTimeSetPSD += VarRecDataID101[5];
		//工作小时设置值
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
		//bit0 GPS解锁密码开始发送
		if( VarRecDataID102[6] & 0x01 )
		{
			VarCanGpsSendUnlockPSDFlag =1;
		}
		else
		{
			VarCanGpsSendUnlockPSDFlag = 0;
		}
	 
		//bit1 GPS取消密码开始发送
		if( VarRecDataID102[6] & 0x02 )
		{
			VarCanGpsCancelCommand = 1;	
		}
		else
		{
			VarCanGpsCancelCommand = 0;
		}
		//bit2 工作小时计设置密码开始发送
		if( VarRecDataID102[6] & 0x04 )
		{
			VanEngineTimeSetPSDSendFlag = 1;
		}
		else
		{
			VanEngineTimeSetPSDSendFlag = 0;
		}
		//bit3 GPS紧急解锁密码开始发送..
		if( VarRecDataID102[6] & 0x08 )
		{
			VarCanGpsUrgencyCommand = 1;
		}
		else
		{
			VarCanGpsUrgencyCommand = 0;
		}
		//bit4 工作小时设置发送
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
		//byte0-1 挖掘机显示屏种类：01-IC屏；02-永青屏；03-Wachendorff屏；04-SW屏
		if(VarExcavatorMonitorType!=VarRecDataID106[1])	
		{
			VarExcavatorMonitorType = VarRecDataID106[1];
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
		}
		//byte2-3 控制器与显示屏的通讯协议版本:01-IC老版；02-IC新版；03-永青版;04-Wachendorff版;05-SW屏1版
		if(VarCMCommunicationVersion!=VarRecDataID106[3])	
		{
			VarCMCommunicationVersion = VarRecDataID106[3];
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
		}
		//byte4-5/6-7 非Wachendorff显示屏的机器型号与机器编号保存
		if(VarCMCommunicationVersion!=4)
		{
			//机器型号
			temp_uint = VarRecDataID106[4];
			temp_uint = temp_uint<<8;
			temp_uint += VarRecDataID106[5];
			if(VarCanExcavatorType!=temp_uint)
			{
				VarCanExcavatorType = temp_uint;
				VarFlashSysDateMasterNeedSaveFlag=1;
				VarFlashSysDateBackupNeedSaveFlag=1;
			}
			//机器编号
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
		//byte4-5 电喷发动机厂家
		VarExcavatorEngineType = VarRecDataID107[5];//电喷发动机厂家:0-康明斯，1-五十铃，2-潍柴；3-沃尔沃；4-三菱；5-大柴		
	}
	
//	//>>>>>>>>>>>>>>>>>>>>>> ID=0x110<<<<<<<<<<<<<<<<<
//	if(LibCan0ReceiveFlag(19))
//	{
//		LibCan0ReadReceiveData(19,VarRecDataID110);
//		//液压破碎器流量值
//		VarHydHammerFlow = VarRecDataID110[0];
//		//液压剪流量值scissors
//		VarHydSicissorsFlow = VarRecDataID110[1];
//		//液压夯流量值
//		VarHydRamFlow = VarRecDataID110[2];
//		//液压破碎器压力设定值
//		VarHydHammerPresure = VarRecDataID110[3];
//		//液压剪压力设定值
//		VarHydSicissorsPresure = VarRecDataID110[4];
//		//液压夯压力设定值
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
				VarPumpPowerParameter[0] = VarRecDataID111[0];  //泵参数1
				VarPumpPowerParameter[1] = VarRecDataID111[1];
				VarPumpPowerParameter[2] = VarRecDataID111[2];
				VarPumpPowerParameter[3] = VarRecDataID111[3];
				VarPumpPowerParameter[4] = VarRecDataID111[4];
				VarPumpPowerParameter[5] = VarRecDataID111[5];
				VarPumpPowerParameter[6] = VarRecDataID111[6];
				VarPumpPowerParameter[7] = VarRecDataID111[7];  //泵参数8
				VarFlashSysDateMasterNeedSaveFlag=1;//数据保存
				VarFlashSysDateBackupNeedSaveFlag=1;
			}
		} 
	}
	
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x112<<<<<<<<<<<<<<<<<
 	if(LibCan0ReceiveFlag(21))
	{
 		LibCan0ReadReceiveData(21,VarRecDataID112);
 		//Byte0
 		//bit0 表盘低位设置
		if( VarRecDataID112[0] & 0x01 )
		{
		   VarCanAccDialPosiMinSet = 1;
		}
		else
		{
		   VarCanAccDialPosiMinSet = 0;
		}
		//bit1 表盘高位设置
		if( VarRecDataID112[0] & 0x02 )
		{
		   VarCanAccDialPosiMaxSet = 1;
		}
		else
		{
		   VarCanAccDialPosiMaxSet = 0;
		}
		//bit2 泵功率发送标志位
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
		   VarCanAccHydraulicCoolingFWD = 0;//等于0时液压冷却风扇为正转
		}
		else
		{
		   VarCanAccHydraulicCoolingFWD = 1;
		}		
		//Byte1,高原模式
		if( (VarRecDataID112[1] & 0x01)!=VarCanHighlandMode)
		{
			VarCanHighlandMode = (UINT8)(VarRecDataID112[1] & 0x01);
			VarFlashSysDateMasterNeedSaveFlag=1;
			VarFlashSysDateBackupNeedSaveFlag=1;
		}
		
		//Byte2,辅助作业模式
		VarCanSysBKRMode = (UINT8)(VarRecDataID112[2]&0x07);	
		//Byte3
		//破碎手动/自动模式
//		if( VarRecDataID112[3] & 0x02 )
//		{
//			VarBrokenManual_AutoModel=1;//等于1为破碎自动模式
//		}
//		else
//		{
//			VarBrokenManual_AutoModel=0;//等于0为破碎手动模式，默认手动模式
//		}
		//bit2,破碎合流模式
//		if( VarRecDataID112[3] & 0x04 )
//		{
//			VarBrokenConfluenceModel=1;
//		}
//		else
//		{
//			VarBrokenConfluenceModel=0;	
//		}
		//Byte4,bit2,自动怠速
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
		//Byte4,bit3,行走高低速
		if( VarRecDataID112[4] & 0x08 )
		{
			VarCanHighSpeedTravel = 1;
		}
		else
		{
			VarCanHighSpeedTravel = 0;
		}
		//Byte5自动怠速档位设置
		VarAutoIdleSpeedGrade=VarRecDataID112[5];
		//Byte6一键怠速档位设置
		VarManualIdleSpeedGrade=VarRecDataID112[6];
		//Byte7,
		//bit0,空气清洁泵
		if( VarRecDataID112[7] & 0x01 )
		{
		   VarAirFilterPump_Enable = 1;
		}
		else
		{
		   VarAirFilterPump_Enable = 0;
		}
		//bit1,燃油过滤泵
		if( VarRecDataID112[7] & 0x02 )
		{
		   VarFuelFilterPump_Enable = 1;
		}
		else
		{
		   VarFuelFilterPump_Enable = 0;
		}
		//bit2,逃脱模式按钮
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
	
	// 博创ID=0x185->101号屏116  总线是1还是0？
    if(LibCan0ReceiveFlag(19)) //接收通道需要变
	{    		
    	LibCan0ReadReceiveData(19,VarRecDataID116);
		//动臂节能模式,回转节能模式,蓄能器泄压模式
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
**控制器接收GPS数据 CAN0 311、312
**大端模式，高字节在前，低字节在后	
**************************************************************/	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x300<<<<<<<<<<<<<<<<<
	if(LibCan0ReceiveFlag(23))
	{
		VarCanGpsHeartBeat = LibCan0ReceiveFlag(23);
		LibCan0ReadReceiveData(23,VarRecDataID300);
		GPSStateByte = (VarRecDataID300[6]<<8);  //添加新变量
		GPSStateByte += VarRecDataID300[7];
		if (GPSStateByte & 0x40)//bit6 GPS天线未接或被剪断
		{
			VarCanAntennaCutLockCommand = 1;
		}
		else
		{
			VarCanAntennaCutLockCommand = 0;
		}
		if (GPSStateByte & 0x100)//bit8 开盖报警
		{
			VarCanUncoverLockCommand = 1;
		}
		else
		{
			VarCanUncoverLockCommand = 0;
		}
		if (GPSStateByte & 0x200)//bit9 拔卡报警    添加新变量
		{
			SimCardLostAlarm = 1;
		}
		else
		{
			SimCardLostAlarm = 0;
		}
		if (GPSStateByte & 0x400)//bit10 与远程平台连接状态  添加新变量
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
		//当前状态赋值
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
		//使能状态切换时，保存
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
**函数名：FunCanDisplayGpsPackSendData()
**功能描述：组合发送至显示屏与GPS的数据
**传入参数：无
**输出参数：无
**************************************************************/

void FunCanDisplayGpsPackSendData(void)
{
	UINT8 temp_uchar,i;
	UINT16 temp_uint16; 
	UINT32 Password_1;	
//**********************************************数据发送*******************************************************************//
/**************************************************************
**控制器数据发送至CAN总面板
**小端模式，低字节在前，高字节在后	
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
	**控制器数据发送至显示屏 CAN1 311、312
	**大端模式，高字节在前，低字节在后	
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
	VarSendDataID201[0] = (UINT8)(VarP1PressureFilter>>8);	//P1压力, bar
	VarSendDataID201[1] = (UINT8)(VarP1PressureFilter);
	VarSendDataID201[2] = (UINT8)(VarP2PressureFilter>>8);	//P2压力,bar
	VarSendDataID201[3] = (UINT8)(VarP2PressureFilter);
	VarSendDataID201[4] = (UINT8)((VarSysVoltageMv/100)>>8);//系统电压:0.1V
	VarSendDataID201[5] = (UINT8)(VarSysVoltageMv/100);
	VarSendDataID201[6] = VarFuelVolumeFilter; //燃油油位
	//VarSendDataID201[7]=VarDialGrade;	
	
	if(VarAccDialPosiNow>(VarAccDialPosiMax+120))//11档
 	{
		VarSendDataID201[7] = VarDialGrade+1; //表盘档位
 	}
 	else
 	{
 		VarSendDataID201[7] = VarDialGrade; //表盘档位

 	}  
	
	//>>>>>>>>>>>>>>>>>>>>>> ID=0x203 <<<<<<<<<<<<<<<<<
	//VarSendDataID203[2] = (UINT8)(VarPiPressureFilter);	//先导压力, bar 
	//VarSendDataID203[3] = (UINT8)(VarBrokenPiPressureFilter);//破碎先导压力, bar
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x209  <<<<<<<<<<<<<<<<<
 	 VarSendDataID209[0] = (UINT8)(VarBoomBigPressureBar>>8 );//动臂大腔压力值bar
 	 VarSendDataID209[1] = (UINT8)((VarBoomBigPressureBar));
 	 
 	 VarSendDataID209[2] =(UINT8) (VarBoomSmallPressureBar>>8 );//动臂小腔压力值bar
 	 VarSendDataID209[3] =(UINT8)((VarBoomSmallPressureBar));
	
   	 VarSendDataID209[4] = 0;//铲斗小腔压力,单位bar
   	 VarSendDataID209[5] = 0;
   	 
   	 VarSendDataID209[6] = (UINT8)((VarPBucCapPressure>>8)&0xFF);//铲斗大腔压力,单位bar
   	 VarSendDataID209[7] = (UINT8)(VarPBucCapPressure & 0xFF );
	
   	 
   	VarSendDataID20A[0] = (UINT8)((VarPBucketArmRodPressure>>8)&0xFF);//pin17,斗杆小腔压力值单位bar
   	VarSendDataID20A[1] = (UINT8)(VarPBucketArmRodPressure & 0xFF );

   	VarSendDataID20A[2] = (UINT8)((VarPBucketArmPressure>>8)&0xFF);//pin23,斗杆大腔压力值单位bar
   	VarSendDataID20A[3] = (UINT8)(VarPBucketArmPressure & 0xFF);
   	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20C  <<<<<<<<<<<<<<<<<
	if (VarCanSysHSLMode==0)
	{
		VarSendDataID20C[0] |= (UINT8)(1<<0); //bit0,H模式
	}
	else if(VarCanSysHSLMode==1)
	{
		VarSendDataID20C[0] |= (UINT8)(1<<1); //bit1,S模式
	}
	else 
	{
		VarSendDataID20C[0] |= (UINT8)(1<<2); //bit2,L模式
	} 
	
	if(VarCanHighlandMode)
	{
		VarSendDataID20C[0] |= (UINT8)(1<<3); //bit3,高原模式
	}
	VarSendDataID20C[1] = (UINT8)(VarCanSysBKRMode & 0x07);	//0-2bit:BKR模式
	VarSendDataID20C[2] = (UINT8)(VarEngineWorkTime1H>>8);	//小时
	VarSendDataID20C[3] = (UINT8)(VarEngineWorkTime1H);
	VarSendDataID20C[4] = (UINT8) VarEngineWorkTime1M;	//分钟
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20D  <<<<<<<<<<<<<<<<<
	VarSendDataID20D[2] = (UINT8)(VarEngineAverageFuelYouHao>>8);	//平均燃油消耗(L/h)，接收端需除100
	VarSendDataID20D[3] = (UINT8)(VarEngineAverageFuelYouHao);
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20E  <<<<<<<<<<<<<<<<<
	VarSendDataID20E[0] = (UINT8)(VarEngineFuelYouHao>>24);	//发动机总油耗(L)，接收端需除2
	VarSendDataID20E[1] = (UINT8)(VarEngineFuelYouHao>>16);
	VarSendDataID20E[2] = (UINT8)(VarEngineFuelYouHao>>8);
	VarSendDataID20E[3] = (UINT8)(VarEngineFuelYouHao);	
	
	VarSendDataID20E[4] = (UINT8)((VarEngineSpeedWorkTome/10)>>24);	//发动机总工作时间(h)，接收端需除2
	VarSendDataID20E[5] = (UINT8)((VarEngineSpeedWorkTome/10)>>16);
	VarSendDataID20E[6] = (UINT8)((VarEngineSpeedWorkTome/10)>>8);
	VarSendDataID20E[7] = (UINT8)((VarEngineSpeedWorkTome/10));	
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x20F  <<<<<<<<<<<<<<<<<
	VarSendDataID20F[2] = (UINT8)(VarAftertreatmentDOCIntakeTemp>>8);	
	VarSendDataID20F[3] = (UINT8)(VarAftertreatmentDOCIntakeTemp);
	VarSendDataID20F[4] = (UINT8)(VarAftertreatmentDOCOutletTemp>>8);	
	VarSendDataID20F[5] = (UINT8)(VarAftertreatmentDOCOutletTemp);
	VarSendDataID20F[6] = (UINT8)(VarCanEngineAirInTemp);  //进气温度，接收端需减40
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x210  <<<<<<<<<<<<<<<<<
	VarSendDataID210[1] = (UINT8)(VarCanEngineTorque);  //发动机扭矩百分比，接收端需减125
	VarSendDataID210[3] = (UINT8)(VarCanEngineBoostTemp); //增压温度，接收端需减40
	VarSendDataID210[4] = (UINT8)(VarIntakeManifoldTemp); //进气歧管内温度，接收端需减40
	VarSendDataID210[5] = (UINT8)(VarInterCoolInletTemp); //中冷器入口温度，接收端需减40
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x211  <<<<<<<<<<<<<<<<<
	VarSendDataID211[0] = (UINT8)(VarCanEngineOilPressure);  //机油压力，接收端需乘4
	VarSendDataID211[2] = (UINT8)(VarCommonRailPressure>>8); //共轨压力，接收端需除256
	VarSendDataID211[3] = (UINT8)(VarCommonRailPressure);
	VarSendDataID211[4] = (UINT8)(VarCanEngineAtmosPressrue); //大气压力，接收端需乘0.5
	VarSendDataID211[5] = (UINT8)(VarCanEngineBoostPressrue); //增压压力，接收端需乘2
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
		VarSendDataID215[0] |= 1<<0;  //bit0 油量不足报警
	}
	if(VarDiStop==1)
	{
		VarSendDataID215[0] |= 1<<1;  //bit1 紧急停车报警
	}
	if(VarHydraulicOilHihgAlarm)
	{
		VarSendDataID215[0] |= 1<<2;  //bit2 液压油温高报警
	}
	if(( VarCanEngineOilPreAlarm>0)||(VarEngineSpeedNow<400))
	{
		VarSendDataID215[0] |= 1<<4;  //bit4 机油压力低报警
	}
	if(VarCanWaterHihgAlarm>0)
	{
		VarSendDataID215[0] |= 1<<5;  //bit5 冷却水温高报警
	}
	if(VarDiAirFilterAlarm==0)      //低有效
	{
		VarSendDataID215[0] |= 1<<6;  //bit6 空滤堵塞报警
	}
	if(VarDiCharge>0)
	{
		VarSendDataID215[0] |= 1<<7;  //bit7 充电指示
	}
	//Byte1
	if(VarCanAutoIdleEnable>0)
	{
		VarSendDataID215[1] |= 1<<0;  //bit0 自动怠速
	}
	if(VarButtonLowSpeedEnable)
	{
		VarSendDataID215[1] |= 1<<1;  //bit1 一键怠速
	}
	if(VarCanInPreheat>0)//预热DI
	{
		VarSendDataID215[7] |= 1<<2;  //bit2 预热	
	}
	if(VarEngineWarmState)
	{
		VarSendDataID215[1] |= 1<<3;  //bit3 暖机提醒
	}
	if(VarDoTravelHighSpeed>0)
	{
		VarSendDataID215[1] |= 1<<4;  //bit4 行走高低速
	}
	if(VarModeSelectionError)
	{
		VarSendDataID215[1] |= 1<<5;  //bit5模式选择错误
	}
/*
	//Byte2
	//bit0-2，再生灯
    if(VarAutoRegenerationLamp)
    {
		VarSendDataID215[2] |= 1<<0;  //bit0-2:001 自动再生中(绿灯常亮)
		VarSendDataID215[2] |= 0<<1;  
		VarSendDataID215[2] |= 0<<2;  
    }
    
    if(VarManualRegenerationLamp==1)
	{
		VarSendDataID215[2] |= 0<<0; //bit0-2:010 手动动再生中(橙灯常亮)
		VarSendDataID215[2] |= 1<<1;
		VarSendDataID215[2] |= 0<<2; 
	}
	else if(VarManualRegenerationLamp==2)
	{
		VarSendDataID215[2] |= 0<<0; //bit0-2:100 手动动再生提醒(橙灯慢闪))
		VarSendDataID215[2] |= 0<<1;
		VarSendDataID215[2] |= 1<<2;
	}
	else if(VarManualRegenerationLamp==3)
	{
		VarSendDataID215[2] |= 0<<0; //bit0-2:110 手动动再生提醒(橙灯快闪)
		VarSendDataID215[2] |= 1<<1;
		VarSendDataID215[2] |= 1<<2;
	}
	//bit4-5,驾驶员警告灯
	if(DriverWarningLamp==1) 
	{
		VarSendDataID215[2]|= (UINT8)1<<4;  //驾驶员警告灯常亮。bit4-5:01
		VarSendDataID215[2]|= (UINT8)0<<5;
	}
	else if(DriverWarningLamp==2) 
	{
		VarSendDataID215[2]|= (UINT8)0<<4;  //驾驶员警告灯慢闪。bit4-5:10
		VarSendDataID215[2]|= (UINT8)1<<5;
	}
	else if(DriverWarningLamp==3) 
	{
		VarSendDataID215[2]|= (UINT8)1<<4;  //驾驶员警告灯快闪。bit4-5:11
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
	VarSendDataID216[0] =(UINT8)(VarAiPump1Pressure/100);	//P1压力AI值
	VarSendDataID216[1] =(UINT8)(VarAiPump2Pressure/100);	//P2压力AI值
	
	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x217  <<<<<<<<<<<<<<<<<
//    VarSendDataID217[0] =(UINT8)(VarAiBrokenPilotPressure/100); //破碎先导压力AI值
//    VarSendDataID217[7] =(UINT8)(VarAiHydraulicTemp2/10); //液压油温2AI值

	//>>>>>>>>>>>>>>>>>>>>>>  ID=0x218  <<<<<<<<<<<<<<<<<
    VarSendDataID218[4] =(UINT8)(VarAiHydraulicTemp/10); //液压油温AI值
    //VarSedDataID218n[5] =(UINT8)(VarAiPilotPressure/100); //先导压力AI值   先导压力？？？？
    VarSendDataID218[6] =(UINT8)(VarAiFuelVolume/10);	//油量传感器AI值
    
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x21E	<<<<<<<<<<<<<<<<<
    //Byte0
//    if(VarDoBrokenValve)
//    {
//		VarSendDataID21E[0]|= (UINT8)1<<2;//bit2破碎锤开关阀
//    }
    //Byte1
    if(VarDoSecondPressure>0) 
	{
		VarSendDataID21E[1] |=  (UINT8)1<<0;//bit0 二次增压阀
	}
	if(VarDoBatteryRelay>0)
	{
		VarSendDataID21E[1] |= (UINT8)1<<1;//bit1 断电延时输出
	}
	if(VarDoPilot>0) 
	{
		VarSendDataID21E[1] |= (UINT8)1<<2;//bit2 先导电磁阀
	}
	if(VarDoTravelHighSpeed>0) 
	{
		VarSendDataID21E[1] |= (UINT8)1<<3;//bit3 行走高低速阀
	}
	if(VarDoManualRegenrationLoad)
	{
		VarSendDataID21E[1] |= (UINT8)1<<5;//bit5 手动再生辅助负载电磁阀
	}
//	if(VarDoBrokenConfluenceValve)
//	{
//		VarSendDataID21E[1] |= (UINT8)1<<6;//bit6 破碎合流先导电磁阀
//	}
	//Byte2
	if(VarDiTravelHighSpeed>0) 
	{
		VarSendDataID21E[2] |= (UINT8)1<<0; // bit0 行走压力H
	}	
	if(VarDiPilot>0) 
	{
		VarSendDataID21E[2] |= (UINT8)1<<1; // bit1 先导开关H
	}
	if(VarDiLowSpeedEnable>0) 
	{
		VarSendDataID21E[2] |= (UINT8)1<<2; // bit2 一键怠速开关
	}
	if(VarManualRegenerationButton)
	{
		VarSendDataID21E[2] |= (UINT8)1<<3; // bit3 手动再生开关
	}
	if(VarRegenerationInhibitButton)
	{
		VarSendDataID21E[2] |= (UINT8)1<<4; // bit4 再生禁止开关
	}
	if(VarDiStop==1)
	{
		VarSendDataID21E[2] |= (UINT8)1<<5; // bit5 急停开关
	}
	//Byte3
    if(VarDoHydraulicCoolingPositiveValve==0)
    {
		VarSendDataID21E[3] |= (UINT8)1<<0; //bit0 风扇正转
    }
    else
    {
		VarSendDataID21E[3] |= (UINT8)1<<0; //风扇反转
    }
    if(VarDoAirFilterPump==0)
	{
    	VarSendDataID21E[3] |= (UINT8)1<<1;;//bit1,空滤清洁泵
	}    
	if(VarDoFuelFilterPump>0) 
	{
		VarSendDataID21E[3] |= (UINT8)1<<2;;//bit2，柴油过滤泵
	} 
    if(VarCanAccHydraulicCoolingFWD==0)
    {
		VarSendDataID21E[3] |= (UINT8)1<<5; //bit5 风扇正转
    }
    else
    {
		VarSendDataID21E[3] |= (UINT8)0<<5; 
    }
	//Byte7******这一段是扶手箱控制板发送给显示屏的数据*******/
//    if(VarDoCabinLamp)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<0; //bit0 驾驶室顶灯	
//    }
//    if(VarDoWorkLamp)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<1; //bit1 工作灯	
//    }
//    if(VarDoCautionLamp)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<2; //bit2 警示灯	
//    }
//    if(VarDoWiper_1&&(VarDoWiper_2==0))
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<5; //bit5 雨刮1档	
//    }
//    if(VarDoWiper_2)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<6; //bit6 雨刮2档	
//    }
//    if(VarDoWaterSpray)
//    {
//		VarSendDataID21E[7] |= (UINT8)1<<7; //bit7 洗涤
//    }
    

	// >>>>>>>>>>>>>>>>>>>>>> ID=0x220	<<<<<<<<<<<<<<<<<
    if(VarCanGpsCancelPSDoK>0)
	{
		VarSendDataID220[0] |= 1<<0; //bit0  GPS取消密码正确
	}
	if(VanEngineTimeSetPSDoKFlag>0)
	{
		VarSendDataID220[0] |= 1<<1; //bit1  小时计设置密码正确
	}	
	if(VarCanGpsUrgencyState>0)
	{
		VarSendDataID220[0] |= 1<<2;//bit2 GPS紧急解锁状态	
	}
	if(VarCanGpsUnlockPSDOK)
	{
		VarSendDataID220[0] |= 1<<3;//bit3 GPS回传	
	}
	if(VarCanGpsUrgencyPSDoK)
	{
		VarSendDataID220[0] |= 1<<4; //bit4 GPS紧急解锁密码正确
	}
	if(VarCanGpsCancel>0)
	{
		VarSendDataID220[0] |= 1<<5; //bit5 GPS取消状态
	}
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x221	<<<<<<<<<<<<<<<<<
	VarSendDataID221[0] = VarRecDataID_0x18FEEE00[0];//水温,接收端需要减40
	VarSendDataID221[1] = (UINT8)(VarHydraulicOilTempFilter);//液压油温1
	VarSendDataID221[2] = (UINT8)(VarEngineSpeedNow>>8); //发动机转速高字节
	VarSendDataID221[3] = (UINT8)(VarEngineSpeedNow); //发动机转动低字节
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x222	<<<<<<<<<<<<<<<<<
	VarSendDataID222[2] = (UINT8)(VarBKRFlowNowCurrent>>8); //辅具流量调节电磁阀当前电流
	VarSendDataID222[3] = (UINT8)(VarBKRFlowNowCurrent); 
	VarSendDataID222[4] = (UINT8)(VarHydraulicCoolingPumpValveCurrent>>8); //液压冷却风扇电磁阀当前电流
	VarSendDataID222[5] = (UINT8)(VarHydraulicCoolingPumpValveCurrent); 
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x224	<<<<<<<<<<<<<<<<<
	if(VarValveCurrentNow<25)
	{
		temp_uint16=0;//电流<25mA显示为0
	}
	else
	{
		temp_uint16=VarValveCurrentNow;
	}
	VarSendDataID224[4] =(UINT8)(temp_uint16>>8); //比例阀电流值
	VarSendDataID224[5] =(UINT8)(temp_uint16);
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x227	<<<<<<<<<<<<<<<<<
	//VarSendDataID227[3] = (UINT8)(VarHydraulicOilTemp2Filter);//液压油温2

	// >>>>>>>>>>>>>>>>>>>>>> ID=0x22F	<<<<<<<<<<<<<<<<<
	//Byte0
	if((VarDialGrade>10) || (VarDialGrade==255))
	{
		VarSendDataID22F[0] |= 1<<0; //bit0 油门表盘传感器异常
	}
	if(VarP1PressureSensorEorror>0)
	{
		VarSendDataID22F[0] |= 1<<1; //bit1 P1压力传感器异常
	}
	if(VarP2PressureSensorEorror>0)
	{
		VarSendDataID22F[0] |= 1<<2; //bit2 P2压力传感器异常
	}
	/*if(VarBrokenPiPressureSensorEorror>0)
	{
		VarSendDataID22F[0] |= 1<<3; //bit3 破碎先导压力传感器异常
	}
	*/
	if(VarFuelSensorError)
	{
		VarSendDataID22F[0] |= 1<<4; //bit4  油量传感器异常报警
	}
	if(VarPiPressureSensorEorror)
	{
		VarSendDataID22F[0] |= 1<<5; //bit5 先导压力传感器异常
	}
	//Byte1
	
	if(VarBoomUpPressureSensorEorror>0) 
	{
		VarSendDataID22F[1] |= (UINT8)1<<4;//bit4 b-up pre error//动臂上升压力传感器故障
	}

	if(VarBoomDownPressureSensorEorror>0) 
	{
		VarSendDataID22F[1] |= (UINT8)1<<5; // bit0 B-down.pre error 动臂下降压力传感器故障
	}
	//Byte2
	
	if(VarBoomBigPressureSensorEorror>0) 
	{
		VarSendDataID22F[2] |= (UINT8)1; //bit2 b-rod.pre error 动臂小腔压力传感器故障
	}
	if(VarBoomSmallPressureSensorEorror>0) //
	{
		VarSendDataID22F[2] |= (UINT8)1<<1; //bit3 b-cap pre error 动臂大腔压力传感器故障
	}
	
	if(VarBucketArmPressureSensorEorror>0) //斗杆大腔
	{
		VarSendDataID22F[2] |= (UINT8)1<<2; // bit0 Arm-cap Pre Error
	}
	if(VarAiCBucketArmRodSensorEorror>0) //斗杆小腔
	{
		VarSendDataID22F[2] |= (UINT8)1<<3; // bit1  Arm-rod Pre Error
	}
    if(VarAiCBucCapPressureSensorEorror>0) 
	{
    	VarSendDataID22F[2] |= (UINT8)1<<4; //bit2  Buc-cap Pre Error
	}
	if(VarHydraulicOilTempSensorError)
	{
		VarSendDataID22F[2] |= 1<<6; //bit6 液压油温传感器异常
	}
	

//	if(VarHydraulicOilTemp2SensorError)
//	{
//		VarSendDataID22F[2] |= 1<<7; //bit7 液压油温传感器1异常
//	}
	//Byte3
	if(VarValveError>0)
	{
		VarSendDataID22F[3] |= 1<<1; //bit1 泵功率控制比例阀异常
	}
	if(VarCanEcmNoDataFlag)
	{
		VarSendDataID22F[3] |= 1<<5;//bit5 ECM与控制器通讯故障
	}
	//Byte4
	if(VarGpsCanBusError)
	{
		VarSendDataID22F[4] |= 1<<4;//bit4 GPS与控制器通讯故障
	}
	
// >>>>>>>>>>>>>>>>>>>>>> ID=0x231	<<<<<<<<<<<<<<<<<
	//Byte0
	if(VarGpsLockWork_A)
	{
		VarSendDataID231[0] |= 1<<0;//bit0 A锁车状态(实际锁车)
	}
	if(VarGpsLockWork_B)
	{
		VarSendDataID231[0] |= 1<<1;//bit1 B锁车状态(实际锁车)
	}
	if(VarGpsLockWork_C)
	{
		VarSendDataID231[0] |= 1<<2;//bit2 C锁车状态(实际锁车)
	}
	if(VarGpsLockWork_D)
	{
		VarSendDataID231[0] |= 1<<3;//bit3 D锁车状态(实际锁车)
	}
	if(VarGpsLockState_A)
	{
		VarSendDataID231[0] |= 1<<5;//bit5 A锁车指令状态(收到锁车指令报警)
	}
	if(VarGpsLockState_B)
	{
		VarSendDataID231[0] |= 1<<6;//bit6 B锁车指令状态(收到锁车指令报警)
	}
	if(VarGpsLockState_C)
	{
		VarSendDataID231[0] |= 1<<7;//bit7 C锁车指令状态(收到锁车指令报警)
	}
	//Byte1
	if(VarGpsLockState_D)
	{
		VarSendDataID231[1] |= 1<<0;//bit0 D锁车指令状态(收到锁车指令报警)
	}
	//Byte2
	if( VarCan2MonthLockState )
	{
		VarSendDataID231[2] |= 0x01; //bit0 G005 盲区锁车
	}
	if( VarCanUncoverLockState )
	{
		VarSendDataID231[2] |= 0x02; //bit1 G007 拆盖锁车
	}
	if( VarCanBusLockState )
	{
		VarSendDataID231[2] |= 0x04; //bit2 G008 总线锁车
	}
	if( VarGpsSIMCardError )
	{
		VarSendDataID231[2] |= 0x08; //bit3 G009 SIM卡锁车
	}
	if( VarCanAntennaCutLockState )
	{
		VarSendDataID231[2] |= 0x10; //bit4 G006 天线断开锁车
	}
	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x233	<<<<<<<<<<<<<<<<<
	temp_uchar = FunSystemPasswordComput(4,&Password_1,VarEngineWorkTime1H,VarEngineWorkTime1M,VarCanExcavatorId);
	if(temp_uchar==0)
	{
		VarMonitorPassword = Password_1;
	}
	//byte2~4:用户超级密码
	VarSendDataID233[0] = (UINT8)(VarMonitorPassword>>16);
	VarSendDataID233[1] = (UINT8)(VarMonitorPassword>>8);
	VarSendDataID233[2] = (UINT8)(VarMonitorPassword); 
	
	//控制器版本信息SWCV-ABC-DE-FGH
	//ABC-222
	temp_uint16 = DefExcavatorEngineType*100+DefineHardwareVersion;//A:2-电喷发动机
	VarSendDataID233[3] = (UINT8)(temp_uint16>>8);     //硬件版本BC：22-sw控制器2代
	VarSendDataID233[4] = (UINT8)temp_uint16;
	//DE
	VarSendDataID233[5] = (UINT8)VarCMCommunicationVersion; //通讯协议版本号
	//FGH 
	VarSendDataID233[6] = (UINT8)(DefineSoftVersion>>8);     //软件升级版本    
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
	
	//节能显示 ID236
	if(VarAirPressureLowFlag>0)//蓄能器气压低报警
	{
		VarSendDataID236[0] |= (UINT8)1<<0;  //bit0	
	}
	
    if(VarPAccumPressureSensorEorror>0) 
	{
		VarSendDataID236[0] |= (UINT8)1<<1; // bit1  ac.pre error 蓄能器压力传感器故障
	}
	
	if(VarPAccumAirSensorError>0)
	{
		VarSendDataID236[0] |= (UINT8)1<<2;  //bit2	atoms.pre error //蓄能器气压压力传感器故障	
	}
	
	VarSendDataID236[0] |= (UINT8)0<<3;  //bit3	回转压力1传感器故障	
	VarSendDataID236[0] |= (UINT8)0<<4;  //bit4	回转压力2传感器故障
	
    if(VarCartridgeValveFaultFlag>0) //插装阀故障
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
		VarSendDataID236[2] |= (UINT8)1<<2; //先导压力开关故障
	}
	
	
	//节能显示 ID237
    VarSendDataID237[0] = VarBoomWorkModeNow;//动臂节能控制（1-9）模式
	if(VarBoomPowerSaveFlag>0) 
	{
		VarSendDataID237[1] |= (UINT8)1;//bit0 b.mode返回值 
	}
	if(VarRatatorPowerSaveFlag>0) 
	{
		VarSendDataID237[1] |= (UINT8)1<<1;//bit1 R.mode返回值
	}
	if(VarXieYaFlag>0) 
	{
		VarSendDataID237[1] |= (UINT8)1<<2;//bit2 AC.decompre返回值
	}

	if(VarPAiBoomUpPressure>5)
	{
		VarSendDataID237[1] |= (UINT8)(1<<3);  //bit3	//计算动臂上升先导压力开关（大于0.5Mpa为开）
	}
  
	if(VarPAiBoomDownPressure>5)
	{
		VarSendDataID237[1] |= (UINT8)(1<<4);  //bit4	//计算动臂下降先导压力开关（大于0.5Mpa为开）
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
		VarSendDataID237[2] |= (UINT8)(1<<7);  //bit7 先导压力开关	
	}
  
	//节能显示 ID238
 	VarSendDataID238[0] = (UINT8)(VarPAccumPressureFilter>>8 );//pin19,蓄能器压力值单位bar
 	VarSendDataID238[1] = (UINT8)((VarPAccumPressureFilter));  

 	VarSendDataID238[2] = (UINT8)(VarPAccumAirPressureBar>>8 );//蓄能器气压压力，单位bar
 	VarSendDataID238[3] = (UINT8)((VarPAccumAirPressureBar));  
 	
 	VarSendDataID238[4] = 0;//回转压力1
 	VarSendDataID238[5] = 0; 
 	
 	VarSendDataID238[6] = 0;//回转压力2
 	VarSendDataID238[7] = 0; 
 	
	//节能显示 ID239
 	VarSendDataID239[0] = (UINT8)(VarDoDT8>>8  );//DT8反馈电流值VarValveDT8CurrentNow
    VarSendDataID239[1] = (UINT8)((VarDoDT8));
    
 	VarSendDataID239[2] = 0; //DT11电流值
    VarSendDataID239[3] = 0;
    
 	VarSendDataID239[4] = 0; //DT12电流值
    VarSendDataID239[5] = 0;
	
/**************************************************************
**控制器数据发送至GPS
**大端模式，高字节在前，低字节在后	
**************************************************************/	
	// >>>>>>>>>>>>>>>>>>>>>> ID=0x2E1	<<<<<<<<<<<<<<<<<
	//远程平台应答，byte0-1被应答ID，byte2-3被应答消息SN

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
	VarSendDataID2F0[0] = VarFuelVolumeFilter; //燃油油位：0-100.0xFF表示无效，单位%
	VarSendDataID2F0[1] = 255;//车速：0xFF表示无效，单位0.1km/h
	VarSendDataID2F0[2] = 255;
/**************************************************************
**控制器数据发送至记录仪
**小端模式	
**************************************************************/		
	//Can总线记录数值初始化为零
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
	VarCanSendCanF11[1] = (UINT8)(VarPAiBoomUpPressure>>8);//上升先导压力
	VarCanSendCanF11[2] = (UINT8)(VarPAiBoomDownPressure);   //单位bar
	VarCanSendCanF11[3] = (UINT8)(VarPAiBoomDownPressure>>8);	//下降先导压力
	VarCanSendCanF11[4] = (UINT8)VarPAccumPressureFilter;
	VarCanSendCanF11[5] = (UINT8)(VarPAccumPressureFilter>>8);	//蓄能器油压
	VarCanSendCanF11[6] = (UINT8)(VarPAccumAirPressureBar); //  蓄能器气压
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
	VarCanSendCanF13[1] = (UINT8)(VarBoomBigPressureBar>>8);//动臂大腔
	VarCanSendCanF13[2] = (UINT8)(VarBoomSmallPressureBar);   
	VarCanSendCanF13[3] = (UINT8)(VarBoomSmallPressureBar>>8);	//动臂小腔
	VarCanSendCanF13[4] = (UINT8)(VarPBucketArmPressure);
	VarCanSendCanF13[5] = (UINT8)(VarPBucketArmPressure>>8);	//斗杆大腔
	VarCanSendCanF13[6] = (UINT8)(VarPBucketArmRodPressure);
	VarCanSendCanF13[7] = (UINT8)(VarPBucketArmRodPressure>>8);//斗杆小腔
	
	//ox514
	
	VarCanSendCanF14[0] = (UINT8)(VarBoomWorkModeNow); //工作模式
	VarCanSendCanF14[1] = (UINT8)(0);
	VarCanSendCanF14[2] = (UINT8)(VarEngineSpeedNow);   
	VarCanSendCanF14[3] = (UINT8)(VarEngineSpeedNow>>8);	//发动机转速
	VarCanSendCanF14[4] = (UINT8)(VarP1PressureFilter);
	VarCanSendCanF14[5] = (UINT8)(VarP1PressureFilter>>8);	//P1
	VarCanSendCanF14[6] = (UINT8)(VarP2PressureFilter);
	VarCanSendCanF14[7] = (UINT8)(VarP2PressureFilter>>8);//P2
	
	//0x515
	VarCanSendCanF15[0] = (UINT8)(VarPBucCapPressure); //铲斗大腔压力
	VarCanSendCanF15[1] = (UINT8)(VarPBucCapPressure>>8);//
	VarCanSendCanF15[2] = (UINT8)(VarDiTreadPre);   //行走压力开关
	VarCanSendCanF15[3] = (UINT8)(0);	//
	VarCanSendCanF15[4] = (UINT8)(VarRecDataID_0x18FFF800[3]-125);//发动机扭矩百分比
	VarCanSendCanF15[5] = (UINT8)(0);	//
	VarCanSendCanF15[6] = (UINT8)(VarRecDataID_0x18FEF200[0]);//临时增加瞬时油耗
	VarCanSendCanF15[7] = (UINT8)(VarRecDataID_0x18FEF200[1]);//
	
	//0x516
	VarCanSendCanF16[0] = (UINT8)(VarRecDataID_0x18FEE900[4]); //五十铃发动机累计油耗（单位：0.5L）低字节
	VarCanSendCanF16[1] = (UINT8)(VarRecDataID_0x18FEE900[5]);//
	VarCanSendCanF16[2] = (UINT8)(VarRecDataID_0x18FEE900[6]);   //
	VarCanSendCanF16[3] = (UINT8)(VarRecDataID_0x18FEE900[7]);	//五十铃发动机累计油耗（单位：0.5L）高字节
	VarCanSendCanF16[4] = (UINT8)(0);//
	VarCanSendCanF16[5] = (UINT8)(0);	//
	VarCanSendCanF16[6] = (UINT8)(0);
	VarCanSendCanF16[7] = (UINT8)(0);//
	
}
	
/**************************************************************
**函数名：FunCanDisplaySendData()
**功能描述：发送数据至显示屏与GPS
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanDisplayGpsSendData(void)
{	
	//CAN0数据发送至GPS、显示屏 311、312
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
	


	//CAN0数据发送GPS	 311、312
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

	//CAN数据发送至CAN总线面板
//	if(LibTimer(17,1,20,1))
//	{
//		LibCan1SendData(13,0x19B,0,VarSendDataID19B,8);
//	}
	

	//can0数据发数据记录仪 311、312
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

