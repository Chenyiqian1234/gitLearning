#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibFunSetPwmRatio
** 功能描述:设置PWM占空比
** 传入参数:
** 返回数据: =0正确
**           =1通道参数错误
** *************************************************** */
UINT8 LibSetPwmRatio(UINT8 Channal,UINT16 Ratio)
{
	UINT32 VarTempUlong=0;
	
	if(Channal>=12)
	{
		return 1;
	}
	VarTempUlong = (UINT32)(REG_PWMA_PWMCM & 0x7FFF);
	VarTempUlong *= Ratio;
	VarTempUlong = VarTempUlong>>16;	
	switch(Channal)
	{
		case 0:
			REG_PWMA_PWMVAL5 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMA_PMCCR &= ~(1<<13);
			}
			else
			{
				REG_PWMA_PMCCR |= (1<<13);
			}
			REG_PWMA_PMCTL |= (1<<1);
			break;
		case 1:
			REG_PWMA_PWMVAL4 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMA_PMCCR &= ~(1<<12);
			}
			else
			{
				REG_PWMA_PMCCR |= (1<<12);
			}
			REG_PWMA_PMCTL |= (1<<1);
			break;	
		case 2:
			REG_PWMA_PWMVAL3 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMA_PMCCR &= ~(1<<11);
			}
			else
			{
				REG_PWMA_PMCCR |= (1<<11);
			}
			REG_PWMA_PMCTL |= (1<<1);
			break;
		case 3:
			REG_PWMB_PWMVAL0 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMB_PMCCR &= ~(1<<8);
			}
			else
			{
				REG_PWMB_PMCCR |= (1<<8);
			}
			REG_PWMB_PMCTL |= (1<<1);
			break;
		case 4:
			REG_PWMA_PWMVAL2 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMA_PMCCR &= ~(1<<10);
			}
			else
			{
				REG_PWMA_PMCCR |= (1<<10);
			}
			REG_PWMA_PMCTL |= (1<<1);
			break;
		case 5:
			REG_PWMA_PWMVAL1 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMA_PMCCR &= ~(1<<9);
			}
			else
			{
				REG_PWMA_PMCCR |= (1<<9);
			}
			REG_PWMA_PMCTL |= (1<<1);
			break;
		case 6:
			REG_PWMA_PWMVAL0 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMA_PMCCR &= ~(1<<8);
			}
			else
			{
				REG_PWMA_PMCCR |= (1<<8);
			}
			REG_PWMA_PMCTL |= (1<<1);
			break;
		case 7:
			REG_PWMB_PWMVAL5 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMB_PMCCR &= ~(1<<13);
			}
			else
			{
				REG_PWMB_PMCCR |= (1<<13);
			}
			REG_PWMB_PMCTL |= (1<<1);
			break;
		case 8:
			REG_PWMB_PWMVAL4 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMB_PMCCR &= ~(1<<12);
			}
			else
			{
				REG_PWMB_PMCCR |= (1<<12);
			}
			REG_PWMB_PMCTL |= (1<<1);
			break;
		case 9:
			REG_PWMB_PWMVAL3 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMB_PMCCR &= ~(1<<11);
			}
			else
			{
				REG_PWMB_PMCCR |= (1<<11);
			}
			REG_PWMB_PMCTL |= (1<<1);
			break;
		case 10:
			REG_PWMB_PWMVAL2 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMB_PMCCR &= ~(1<<10);
			}
			else
			{
				REG_PWMB_PMCCR |= (1<<10);
			}
			REG_PWMB_PMCTL |= (1<<1);
			break;
		case 11:
			REG_PWMB_PWMVAL1 = (UINT16)(VarTempUlong);
			if(Ratio>0)
			{
				REG_PWMB_PMCCR &= ~(1<<9);
			}
			else
			{
				REG_PWMB_PMCCR |= (1<<9);
			}
			REG_PWMB_PMCTL |= (1<<1);
			break;
		default:
			return 1;
	}
	return 0;
}
/* ******************************************************
** 函数名称:LibFunInitPWM
** 功能描述:初始化PWM
** 传入参数:
** 返回数据: =0正确
**           =1模块参数错误
**           =2频率设置错误
** *************************************************** */
UINT8 LibPwmInit(UINT8 ModeID,UINT32 Frequency)
{
	// 分频为1: 60MHz, 60MHz~1831.11Hz
	// 分频为2: 30MHz, 30MHz~915.555Hz
	// 分频为4: 15MHz, 15MHz~457.777Hz
	// 分频为8: 7.5MHz,7.5MHz~228.889Hz
	
	// ModeID: 0对应PWMA(PWM0,PWM1,PWM2,PWM4,PWM5,PWM6)
	// ModeID: 1对应PWMB(PWM3,PWM7,PWM8,PWM9,PWM10,PWM11)
	
	UINT32 VarTempUlong;
	
	if(ModeID==0)
	{
		REG_PWMA_PMICCR = 0;
		REG_PWMA_PMDISMAP1 = 0;
		REG_PWMA_PMDISMAP2 = 0;
		REG_PWMA_PMOUT = 0x3F3F;
		REG_PWMA_PMDEADTM = 0;
		REG_PWMA_PMCCR = 0x3F00;
		REG_PWMA_PMCFG = 0x100E;
		REG_PWMA_PMCNT = 0;
		
		if(Frequency>=1832)
		{
			REG_PWMA_PMCTL &= ~(3<<6);  //分频1: 60MHz
			VarTempUlong = 60000000;
		}
		else if(Frequency>=916)
		{
			REG_PWMA_PMCTL &= ~(3<<6);  //分频2: 30MHz
			REG_PWMA_PMCTL |= (1<<6);
			VarTempUlong = 30000000;
		}
		else if(Frequency>=458)
		{
			REG_PWMA_PMCTL &= ~(3<<6);  //分频4: 15MHz
			REG_PWMA_PMCTL |= (1<<7);
			VarTempUlong = 15000000;
		}
		else if(Frequency>=229)
		{
			REG_PWMA_PMCTL |= (3<<6);   //分频8: 7.5MHz
			VarTempUlong = 7500000;
		}
		else
		{
			return 2;
		}
		
		VarTempUlong = VarTempUlong/Frequency;
		REG_PWMA_PWMCM = (UINT16 )(VarTempUlong);
		
		REG_PWMA_PWMVAL0 = 0;
		REG_PWMA_PWMVAL1 = 0;
		REG_PWMA_PWMVAL2 = 0;
		REG_PWMA_PWMVAL3 = 0;
		REG_PWMA_PWMVAL4 = 0;
		REG_PWMA_PWMVAL5 = 0;
		
		REG_PWMA_PMOUT &= ~(1<<8);
		REG_PWMA_PMOUT &= ~(1<<9);
		REG_PWMA_PMOUT &= ~(1<<10);
		REG_PWMA_PMOUT &= ~(1<<11);
		REG_PWMA_PMOUT &= ~(1<<12);
		REG_PWMA_PMOUT &= ~(1<<13);	
		/*
		REG_PWMA_PMCCR &= ~(1<<8);
		REG_PWMA_PMCCR &= ~(1<<9);
		REG_PWMA_PMCCR &= ~(1<<10);
		REG_PWMA_PMCCR &= ~(1<<11);
		REG_PWMA_PMCCR &= ~(1<<12);
		REG_PWMA_PMCCR &= ~(1<<13);
		*/
		REG_PWMA_PMOUT |= (1<<15);
		REG_PWMA_PMCTL |= (3<<0);	
	}
	else if(ModeID==1)
	{
		REG_PWMB_PMICCR = 0;
		REG_PWMB_PMDISMAP1 = 0;
		REG_PWMB_PMDISMAP2 = 0;
		REG_PWMB_PMOUT = 0x3F3F;
		REG_PWMB_PMDEADTM = 0;
		REG_PWMB_PMCCR = 0x3F00;
		REG_PWMB_PMCFG = 0x100E;
		REG_PWMB_PMCNT = 0;
		
		if(Frequency>=1832)
		{
			REG_PWMB_PMCTL &= ~(3<<6);  //分频1: 60MHz
			VarTempUlong = 60000000;
		}
		else if(Frequency>=916)
		{
			REG_PWMB_PMCTL &= ~(3<<6);  //分频2: 30MHz
			REG_PWMB_PMCTL |= (1<<6);
			VarTempUlong = 30000000;
		}
		else if(Frequency>=458)
		{
			REG_PWMB_PMCTL &= ~(3<<6);  //分频4: 15MHz
			REG_PWMB_PMCTL |= (1<<7);
			VarTempUlong = 15000000;
		}
		else if(Frequency>=229)
		{
			REG_PWMB_PMCTL |= (3<<6);   //分频8: 7.5MHz
			VarTempUlong = 7500000;
		}
		else
		{
			return 2;
		}
	
		VarTempUlong = VarTempUlong/Frequency;
		REG_PWMB_PWMCM = (UINT16 )(VarTempUlong);
		
		REG_PWMB_PWMVAL0 = 0;
		REG_PWMB_PWMVAL1 = 0;
		REG_PWMB_PWMVAL2 = 0;
		REG_PWMB_PWMVAL3 = 0;
		REG_PWMB_PWMVAL4 = 0;
		REG_PWMB_PWMVAL5 = 0;
		
		REG_PWMB_PMOUT &= ~(1<<8);
		REG_PWMB_PMOUT &= ~(1<<9);
		REG_PWMB_PMOUT &= ~(1<<10);
		REG_PWMB_PMOUT &= ~(1<<11);
		REG_PWMB_PMOUT &= ~(1<<12);
		REG_PWMB_PMOUT &= ~(1<<13);		
		/*
		REG_PWMB_PMCCR &= ~(1<<8);
		REG_PWMB_PMCCR &= ~(1<<9);
		REG_PWMB_PMCCR &= ~(1<<10);
		REG_PWMB_PMCCR &= ~(1<<11);
		REG_PWMB_PMCCR &= ~(1<<12);
		REG_PWMB_PMCCR &= ~(1<<13);
		*/
		REG_PWMB_PMOUT |= (1<<15);
		REG_PWMB_PMCTL |= (3<<0);

	}
	else
	{
		return 1;
	}	
	return 0;
}
/* *************************************************************** 
** File End
** ************************************************************ */
