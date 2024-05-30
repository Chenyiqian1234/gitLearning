#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** ��������:LibArrayUint16Filter
** ��������:
** �������:Method=0  �±�Ϊ0������Ϊ��������
**                =1  �±�Ϊ(Length-1)������Ϊ��������
** ��������:
** *************************************************** */
void LibArrayUint16Inset(UINT16 Data,UINT16 *Array,UINT8 Length,UINT8 Method)
{
	UINT8 i;
	if(Length==0)
	{
		return;
	}
	else if(Length==1)
	{
		*Array = Data;
		return;
	}
	
	if(Method==0)
	{
		for(i=(UINT8)(Length-1);i>0;i--)
		{
			*(Array+i) = *(Array+i-1);
		}
		*Array = Data;
	}
	else
	{
		for(i=0;i<Length-1;i++)
		{
			*(Array+i) = *(Array+i+1);
		}
		*(Array+i) = Data;
	}
}
/* ******************************************************
** ��������:LibArrayUint16Filter
** ��������:
** �������:Method=0  ��������ƽ��ֵ
**                =1  ȥ�����ֵ��Сֵ���ƽ��ֵ
** ��������:
** *************************************************** */
UINT16 LibArrayUint16Filter(UINT16 *Data,UINT8 Length,UINT8 Method)
{
	UINT32 Sun=0;
	UINT16 Min=*Data;
	UINT16 Max=*Data;
	UINT8 i;
	for(i=0;i<Length;i++)
	{
		Sun += *Data;
		if(*Data > Max)Max = *Data;
		if(*Data < Min)Min = *Data;
		Data++;
	}	
	if(Method==0 || Length<=2)
	{
		return (UINT16)(Sun/Length);
	}
	else
	{
		Sun = Sun-Max-Min;
		return (UINT16)(Sun/(Length-2));
	}
}
/* ******************************************************
** ��������:LibMinUint16
** ��������:
** �������:
** ��������:
** *************************************************** */
UINT16 LibMinUint16(UINT16 a,UINT16 b)
{
	return (a>b?b:a);
}
/* ******************************************************
** ��������:LibMinUint16
** ��������:
** �������:
** ��������:
** *************************************************** */
UINT16 LibMaxUint16(UINT16 a,UINT16 b)
{
	return (a>b?a:b);
}
/* ******************************************************
** ��������:LibJoinByteToUint
** ��������:
** �������:
** ��������:
** *************************************************** */
UINT16 LibJoinByteToUint16(UINT8 H,UINT8 L)
{
	UINT16 Data = H;
	Data = Data<<8;
	Data += L;
	return Data;
}
/* ******************************************************
** ��������:LibAbsUint16
** ��������:
** �������:
** ��������:
** *************************************************** */
UINT16 LibAbsUint16(UINT16 a,UINT16 b)
{
	if(a>b)
	{
		return (a-b);
	}
	else
	{
		return (b-a);
	}
}
/* ******************************************************
** ��������:LibAbsUint32
** ��������:
** �������:
** ��������:
** *************************************************** */
UINT32 LibAbsUint32(UINT32 a,UINT32 b)
{
	if(a>=b)
	{
		return (a-b);
	}
	else
	{
		return (b-a);
	}
}
/* ******************************************************
** ��������:LibAbsInt16
** ��������:
** �������:
** ��������:
** *************************************************** */
INT32 LibAbsInt16(INT16 a,INT16 b)
{
	INT32 Result;
	Result = a - b;
	if(Result<0) Result = -Result;
	if(Result>32767) Result = 32767;
	return (INT16)Result;
}
/* ******************************************************
** ��������:LibSqrt
** ��������:
** �������:
** ��������:
** *************************************************** */
FLOAT32 LibSqrt(FLOAT32 Data)
{
	FLOAT32 Result,x;
	FLOAT32 threehalfs = 1.5L;
	INT32 j;
	if(Data<=0)
	{
		return 0;
	}
	x = Data * 0.5L;
	Result = Data;
	j = *(INT32 *)&Result;
	j = 0x5F375A86 - (j>>1);
	Result = *(FLOAT32 *)&j;
	Result = Result * (threehalfs - (x * Result * Result));
	Result = Result * (threehalfs - (x * Result * Result));
	Result = Result * (threehalfs - (x * Result * Result));
	Result = 1/Result;
	return Result;
}

/* *************************************************************** 
** File End
** ************************************************************ */
