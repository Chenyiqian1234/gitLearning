#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppVar.h"
/**************************************************************
**函数名：FunCanDataDeal()
**功能描述：CAN总线数据处理，包括显示屏、GPS与发动机MCU之间的通讯
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanDataDeal(void)
{
	//控制器与显示屏、GPS之间的通讯
	FunCanDisplayGpsReceiveData();
	FunCanDisplayGpsPackSendData();
	FunCanDisplayGpsSendData();
	
	//控制器与发动机MCU之间的通讯
	FunCanReceiveEngineData();
	FunCanSendEngineDataPack();	
	FunCanSendEngineData();
}
/**************************************************************
**函数名：FunCanReceiveEngineData()
**功能描述：接收发动机控制器的数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanReceiveEngineData(void)
{
	UINT8 VarBool;
	UINT32 Temp_ulong;
	//电喷发动机厂家:0-康明斯，1-五十铃，2-潍柴	
	switch(VarExcavatorEngineType)
	{
		case 0:FunCanReceiveCumminsData();		//接收发动机ECU的CAN数据
				FunWeiChaiFaultSPNCodeGet();
			//	FunCumminsFaultSPNCodeGet();	//故障代码获取
				FunCumminsFaultCodeDiagnose();	//故障诊断
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
	//控制器与发动机通讯故障判断，延时10S判断
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
**函数名：FunCanSendEngineDataPack()
**功能描述：组合发送至发动机控制器的数据
**传入参数：无
**输出参数：无
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
**函数名：FunCanSendEngineData()
**功能描述：将组合的数据发送至发动机控制器
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanSendEngineData(void)
{
	//CAN数据发送,转速控制10ms发送周期
	if(LibTimer(10,1,10,1))
	{
		VarCanSendEngineStep++;
		//电喷发动机厂家:0-康明斯，1-五十铃，2-潍柴	
		switch(VarExcavatorEngineType)
		{
			case 0:
			//	LibCan0SendData(13,0x0C000003,1,VarSendDataID_0x0C000003,8);break;//转速控制
			  //  LibCan0SendData(13,0x0CF00330,1,VarSendDataID_0x0CF00330,8);//开度控制
			    LibCan0SendData(13,0x18FDCB30,1,VarSendDataID_0x18FDCB30,8);break;//调速率控制

			case 1:
				
				if(VarEngineNeedStopFlag)//发动机停机控制
				{
					LibCan0SendData(13,0x18FEE4E4,1,VarSendDataID_0x18FEE4E4,8);
				}
				else//发动机转速控制
				{
				    //LibCan0SendData(12,0x18EA0028,1,VarSendDataID_0x18EA0028,8);
					LibCan0SendData(13,0x0C0000E4,1,VarSendDataID_0x0C0000E4,8);
				}
			
		        LibCan0SendData(12,0x18EA00FA,1,VarSendDataID0x18EA00FA,8);//向发动机发送数据请求
				break;
			case 2:
			    LibCan0SendData(13,0x0C000003,1,VarSendDataID_0x0C000003,8);break;//转速控制
			default:break;

		}
	}
}
