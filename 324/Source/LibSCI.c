#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibSciReadReceiveData
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibSciReadReceiveData(void)
{
	UINT16 ReadPosi;
	// LibVarSciRecDataLength        缓存里数据长度
	// LibVarSciRecDataNextSavePosi  下一个接收到的数据要存储的位置
	if(LibVarSciRecDataLength==0)
	{
		return 0;
	}
	
	if(LibVarSciRecDataNextSavePosi>=LibVarSciRecDataLength)
	{
		ReadPosi = LibVarSciRecDataNextSavePosi-LibVarSciRecDataLength;
	}
	else
	{
		ReadPosi = 256 + LibVarSciRecDataNextSavePosi - LibVarSciRecDataLength;
	}
	
	LibVarSciRecDataLength--;
	return LibVarSciRecData[ReadPosi];
}
/* ******************************************************
** 函数名称:LibSciSendDataLenth
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
UINT16 LibSciSendDataLenth(void)
{
	return LibVarSciSendDataLength;
}
/* ******************************************************
** 函数名称:LibSciReceiveDataLenth
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
UINT16 LibSciReceiveDataLenth(void)
{
	return LibVarSciRecDataLength;
}
/* ******************************************************
** 函数名称:LibSciSendNumInt16
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibSciSendNumInt16(INT16 Num,UINT8 Mode,UINT8 FillZore)
{
	if(Num>0)
	{
		LibSciSendAddOneByte('+');
	}
	else if(Num<0)
	{
		LibSciSendAddOneByte('-');
		Num = -Num;
	}
	else
	{
		LibSciSendAddOneByte(' ');
	}
	LibSciSendNumUint16((UINT16)Num,Mode,FillZore);
}
/* ******************************************************
** 函数名称:LibFunSciSendNumUint16
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibSciSendNumUint16(UINT16 Num,UINT8 Mode,UINT8 FillZore)
{ 
	UINT8 Data[5];
	if(Mode==0)
	{
		LibSciSendAddOneByte((UINT8)(Num>>8));
		LibSciSendAddOneByte((UINT8)(Num));		
	}
	else if(Mode==1)
	{
		Data[0] = (UINT8)(Num/10000);
		Data[1] = (UINT8)((Num%10000)/1000);
		Data[2] = (UINT8)((Num%1000)/100);
		Data[3] = (UINT8)((Num%100)/10);
		Data[4] = (UINT8)(Num%10);
		if( FillZore>0 || Data[0]>0 )
		{
			LibSciSendAddOneByte((UINT8)(Data[0]+0x30));
		}
		if( FillZore>0 || Data[0]>0 || Data[1]>0 )
		{
			LibSciSendAddOneByte((UINT8)(Data[1]+0x30));
		}
		if( FillZore>0 || Data[0]>0 || Data[1]>0 || Data[2]>0)
		{
			LibSciSendAddOneByte((UINT8)(Data[2]+0x30));
		}
		if( FillZore>0 || Data[0]>0 || Data[1]>0 || Data[2]>0 || Data[3]>0)
		{
			LibSciSendAddOneByte((UINT8)(Data[3]+0x30));
		}		
		LibSciSendAddOneByte((UINT8)(Data[4]+0x30));
	}
}
/* ******************************************************
** 函数名称:LibFunSciSendString
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibSciSendNumUint8(UINT8 Num,UINT8 Mode,UINT8 FillZore)
{
	UINT8 Data[3];
	if(Mode==0)
	{
		LibSciSendAddOneByte(Num);
	}
	else if(Mode==1)
	{
		Data[0] = (UINT8)(Num/100);
		Data[1] = (UINT8)((Num%100)/10);
		Data[2] = (UINT8)(Num%10);
		if( FillZore>0 || Data[0]>0 )LibSciSendAddOneByte((UINT8)(Data[0]+0x30));
		if( FillZore>0 || Data[0]>0 || Data[1]>0 )LibSciSendAddOneByte((UINT8)(Data[1]+0x30));
		LibSciSendAddOneByte((UINT8)(Data[2]+0x30));		
	}
}
/* ******************************************************
** 函数名称:LibFunSciSendString
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibSciSendString(UINT8 *str)
{
	UINT16 i;
	for(i=0;i<sizeof(LibVarSciSendData);i++)
	{
		if( (*str)!=0x00 )
		{
			LibSciSendAddOneByte( *str );
			str++;
		}
		else
		{
			break;
		}
	}
}
/* ******************************************************
** 函数名称:LibFunSciSendByte
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibSciSendByte(UINT8 data)
{
	LibSciSendAddOneByte( data );
}
/* ******************************************************
** 函数名称:LibFunSciInit
** 功能描述:SCI0初始化
** 传入参数:波特率
** *************************************************** */
void LibSciInit(UINT32 BitsPerSencond)
{
	UINT16 SR;
	UINT16 Result;	
	if(BitsPerSencond > 500000)
	{
		BitsPerSencond = 500000;
	}
	BitsPerSencond *= 8;
	if(BitsPerSencond==0)
	{
		BitsPerSencond = 1;
	}
	BitsPerSencond = (60000000*50)/BitsPerSencond;  //放大了100倍
	Result = (UINT16)(BitsPerSencond/100);
	if( (BitsPerSencond%100)>50 )
	{
		Result++;
	}	
	REG_SIM_PCE |= (1<<4);
	SR = REG_SCI0_SCISR;	
	REG_GPIOE_PUR |= (3<<0);
	REG_GPIOE_DDR &= ~(3<<0);
	REG_GPIOE_DDR |= (1<<0);
	REG_GPIOE_PER |= (3<<0);
	REG_SCI0_SCIBR = Result;
	REG_SCI0_SCICR = (0<<7)|(0<<6)|(1<<5)|(0<<4)|(1<<3)|(1<<2)|(0<<0);
	//接收中断
	REG_ITCN_IPR8 &= ~(3<<14);
	REG_ITCN_IPR8 |= (1<<15);
	//错误中断
	REG_ITCN_IPR8 &= ~(3<<12);
	//idle中断
	REG_ITCN_IPR8 &= ~(3<<8);
	//空闲中断
	REG_ITCN_IPR8 &= ~(3<<6);
	REG_ITCN_IPR8 |= (1<<7);
}
/* ******************************************************
** 函数名称:LibFunSciSendLoop
** 功能描述:SCI0循环发送数据
** 传入参数:无
** 返回参数:无
** *************************************************** */
void LibSciSendLoop(void)
{
	if(LibVarSciSendDataLength>0)
	{
		if(LibVarSciTranEmptyTimer1MS>10)
		{
			LibVarSciTranEmptyTimer1MS = 0;
			if((REG_SCI0_SCISR&(1<<14))>0)
			{
				REG_SCI0_SCIDR = LibVarSciSendData[LibVarSciSendDataPosi];
				LibVarSciSendDataPosi++;
				if(LibVarSciSendDataPosi>=sizeof(LibVarSciSendData))
				{
					LibVarSciSendDataPosi = 0;
				}
				LibVarSciSendDataLength--;
				if(LibVarSciSendDataLength==0)
				{
					LibVarSciSendDataPosi = 0;
				}
			}
		}
	}
	else
	{
		LibVarSciSendDataPosi = 0;
	}
}
/* ******************************************************
** 函数名称:LibFunSCISendAddOneByte
** 功能描述:SCI0添加待发送数据
** 传入参数:无
** 返回参数:ErrorCode: 0  Ok
**                     1  Overflow
** *************************************************** */
UINT8 LibSciSendAddOneByte(UINT8 data)
{
	UINT16 VarNewPosi=0;
	if(LibVarSciSendDataLength<sizeof(LibVarSciSendData))
	{
		REG_SCI0_SCICR &= ~(1<<7);
		VarNewPosi = LibVarSciSendDataPosi + LibVarSciSendDataLength;
		while(VarNewPosi>=sizeof(LibVarSciSendData))
		{
			VarNewPosi = VarNewPosi-(UINT16)(sizeof(LibVarSciSendData));
		}
		LibVarSciSendData[VarNewPosi] = data;
		LibVarSciSendDataLength++;
		REG_SCI0_SCICR |= (1<<7);
		return 0;
	}
	else
	{
		return 1;
	}
}
/* *************************************************************** 
** File End
** ************************************************************ */
