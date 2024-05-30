#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
#include "AppVar.h"

UINT8 LibSciRec[7];

/* ******************************************************
** 函数名称:LibInterruptTimerD2
** 功能描述:
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptTimerD2(void)
{
	REG_TIMERD2_SCR &= ~(1<<13);
}
/* ******************************************************
** 函数名称:LibInterruptTimerD1
** 功能描述:
** 传入参数:无
*** 返回参数:无
** ************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptTimerD1(void)
{
	REG_TIMERD1_SCR &= ~(1<<13);
}
/* ******************************************************
** 函数名称:LibInterruptTimerA1
** 功能描述:
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptTimerA1(void)
{
	REG_TIMERA1_SCR &= ~(1<<13);
}
/* ******************************************************
** 函数名称:LibInterruptTimerA0
** 功能描述:
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptTimerA0(void)
{
	REG_TIMERA0_SCR &= ~(1<<13);
}

/* ******************************************************
** 函数名称:LibIrqaInterrupt
** 功能描述:
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibIrqaInterrupt(void)
{
	FunAppIrqa();
}
/* ******************************************************
** 函数名称:LibIrqbInterrupt
** 功能描述:
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibIrqbInterrupt(void)
{
	FunAppIrqb();
}
/* ******************************************************
** 函数名称:LibFunSPI1RecInterrupt
** 功能描述:SPI1接收中断
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibSpi1RecInterrupt(void)
{
	UINT16 data;
	UINT8 i;
	UINT16 stat;
	stat = REG_SPI1_SPSCR & ( (1<<2)|(1<<3) );
	if( stat != (1<<3) )
	{
		LibMCP3208U5003CS(1);
		LibMCP3208U5013CS(1);
		
		LibVarSpi1CommandStep = 0xFF;
		
		while( REG_SPI1_SPSCR&(1<<2))
		{
			data = REG_SPI1_SPDRR;
		}
	}
	data = REG_SPI1_SPDRR;
	
	switch(LibVarSpi1CommandStep)
	{
		case 0:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 1:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[3][i] = LibVarPWMCurrentADC[3][i-1];}
			LibVarPWMCurrentADC[3][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(1);
			LibMCP3208U5013CS(0);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xC000;
			break;
		case 2:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 3:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[6][i] = LibVarPWMCurrentADC[6][i-1];}
			LibVarPWMCurrentADC[6][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(0);
			LibMCP3208U5013CS(1);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xC800;
			break;
		case 4:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 5:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[11][i] = LibVarPWMCurrentADC[11][i-1];}
			LibVarPWMCurrentADC[11][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(1);
			LibMCP3208U5013CS(0);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xC800;
			break;
		case 6:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 7:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[5][i] = LibVarPWMCurrentADC[5][i-1];}
			LibVarPWMCurrentADC[5][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(0);
			LibMCP3208U5013CS(1);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xD000;
			break;
		case 8:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 9:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[10][i] = LibVarPWMCurrentADC[10][i-1];}
			LibVarPWMCurrentADC[10][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(1);
			LibMCP3208U5013CS(0);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xD000;
			break;
		case 10:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 11:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[4][i] = LibVarPWMCurrentADC[4][i-1];}
			LibVarPWMCurrentADC[4][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(0);
			LibMCP3208U5013CS(1);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xD800;
			break;
		case 12:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 13:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[9][i] = LibVarPWMCurrentADC[9][i-1];}
			LibVarPWMCurrentADC[9][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(1);
			LibMCP3208U5013CS(0);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xD800;
			break;
		case 14:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 15:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[2][i] = LibVarPWMCurrentADC[2][i-1];}
			LibVarPWMCurrentADC[2][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(0);
			LibMCP3208U5013CS(1);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xE000;
			break;
		case 16:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 17:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[8][i] = LibVarPWMCurrentADC[8][i-1];}
			LibVarPWMCurrentADC[8][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(1);
			LibMCP3208U5013CS(0);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xE000;
			break;
		case 18:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 19:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[1][i] = LibVarPWMCurrentADC[1][i-1];}
			LibVarPWMCurrentADC[1][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(0);
			LibMCP3208U5013CS(1);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xE800;
			break;
		case 20:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 21:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[7][i] = LibVarPWMCurrentADC[7][i-1];}
			LibVarPWMCurrentADC[7][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(1);
			LibMCP3208U5013CS(0);
			LibVarSpi1CommandStep++;
			REG_SPI1_SPDTR = 0xE800;
			break;
		case 22:
			LibVarSpi1RecData = ((data & 0x01FF)<<3);
			REG_SPI1_SPDTR = 0x0000;
			LibVarSpi1CommandStep++;
			break;
		case 23:
			LibVarSpi1RecData |= ((data>>13) & 0x0007);
			for(i=99;i>0;i--){LibVarPWMCurrentADC[0][i] = LibVarPWMCurrentADC[0][i-1];}
			LibVarPWMCurrentADC[0][0] = LibVarSpi1RecData;
			LibMCP3208U5003CS(0);
			LibMCP3208U5013CS(1);
			LibVarSpi1CommandStep = 0;
			REG_SPI1_SPDTR = 0xC000;
			LibVarSpi1StoptimerMS = 0;
			break;
		default:
			LibMCP3208U5003CS(0);
			LibMCP3208U5013CS(1);
			LibVarSpi1CommandStep = 0;
			REG_SPI1_SPDTR = 0xC000;	
	}
}
/* ******************************************************
** 函数名称:LibFunMCP3208U5003CS
** 功能描述:设置MCP3208 U5003片选信号
** 传入参数:
** 返回数据: 
** *************************************************** */
#pragma interrupt called
void LibMCP3208U5003CS(UINT8 Data)
{
	REG_GPIOC_PUR |= (1<<3);
	REG_GPIOC_DDR |= (1<<3);
	REG_GPIOC_PER &= ~(1<<3);
	if(Data==0)
	{
		REG_GPIOC_DR  &= ~(1<<3);
	}
	else
	{
		REG_GPIOC_DR  |= (1<<3);
	}
}
/* ******************************************************
** 函数名称:LibFunMCP3208U5013CS
** 功能描述:设置MCP3208 U5003片选信号
** 传入参数:
** 返回数据: 
** *************************************************** */
#pragma interrupt called
void LibMCP3208U5013CS(UINT8 Data)
{
	REG_GPIOA_PUR |= (1<<9);
	REG_GPIOA_DDR |= (1<<9);
	REG_GPIOA_PER &= ~(1<<9);
	if(Data==0)
	{
		REG_GPIOA_DR  &= ~(1<<9);
	}
	else
	{
		REG_GPIOA_DR  |= (1<<9);
	}
}
/* ******************************************************
** 函数名称:LibFunMcuAdcbInterrupt
** 功能描述:ADCB转换完成中断
** 传入参数:无
** 返回数据:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibMcuAdcbInterrupt(void)
{
	REG_ADCB_ADSTAT = (1<<11);
	LibVarMcuAdcOrgData[8] = (REG_ADCB_ADRSLT0>>3);
	LibVarMcuAdcOrgData[9] = (REG_ADCB_ADRSLT1>>3);
	LibVarMcuAdcOrgData[10] = (REG_ADCB_ADRSLT2>>3);
	LibVarMcuAdcOrgData[11] = (REG_ADCB_ADRSLT3>>3);
	LibVarMcuAdcOrgData[12] = (REG_ADCB_ADRSLT4>>3);
	LibVarMcuAdcOrgData[13] = (REG_ADCB_ADRSLT5>>3);
	LibVarMcuAdcOrgData[14] = (REG_ADCB_ADRSLT6>>3);
	LibVarMcuAdcOrgData[15] = (REG_ADCB_ADRSLT7>>3);
	//REG_ADCB_ADCTL1 |= (1<<13);
	
	LibVarMcuAdcbNoIntTimer1MS = 0;	
}
/* ******************************************************
** 函数名称:LibFunMcuAdcaInterrupt
** 功能描述:ADCA转换完成中断
** 传入参数:无
** 返回数据:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibMcuAdcaInterrupt(void)
{
	REG_ADCA_ADSTAT = (1<<11);
	LibVarMcuAdcOrgData[0] = (REG_ADCA_ADRSLT0>>3);
	LibVarMcuAdcOrgData[1] = (REG_ADCA_ADRSLT1>>3);
	LibVarMcuAdcOrgData[2] = (REG_ADCA_ADRSLT2>>3);
	LibVarMcuAdcOrgData[3] = (REG_ADCA_ADRSLT3>>3);
	LibVarMcuAdcOrgData[4] = (REG_ADCA_ADRSLT4>>3);
	LibVarMcuAdcOrgData[5] = (REG_ADCA_ADRSLT5>>3);
	LibVarMcuAdcOrgData[6] = (REG_ADCA_ADRSLT6>>3);
	LibVarMcuAdcOrgData[7] = (REG_ADCA_ADRSLT7>>3);
	//REG_ADCA_ADCTL1 |= (1<<13);
	
	LibVarMcuAdcaNoIntTimer1MS = 0;
}
/* ******************************************************
** 函数名称:LibFunPIReadNum
** 功能描述:初始化PI
** 传入参数:
** 返回数据: 
** *************************************************** */
#pragma interrupt called
UINT16 LibPiReadNum(UINT8 Channal)
{
	UINT16 Data;
	#if DefineHardwareNewVersion
		switch(Channal)
		{	
			case 0:
				Data = REG_TIMERA0_CNTR;
				REG_TIMERA0_CNTR = 0;
				LibVarPiOverFlow[0] = 0;
				break;
			case 1:
				Data = REG_TIMERD0_CNTR;
				REG_TIMERD0_CNTR = 0;
				LibVarPiOverFlow[1] = 0;
				break;
			case 2:
				Data = REG_TIMERD1_CNTR;
				REG_TIMERD1_CNTR = 0;
				LibVarPiOverFlow[2] = 0;
				break;
			case 3:
				Data = REG_TIMERA1_CNTR;
				REG_TIMERA1_CNTR = 0;
				LibVarPiOverFlow[3] = 0;
				break;
			default:
				Data = 0;
				break;
		}
	#else 
		switch(Channal)
		{	
			case 0:
				Data = REG_TIMERD2_CNTR;
				REG_TIMERD2_CNTR = 0;
				LibVarPiOverFlow[0] = 0;
				break;
			case 1:
				Data = REG_TIMERD0_CNTR;
				REG_TIMERD0_CNTR = 0;
				LibVarPiOverFlow[1] = 0;
				break;
			case 2:
				Data = REG_TIMERD1_CNTR;
				REG_TIMERD1_CNTR = 0;
				LibVarPiOverFlow[2] = 0;
				break;
			case 3:
				Data = REG_TIMERD3_CNTR;
				REG_TIMERD3_CNTR = 0;
				LibVarPiOverFlow[3] = 0;
				break;
			default:
				Data = 0;
				break;
		}
	#endif
	return Data;
}
/* ******************************************************
** 函数名称:LibInteruptSciEmpty
** 功能描述:SCI0 Empty
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInteruptSciEmpty(void)
{
	UINT16 SR;
	REG_SCI0_SCICR &= ~(1<<7);
	SR = REG_SCI0_SCISR;
	if(LibVarSciSendDataLength>0)
	{
		REG_SCI0_SCIDR = LibVarSciSendData[LibVarSciSendDataPosi];
		LibVarSciSendDataPosi++;
		if(LibVarSciSendDataPosi>=sizeof(LibVarSciSendData))
		{
			LibVarSciSendDataPosi = 0;
		}
		LibVarSciSendDataLength--;
		LibVarSciTranEmptyTimer1MS = 0;
		REG_SCI0_SCICR |= (1<<7);
	}
	else
	{
		LibVarSciSendDataPosi = 0;
	}
}
/* ******************************************************
** 函数名称:LibInteruptSciIdle
** 功能描述:SCI0 IDLE
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInteruptSciIdle(void)
{
	UINT16 SR;
	SR = REG_SCI0_SCISR;
	REG_SCI0_SCICR &= ~(1<<6);
}
/* ******************************************************
** 函数名称:LibFunInteruptSciRec
** 功能描述:SCI0接收数据中断
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInteruptSciRec(void)
{
	UINT16 SR;
	UINT16 data;
	SR = REG_SCI0_SCISR;
	REG_SCI0_SCISR = 0;
	
	if( SR & (1<<13) )
	{
		data = REG_SCI0_SCIDR;
		LibSciRec[0] = LibSciRec[1];
		LibSciRec[1] = LibSciRec[2];
		LibSciRec[2] = LibSciRec[3];
		LibSciRec[3] = LibSciRec[4];
		LibSciRec[4] = LibSciRec[5];
		LibSciRec[5] = LibSciRec[6];
		LibSciRec[6] = (UINT8)data;
		if(     LibSciRec[0]=='R'     )
		{
			if( LibSciRec[1]=='E' &&
				LibSciRec[2]=='S' &&
				LibSciRec[3]=='T' &&
				LibSciRec[4]=='A' &&
				LibSciRec[5]=='R' &&
				LibSciRec[6]=='T'
			)
			{
				LibWatchDogDisable();
				LibWatchDogInit(1);
				while(1)
				{
					;
				}
			}
		}
		if(LibVarSciRecDataNextSavePosi>=256)
		{
			LibVarSciRecDataNextSavePosi=0;
		}
		LibVarSciRecData[LibVarSciRecDataNextSavePosi] = (UINT8)data;
		if(LibVarSciRecDataLength<256)
		{
			LibVarSciRecDataLength++;
		}
		LibVarSciRecDataNextSavePosi++;
	}
	
}
/* ******************************************************
** 函数名称:LibInterruptCan0Rec
** 功能描述:CAN0收发中断
** 传入参数:
** 返回数据:
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptCan0Rec(void)
{
	UINT16 i;
	UINT16 VarIFlag;
	volatile UINT16 *AddrBase = (&REG_CAN1_FCMB0_CTL);
	UINT16 VarUint;
	UINT16 VarIdH,VarIdL;
	UINT32 VarUlong;
	
	VarIFlag = REG_CAN1_FCIFLAG1;
	REG_CAN1_FCIFLAG1 = VarIFlag;
	
	LibVarCan0NoIntTimer1Ms = 0;
	
	for(i=0;i<14;i++)
	{
		if( VarIFlag&(1<<i) )
		{
			if(LibVarCan0BufferMode[i])
			{
				VarUlong = LibVarTimer1MS;
				while(1)
				{
					VarUint = REG_CAN1_FCSTATUS;
					if(VarUint&(1<<7))
					{
						break;
					}
					if(LibVarTimer1MS>(VarUlong+100L))
					{
						LibVarCan0NeedInit = 1;
						break;
					}
				}
				VarUlong = LibVarTimer1MS;
				while(1)
				{
					VarUint = *(AddrBase+0);
					if(!(VarUint&(1<<4)))
					{
						break;
					}
					if(LibVarTimer1MS>(VarUlong+100L))
					{
						LibVarCan0NeedInit = 1;
						break;
					}
				}
				
				(*(AddrBase+0)) = 0x0000;
				
				VarIdH = (*(AddrBase+1));
				VarIdL = (*(AddrBase+2));
				
				if(LibVarCan0BufferMode[i]==1)
				{
					VarUlong = VarIdH>>5;
					VarUlong = VarUlong & 0x000007FF;
				}
				else
				{
					VarUlong = (VarIdH>>2)&0xFFF8;
					VarUlong |= (VarIdH&0x0007);
					VarUlong = VarUlong<<15;
					VarUlong += (VarIdL>>1);
				}
				
				if(VarUlong==LibVarCan0ReceiveTargetID[i])
				{
					LibVarCan0ReceiveLength[i] = (UINT8)(VarUint&0x000F);
					if(LibVarCan0ReceiveLength[i]>8)LibVarCan0ReceiveLength[i]=8;
					LibVarCan0ReceiveData[i][0] = (UINT8)((*(AddrBase+3))>>8);
					LibVarCan0ReceiveData[i][1] = (UINT8)((*(AddrBase+3)));
					LibVarCan0ReceiveData[i][2] = (UINT8)((*(AddrBase+4))>>8);
					LibVarCan0ReceiveData[i][3] = (UINT8)((*(AddrBase+4)));
					LibVarCan0ReceiveData[i][4] = (UINT8)((*(AddrBase+5))>>8);
					LibVarCan0ReceiveData[i][5] = (UINT8)((*(AddrBase+5)));
					LibVarCan0ReceiveData[i][6] = (UINT8)((*(AddrBase+6))>>8);
					LibVarCan0ReceiveData[i][7] = (UINT8)((*(AddrBase+6)));
					LibVarCan0ReceiveFlag[i] = 1;
				}
				else
				{
					if(LibVarCan0ErrorCount<0xFFFF)LibVarCan0ErrorCount++;
				}
				LibCanSeparateExIDInt(&VarIdH,&VarIdL,LibVarCan0ReceiveTargetID[i],LibVarCan0BufferMode[i]);
				(*(AddrBase+1)) = VarIdH;
				(*(AddrBase+2)) = VarIdL;
				
				(*(AddrBase+0)) = 0x0040;
			}
		}
		AddrBase += 0x08;
	}
	
	/*******************************增加MB14接收 ************/
	if (VarIFlag&(1<<14))
	{
		if(CAN0MB14Mode)
		{
			VarUlong = LibVarTimer1MS;
			while(1)
			{
				VarUint = REG_CAN1_FCSTATUS;
				if(VarUint&(1<<7))
				{
					break;
				}
				if(LibVarTimer1MS>(VarUlong+100L))
				{
					LibVarCan0NeedInit = 1;
					break;
				}
			}
			VarUlong = LibVarTimer1MS;
			while(1)
			{
				VarUint = *(AddrBase+0);
				if(!(VarUint&(1<<4)))
				{
					break;
				}
				if(LibVarTimer1MS>(VarUlong+100L))
				{
					LibVarCan0NeedInit = 1;
					break;
				}
			}
			(*(AddrBase+0)) = 0x0000;
			
			VarIdH = (*(AddrBase+1));
			VarIdL = (*(AddrBase+2));
			
			if (CAN0MB14Mode == 1)
			{
				VarUlong = VarIdH>>5;
				VarUlong = VarUlong & 0x000007FF;
			}
			else if (CAN0MB14Mode == 2)
			{
				VarUlong = (VarIdH>>2)&0xFFF8;
				VarUlong |= (VarIdH&0x0007);
				VarUlong = VarUlong<<15;
				VarUlong += (VarIdL>>1);
			}
			
			for (i = 14; i < 38; i++)
			{
				if(VarUlong==LibVarCan0ReceiveTargetID[i])
				{
					//保存本次数据
					LibVarCan0ReceiveLength[i] = (UINT8)(VarUint&0x000F);
					if(LibVarCan0ReceiveLength[i]>8)LibVarCan0ReceiveLength[i]=8;

					LibVarCan0ReceiveData[i][0] = (UINT8)((*(AddrBase+3))>>8);
					LibVarCan0ReceiveData[i][1] = (UINT8)((*(AddrBase+3)));
					LibVarCan0ReceiveData[i][2] = (UINT8)((*(AddrBase+4))>>8);
					LibVarCan0ReceiveData[i][3] = (UINT8)((*(AddrBase+4)));
					LibVarCan0ReceiveData[i][4] = (UINT8)((*(AddrBase+5))>>8);
					LibVarCan0ReceiveData[i][5] = (UINT8)((*(AddrBase+5)));
					LibVarCan0ReceiveData[i][6] = (UINT8)((*(AddrBase+6))>>8);
					LibVarCan0ReceiveData[i][7] = (UINT8)((*(AddrBase+6)));
					LibVarCan0ReceiveFlag[i] = 1;
				}	
			}
			LibCanSeparateExIDInt(&VarIdH,&VarIdL,CAN0MB14ID,CAN0MB14Mode);
			(*(AddrBase+1)) = VarIdH;
			(*(AddrBase+2)) = VarIdL;
			(*(AddrBase+0)) = 0x0040;
		}
	}
	/*******************************************************************/
	
	
	REG_CAN1_FCIMASK1 = 0x0000;
}
/* ******************************************************
** 函数名称:LibCan1RecInterrupt
** 功能描述:CAN1收发中断
** 传入参数:
** 返回数据:
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptCan1Rec(void)
{
	UINT16 i;
	UINT16 VarIFlag;
	volatile UINT16 *AddrBase = (&REG_CAN0_FCMB0_CTL);
	UINT16 VarUint;
	UINT16 VarIdH,VarIdL;
	UINT32 VarUlong;
	
	VarIFlag = REG_CAN0_FCIFLAG1;
	REG_CAN0_FCIFLAG1 = VarIFlag;
	
	LibVarCan1NoIntTimer1Ms = 0;
	
	for(i=0;i<14;i++)
	{
		if( VarIFlag&(1<<i) )
		{
			if(LibVarCan1BufferMode[i])
			{
				VarUlong = LibVarTimer1MS;
				while(1)
				{
					VarUint = REG_CAN0_FCSTATUS;
					if(VarUint&(1<<7))
					{
						break;
					}
					if(LibVarTimer1MS>(VarUlong+100L))
					{
						LibVarCan1NeedInit = 1;
						break;
					}
				}
				VarUlong = LibVarTimer1MS;
				while(1)
				{
					VarUint = *(AddrBase+0);
					if(!(VarUint&(1<<4)))
					{
						break;
					}
					if(LibVarTimer1MS>(VarUlong+100L))
					{
						LibVarCan1NeedInit = 1;
						break;
					}
				}
				
				(*(AddrBase+0)) = 0x0000;
				
				VarIdH = (*(AddrBase+1));
				VarIdL = (*(AddrBase+2));
				
				if(LibVarCan1BufferMode[i]==1)
				{
					VarUlong = VarIdH>>5;
					VarUlong = VarUlong & 0x000007FF;
				}
				else
				{
					VarUlong = (VarIdH>>2)&0xFFF8;
					VarUlong |= (VarIdH&0x0007);
					VarUlong = VarUlong<<15;
					VarUlong += (VarIdL>>1);
				}
				
				if(VarUlong==LibVarCan1ReceiveTargetID[i])
				{
					LibVarCan1ReceiveLength[i] = (UINT8)(VarUint&0x000F);
					if(LibVarCan1ReceiveLength[i]>8)LibVarCan1ReceiveLength[i]=8;
					LibVarCan1ReceiveData[i][0] = (UINT8)((*(AddrBase+3))>>8);
					LibVarCan1ReceiveData[i][1] = (UINT8)((*(AddrBase+3)));
					LibVarCan1ReceiveData[i][2] = (UINT8)((*(AddrBase+4))>>8);
					LibVarCan1ReceiveData[i][3] = (UINT8)((*(AddrBase+4)));
					LibVarCan1ReceiveData[i][4] = (UINT8)((*(AddrBase+5))>>8);
					LibVarCan1ReceiveData[i][5] = (UINT8)((*(AddrBase+5)));
					LibVarCan1ReceiveData[i][6] = (UINT8)((*(AddrBase+6))>>8);
					LibVarCan1ReceiveData[i][7] = (UINT8)((*(AddrBase+6)));
					LibVarCan1ReceiveFlag[i] = 1;
				}
				else
				{
					if(LibVarCan1ErrorCount<0xFFFF)LibVarCan1ErrorCount++;
				}
				LibCanSeparateExIDInt(&VarIdH,&VarIdL,LibVarCan1ReceiveTargetID[i],LibVarCan1BufferMode[i]);
				(*(AddrBase+1)) = VarIdH;
				(*(AddrBase+2)) = VarIdL;
				
				(*(AddrBase+0)) = 0x0040;
			}
		}
		AddrBase += 0x08;
	}
	
	/*******************************增加MB14接收 ************/
		if (VarIFlag&(1<<14))
		{
			if(CAN1MB14Mode)
			{
				VarUlong = LibVarTimer1MS;
				while(1)
				{
					VarUint = REG_CAN0_FCSTATUS;
					if(VarUint&(1<<7))
					{
						break;
					}
					if(LibVarTimer1MS>(VarUlong+100L))
					{
						LibVarCan1NeedInit = 1;
						break;
					}
				}
				VarUlong = LibVarTimer1MS;
				while(1)
				{
					VarUint = *(AddrBase+0);
					if(!(VarUint&(1<<4)))
					{
						break;
					}
					if(LibVarTimer1MS>(VarUlong+100L))
					{
						LibVarCan1NeedInit = 1;
						break;
					}
				}
				(*(AddrBase+0)) = 0x0000;
				VarIdH = (*(AddrBase+1));
				VarIdL = (*(AddrBase+2));
				
				if (CAN1MB14Mode == 1)
				{
					VarUlong = VarIdH>>5;
					VarUlong = VarUlong & 0x000007FF;
				}
				else if (CAN1MB14Mode == 2)
				{
					VarUlong = (VarIdH>>2)&0xFFF8;
					VarUlong |= (VarIdH&0x0007);
					VarUlong = VarUlong<<15;
					VarUlong += (VarIdL>>1);
				}
				
				for (i = 14; i < 38; i++)
				{
					if(VarUlong==LibVarCan1ReceiveTargetID[i])
					{						
						//保存本次数据
						LibVarCan1ReceiveLength[i] = (UINT8)(VarUint&0x000F);
						if(LibVarCan1ReceiveLength[i]>8)LibVarCan1ReceiveLength[i]=8;
						
						LibVarCan1ReceiveData[i][0] = (UINT8)((*(AddrBase+3))>>8);
						LibVarCan1ReceiveData[i][1] = (UINT8)((*(AddrBase+3)));
						LibVarCan1ReceiveData[i][2] = (UINT8)((*(AddrBase+4))>>8);
						LibVarCan1ReceiveData[i][3] = (UINT8)((*(AddrBase+4)));
						LibVarCan1ReceiveData[i][4] = (UINT8)((*(AddrBase+5))>>8);
						LibVarCan1ReceiveData[i][5] = (UINT8)((*(AddrBase+5)));
						LibVarCan1ReceiveData[i][6] = (UINT8)((*(AddrBase+6))>>8);
						LibVarCan1ReceiveData[i][7] = (UINT8)((*(AddrBase+6)));
						LibVarCan1ReceiveFlag[i] = 1;
					}	
				}
				LibCanSeparateExIDInt(&VarIdH,&VarIdL,CAN1MB14ID,CAN1MB14Mode);
				(*(AddrBase+1)) = VarIdH;
				(*(AddrBase+2)) = VarIdL;
				(*(AddrBase+0)) = 0x0040;
			}
		}
		/*******************************************************************/
	
	REG_CAN0_FCIMASK1 = 0x0000;
}
/* ******************************************************
** 函数名称:LibFunInterruptTimerB0
** 功能描述:定制器BO中断
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptTimerB0(void)
{
	UINT8 i;
	//系统计时递增
	REG_TIMERB0_SCR &= ~(1<<15);
	REG_TIMERB0_COMSCR &= ~(1<<4);
	if(LibVarTimer1MS<0xFFFFFFFF)
	{
		LibVarTimer1MS++;
		
		if(LibVarTimer1MS%10==0) //20220112。防止写Flash时，存在800ms无转速信号发送，导致发动机转速不稳。将转速发送放到中断中执行。
		{
			if(VarEngineNeedStopFlag || VarEngineStop)//发动机停机控制
			{
				LibCan0SendData(13,0x18FEE4E4,1,VarSendDataID_0x18FEE4E4,8);
			}
			else//发动机转速控制
			{
				LibCan0SendData(13,0x0C0000E4,1,VarSendDataID_0x0C0000E4,8);
			}
		}
	
	}
	//PI统计
	LibVarPiSampleSingle10MS++;
	if(LibVarPiSampleSingle10MS>=10)
	{
		LibVarPiSampleSingle10MS = 0;
		for(i=99;i>0;i--){LibVarPiOrgData[0][i] = LibVarPiOrgData[0][i-1];}
		for(i=99;i>0;i--){LibVarPiOrgData[1][i] = LibVarPiOrgData[1][i-1];}
		for(i=99;i>0;i--){LibVarPiOrgData[2][i] = LibVarPiOrgData[2][i-1];}
		for(i=99;i>0;i--){LibVarPiOrgData[3][i] = LibVarPiOrgData[3][i-1];}

		LibVarPiOrgData[0][0] = LibPiReadNum(0);
		LibVarPiOrgData[1][0] = LibPiReadNum(1);
		LibVarPiOrgData[2][0] = LibPiReadNum(2);
		LibVarPiOrgData[3][0] = LibPiReadNum(3);

		LibVarPiUpdateFlag = 1;
	}
	//Timer
	for(i=0;i<40;i++)
	{
		LibVarTimer[i]++;
	}
	//TON TOF
	for(i=0;i<32;i++)
	{
		LibVarTonEt[i]++;
		LibVarTofEt[i]++;
	}
	//CAN
	if(LibVarCan0NoIntTimer1Ms<0xFFFF)LibVarCan0NoIntTimer1Ms++;
	if(LibVarCan1NoIntTimer1Ms<0xFFFF)LibVarCan1NoIntTimer1Ms++;
	//ADC
	if(LibVarMcuAdcaNoIntTimer1MS<0xFF)LibVarMcuAdcaNoIntTimer1MS++;
	if(LibVarMcuAdcbNoIntTimer1MS<0xFF)LibVarMcuAdcbNoIntTimer1MS++;
	//SPI1
	if(LibVarSpi1StoptimerMS<0xFF){LibVarSpi1StoptimerMS++;}
	//SCI
	if(LibVarSciTranEmptyTimer1MS<0xFF){LibVarSciTranEmptyTimer1MS++;}
}
/* ******************************************************
** 函数名称:LibFunInterruptTimerB1
** 功能描述:定制器B1中断,0.25MS
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptTimerB1(void)
{
	REG_TIMERB1_SCR &= ~(1<<15);
	REG_TIMERB1_COMSCR &= ~(1<<4);	
	REG_ADCA_ADCTL1 |= (1<<13);
	REG_ADCB_ADCTL1 |= (1<<13);
}
/* ******************************************************
** 函数名称:LibFunInterruptTimerB2
** 功能描述:定制器B2中断,10MS
** 传入参数:无
** 返回参数:无
** *************************************************** */
#pragma interrupt alignsp saveall
void LibInterruptTimerB2(void)
{
	REG_TIMERB2_SCR &= ~(1<<15);
	REG_TIMERB2_COMSCR &= ~(1<<4);
	
	LibVarTimerB2Count++;
	
	if(LibVarTimerB2Count%5==0)	
	{
		LibVarQDA1[1] = LibVarQDA1[0];
		LibVarQDB1[1] = LibVarQDB1[0];
		
		if(REG_GPIOB_DR & (1<<4))
		{
			LibVarQDA1[0] = 0;
		}
		else
		{
			LibVarQDA1[0] = 1;
		}
		if(REG_GPIOB_DR & (1<<5))
		{
			LibVarQDB1[0] = 0;
		}
		else
		{
			LibVarQDB1[0] = 1;
		}
		
		if(LibVarQDA1[1]==0 && LibVarQDA1[0]>0) // A上降沿
		{
			if(LibVarQDB1[0]==0)
			{
				LibVarQD1Position++;
			}
			else
			{
				LibVarQD1Position--;
			}
		}
		else if(LibVarQDA1[1]>0 && LibVarQDA1[0]==0) // A下降沿
		{
			if(LibVarQDB1[0])
			{
				LibVarQD1Position++;
			}
			else
			{
				LibVarQD1Position--;
			}
		}
		
		if(LibVarQDB1[1]==0 && LibVarQDB1[0]>0) // B上升沿
		{
			if(LibVarQDA1[0])
			{
				LibVarQD1Position++;
			}
			else
			{
				LibVarQD1Position--;
			}
		}
		else if(LibVarQDB1[1]>0 && LibVarQDB1[0]==0) // B下降沿
		{
			if(LibVarQDA1[0]==0)
			{
				LibVarQD1Position++;
			}
			else
			{
				LibVarQD1Position--;
			}
		}
	}
	
	//
	LibVarQDA0[1] = LibVarQDA0[0];
	LibVarQDB0[1] = LibVarQDB0[0];
	
	if(REG_GPIOB_DR & (1<<3))
	{
		LibVarQDA0[0] = 0;
	}
	else
	{
		LibVarQDA0[0] = 1;
	}
	if(REG_GPIOB_DR & (1<<2))
	{
		LibVarQDB0[0] = 0;
	}
	else
	{
		LibVarQDB0[0] = 1;
	}
	
	if(LibVarQDA0[1]==0 && LibVarQDA0[0]>0) // A上降沿
	{
		if(LibVarQDB0[0]==0)
		{
			LibVarQD0Position++;
		}
		else
		{
			LibVarQD0Position--;
		}
	}
	else if(LibVarQDA0[1]>0 && LibVarQDA0[0]==0) // A下降沿
	{
		if(LibVarQDB0[0])
		{
			LibVarQD0Position++;
		}
		else
		{
			LibVarQD0Position--;
		}
	}
	
	if(LibVarQDB0[1]==0 && LibVarQDB0[0]>0) // B上升沿
	{
		if(LibVarQDA0[0])
		{
			LibVarQD0Position++;
		}
		else
		{
			LibVarQD0Position--;
		}
	}
	else if(LibVarQDB0[1]>0 && LibVarQDB0[0]==0) // B下降沿
	{
		if(LibVarQDA0[0]==0)
		{
			LibVarQD0Position++;
		}
		else
		{
			LibVarQD0Position--;
		}
	}
}
/* *************************************************************** 
** File End
** ************************************************************ */
