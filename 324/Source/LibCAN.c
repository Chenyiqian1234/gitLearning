#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"

void LibCan0SetRecMaskId(UINT16 FrameEx, UINT32 FrameID, UINT32 MaskID)
{
	if(FrameEx)
	{
		CAN0MB14Mode = 2;
		CAN0MB14ID = FrameID & (UINT32)0x1FFFFFFF;
	}
	else
	{
		CAN0MB14Mode = 1;
		CAN0MB14ID = FrameID & (UINT32)0x000007FF;
	}
	CAN0MB14IDMask = MaskID;
}

void LibCan1SetRecMaskId(UINT16 FrameEx, UINT32 FrameID, UINT32 MaskID)
{
	if(FrameEx)
	{
		CAN1MB14Mode = 2;
		CAN1MB14ID = FrameID & (UINT32)0x1FFFFFFF;
	}
	else
	{
		CAN1MB14Mode = 1;
		CAN1MB14ID = FrameID & (UINT32)0x000007FF;
	}
	CAN1MB14IDMask = MaskID;
}

/* ******************************************************
** 函数名称:LibFunCan0ReadReceiveData
** 功能描述:读取CAN0 Buffer接收的数据
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibCan0ReadReceiveData(UINT8 BufferID,UINT8 *Data)
{
	UINT8 i;
	if( BufferID<38 && LibVarCan0BufferMode[BufferID]!=0 )
	{
		for(i=0;i<8;i++)
		{
			*(Data+i) = LibVarCan0ReceiveData[BufferID][i];
		}
		LibVarCan0ReceiveFlag[BufferID] = 0;
		if(LibVarCan0ReceiveLength[BufferID]>8)
		{
			LibVarCan0ReceiveLength[BufferID]=8;
		}
		return LibVarCan0ReceiveLength[BufferID];
	}
	return 0;
}
/* ******************************************************
** 函数名称:LibFunCan1ReadReceiveData
** 功能描述:读取CAN1 Buffer接收的数据
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibCan1ReadReceiveData(UINT8 BufferID,UINT8 *Data)
{
	UINT8 i;
	if( BufferID<38 && LibVarCan1BufferMode[BufferID]!=0 )
	{
		for(i=0;i<8;i++)
		{
			*(Data+i) = LibVarCan1ReceiveData[BufferID][i];
		}
		LibVarCan1ReceiveFlag[BufferID] = 0;
		if(LibVarCan1ReceiveLength[BufferID]>8)
		{
			LibVarCan1ReceiveLength[BufferID]=8;
		}
		return LibVarCan1ReceiveLength[BufferID];
	}
	return 0;
}
/* ******************************************************
** 函数名称:LibFunCan0ReceiveFlag
** 功能描述:读取CAN0 Buffer接收数据标志
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibCan0ReceiveFlag(UINT8 BufferID)
{
	if( BufferID<38 && LibVarCan0BufferMode[BufferID]!=0 )
	{
		return LibVarCan0ReceiveFlag[BufferID];
	}
	return 0;
}
/* ******************************************************
** 函数名称:LibFunCan1ReceiveFlag
** 功能描述:读取CAN1 Buffer接收数据标志
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibCan1ReceiveFlag(UINT8 BufferID)
{
	if( BufferID<38 && LibVarCan1BufferMode[BufferID]!=0 )
	{
		return LibVarCan1ReceiveFlag[BufferID];
	}
	return 0;
}
/* ******************************************************
** 函数名称:LibFunCan0SetRecMode
** 功能描述:设置CAN0 Buffer接收模式
** 传入参数:
** 返回数据:
** *************************************************** */
void LibCan0SetRecMode(UINT16 BufferID,UINT16 FrameEx,UINT32 FrameID)
{
	if(BufferID<38)
	{
		if(FrameEx)
		{
			LibVarCan0BufferMode[BufferID] = 2;  //扩展帧
			LibVarCan0ReceiveTargetID[BufferID] = FrameID & (UINT32)0x1FFFFFFF;
		}
		else
		{
			LibVarCan0BufferMode[BufferID] = 1; //标准帧
			LibVarCan0ReceiveTargetID[BufferID] = FrameID & (UINT32)0x000007FF;
		}
	}
}
/* ******************************************************
** 函数名称:LibFunCan1SetRecMode
** 功能描述:设置CAN1 Buffer接收模式
** 传入参数:
** 返回数据:
** *************************************************** */
void LibCan1SetRecMode(UINT16 BufferID,UINT16 FrameEx,UINT32 FrameID)
{
	if(BufferID<38)
	{
		if(FrameEx)
		{
			LibVarCan1BufferMode[BufferID] = 2;  //扩展帧
			LibVarCan1ReceiveTargetID[BufferID] = FrameID & (UINT32)0x1FFFFFFF;
		}
		else
		{
			LibVarCan1BufferMode[BufferID] = 1; //标准帧
			LibVarCan1ReceiveTargetID[BufferID] = FrameID & (UINT32)0x000007FF;
		}
	}
}
/* ******************************************************
** 函数名称:LibFunCan0SendData
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibCan0SendData(UINT16 BufferID,UINT32 FrameID,UINT16 FrameEx, UINT8 *Data,UINT16 DataLength)
{
	UINT16 VarStandardFrameID;
	UINT16 VarExFrameID0_14;
	UINT16 VarExFrameID15_17;
	UINT16 VarExFrameID18_28;
	UINT16 VarSendData[4];
	volatile UINT16 *AddrBase = (&REG_CAN1_FCMB0_CTL);
	
	if(BufferID>=38)
	{
		return;
	}
	if(LibVarCan0BufferMode[BufferID])
	{
		return;
	}
	
	if(DataLength>8)
	{
		DataLength = 8;
	}	
	AddrBase += (BufferID*0x08);
	VarSendData[0] = Data[0];
	VarSendData[0] = VarSendData[0]<<8;
	VarSendData[0] += Data[1];	
	VarSendData[1] = Data[2];
	VarSendData[1] = VarSendData[1]<<8;
	VarSendData[1] += Data[3];	
	VarSendData[2] = Data[4];
	VarSendData[2] = VarSendData[2]<<8;
	VarSendData[2] += Data[5];	
	VarSendData[3] = Data[6];
	VarSendData[3] = VarSendData[3]<<8;
	VarSendData[3] += Data[7];
	if(FrameEx==0)
	{
		VarStandardFrameID = (UINT16)(FrameID&0x000007FF);
		*(AddrBase+0) = 0x0080;
		*(AddrBase+1) = (VarStandardFrameID<<5);
		*(AddrBase+3) = VarSendData[0];
		*(AddrBase+4) = VarSendData[1];
		*(AddrBase+5) = VarSendData[2];
		*(AddrBase+6) = VarSendData[3];
		*(AddrBase+0) = (0x0C<<4) | ((DataLength&0x000F)<<0);
	}
	else
	{
		VarExFrameID0_14 = (UINT16)(FrameID&0x00007FFF);
		VarExFrameID15_17 = (UINT16)((FrameID>>15)&0x00000007);
		VarExFrameID18_28 = (UINT16)((FrameID>>18)&0x000007FF);
		*(AddrBase+0) = 0x0080;
		*(AddrBase+1) = (VarExFrameID18_28<<5)|(1<<4)|(1<<3)|(VarExFrameID15_17<<0);
		*(AddrBase+2) = (VarExFrameID0_14<<1)|(0<<0);
		*(AddrBase+3) = VarSendData[0];
		*(AddrBase+4) = VarSendData[1];
		*(AddrBase+5) = VarSendData[2];
		*(AddrBase+6) = VarSendData[3];
		*(AddrBase+0) = (0x0C<<4) | ((DataLength&0x000F)<<0);
	}
}
/* ******************************************************
** 函数名称:LibFunCan1SendData
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibCan1SendData(UINT16 BufferID,UINT32 FrameID,UINT16 FrameEx, UINT8 *Data,UINT16 DataLength)
{
	UINT16 VarStandardFrameID;
	UINT16 VarExFrameID0_14;
	UINT16 VarExFrameID15_17;
	UINT16 VarExFrameID18_28;
	UINT16 VarSendData[4];
	volatile UINT16 *AddrBase = (&REG_CAN0_FCMB0_CTL);
	if(BufferID>=38)
	{
		return;
	}
	if(LibVarCan1BufferMode[BufferID])
	{
		return;
	}
	
	if(DataLength>8)
	{
		DataLength = 8;
	}
	
	AddrBase += (BufferID*0x08);
	VarSendData[0] = Data[0];
	VarSendData[0] = VarSendData[0]<<8;
	VarSendData[0] += Data[1];	
	VarSendData[1] = Data[2];
	VarSendData[1] = VarSendData[1]<<8;
	VarSendData[1] += Data[3];	
	VarSendData[2] = Data[4];
	VarSendData[2] = VarSendData[2]<<8;
	VarSendData[2] += Data[5];	
	VarSendData[3] = Data[6];
	VarSendData[3] = VarSendData[3]<<8;
	VarSendData[3] += Data[7];
	if(FrameEx==0)
	{
		VarStandardFrameID = (UINT16)(FrameID&0x000007FF);
		*(AddrBase+0) = 0x0080;
		*(AddrBase+1) = (VarStandardFrameID<<5);
		*(AddrBase+3) = VarSendData[0];
		*(AddrBase+4) = VarSendData[1];
		*(AddrBase+5) = VarSendData[2];
		*(AddrBase+6) = VarSendData[3];
		*(AddrBase+0) = (0x0C<<4) | ((DataLength&0x000F)<<0);
	}
	else
	{
		VarExFrameID0_14 = (UINT16)(FrameID&0x00007FFF);
		VarExFrameID15_17 = (UINT16)((FrameID>>15)&0x00000007);
		VarExFrameID18_28 = (UINT16)((FrameID>>18)&0x000007FF);
		*(AddrBase+0) = 0x0080;
		*(AddrBase+1) = (VarExFrameID18_28<<5)|(1<<4)|(1<<3)|(VarExFrameID15_17<<0);
		*(AddrBase+2) = (VarExFrameID0_14<<1)|(0<<0);
		*(AddrBase+3) = VarSendData[0];
		*(AddrBase+4) = VarSendData[1];
		*(AddrBase+5) = VarSendData[2];
		*(AddrBase+6) = VarSendData[3];
		*(AddrBase+0) = (0x0C<<4) | ((DataLength&0x000F)<<0);
	}		
}
/* ******************************************************
** 函数名称:LibFunCan0busInit
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibCan0Init(UINT16 bps)
{
	UINT16 VarTempUint1,VarTempUint2;
	UINT16 VarMask=0x0000;
	bps = bps;
	
	REG_ITCN_IPR10 &= ~(3<<0);
	REG_ITCN_IPR10 &= ~(3<<2);
	REG_ITCN_IPR10 &= ~(3<<4);
	REG_ITCN_IPR10 &= ~(3<<6);
	
	REG_GPIOD_PER |= (3<<0);
	REG_SIM_GPS |= (3<<4);
	
	REG_CAN1_FCMCR |= (1<<9);
	
	while( (REG_CAN1_FCMCR&((UINT16)1<<8) )==0 ){;}
	
	REG_CAN1_FCMAXMB = 14;
	
	//buffer0
	if(LibVarCan0BufferMode[0]==1)     //接收标准帧
	{
		REG_CAN1_FCMB0_CTL = 0x0040;
		REG_CAN1_FCMB0_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[0]<<5);
		REG_CAN1_FCMB0_ID_L = 0x0000;
		VarMask |= (1<<0);
	}
	else if(LibVarCan0BufferMode[0]==2)//接收扩展帧
	{
		REG_CAN1_FCMB0_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[0]);
		REG_CAN1_FCMB0_ID_H = VarTempUint1;
		REG_CAN1_FCMB0_ID_L = VarTempUint2;
		VarMask |= (1<<0);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB0_CTL = 0x0080;
	}	
	//buffer1
	if(LibVarCan0BufferMode[1]==1)     //接收标准帧
	{
		REG_CAN1_FCMB1_CTL = 0x0040;
		REG_CAN1_FCMB1_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[1]<<5);
		REG_CAN1_FCMB1_ID_L = 0x0000;
		VarMask |= (1<<1);
	}
	else if(LibVarCan0BufferMode[1]==2)//接收扩展帧
	{
		REG_CAN1_FCMB1_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[1]);
		REG_CAN1_FCMB1_ID_H = VarTempUint1;
		REG_CAN1_FCMB1_ID_L = VarTempUint2;
		VarMask |= (1<<1);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB1_CTL = 0x0080;
	}
	//buffer2
	if(LibVarCan0BufferMode[2]==1)     //接收标准帧
	{
		REG_CAN1_FCMB2_CTL = 0x0040;
		REG_CAN1_FCMB2_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[2]<<5);
		REG_CAN1_FCMB2_ID_L = 0x0000;
		VarMask |= (1<<2);
	}
	else if(LibVarCan0BufferMode[2]==2)//接收扩展帧
	{
		REG_CAN1_FCMB2_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[2]);
		REG_CAN1_FCMB2_ID_H = VarTempUint1;
		REG_CAN1_FCMB2_ID_L = VarTempUint2;
		VarMask |= (1<<2);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB2_CTL = 0x0080;
	}
	//buffer3
	if(LibVarCan0BufferMode[3]==1)     //接收标准帧
	{
		REG_CAN1_FCMB3_CTL = 0x0040;
		REG_CAN1_FCMB3_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[3]<<5);
		REG_CAN1_FCMB3_ID_L = 0x0000;
		VarMask |= (1<<3);
	}
	else if(LibVarCan0BufferMode[2]==2)//接收扩展帧
	{
		REG_CAN1_FCMB3_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[3]);
		REG_CAN1_FCMB3_ID_H = VarTempUint1;
		REG_CAN1_FCMB3_ID_L = VarTempUint2;
		VarMask |= (1<<3);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB3_CTL = 0x0080;
	}
	//buffer4
	if(LibVarCan0BufferMode[4]==1)     //接收标准帧
	{
		REG_CAN1_FCMB4_CTL = 0x0040;
		REG_CAN1_FCMB4_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[4]<<5);
		REG_CAN1_FCMB4_ID_L = 0x0000;
		VarMask |= (1<<4);
	}
	else if(LibVarCan0BufferMode[4]==2)//接收扩展帧
	{
		REG_CAN1_FCMB4_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[4]);
		REG_CAN1_FCMB4_ID_H = VarTempUint1;
		REG_CAN1_FCMB4_ID_L = VarTempUint2;
		VarMask |= (1<<4);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB4_CTL = 0x0080;
	}
	//buffer5
	if(LibVarCan0BufferMode[5]==1)     //接收标准帧
	{
		REG_CAN1_FCMB5_CTL = 0x0040;
		REG_CAN1_FCMB5_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[5]<<5);
		REG_CAN1_FCMB5_ID_L = 0x0000;
		VarMask |= (1<<5);
	}
	else if(LibVarCan0BufferMode[5]==2)//接收扩展帧
	{
		REG_CAN1_FCMB5_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[5]);
		REG_CAN1_FCMB5_ID_H = VarTempUint1;
		REG_CAN1_FCMB5_ID_L = VarTempUint2;
		VarMask |= (1<<5);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB5_CTL = 0x0080;
	}
	//buffer6
	if(LibVarCan0BufferMode[6]==1)     //接收标准帧
	{
		REG_CAN1_FCMB6_CTL = 0x0040;
		REG_CAN1_FCMB6_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[6]<<5);
		REG_CAN1_FCMB6_ID_L = 0x0000;
		VarMask |= (1<<6);
	}
	else if(LibVarCan0BufferMode[6]==2)//接收扩展帧
	{
		REG_CAN1_FCMB6_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[6]);
		REG_CAN1_FCMB6_ID_H = VarTempUint1;
		REG_CAN1_FCMB6_ID_L = VarTempUint2;
		VarMask |= (1<<6);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB6_CTL = 0x0080;
	}
	//buffer7
	if(LibVarCan0BufferMode[7]==1)     //接收标准帧
	{
		REG_CAN1_FCMB7_CTL = 0x0040;
		REG_CAN1_FCMB7_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[7]<<5);
		REG_CAN1_FCMB7_ID_L = 0x0000;
		VarMask |= (1<<7);
	}
	else if(LibVarCan0BufferMode[7]==2)//接收扩展帧
	{
		REG_CAN1_FCMB7_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[7]);
		REG_CAN1_FCMB7_ID_H = VarTempUint1;
		REG_CAN1_FCMB7_ID_L = VarTempUint2;
		VarMask |= (1<<7);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB7_CTL = 0x0080;
	}
	//buffer8
	if(LibVarCan0BufferMode[8]==1)     //接收标准帧
	{
		REG_CAN1_FCMB8_CTL = 0x0040;
		REG_CAN1_FCMB8_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[8]<<5);
		REG_CAN1_FCMB8_ID_L = 0x0000;
		VarMask |= (1<<8);
	}
	else if(LibVarCan0BufferMode[8]==2)//接收扩展帧
	{
		REG_CAN1_FCMB8_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[8]);
		REG_CAN1_FCMB8_ID_H = VarTempUint1;
		REG_CAN1_FCMB8_ID_L = VarTempUint2;
		VarMask |= (1<<8);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB8_CTL = 0x0080;
	}
	//buffer9
	if(LibVarCan0BufferMode[9]==1)     //接收标准帧
	{
		REG_CAN1_FCMB9_CTL = 0x0040;
		REG_CAN1_FCMB9_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[9]<<5);
		REG_CAN1_FCMB9_ID_L = 0x0000;
		VarMask |= (1<<9);
	}
	else if(LibVarCan0BufferMode[9]==2)//接收扩展帧
	{
		REG_CAN1_FCMB9_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[9]);
		REG_CAN1_FCMB9_ID_H = VarTempUint1;
		REG_CAN1_FCMB9_ID_L = VarTempUint2;
		VarMask |= (1<<9);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB9_CTL = 0x0080;
	}
	//buffer10
	if(LibVarCan0BufferMode[10]==1)     //接收标准帧
	{
		REG_CAN1_FCMB10_CTL = 0x0040;
		REG_CAN1_FCMB10_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[10]<<5);
		REG_CAN1_FCMB10_ID_L = 0x0000;
		VarMask |= (1<<10);
	}
	else if(LibVarCan0BufferMode[10]==2)//接收扩展帧
	{
		REG_CAN1_FCMB10_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[10]);
		REG_CAN1_FCMB10_ID_H = VarTempUint1;
		REG_CAN1_FCMB10_ID_L = VarTempUint2;
		VarMask |= (1<<10);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB10_CTL = 0x0080;
	}
	//buffer11
	if(LibVarCan0BufferMode[11]==1)     //接收标准帧
	{
		REG_CAN1_FCMB11_CTL = 0x0040;
		REG_CAN1_FCMB11_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[11]<<5);
		REG_CAN1_FCMB11_ID_L = 0x0000;
		VarMask |= (1<<11);
	}
	else if(LibVarCan0BufferMode[11]==2)//接收扩展帧
	{
		REG_CAN1_FCMB11_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[11]);
		REG_CAN1_FCMB11_ID_H = VarTempUint1;
		REG_CAN1_FCMB11_ID_L = VarTempUint2;
		VarMask |= (1<<11);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB11_CTL = 0x0080;
	}
	//buffer12
	if(LibVarCan0BufferMode[12]==1)     //接收标准帧
	{
		REG_CAN1_FCMB12_CTL = 0x0040;
		REG_CAN1_FCMB12_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[12]<<5);
		REG_CAN1_FCMB12_ID_L = 0x0000;
		VarMask |= (1<<12);
	}
	else if(LibVarCan0BufferMode[12]==2)//接收扩展帧
	{
		REG_CAN1_FCMB12_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[12]);
		REG_CAN1_FCMB12_ID_H = VarTempUint1;
		REG_CAN1_FCMB12_ID_L = VarTempUint2;
		VarMask |= (1<<12);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB12_CTL = 0x0080;
	}
	//buffer13
	if(LibVarCan0BufferMode[13]==1)     //接收标准帧
	{
		REG_CAN1_FCMB13_CTL = 0x0040;
		REG_CAN1_FCMB13_ID_H = (UINT16)(LibVarCan0ReceiveTargetID[13]<<5);
		REG_CAN1_FCMB13_ID_L = 0x0000;
		VarMask |= (1<<13);
	}
	else if(LibVarCan0BufferMode[13]==2)//接收扩展帧
	{
		REG_CAN1_FCMB13_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan0ReceiveTargetID[13]);
		REG_CAN1_FCMB13_ID_H = VarTempUint1;
		REG_CAN1_FCMB13_ID_L = VarTempUint2;
		VarMask |= (1<<13);
	}
	else                               //发送模式
	{
		REG_CAN1_FCMB13_CTL = 0x0080;
	}
	
	//buffer14
	if (CAN0MB14Mode == 1)	//接收标准帧
	{
		REG_CAN1_FCMB14_CTL = 0x0040;
		REG_CAN1_FCMB14_ID_H = (UINT16)(CAN0MB14ID << 5);
		REG_CAN1_FCMB14_ID_L = 0x0000;
		VarMask |= (1<<14);
	}
	else if (CAN0MB14Mode == 2)//接收扩展帧
	{
		REG_CAN1_FCMB14_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2, CAN0MB14ID);
		REG_CAN1_FCMB14_ID_H = VarTempUint1;
		REG_CAN1_FCMB14_ID_L = VarTempUint2;
		VarMask |= (1<<14);
	}
	else						//发送模式
	{
		REG_CAN1_FCMB14_CTL = 0x0080;
	}
	
	//Mask
	REG_CAN1_FCRXGMASK_H = 0xFFEF;
	REG_CAN1_FCRXGMASK_L = 0xFFFE;
	if (CAN0MB14Mode == 1)	//接收标准帧 
	{
		REG_CAN1_FCRX14MASK_H = (UINT16)(CAN0MB14IDMask << 5);
		REG_CAN1_FCRX14MASK_L = 0xFFFE;
	}
	else if (CAN0MB14Mode == 2)
	{
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2, CAN0MB14IDMask);
		REG_CAN1_FCRX14MASK_H = VarTempUint1;
		REG_CAN1_FCRX14MASK_L = VarTempUint2;
	}
	else
	{
		REG_CAN1_FCRX14MASK_H = 0xFFEF;
		REG_CAN1_FCRX14MASK_L = 0xFFFE;
	}
	
	REG_CAN1_FCRX15MASK_H = 0xFFEF;
	REG_CAN1_FCRX15MASK_L = 0xFFFE;

	REG_CAN1_FCIMASK1 = VarMask;
	REG_CAN1_FCIFLAG1 = 0xFFFF;
	
	REG_CAN1_FCCTL1 = (23<<8) | (0<<6) | (5<<3) | (1<<0);
	REG_CAN1_FCCTL0 = (0<<7) | (0<<5);
	
	REG_CAN1_FCMCR = 0;
	
	REG_ITCN_IPR10 &= ~(3<<6);
	REG_ITCN_IPR10 |= (1<<7);
	
}
/* ******************************************************
** 函数名称:LibFunCan1busInit
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibCan1Init(UINT16 bps)
{
	UINT16 VarTempUint1,VarTempUint2;
	UINT16 VarMask=0x0000;
	bps = bps;
	
	REG_ITCN_IPR3 &= ~(3<<2);
	REG_ITCN_IPR3 &= ~(3<<4);
	REG_ITCN_IPR3 &= ~(3<<6);
	REG_ITCN_IPR3 &= ~(3<<8);
	
	REG_CAN0_FCMCR |= (1<<9);
	
	while( (REG_CAN0_FCMCR&((UINT16)1<<8) )==0 ){;}
	
	REG_CAN0_FCMAXMB = 14;			//14+1=15??MB
	//buffer0
	if(LibVarCan1BufferMode[0]==1)     //接收标准帧
	{
		REG_CAN0_FCMB0_CTL = 0x0040;
		REG_CAN0_FCMB0_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[0]<<5);
		REG_CAN0_FCMB0_ID_L = 0x0000;
		VarMask |= (1<<0);
	}
	else if(LibVarCan1BufferMode[0]==2)//接收扩展帧
	{
		REG_CAN0_FCMB0_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[0]);
		REG_CAN0_FCMB0_ID_H = VarTempUint1;
		REG_CAN0_FCMB0_ID_L = VarTempUint2;
		VarMask |= (1<<0);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB0_CTL = 0x0080;
	}
	//buffer1
	if(LibVarCan1BufferMode[1]==1)     //接收标准帧
	{
		REG_CAN0_FCMB1_CTL = 0x0040;
		REG_CAN0_FCMB1_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[1]<<5);
		REG_CAN0_FCMB1_ID_L = 0x0000;
		VarMask |= (1<<1);
	}
	else if(LibVarCan1BufferMode[1]==2)//接收扩展帧
	{
		REG_CAN0_FCMB1_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[1]);
		REG_CAN0_FCMB1_ID_H = VarTempUint1;
		REG_CAN0_FCMB1_ID_L = VarTempUint2;
		VarMask |= (1<<1);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB1_CTL = 0x0080;
	}	
	//buffer2
	if(LibVarCan1BufferMode[2]==1)     //接收标准帧
	{
		REG_CAN0_FCMB2_CTL = 0x0040;
		REG_CAN0_FCMB2_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[2]<<5);
		REG_CAN0_FCMB2_ID_L = 0x0000;
		VarMask |= (1<<2);
	}
	else if(LibVarCan1BufferMode[2]==2)//接收扩展帧
	{
		REG_CAN0_FCMB2_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[2]);
		REG_CAN0_FCMB2_ID_H = VarTempUint1;
		REG_CAN0_FCMB2_ID_L = VarTempUint2;
		VarMask |= (1<<2);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB2_CTL = 0x0080;
	}
	//buffer3
	if(LibVarCan1BufferMode[3]==1)     //接收标准帧
	{
		REG_CAN0_FCMB3_CTL = 0x0040;
		REG_CAN0_FCMB3_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[3]<<5);
		REG_CAN0_FCMB3_ID_L = 0x0000;
		VarMask |= (1<<3);
	}
	else if(LibVarCan1BufferMode[3]==2)//接收扩展帧
	{
		REG_CAN0_FCMB3_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[3]);
		REG_CAN0_FCMB3_ID_H = VarTempUint1;
		REG_CAN0_FCMB3_ID_L = VarTempUint2;
		VarMask |= (1<<3);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB3_CTL = 0x0080;
	}
	//buffer4
	if(LibVarCan1BufferMode[4]==1)     //接收标准帧
	{
		REG_CAN0_FCMB4_CTL = 0x0040;
		REG_CAN0_FCMB4_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[4]<<5);
		REG_CAN0_FCMB4_ID_L = 0x0000;
		VarMask |= (1<<4);
	}
	else if(LibVarCan1BufferMode[4]==2)//接收扩展帧
	{
		REG_CAN0_FCMB4_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[4]);
		REG_CAN0_FCMB4_ID_H = VarTempUint1;
		REG_CAN0_FCMB4_ID_L = VarTempUint2;
		VarMask |= (1<<4);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB4_CTL = 0x0080;
	}
	//buffer5
	if(LibVarCan1BufferMode[5]==1)     //接收标准帧
	{
		REG_CAN0_FCMB5_CTL = 0x0040;
		REG_CAN0_FCMB5_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[5]<<5);
		REG_CAN0_FCMB5_ID_L = 0x0000;
		VarMask |= (1<<5);
	}
	else if(LibVarCan1BufferMode[5]==2)//接收扩展帧
	{
		REG_CAN0_FCMB5_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[5]);
		REG_CAN0_FCMB5_ID_H = VarTempUint1;
		REG_CAN0_FCMB5_ID_L = VarTempUint2;
		VarMask |= (1<<5);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB5_CTL = 0x0080;
	}
	//buffer6
	if(LibVarCan1BufferMode[6]==1)     //接收标准帧
	{
		REG_CAN0_FCMB6_CTL = 0x0040;
		REG_CAN0_FCMB6_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[6]<<5);
		REG_CAN0_FCMB6_ID_L = 0x0000;
		VarMask |= (1<<6);
	}
	else if(LibVarCan1BufferMode[6]==2)//接收扩展帧
	{
		REG_CAN0_FCMB6_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[6]);
		REG_CAN0_FCMB6_ID_H = VarTempUint1;
		REG_CAN0_FCMB6_ID_L = VarTempUint2;
		VarMask |= (1<<6);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB6_CTL = 0x0080;
	}
	//buffer7
	if(LibVarCan1BufferMode[7]==1)     //接收标准帧
	{
		REG_CAN0_FCMB7_CTL = 0x0040;
		REG_CAN0_FCMB7_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[7]<<5);
		REG_CAN0_FCMB7_ID_L = 0x0000;
		VarMask |= (1<<7);
	}
	else if(LibVarCan1BufferMode[7]==2)//接收扩展帧
	{
		REG_CAN0_FCMB7_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[7]);
		REG_CAN0_FCMB7_ID_H = VarTempUint1;
		REG_CAN0_FCMB7_ID_L = VarTempUint2;
		VarMask |= (1<<7);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB7_CTL = 0x0080;
	}
	//buffer8
	if(LibVarCan1BufferMode[8]==1)     //接收标准帧
	{
		REG_CAN0_FCMB8_CTL = 0x0040;
		REG_CAN0_FCMB8_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[8]<<5);
		REG_CAN0_FCMB8_ID_L = 0x0000;
		VarMask |= (1<<8);
	}
	else if(LibVarCan1BufferMode[8]==2)//接收扩展帧
	{
		REG_CAN0_FCMB8_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[8]);
		REG_CAN0_FCMB8_ID_H = VarTempUint1;
		REG_CAN0_FCMB8_ID_L = VarTempUint2;
		VarMask |= (1<<8);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB8_CTL = 0x0080;
	}
	//buffer9
	if(LibVarCan1BufferMode[9]==1)     //接收标准帧
	{
		REG_CAN0_FCMB9_CTL = 0x0040;
		REG_CAN0_FCMB9_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[9]<<5);
		REG_CAN0_FCMB9_ID_L = 0x0000;
		VarMask |= (1<<9);
	}
	else if(LibVarCan1BufferMode[9]==2)//接收扩展帧
	{
		REG_CAN0_FCMB9_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[9]);
		REG_CAN0_FCMB9_ID_H = VarTempUint1;
		REG_CAN0_FCMB9_ID_L = VarTempUint2;
		VarMask |= (1<<9);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB9_CTL = 0x0080;
	}
	//buffer10
	if(LibVarCan1BufferMode[10]==1)     //接收标准帧
	{
		REG_CAN0_FCMB10_CTL = 0x0040;
		REG_CAN0_FCMB10_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[10]<<5);
		REG_CAN0_FCMB10_ID_L = 0x0000;
		VarMask |= (1<<10);
	}
	else if(LibVarCan1BufferMode[10]==2)//接收扩展帧
	{
		REG_CAN0_FCMB10_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[10]);
		REG_CAN0_FCMB10_ID_H = VarTempUint1;
		REG_CAN0_FCMB10_ID_L = VarTempUint2;
		VarMask |= (1<10);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB10_CTL = 0x0080;
	}
	//buffer11
	if(LibVarCan1BufferMode[11]==1)     //接收标准帧
	{
		REG_CAN0_FCMB11_CTL = 0x0040;
		REG_CAN0_FCMB11_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[11]<<5);
		REG_CAN0_FCMB11_ID_L = 0x0000;
		VarMask |= (1<<11);
	}
	else if(LibVarCan1BufferMode[11]==2)//接收扩展帧
	{
		REG_CAN0_FCMB11_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[11]);
		REG_CAN0_FCMB11_ID_H = VarTempUint1;
		REG_CAN0_FCMB11_ID_L = VarTempUint2;
		VarMask |= (1<<11);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB11_CTL = 0x0080;
	}
	//buffer12
	if(LibVarCan1BufferMode[12]==1)     //接收标准帧
	{
		REG_CAN0_FCMB12_CTL = 0x0040;
		REG_CAN0_FCMB12_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[12]<<5);
		REG_CAN0_FCMB12_ID_L = 0x0000;
		VarMask |= (1<<12);
	}
	else if(LibVarCan1BufferMode[12]==2)//接收扩展帧
	{
		REG_CAN0_FCMB12_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[12]);
		REG_CAN0_FCMB12_ID_H = VarTempUint1;
		REG_CAN0_FCMB12_ID_L = VarTempUint2;
		VarMask |= (1<<12);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB12_CTL = 0x0080;
	}
	//buffer13
	if(LibVarCan1BufferMode[13]==1)     //接收标准帧
	{
		REG_CAN0_FCMB13_CTL = 0x0040;
		REG_CAN0_FCMB13_ID_H = (UINT16)(LibVarCan1ReceiveTargetID[13]<<5);
		REG_CAN0_FCMB13_ID_L = 0x0000;
		VarMask |= (1<<13);
	}
	else if(LibVarCan1BufferMode[13]==2)//接收扩展帧
	{
		REG_CAN0_FCMB13_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2,LibVarCan1ReceiveTargetID[13]);
		REG_CAN0_FCMB13_ID_H = VarTempUint1;
		REG_CAN0_FCMB13_ID_L = VarTempUint2;
		VarMask |= (1<<13);
	}
	else                               //发送模式
	{
		REG_CAN0_FCMB13_CTL = 0x0080;
	}
	//buffer14
	if (CAN1MB14Mode == 1)	//接收标准帧
	{
		REG_CAN0_FCMB14_CTL = 0x0040;
		REG_CAN0_FCMB14_ID_H = (UINT16)(CAN1MB14ID << 5);
		REG_CAN0_FCMB14_ID_L = 0x0000;
		VarMask |= (1<<14);
	}
	else if (CAN1MB14Mode == 2)//接收扩展帧
	{
		REG_CAN0_FCMB14_CTL = 0x0040;
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2, CAN1MB14ID);
		REG_CAN0_FCMB14_ID_H = VarTempUint1;
		REG_CAN0_FCMB14_ID_L = VarTempUint2;
		VarMask |= (1<<14);
	}
	
	//Mask
	REG_CAN0_FCRXGMASK_H = 0xFFEF;
	REG_CAN0_FCRXGMASK_L = 0xFFFE;
	if (CAN1MB14Mode == 1)	//接收标准帧  
	{
		REG_CAN0_FCRX14MASK_H = (UINT16)(CAN1MB14IDMask << 5);
		REG_CAN0_FCRX14MASK_L = 0xFFFE;
	}
	else if (CAN1MB14Mode == 2)
	{
		LibCanSeparateExID(&VarTempUint1,&VarTempUint2, CAN1MB14IDMask);
		REG_CAN0_FCRX14MASK_H = VarTempUint1;
		REG_CAN0_FCRX14MASK_L = VarTempUint2;
	}
	else
	{
		REG_CAN0_FCRX14MASK_H = 0xFFEF;
		REG_CAN0_FCRX14MASK_L = 0xFFFE;
	}
	REG_CAN0_FCRX15MASK_H = 0xFFEF;
	REG_CAN0_FCRX15MASK_L = 0xFFFE;
	
	REG_CAN0_FCIMASK1 = VarMask;
	REG_CAN0_FCIFLAG1 = 0xFFFF;
	
	REG_CAN0_FCCTL1 = (23<<8) | (0<<6) | (5<<3) | (1<<0);
	REG_CAN0_FCCTL0 = (0<<7) | (0<<5);
	
	REG_CAN0_FCMCR = 0;
	
	REG_ITCN_IPR3 &= ~(3<<8);
	REG_ITCN_IPR3 |= (1<<9);
}
/* ******************************************************
** 函数名称:LibCanSeparateExID
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibCanSeparateExID(UINT16 *High,UINT16 *Low,UINT32 FrameID)
{
	UINT32 VarExtendedFrameID0_14;
	UINT32 VarExtendedFrameID15_17;
	UINT32 VarExtendedFrameID18_28;
	
	VarExtendedFrameID0_14 = (UINT32)(FrameID&0x00007FFF);
	VarExtendedFrameID15_17 = (UINT32)( (FrameID>>15)&0x0007 );
	VarExtendedFrameID18_28 = (UINT32)( (FrameID>>18)&0x07FF );
	
	*High = (UINT16)( (VarExtendedFrameID18_28<<5)|(1<<4)|(1<<3)|(VarExtendedFrameID15_17<<0) );
	*Low = (UINT16)(VarExtendedFrameID0_14<<1);
}

/* ******************************************************
** 函数名称:LibCanSeparateExIDInt
** 功能描述:中断调用
** 传入参数:
** 返回数据:
** *************************************************** */
#pragma interrupt called
void LibCanSeparateExIDInt(UINT16 *High,UINT16 *Low,UINT32 FrameID,UINT8 FrameEx)
{
	UINT32 VarExtendedFrameID0_14;
	UINT32 VarExtendedFrameID15_17;
	UINT32 VarExtendedFrameID18_28;
	if(FrameEx==2)
	{
		VarExtendedFrameID0_14 = (UINT32)(FrameID&0x00007FFF);
		VarExtendedFrameID15_17 = (UINT32)( (FrameID>>15)&0x0007 );
		VarExtendedFrameID18_28 = (UINT32)( (FrameID>>18)&0x07FF );
		*High = (UINT16)( (VarExtendedFrameID18_28<<5)|(1<<4)|(1<<3)|(VarExtendedFrameID15_17<<0) );
		*Low = (UINT16)(VarExtendedFrameID0_14<<1);
	}
	else if(FrameEx==1)
	{
		*High = (UINT16)((FrameID<<5)&0xFFE0);
		
		*Low = 0x0000;
	}
}

/* *************************************************************** 
** File End
** ************************************************************ */
