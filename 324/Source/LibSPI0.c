#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibEepromWriteByte
** 功能描述:
** 传入参数:
** 返回参数:
** *************************************************** */
void LibEepromWriteByte(UINT16 Addr,UINT8 Data)
{
	UINT8 i,j;          //上升沿写数据读数据
	UINT8 Command=0x02;
	//WriteEnable
	LibEepromWriteEnable();
	//writeStatus
	LibEepromWriteStatus(0x80);
	//WriteEnable
	LibEepromWriteEnable();
	//CS=0
	REG_GPIOE_DR |= (1<<7);
	LibFunX5325Delay();
	REG_GPIOE_DR &= ~(1<<7);
	//Command
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Command&0x80){REG_GPIOE_DR |= (1<<5);;}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Command = (UINT8)(Command<<1);
	}
	//Write Addr
	for(j=0;j<16;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Addr&0x8000){REG_GPIOE_DR |= (1<<5);}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Addr = (UINT16)(Addr<<1);
	}
	//Write Data
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Data&0x80){REG_GPIOE_DR |= (1<<5);}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Data = (UINT8)(Data<<1);
	}
	//CLK=0
	REG_GPIOE_DR &= ~(1<<4);
	//CS=1
	REG_GPIOE_DR |= (1<<7);
	//Busy?
	i = 0;
	while(1)
	{
		j = LibEepromReadStatus();
		if(((j&0x01)==0x00) || (i>=255))
		{
			break;
		}
		i++;
	}
	//lock
	//LibEepromWriteStatus(0x0C);
}
/* ******************************************************
** 函数名称:LibEepromReadByte
** 功能描述:
** 传入参数:
** 返回参数:
** *************************************************** */
UINT8 LibEepromReadByte(UINT16 Addr)
{
	UINT8 j; //上升沿写数据读数据
	UINT8 Status=0;
	UINT8 Command=0x03;
	UINT8 Data=0;
	//CS=0
	REG_GPIOE_DR |= (1<<7);
	LibFunX5325Delay();
	REG_GPIOE_DR &= ~(1<<7);
	//Command
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Command&0x80){REG_GPIOE_DR |= (1<<5);;}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Command = (UINT8)(Command<<1);
	}
	//Addr
	for(j=0;j<16;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Addr&0x8000){REG_GPIOE_DR |= (1<<5);;}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Addr = (UINT16)(Addr<<1);
	}
	//Read
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		Data = (UINT8)(Data<<1);
		LibFunX5325Delay();
		if(REG_GPIOE_DR&(1<<6)){Data |= 0x01;}	
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
	}
	//CLK=0
	REG_GPIOE_DR &= ~(1<<4);
	//CS=1
	REG_GPIOE_DR |= (1<<7);
	return Data;
}
/* ******************************************************
** 函数名称:LibEepromWriteEnable
** 功能描述:
** 传入参数:
** 返回参数:
** *************************************************** */
void LibEepromWriteEnable(void)
{
	UINT8 j;          //上升沿写数据读数据
	UINT8 Command=0x06;
	//CS=0
	REG_GPIOE_DR |= (1<<7);
	LibFunX5325Delay();
	REG_GPIOE_DR &= ~(1<<7);
	//Command
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Command&0x80){REG_GPIOE_DR |= (1<<5);;}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Command = (UINT8)(Command<<1);
	}
	//CLK=0
	REG_GPIOE_DR &= ~(1<<4);
	//CS=1
	REG_GPIOE_DR |= (1<<7);
}
/* ******************************************************
** 函数名称:LibEepromWriteStatus
** 功能描述:
** 传入参数:
** 返回参数:
** *************************************************** */
void LibEepromWriteStatus(UINT8 Status)
{
	UINT8 i,j;          //上升沿写数据读数据
	UINT8 Command=0x01;
	//WriteEnable
	LibEepromWriteEnable();
	//CS=0
	REG_GPIOE_DR |= (1<<7);
	LibFunX5325Delay();
	REG_GPIOE_DR &= ~(1<<7);
	//Command
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Command&0x80){REG_GPIOE_DR |= (1<<5);;}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Command = (UINT8)(Command<<1);
	}
	//Write
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Status&0x80){REG_GPIOE_DR |= (1<<5);;}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Status = (UINT8)(Status<<1);
	}
	//CLK=0
	REG_GPIOE_DR &= ~(1<<4);
	//CS=1
	REG_GPIOE_DR |= (1<<7);
	//Busy?
	i = 0;
	while(1)
	{
		j = LibEepromReadStatus();
		if(((j&0x01)==0x00) || (i>=255))
		{
			break;
		}
		i++;
	}
}
/* ******************************************************
** 函数名称:LibEepromReadStatus
** 功能描述:
** 传入参数:
** 返回参数:
** *************************************************** */
UINT8 LibEepromReadStatus(void)
{
	UINT8 j; //上升沿写数据读数据
	UINT8 Status=0;
	UINT8 Command=0x05;
	//CS=0
	REG_GPIOE_DR |= (1<<7);
	LibFunX5325Delay();
	REG_GPIOE_DR &= ~(1<<7);
	//Command
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		if(Command&0x80){REG_GPIOE_DR |= (1<<5);;}else{REG_GPIOE_DR &= ~(1<<5);}
		LibFunX5325Delay();
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
		Command = (UINT8)(Command<<1);
	}
	//Read
	for(j=0;j<8;j++)
	{
		//CLK=0
		REG_GPIOE_DR &= ~(1<<4);
		Status = (UINT8)(Status<<1);
		LibFunX5325Delay();
		if(REG_GPIOE_DR&(1<<6)){Status |= 0x01;}	
		//CLK=1
		REG_GPIOE_DR |= (1<<4);
		LibFunX5325Delay();
	}
	//CLK=0
	REG_GPIOE_DR &= ~(1<<4);
	//CS=1
	REG_GPIOE_DR |= (1<<7);
	return Status;
}
/* ******************************************************
** 函数名称:LibSpi0Init
** 功能描述:
** 传入参数:
** 返回参数:
** *************************************************** */
void LibFunSpi0Init(void)
{
	//X5323 CLK:GPIOE4  Output
	REG_GPIOE_PUR |= (1<<4);
	REG_GPIOE_DDR |= (1<<4);
	REG_GPIOE_PER &= (~(1<<4));
	REG_GPIOE_DR |= (1<<4);
	//X5323 MOSI:GPIOE5  Output
	REG_GPIOE_PUR |= (1<<5);
	REG_GPIOE_DDR |= (1<<5);
	REG_GPIOE_PER &= (~(1<<5));
	REG_GPIOE_DR |= (1<<5);
	//X5323 MISO:GPIOE6  Input
	REG_GPIOE_PUR |= (1<<6);
	REG_GPIOE_DDR &= ~(1<<6);
	REG_GPIOE_PER &= (~(1<<6));
	//X5323 CS:GPIOE7  Output
	REG_GPIOE_PUR |= (1<<7);
	REG_GPIOE_DDR |= (1<<7);
	REG_GPIOE_PER &= (~(1<<7));
	REG_GPIOE_DR |= (1<<7);
}
/* ******************************************************
** 函数名称:LibFunX5325Delay
** 功能描述:
** 传入参数:
** 返回参数:
** *************************************************** */
void LibFunX5325Delay(void)
{
	UINT16 i;
	for(i=0;i<280;i++)
	{
		;
	}
}
/* *************************************************************** 
** File End
** ************************************************************ */
