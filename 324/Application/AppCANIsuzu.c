#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppVar.h"
/**************************************************************
**函数名：FunCanReceiveISUZUData()
**功能描述：接收五十铃发动机ECU的数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanReceiveISUZUData(void)
{
	UINT16 temp_A;
	UINT32 temp_B;
	UINT16 temp_C;
	UINT32 temp_D;
	FLOAT64 temp_E;
  	VarCanEngineNoDataFlag=1;
  	
  	
  	// ID=0x18FFF800
	if(LibCan0ReceiveFlag(0))
	{
		VarCanEngineNoDataFlag=0;
		LibCan0ReadReceiveData(0,VarRecDataID_0x18FFF800);
		VarCanEngineTorque = (INT8)(VarRecDataID_0x18FFF800[3]);//扭矩百分比,-125%~125%，接收端需减125.
	}
  	
	
   // ID=0x0CF00400
	if(LibCan0ReceiveFlag(1))
	{
	    VarCanEngineNoDataFlag=0;
	    LibCan0ReadReceiveData(1,VarRecDataID_0CF00400);
//	    VarCanEngineTorque = (INT8)(VarRecDataID_0CF00400[2]-125);//扭矩百分比,-125%~125%
	    VarCanEngineSpeed = (UINT16)(VarRecDataID_0CF00400[4]<<8);
	    VarCanEngineSpeed += VarRecDataID_0CF00400[3];
	    VarEngineSpeedNow = (UINT16)(VarCanEngineSpeed/8);	 //分辨率0.125rpm 
	}
	
	
	// ID=0x18FFF900
	if(LibCan0ReceiveFlag(2))
	{
	    VarCanEngineNoDataFlag=0;
	    LibCan0ReadReceiveData(2,VarRecDataID_0x18FFF900);
	      //接收CAN报警数据,五十铃发动机有，其余无
	    if(VarExcavatorEngineType==1)
	    {
			VarCanInFuelFilterAlarm  = (UINT8)((VarRecDataID_0x18FFF900[4]&0xB0)>>6);//燃油滤芯堵塞：0-无，1-Step1;2-Step2
			VarCanEngineOilPreAlarm = (UINT8)((VarRecDataID_0x18FFF900[4]&0x30)>>4);//机油压力地下:0-无，1-有
			VarCanInPreBoostAlarm = (UINT8)((VarRecDataID_0x18FFF900[4]&0x0B)>>2);//增压温度上升
			VarCanInFuelTemAlarm = (UINT8)((VarRecDataID_0x18FFF900[4]&0x03)>>0);//燃油温度上升

			VarCanInWaterTempAlarm  = (UINT8)((VarRecDataID_0x18FFF900[5]&0xB0)>>6);//水温上升报警
			VarCanInFeicheAlarm = (UINT8)((VarRecDataID_0x18FFF900[5]&0x30)>>4);//飞车报警
			VarCanInStopUrgency = (UINT8)((VarRecDataID_0x18FFF900[5]&0x0B)>>2);//紧急停车信号
			VarCanInPreheat = (UINT8)((VarRecDataID_0x18FFF900[5]&0x03)>>0);//预热信号
	    }
	}
	
	
   // ID=0x18FEEE00
	if(LibCan0ReceiveFlag(3))
	{
	    VarCanEngineNoDataFlag=0;
	    LibCan0ReadReceiveData(3,VarRecDataID_0x18FEEE00);
	    //水温计算
	    if(VarRecDataID_0x18FEEE00[0]>40)
	    {
	       VarCanEngineWaterTemp =(UINT8)(VarRecDataID_0x18FEEE00[0]-40);//减40，0~250：-40~210 C	
	    }
	    else
	    {
	       VarCanEngineWaterTemp=0;	
	    }
    	//水温高报警
		if(VarCanEngineWaterTemp>VarWaterHighAlarmLimit)
		{
			VarCanWaterHihgAlarm = 1;
		}
		else
		{
			VarCanWaterHihgAlarm = 0;
		}
	}
	
	
	// ID=0x18FEEF00
	if(LibCan0ReceiveFlag(4))
	{
	    VarCanEngineNoDataFlag=0;
	    LibCan0ReadReceiveData(4,VarRecDataID_0x18FEEF00);
	    VarCanEngineOilPressure = (UINT16)(VarRecDataID_0x18FEEF00[3]);//机油压力:0~1000Kpa,接收端需乘4.
	    VarCommonRailPressure = (UINT16)(VarRecDataID_0x18FEEF00[5]<<8);
	    VarCommonRailPressure += (UINT16)(VarRecDataID_0x18FEEF00[4]);//共轨压力:0～251 (MPa),接收端需除256.
	}
	
	
	//0x18FEB100
	if(LibCan0ReceiveFlag(5))
	{
		VarCanEngineNoDataFlag = 0;
		LibCan0ReadReceiveData(5,VarRecDataID0x18FEB100);
					
		temp_A=VarRecDataID0x18FEB100[5];
		temp_A=temp_A<<8;
		temp_A=temp_A+VarRecDataID0x18FEB100[4];
		
		temp_B=VarRecDataID0x18FEB100[6];
		temp_B=temp_B<<16;
		VarEngineSpeedWorkTome = VarRecDataID0x18FEB100[7];
		VarEngineSpeedWorkTome=VarEngineSpeedWorkTome<<24;
		
		VarEngineSpeedWorkTome=VarEngineSpeedWorkTome+temp_B+temp_A;//发动机总工作时间:0～210,554,060.75H,接收端需乘0.05.
	}

	
	// ID=0x18FEF500
	if(LibCan0ReceiveFlag(6))
	{
	    VarCanEngineNoDataFlag=0;
	    LibCan0ReadReceiveData(6,VarRecDataID_0x18FEF500);
	    if((VarExcavatorEngineType==0)||(VarExcavatorEngineType==1))
	    {
			VarCanEngineAtmosPressrue =(UINT8)(VarRecDataID_0x18FEF500[0]);//大气压力:0~125KPa,接收端需乘0.5.
			VarCanEngineAirInTemp =(INT16)(VarRecDataID_0x18FEF500[5]);//进气温度:-40~210°C,接收端需减40.
	    }
	    else if(VarExcavatorEngineType==2)
	    {
	    	VarCanEngineAtmosPressrue =(UINT8)(VarRecDataID_0x18FEF500[0]);//大气压力:0~125KPa,接收端需乘0.5.
			VarCanEngineAirInTemp =(INT16)(VarRecDataID_0x18FEF500[5]);//进气温度:-40~210°C,接收端需减40.
	    }
	}
	
	
	// ID=0x18FEF600
	if(LibCan0ReceiveFlag(7))
	{
	    VarCanEngineNoDataFlag=0;
	    LibCan0ReadReceiveData(7,VarRecDataID_0x18FEF600);
	    VarAftertreatmentDPFDifferentialPressure = (UINT16)(VarRecDataID_0x18FEF600[1]<<8);//DPf尾气压差：-250～250 (kPa),接收端需乘0.02，再减250. 
	    VarAftertreatmentDPFDifferentialPressure += (UINT16)(VarRecDataID_0x18FEF600[0]);
	    VarAftertreatmentDPFDifferentialPressure = (VarAftertreatmentDPFDifferentialPressure/50)-250;
	    VarCanEngineBoostTemp =(INT8)(VarRecDataID_0x18FEF600[2]);//增压温度:-40~210°C, 接收端需减40.
	    VarCanEngineBoostPressrue =(UINT16)(VarRecDataID_0x18FEF600[3]);//增压压力:0~500KPa,接收端需乘2.
	    VarIntakeManifoldTemp=(VarRecDataID_0x18FEF600[4]);//进气歧管内温度：-40~210°C, 接收端需减40.
	    VarAftertreatmentDOCIntakeTemp=(VarRecDataID_0x18FEF600[5])*5;//后处理尾气温度(DOC前)：0-1000°C,接收端需乘5.
	    VarAftertreatmentDOCOutletTemp=(VarRecDataID_0x18FEF600[6])*5;//后处理尾气温度(DOC后)：0-1000°C,接收端需乘5.
	    VarInterCoolInletTemp=(VarRecDataID_0x18FEF600[7]);//中冷器入口温度：-40~210°C, 接收端需减40.
	}
	//0x18FEE900
	if(LibCan0ReceiveFlag(8))
	{
		VarCanEngineNoDataFlag = 0;
		LibCan0ReadReceiveData(8,VarRecDataID0x18FEE900);
	//发动机总油耗:0～2105540607.5L,接收端需乘0.5.	
		temp_C=VarRecDataID0x18FEE900[5];
		temp_C=temp_C<<8;
		temp_C=temp_C+VarRecDataID0x18FEE900[4];
		
		temp_D=VarRecDataID0x18FEE900[6];
		temp_D=temp_D<<16;
		VarEngineFuelYouHao = VarRecDataID0x18FEE900[7];
		VarEngineFuelYouHao=VarEngineFuelYouHao<<24;
		
		VarEngineFuelYouHao=VarEngineFuelYouHao+temp_D+temp_C;//总油耗0.5L		    
	}
	
	//发动机平均油耗L/h
	if(VarEngineSpeedWorkTome!=0)
	{
		temp_E=VarEngineFuelYouHao;
		temp_E=temp_E/VarEngineSpeedWorkTome;
		temp_E=temp_E*10; //平均油耗计算,0.5/0.05=10;
	}
	VarEngineAverageFuelYouHao=(UINT16)temp_E*100;//显示屏接收端统一除100
	  
/*	
	//0x18FFE200
	if(LibCan0ReceiveFlag(9))
	{
		VarCanEngineNoDataFlag = 0;
		LibCan0ReadReceiveData(9,VarRecDataID_0x18FFE200);
		
		EscapeModeLamp = (UINT8)(VarRecDataID_0x18FFE200[5]&0x10); //bit6-5:01
		NoPowerLamp = (UINT8)(VarRecDataID_0x18FFE200[5]&0x40); //bit8-7:01
		AftertreatmentFailureLamp = (UINT8)(VarRecDataID_0x18FFE200[6]&0x04); //bit4-3:01
		EXHSystemLamp = (UINT8)(VarRecDataID_0x18FFE200[6]&0x10); //bit6-5:01
	
		//驾驶员警告灯状态
		if((VarRecDataID_0x18FFE200[6]&0xC0)==0x40)
		{
			DriverWarningLamp = 1; //bit8-7:01，驾驶员警告灯常亮
		}
		else if((VarRecDataID_0x18FFE200[6]&0xC0)==0x80)
		{
			DriverWarningLamp = 2; //bit8-7:10，驾驶员警告灯慢闪
		}
		else if((VarRecDataID_0x18FFE200[6]&0xC0)==0xC0)
		{
			DriverWarningLamp = 3; //bit8-7:11，驾驶员警告灯快闪
		}
		else
		{
			DriverWarningLamp = 0;
		}
	}	    
*/	 
	
	//0x18FED900，再生指示灯状态
	if(LibCan0ReceiveFlag(9))
	{
		VarCanEngineNoDataFlag = 0;
		LibCan0ReadReceiveData(9,VarRecDataID_0x18FED900);
		VarAutoRegenerationLamp = (UINT8)(VarRecDataID_0x18FED900[5]&0x40);//bit8~7:01，自动再生中
		if((VarRecDataID_0x18FED900[5]&0x30)==0x10)
		{
			VarManualRegenerationLamp = 1;//bit6-5:01，手动再生中
		}
		else if((VarRecDataID_0x18FED900[5]&0x30)==0x20)
		{
			VarManualRegenerationLamp = 2;//bit5-4:10，手动再生提醒:慢闪
		}
		else if((VarRecDataID_0x18FED900[5]&0x30)==0x30)
		{
			VarManualRegenerationLamp = 3;//bit5-4:11，手动再生提醒:快闪
		}
		else
		{
			VarManualRegenerationLamp = 0;
		}	
		
		if((VarManualRegenerationLamp==1)&&(VarRecDataID_0x18FED900[7]&0x08))//手动再生辅助负载电磁阀开闭判断：手动再生中及再生标识为1时开启
		{ 
			VarDoManualRegenrationLoadEnabled = 1;
		}
		else
		{
			VarDoManualRegenrationLoadEnabled = 0;
		}
	}
	
	
	//0x18FF0300
	if(LibCan0ReceiveFlag(10))
	{
		VarCanEngineNoDataFlag = 0;
		LibCan0ReadReceiveData(10,VarRecDataID_0x18FF0300);
		VarDPFRegenerationStatus = (VarRecDataID_0x18FF0300[1]&0x0F);//DPF再生状态信号bit0-3:0-8;
		VarDPFTripStatus = (VarRecDataID_0x18FF0300[3]&0x0F);	//DPF Trip Statusit bit0-3:0-15;
		VarDPFPMAccumulationStatus = ((VarRecDataID_0x18FF0300[3]>>4)&0x0F);//DPF PM堆积状态 bit4-7:0-15;
		VarDPFModeL = (UINT16)(VarRecDataID_0x18FF0300[7]<<8);  //DPF模式：0-999.
		VarDPFModeL += (UINT16)(VarRecDataID_0x18FF0300[6]);
	}
	
	/*if(LibCan0ReceiveFlag(11))
	{
		LibCan0ReadReceiveData(11,VarRecDataID_0x18FEF200);
	}*/

}
/**************************************************************
**函数名：FunCanSendEngineDataPack()
**功能描述：组合发送至五十铃发动机ECU的数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanSendISUZUDataPack(void)
{
	 //ID=0x0C0000E4,转速控制
	VarSendDataID_0x0C0000E4[0]=89;//bit8-bit7:01运行再生
	VarSendDataID_0x0C0000E4[1]=(UINT8)(VarCanEngineLevelSpeed*8);
	VarSendDataID_0x0C0000E4[2]=(UINT8)((VarCanEngineLevelSpeed*8)>>8);
	//VarSendDataID_0x0C0000E4[1]=(UINT8)(1250*8);
	//VarSendDataID_0x0C0000E4[2]=(UINT8)((1250*8)>>8);
	if(EscapeModeButton)
	{
		VarSendDataID_0x0C0000E4[3]=4;//逃脱模式：bit3-4：01-打开
	}
	else
	{
		VarSendDataID_0x0C0000E4[3]=255;
	}
	VarSendDataID_0x0C0000E4[4]=255;
	VarSendDataID_0x0C0000E4[5]=0;//油门位置发0，才能进行再生
	VarSendDataID_0x0C0000E4[6]=255;
	VarSendDataID_0x0C0000E4[7]=255;
	
	//发动机机停机控制
	VarSendDataID_0x18FEE4E4[0]=255;
	VarSendDataID_0x18FEE4E4[1]=255;
	VarSendDataID_0x18FEE4E4[2]=255;
	VarSendDataID_0x18FEE4E4[3]=255;
	VarSendDataID_0x18FEE4E4[4]=253;//bit1-0:00-不关机，01-关机
	VarSendDataID_0x18FEE4E4[5]=255;
	VarSendDataID_0x18FEE4E4[6]=255;
	VarSendDataID_0x18FEE4E4[7]=255;


	//五十铃发动机数据请求
	VarSendDataID0x18EA00FA[0] = 0xB1;
	VarSendDataID0x18EA00FA[1] = 0xFE;
	VarSendDataID0x18EA00FA[2] = 0x00;
	VarSendDataID0x18EA00FA[3] = 0;
	VarSendDataID0x18EA00FA[4] = 0;
	VarSendDataID0x18EA00FA[5] = 0;
	VarSendDataID0x18EA00FA[6] = 0;
	VarSendDataID0x18EA00FA[7] = 0;

}
/**************************************************************
**函数名：FunISUZUFaultSPNCodeGet()
**功能描述：五十铃发动机的故障代码提取
**传入参数：无
**输出参数：无
**************************************************************/
void FunISUZUFaultSPNCodeGet(void)
{
	UINT8 i=0,k=0;
	UINT16 A,B,C,D;
	/**********单条故障代码***********/
	if(VarIsuzuFaultCodeSingle>0)
	{
		VarIsuzuSPN[0]=(UINT32)VarRecDataID_0x18FECA00[2]*2048+(UINT16)VarRecDataID_0x18FECA00[3]*8+(UINT8)((VarRecDataID_0x18FECA00[4]&0xE0)>>5);
		VarIsuzuFMI[0]=(UINT8)(VarRecDataID_0x18FECA00[4]&0x1F);
		VarUartFaultCode=(UINT16)(VarIsuzuSPN[0]);//test..............
		VarIszuFaultSPNNumber=1;
	}
	/**********多条故障代码***********/
	if(VarIsuzuFaultCodeMany>0)
	{
		//将所有的故障代码都放入二维矩阵中，二维矩阵的第i行表示第i个循环NO.
		for(i=0;i<8;i++)
		{
			VarIsuzuFault[VarRecDataID_0x1CEBFF00[0]][i]=VarRecDataID_0x1CEBFF00[i];
			//获取当前故障代码循环NO.数
			if(VarIsuzuCodeNumber<VarRecDataID_0x1CEBFF00[0])
			{
				VarIsuzuCodeNumber=VarRecDataID_0x1CEBFF00[0];
			}
		}
		//计算故障代码中的SPN
		for(i=1;i<VarIsuzuCodeNumber+1;i++)
		{
			switch(i%4)
			{
				case 0:
					VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][4]&0x1F);
					VarIsuzuSPN[k++] = (UINT32)VarIsuzuFault[i][2]*2048+(UINT16)VarIsuzuFault[i][3]*8+(UINT8)((VarIsuzuFault[i][4]&0xE0)>>5);
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					break;
				case 1:
				    VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][5]&0x1F);
					VarIsuzuSPN[k++] = (UINT32)VarIsuzuFault[i][3]*2048+(UINT16)VarIsuzuFault[i][4]*8+(UINT8)((VarIsuzuFault[i][5]&0xE0)>>5);
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					if(i!=1)//不是NO.1，则有两条故障代码
					{
						VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][1]&0x1F);
						VarIsuzuSPN[k++] = (UINT32)VarIsuzuFault[i-1][6]*2048+(UINT16)VarIsuzuFault[i-1][7]*8+(UINT8)((VarIsuzuFault[i][1]&0xE0)>>5);
						VarIszuFaultSPNNumber = (UINT8)(k-1);
					}
					break;
				case 2:
				    VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][6]&0x1F);
				    A=(UINT16)VarIsuzuFault[i][4]*2048;B=(UINT16)VarIsuzuFault[i][5]*8;C=(UINT8)((VarIsuzuFault[i][6]&0xE0)>>5);
					D=A+B+C;
					VarIsuzuSPN[k++] = (UINT32)VarIsuzuFault[i][4]*2048+(UINT16)VarIsuzuFault[i][5]*8+(UINT8)((VarIsuzuFault[i][6]&0xE0)>>5);
					VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][2]&0x1F);
					VarIsuzuSPN[k++] = (UINT32)VarIsuzuFault[i-1][7]*2048+(UINT16)VarIsuzuFault[i][1]*8+(UINT8)((VarIsuzuFault[i][2]&0xE0)>>5);
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					break;
				case 3:
				    VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][3]&0x1F);
					VarIsuzuSPN[k++] = (UINT32)VarIsuzuFault[i][1]*2048+VarIsuzuFault[i][2]*8+(UINT8)((VarIsuzuFault[i][3]&0xE0)>>5);
					VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][7]&0x1F);
					VarIsuzuSPN[k++] = (UINT32)VarIsuzuFault[i][5]*2048+VarIsuzuFault[i][6]*8+(UINT8)((VarIsuzuFault[i][7]&0xE0)>>5);
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					break;
				default:break;
			}
		}
		VarEngineFaultCode2 = (UINT16)VarIsuzuSPN[1];
		VarEngineFaultCode3 = (UINT16)VarIsuzuSPN[2];
		VarEngineFaultCode4 = (UINT16)VarIsuzuSPN[3];
		VarEngineFaultCode5 = (UINT16)VarIsuzuSPN[4];
		VarEngineFaultCode6 = (UINT16)VarIsuzuSPN[5];
	}
}
/**************************************************************
**函数名：FunISUZUFaultCodeDiagnose()
**功能描述：五十铃发动机的故障代码判断
**传入参数：无
**输出参数：无
**************************************************************/
void FunISUZUFaultCodeDiagnose(void)
{
	UINT8 i=0;	
	for(i=0;i<8;i++)
	{
		VarSendDataID1A0[i]=0;
	}
	//根据SPN确认故障位置
	for(i=0;i<VarIszuFaultSPNNumber;i++)
	{
		switch(VarIsuzuSPN[i])
		{
			case 91:VarSendDataID1A0[0] |= 1<<0;;break;
			case 100:VarSendDataID1A0[0] |= 1<<1;break;
			case 102:VarSendDataID1A0[0] |= 1<<2;break;
			case 105:VarSendDataID1A0[0] |= 1<<3;break;
			case 108:VarSendDataID1A0[0] |= 1<<4;break;
			case 110:VarSendDataID1A0[0] |= 1<<5;break;
			case 157:VarSendDataID1A0[0] |= 1<<6;break;
			case 172:VarSendDataID1A0[0] |= 1<<7;break;
			
			case 174:VarSendDataID1A0[1] |= 1<<0;break;
			case 190:VarSendDataID1A0[1] |= 1<<1;break;
			case 628:VarSendDataID1A0[1] |= 1<<2;break;
			case 633:VarSendDataID1A0[1] |= 1<<3;break;
			case 636:VarSendDataID1A0[1] |= 1<<4;break;
			case 639:VarSendDataID1A0[1] |= 1<<5;break;
			case 651:VarSendDataID1A0[1] |= 1<<6;break;
			case 652:VarSendDataID1A0[1] |= 1<<7;break;
			
			case 653:VarSendDataID1A0[2] |= 1<<0;break;
			case 654:VarSendDataID1A0[2] |= 1<<1;break;
			case 655:VarSendDataID1A0[2] |= 1<<2;break;
			case 656:VarSendDataID1A0[2] |= 1<<3;break;
			case 675:VarSendDataID1A0[2] |= 1<<4;break;
			case 676:VarSendDataID1A0[2] |= 1<<5;break;
			case 677:VarSendDataID1A0[2] |= 1<<6;break;
			case 723:VarSendDataID1A0[2] |= 1<<7;break;
			
			case 968:VarSendDataID1A0[3] |= 1<<0;break;
			case 987:VarSendDataID1A0[3] |= 1<<1;break;
			case 1077:VarSendDataID1A0[3] |= 1<<2;break;
			case 1079:VarSendDataID1A0[3] |= 1<<3;break;
			case 1080:VarSendDataID1A0[3] |= 1<<4;break;
			case 1239:VarSendDataID1A0[3] |= 1<<5;break;
			case 1347:VarSendDataID1A0[3] |= 1<<6;break;
			case 1381:VarSendDataID1A0[3] |= 1<<7;break;
			
			case 1485:VarSendDataID1A0[4] |= 1<<0;break;
			case 10001:VarSendDataID1A0[4] |= 1<<1;break;
			case 10002:VarSendDataID1A0[4] |= 1<<2;break;
			case 10003:VarSendDataID1A0[4] |= 1<<3;break;
			case 10004:VarSendDataID1A0[4] |= 1<<4;break;
			case 10005:VarSendDataID1A0[4] |= 1<<5;break;
			case 10006:VarSendDataID1A0[4] |= 1<<6;break;
			case 10007:VarSendDataID1A0[4] |= 1<<7;break;
			
			case 10008:VarSendDataID1A0[5] |= 1<<0;break;
			case 10009:VarSendDataID1A0[5] |= 1<<1;break;
			case 10010:VarSendDataID1A0[5] |= 1<<2;break;
			case 10011:VarSendDataID1A0[5] |= 1<<3;break;
			case 10013:VarSendDataID1A0[5] |= 1<<4;break;
			default:break;
		}
	}
}
