#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** ��������:LibFunSpi1Restart
** ��������:��ֹSPI1�����ж�
** �������:��
** ���ز���:��
** *************************************************** */
void LibSpi1Restart(void)
{
	if(LibVarSpi1StoptimerMS>20)
	{
		LibSpi1Init();
		LibVarSpi1StoptimerMS = 0;
	}
}
/* ******************************************************
** ��������:LibFunSpi1RecInterruptDisable
** ��������:��ֹSPI1�����ж�
** �������:��
** ���ز���:��
** *************************************************** */
void LibSpi1RecInterruptDisable(void)
{
	REG_SPI1_SPSCR &= ~(1<<9);
}
/* ******************************************************
** ��������:LibFunSpi1RecInterruptEnable
** ��������:��ֹSPI1�����ж�
** �������:��
** ���ز���:��
** *************************************************** */
void LibSpi1RecInterruptEnable(void)
{
	REG_SPI1_SPSCR |= (1<<9);
}
/* ******************************************************
** ��������:LibFunGetPwmCurrent
** ��������:����PWM����
** �������:
** ���ز���:
** *************************************************** */
UINT16 LibGetPwmCurrent(UINT8 Channal)
{
	UINT32 VarTempUlong=0;
	UINT8 i;
	UINT8 Num;
	
	if(Channal<12)
	{
		Num = LibVarPWMCurrentFilerNum[Channal];
		if(Num<1)Num=1;
		if(Num>100)Num=100;
		LibSpi1RecInterruptDisable();
		for(i=0;i<Num;i++)
		{
			VarTempUlong += LibVarPWMCurrentADC[Channal][i];
		}
		LibSpi1RecInterruptEnable();
		VarTempUlong = VarTempUlong/Num;
		VarTempUlong = VarTempUlong*3000;
		VarTempUlong = VarTempUlong/4096;
		VarTempUlong = VarTempUlong*3;
		VarTempUlong = VarTempUlong>>1;
		VarTempUlong = VarTempUlong>>1;
		
		if(VarTempUlong<8)
		{
			VarTempUlong = VarTempUlong;
		}
	}
	return (UINT16)VarTempUlong;
}
/* ******************************************************
** ��������:LibFunSetPwmCurrentFilter
** ��������:����PWM���������˲���Ŀ
** �������:
** ���ز���:
** *************************************************** */
UINT8 LibSetPwmCurrentFilter(UINT8 Channal,UINT8 FilterNum)
{
	if(Channal<12)
	{
		if(FilterNum<1){FilterNum = 1;}
		if(FilterNum>100){FilterNum = 100;}
		LibVarPWMCurrentFilerNum[Channal] = FilterNum;
		return 0;
	}
	return 1;
}
/* ******************************************************
** ��������:LibFunSpi1Init
** ��������:
** �������:
** ��������: 
** *************************************************** */
void LibSpi1Init(void)
{
	/* GPIO */
	REG_GPIOC_PUR |= (1<<3);
	REG_GPIOC_DDR |= (1<<3);
	REG_GPIOC_PER &= ~(1<<3);
	REG_GPIOC_DR  |= (1<<3);
	REG_GPIOA_PUR |= (1<<9);
	REG_GPIOA_DDR |= (1<<9);
	REG_GPIOA_PER &= ~(1<<9);
	REG_GPIOA_DR  |= (1<<9);
	//GPIOC3
	REG_GPIOC_PUR |= (1<<3);
	REG_GPIOC_DDR |= (1<<3);
	REG_GPIOC_PER &= ~(1<<3);
	REG_GPIOC_DR  |= (1<<3);
	//GPIOA9
	REG_GPIOA_PUR |= (1<<9);
	REG_GPIOA_DDR |= (1<<9);
	REG_GPIOA_PER &= ~(1<<9);
	REG_GPIOA_DR  |= (1<<9);
	//SCLK1,GPIOC0
	REG_GPIOC_PUR |= (1<<0);
	REG_GPIOC_DDR |= (1<<0);
	REG_GPIOC_PER |= (1<<0);
	REG_SIM_GPS |= (1<<0);
	//MOSI1,GPIOC1
	REG_GPIOC_PUR |= (1<<1);
	REG_GPIOC_DDR |= (1<<1);
	REG_GPIOC_PER |= (1<<1);
	REG_SIM_GPS |= (1<<1);
	//MISO1,GPIOC2
	REG_GPIOC_PUR |= (1<<2);
	REG_GPIOC_DDR &= ~(1<<2);
	REG_GPIOC_PER |= (1<<2);
	REG_SIM_GPS |= (1<<2);
	/* REG */
	REG_SPI1_SPSCR &= ~(1<<5);
	REG_SIM_PCE |= (1<<3);
	REG_SPI1_SPDSR = 0x000F;
	REG_SPI1_SPSCR = (UINT16)((1<<15)|(0<<14)|(1<<13)|(0<<12)|(0<<11)|(0<<10)|(1<<9)|(1<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4));
	REG_ITCN_IPR4 &= (0x0F<<10);
	REG_ITCN_IPR4 |= (0x01<<10);
	REG_SPI1_SPSCR |= (1<<5);
	// sample start
	REG_GPIOC_DR  &= ~(1<<3);
	REG_GPIOA_DR  |= (1<<9);
	LibVarSpi1CommandStep = 0;
	REG_SPI1_SPDTR = 0xC000;
}
/* *************************************************************** 
** File End
** ************************************************************ */
