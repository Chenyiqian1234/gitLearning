#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibGetAiRes
** 功能描述:读取AI输入电阻值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT16 LibGetAiRes(UINT8 Channal)
{
	UINT32 Voltage;
	UINT32 Current;
	UINT32 Res;
	UINT32 ResTemp;
	Voltage = LibGetAiVoltage(Channal);
	if(Voltage>5000){Voltage = 5000;}
	
	#if DefineHardwareSWE75
		if(Channal==6 || Channal==12)
		{
			Current = (DefineAiResPullUpVoltageMv - Voltage)/200; // mA
			if(Current!=0)
			{
				Res = (Voltage*10)/Current;  //mR
			}
			else
			{
				Res= 0xFFFF;
			}
			return (UINT16)Res;
		}
	#endif
	
	if(Channal<=5)
	{
		//200R,5V
		Current = (DefineAiResPullUpVoltageMv - Voltage)/2;
		if(Current!=0)
		{
			Res = Voltage*1000/Current;  //mR
		}
		else
		{
			Res= 0xFFFF;
		}
		//对误差的标定
#if 0
		switch(Channal)
		{
			case 0:
			{
				ResTemp = Res * 97 / 100;
				Res = ResTemp;
				break;	
			}
			case 1:
			{
				ResTemp = Res * 96 / 100;
				Res = ResTemp;
				break;	
			}
			case 2:
			{
				ResTemp = Res * 96 / 100;
				Res = ResTemp;
				break;	
			}
			case 3:
			{
				ResTemp = Res * 96 / 100;
				Res = ResTemp;
				break;	
			}
			case 4:
			{
				ResTemp = Res * 96 / 100;
				Res = ResTemp;
				break;
			}
			case 5:
			{
				ResTemp = Res * 96 / 100;
				Res = ResTemp;
				break;
			}
			default:
			{
				break;	
			}
		}
#endif
		/*电阻采集标定通道0-5*/
		ResTemp = Res * 96 / 100;
		Res = ResTemp;
	}
	else if(Channal<=9)
	{
		//1KR,5V
		Current = (DefineAiResPullUpVoltageMv - Voltage);    //uA
		if(Current!=0)
		{
			Res = (Voltage*1000)/Current; 
		}
		else
		{
			Res= 0xFFFF;
		}
		ResTemp = Res * 98 / 100;
		Res = ResTemp;
	}
	else
	{
		//2KR,5V
		Current = (DefineAiResPullUpVoltageMv - Voltage)/2;  //uA
		if(Current!=0)
		{
			Res = (Voltage*1000)/Current; 
		}
		else
		{
			Res= 0xFFFF;
		}
		/*电阻标定*/
		if(Channal == 10 || Channal == 11)
		{
			if(Res < 200 && Res > 100)
				Res = Res * 62 / 100;
			else if(Res >= 200 && Res < 300)
			{
				Res = Res * 83 / 100;
			}
			else if(Res >= 300 && Res < 600)
			{
				Res = Res * 92 / 100;
			}
			else if(Res >= 600 && Res < 1000)
			{
				Res = Res * 98 / 100;
			}
			else if(Res >= 1000 && Res < 1200)
			{
				;
			}
			else if(Res >= 1200 && Res < 1400)
			{
				Res = Res * 101 / 100;
			}
			else if(Res >= 1400 && Res < 1600)
			{
				Res = Res * 102 / 100;
			}
			else if(Res >=  1600 && Res < 2400)
			{
				Res = Res * 104 / 100;
			}
			else 
				;
		}
		else if(Channal == 12)
		{
			Res =  Res * 90 / 100;
		}
		else if(Channal == 13)
		{
			if(Res < 5000)
			{
				Res = Res * 95 / 100;
			}
			else
			{
				Res = Res * 92 / 100;
			}
		}
	}
	return (UINT16 )Res;
}
/* ******************************************************
** 函数名称:LibGetAiCurrent
** 功能描述:读取AI输入电流值uA
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT16 LibGetAiCurrent(UINT8 Channal)
{
	UINT32 Data;
	Data = LibGetAiVoltage(Channal);
	if(Channal<=7)
	{
		Data = Data * 5;
	}
	else if(Channal<=13)
	{
		Data = Data * 100;
		Data = Data/47;
	}
	else
	{
		Data = 0;
	}
	if(Channal == 6)
	{
		if(Data < 1500 && Data >= 500)
		{
			Data -= 130;
		}
		else if(Data >= 1500 && Data < 3500)
		{
			Data -= 165;
		}
		else if(Data >= 3500 && Data < 4500)
		{
			Data -= 180;
		}
		else if(Data >= 4500 && Data < 5500)
		{
			Data -= 195;
		}
		else if(Data >= 5500 && Data < 7500)
		{
			Data -= 216;
		}
		else if(Data >= 7500 && Data < 8500)
		{
			Data -= 228;
		}
		else if(Data >= 8500 && Data < 12500)
		{
			Data -= 260;
		}
		else if(Data >= 12500 && Data < 13500)
		{
			Data -= 273;
		}
		else if(Data >= 13500 && Data < 15500)
		{
			Data -= 291;
		}
		else if(Data >= 15500 && Data < 19500)
		{
			Data -= 300;
		}
		else if(Data >= 19500 && Data < 22500)
		{
			Data -=320;
		}
		else
		{
			;
		}
	}
	else if(Channal == 12)
	{
		if(Data < 1500 && Data >= 500)
		{
			Data -= 111;
		}
		else if(Data >= 1500 && Data < 2500)
		{
			Data -= 96;
		}
		else if(Data >= 2500 && Data < 4500)
		{
			Data -= 84;
		}
		else if(Data >= 4500 && Data < 5500)
		{
			Data -= 72;
		}
		else if(Data >= 5500 && Data < 6500)
		{
			Data -= 59;
		}
		else if(Data >= 6500 && Data < 7500)
		{
			Data -= 45;
		}
		else if(Data >= 7500 && Data < 8500)
		{
			Data -= 36;
		}
		else if(Data >= 8500 && Data < 10500)
		{
			Data -= 22;
		}
		else if(Data >= 10500 && Data < 11500)
		{
			Data -= 15;
		}
		else if(Data >= 11500 && Data < 12500)
		{
			Data += 5;
		}
		else if(Data >= 12500 && Data < 13500)
		{
			Data += 17;
		}
		else if(Data >= 13500 && Data < 15500)
		{
			Data += 37;
		}
		else if(Data >= 15500 && Data < 17500)
		{
			Data += 54;
		}
		else if(Data >= 17500 && Data < 18500)
		{
			Data += 65;
		}
		else if(Data >= 18500 && Data < 20500)
		{
			Data += 93;
		}
		else if(Data >= 20500 && Data < 22500)
		{
			Data += 113;
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}
	if(Data>0xFFFF)Data = 0xFFFF;
	return (UINT16)Data;
}
/* ******************************************************
** 函数名称:LibFunGetMcuTemperature
** 功能描述:读取系统电压值
** 传入参数:无
** 返回数据:无
** *************************************************** */
char LibGetMcuTemperature(void)
{
	INT8 TempChar=0;
	INT32 TempLong=0;
	LibMcuAdcInterruptDisable();
	TempLong = (INT32)(LibVarMcuAdcOrgData[7]);
	LibMcuAdcInterruptEnable();
	TempLong = (INT32)(TempLong*DefineMcuAdcVref);
	TempLong = (INT32)(TempLong/4095);
	TempLong = TempLong-1370;
	TempLong = TempLong*500;     
	TempLong = TempLong/3881;
	if(TempLong>127)
	{
		TempLong = 127;
	}
	else if(TempLong<-128)
	{
		TempLong = -128;
	}
	TempChar = (INT8)TempLong;
	return TempChar;
}
/* ******************************************************
** 函数名称:LibFunGetSystemVoltage
** 功能描述:读取系统电压值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT16 LibGetSystemVoltage(void)
{
	UINT32 TempUlong=0;	
	LibMcuAdcInterruptDisable();
	TempUlong = LibVarMcuAdcOrgData[15];
	LibMcuAdcInterruptEnable();
	TempUlong = (UINT32)(TempUlong*DefineMcuAdcVref);
	TempUlong = (UINT32)(TempUlong/4095);
	TempUlong = (UINT32)(TempUlong*11);
	if(TempUlong>1000)
	{
		TempUlong += 390;
	}
	return (UINT16)(TempUlong);
}
/* ******************************************************
** 函数名称:LibFunGetAiVoltage
** 功能描述:读取AI通道电压值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT16 LibGetAiVoltage(UINT8 Channal)
{
	UINT32 data;
	data = LibGetAiAdcValue(Channal);
	data = (UINT32)(data*DefineMcuAdcVref);
	data = (UINT32)(data/4095);
	switch(Channal)
	{
		case 0:
			if(LibVarPinoutsSelect[3]==0 ||  //AI5V
			   LibVarPinoutsSelect[3]==2 ||  //AIC
			   LibVarPinoutsSelect[3]==3 ||  //AIR
			   LibVarPinoutsSelect[3]==5     //DIL
			)
			{
				data *= 11;
				data = data/6;
			}
			else if(LibVarPinoutsSelect[3]==1 || //AIV35V
			        LibVarPinoutsSelect[3]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 1:
			if(LibVarPinoutsSelect[4]==0 ||  //AI5V
			   LibVarPinoutsSelect[4]==2 ||  //AIC
			   LibVarPinoutsSelect[4]==3 ||  //AIR
			   LibVarPinoutsSelect[4]==5     //DIL
			)
			{
				data *= 11;
				data = data/6;
			}
			else if(LibVarPinoutsSelect[4]==1 || //AIV12V
			        LibVarPinoutsSelect[4]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 2:
			if(LibVarPinoutsSelect[5]==0 ||  //AI5V
			   LibVarPinoutsSelect[5]==2 ||  //AIC
			   LibVarPinoutsSelect[5]==3 ||  //AIR
			   LibVarPinoutsSelect[5]==5     //DIL
			)
			{
				data *= 11;
				data = data/6;
			}
			else if(LibVarPinoutsSelect[5]==1 || //AIV12V
			        LibVarPinoutsSelect[5]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 3:
			if(LibVarPinoutsSelect[6]==0 ||  //AI5V
			   LibVarPinoutsSelect[6]==2 ||  //AIC
			   LibVarPinoutsSelect[6]==3 ||  //AIR
			   LibVarPinoutsSelect[6]==5     //DIL
			)
			{
				data *= 11;
				data = data/6;
			}
			else if(LibVarPinoutsSelect[6]==1 || //AIV12V
			        LibVarPinoutsSelect[6]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 4:
			if(LibVarPinoutsSelect[7]==0 ||  //AI5V
			   LibVarPinoutsSelect[7]==2 ||  //AIC
			   LibVarPinoutsSelect[7]==3 ||  //AIR
			   LibVarPinoutsSelect[7]==5     //DIL
			)
			{
				data *= 11;
				data = data/6;
			}
			else if(LibVarPinoutsSelect[7]==1 || //AIV35V
			        LibVarPinoutsSelect[7]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 5:
			if(LibVarPinoutsSelect[8]==0 ||  //AI5V
			   LibVarPinoutsSelect[8]==2 ||  //AIC
			   LibVarPinoutsSelect[8]==3 ||  //AIR
			   LibVarPinoutsSelect[8]==5     //DIL
			)
			{
				data *= 11;
				data = data/6;
			}
			else if(LibVarPinoutsSelect[8]==1 || //AIV12V
			        LibVarPinoutsSelect[8]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 6://PIN10   高阻输入
			if(LibVarPinoutsSelect[9]==0 ||  //AI5V
			   LibVarPinoutsSelect[9]==2 ||  //AIC
			   LibVarPinoutsSelect[9]==3 ||  //AIR
			   LibVarPinoutsSelect[9]==5     //DIL
			)
			{
				data *= 80;
				data = data/47;
			}
			else if(LibVarPinoutsSelect[9]==1 || //AIV35V
			        LibVarPinoutsSelect[9]==4    //DIH
			)
			{
				data *= 80;
				data = data/47;
				data *= (47000+10000);
				data = data/10000;
			}
			else
			{
				data = 0;
			}
			break;
		case 7://PIN11   高阻输入
			if(LibVarPinoutsSelect[10]==0 ||  //AI5V
			   LibVarPinoutsSelect[10]==2 ||  //AIC
			   LibVarPinoutsSelect[10]==3 ||  //AIR
			   LibVarPinoutsSelect[10]==5     //DIL
			)
			{
				data *= 80;
				data = data/47;
			}
			else if(LibVarPinoutsSelect[10]==1 || //AIV35V
			        LibVarPinoutsSelect[10]==4    //DIH
			)
			{
				data *= 80;
				data = data/47;
				data *= (47000+10000);
				data = data/10000;
			}
			else
			{
				data = 0;
			}
			break;
		case 8:
			if(LibVarPinoutsSelect[15]==0 ||  //AI5V
			   LibVarPinoutsSelect[15]==2 ||  //AIC
			   LibVarPinoutsSelect[15]==3 ||  //AIR
			   LibVarPinoutsSelect[15]==5     //DIL
			)
			{
				data *= (120+2+40);
				data = data/40;
			}
			else if(LibVarPinoutsSelect[15]==1 || //AIV35V
			        LibVarPinoutsSelect[15]==4    //DIH
			)
			{
				data *= (2+40);
				data = data/40;
				
				data *= (120000+12840);
				data = data/12840;
			}
			else
			{
				data = 0;
			}
			break;
		case 9:
			if(LibVarPinoutsSelect[16]==0 ||  //AI5V
			   LibVarPinoutsSelect[16]==2 ||  //AIC
			   LibVarPinoutsSelect[16]==3 ||  //AIR
			   LibVarPinoutsSelect[16]==5     //DIL
			)
			{
				data *= (120+2+40);
				data = data/40;
			}
			else if(LibVarPinoutsSelect[16]==1 || //AIV12V
			        LibVarPinoutsSelect[16]==4    //DIH
			)
			{
				data *= (2+40);
				data = data/40;
				
				data *= (120000+12840);
				data = data/12840;
			}
			else
			{
				data = 0;
			}
			break;
		case 10:
			if(LibVarPinoutsSelect[18]==0 ||  //AI5V
			   LibVarPinoutsSelect[18]==2 ||  //AIC
			   LibVarPinoutsSelect[18]==3 ||  //AIR
			   LibVarPinoutsSelect[18]==5     //DIL
			)
			{
				data *= 81;
				data = data/21;
			}
			else if(LibVarPinoutsSelect[18]==1 || //AIV12V
			        LibVarPinoutsSelect[18]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 11:
			if(LibVarPinoutsSelect[19]==0 ||  //AI5V
			   LibVarPinoutsSelect[19]==2 ||  //AIC
			   LibVarPinoutsSelect[19]==3 ||  //AIR
			   LibVarPinoutsSelect[19]==5     //DIL
			)
			{
				data *= 81;
				data = data/21;
			}
			else if(LibVarPinoutsSelect[19]==1 || //AIV12V
			        LibVarPinoutsSelect[19]==4    //DIH
			)
			{
				data *= (100000+9231);
				data = data/9231;
			}
			else
			{
				data = 0;
			}
			break;
		case 12://PIN21,高阻输入
			if(LibVarPinoutsSelect[20]==0 ||  //AI12V
			   LibVarPinoutsSelect[20]==2 ||  //AIC
			   LibVarPinoutsSelect[20]==3 ||  //AIR
			   LibVarPinoutsSelect[20]==5     //DIL
			)
			{
				#if DefineHardwareSWE75
				data *= 80;
				data = data/47;
				#else
				data *= 49;
				data = data/22;
				data *= 901;
				data = data/499;
				#endif
			}
			else if(LibVarPinoutsSelect[20]==1 || //AIV35V
			        LibVarPinoutsSelect[20]==4    //DIH
			)
			{
				data *= (100+33);
				data = data/33;
				
				data *= (47+22);
				data = data/22;
			}
			else
			{
				data = 0;
			}
			break;
		case 13://PIN23,高阻输入
			if(LibVarPinoutsSelect[22]==0 ||  //AI5V
			   LibVarPinoutsSelect[22]==2 ||  //AIC
			   LibVarPinoutsSelect[22]==3 ||  //AIR
			   LibVarPinoutsSelect[22]==5     //DIL
			)
			{
				data *= 49;
				data = data/22;
				data *= 901;
				data = data/499;
			}
			else if(LibVarPinoutsSelect[22]==1 || //AIV35V
			        LibVarPinoutsSelect[22]==4    //DIH
			)
			{
				data *= (100+33);
				data = data/33;
				
				data *= (47+22);
				data = data/22;
			}
			else
			{
				data = 0;
			}
			break;	
		default:
			data = 0;
	}
	return (UINT16)(data);
}
/* ******************************************************
** 函数名称:LibFunGetAiAdcValue
** 功能描述:读取AI通道AI值
** 传入参数:无
** 返回数据:无
** *************************************************** */
UINT16 LibGetAiAdcValue(UINT8 Channal)
{
	UINT8 i;
	UINT16 data;
	if(Channal<14)
	{
		switch(Channal)
		{
			case 0:
				i = 10; break;
			case 1:
				i = 11; break;
			case 2:
				i = 6; break;
			case 3:
				i = 12; break;
			case 4:
				i = 13; break;
			case 5:
				i = 14; break;
			case 6:
				i = 1; break;
			case 7:
				i = 2; break;
			case 8:
				i = 4; break;
			case 9:
				i = 5; break;
			case 10:
				i = 8; break;
			case 11:
				i = 9; break;
			case 12:
				i = 0; break;
			case 13:
				i = 3; break;
			default:
				return 0;
		}
		LibMcuAdcInterruptDisable();
		data = LibVarMcuAdcOrgData[i];
		LibMcuAdcInterruptEnable();
		if(data>4095)
		{
			data = 4095;
		}
		return data;
	}
	else
	{
		return 0;
	}
}
/* ******************************************************
** 函数名称:LibFunMcuAdcInterruptEnable
** 功能描述:ADC中断使能
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibMcuAdcInterruptEnable(void)
{
	REG_ADCA_ADCTL1 |= (1<<11);
	REG_ADCB_ADCTL1 |= (1<<11);
}
/* ******************************************************
** 函数名称:LibFunMcuAdcInterruptDisable
** 功能描述:ADC中断禁止
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibMcuAdcInterruptDisable(void)
{
	REG_ADCA_ADCTL1 &= ~(1<<11);
	REG_ADCB_ADCTL1 &= ~(1<<11);
}
/* ******************************************************
** 函数名称:LibFunMcuAdcInit
** 功能描述:初始化ADC
** 传入参数:无
** 返回数据:无
** *************************************************** */
void LibMcuAdcInit(void)
{
	//TSENSOR
	REG_TSENSOR_CTRL = 0x0001;
	// ADCA
	REG_ADCA_ADCTL1 |= (1<<14);
	REG_ADCA_ADCTL2 = 0x001F;
	REG_ADCA_ADZCC = 0x0000;
	REG_ADCA_ADLST1 = 0x3210;
	REG_ADCA_ADLST2 = 0x7654;
	REG_ADCA_ADSDIS = 0x0000;
	REG_ADCA_ADCAL = 0x0000;
	REG_ADCA_ADLLMT0 = 0;
	REG_ADCA_ADLLMT1 = 0;
	REG_ADCA_ADLLMT2 = 0;
	REG_ADCA_ADLLMT3 = 0;
	REG_ADCA_ADLLMT4 = 0;
	REG_ADCA_ADLLMT5 = 0;
	REG_ADCA_ADLLMT6 = 0;
	REG_ADCA_ADLLMT7 = 0;
	REG_ADCA_ADHLMT0 = 0x7FF8;
	REG_ADCA_ADHLMT1 = 0x7FF8;
	REG_ADCA_ADHLMT2 = 0x7FF8;
	REG_ADCA_ADHLMT3 = 0x7FF8;
	REG_ADCA_ADHLMT4 = 0x7FF8;
	REG_ADCA_ADHLMT5 = 0x7FF8;
	REG_ADCA_ADHLMT6 = 0x7FF8;
	REG_ADCA_ADHLMT7 = 0x7FF8;	
	REG_ADCA_ADOFS0 = 0;
	REG_ADCA_ADOFS1 = 0;
	REG_ADCA_ADOFS2 = 0;
	REG_ADCA_ADOFS3 = 0;
	REG_ADCA_ADOFS4 = 0;
	REG_ADCA_ADOFS5 = 0;
	REG_ADCA_ADOFS6 = 0;
	REG_ADCA_ADOFS7 = 0;
	REG_ADCA_ADPOWER = 0x00D0;	
	REG_ADCA_ADLSTAT = 0xFFFF;
	REG_ADCA_ADZCSTAT = 0x00FF;
	REG_ADCA_ADSTAT = (1<<11);
	REG_ADCA_ADCTL1 = (0<<14)|(0<<13)|(0<<12)|(1<<11)|(0<<7)|(1<<0);
	REG_ADCA_ADCTL1 |= (1<<13);		
	// ADCB
	REG_ADCB_ADCTL1 = (1<<14);
	REG_ADCB_ADCTL2 = 0x001F;
	REG_ADCB_ADZCC = 0x0000;
	REG_ADCB_ADLST1 = 0x3210;
	REG_ADCB_ADLST2 = 0x7654;
	REG_ADCB_ADSDIS = 0x0000;
	REG_ADCB_ADCAL = 0x0000;
	REG_ADCB_ADLLMT0 = 0;
	REG_ADCB_ADLLMT1 = 0;
	REG_ADCB_ADLLMT2 = 0;
	REG_ADCB_ADLLMT3 = 0;
	REG_ADCB_ADLLMT4 = 0;
	REG_ADCB_ADLLMT5 = 0;
	REG_ADCB_ADLLMT6 = 0;
	REG_ADCB_ADLLMT7 = 0;
	REG_ADCB_ADHLMT0 = 0x7FF8;
	REG_ADCB_ADHLMT1 = 0x7FF8;
	REG_ADCB_ADHLMT2 = 0x7FF8;
	REG_ADCB_ADHLMT3 = 0x7FF8;
	REG_ADCB_ADHLMT4 = 0x7FF8;
	REG_ADCB_ADHLMT5 = 0x7FF8;
	REG_ADCB_ADHLMT6 = 0x7FF8;
	REG_ADCB_ADHLMT7 = 0x7FF8;	
	REG_ADCB_ADOFS0 = 0;
	REG_ADCB_ADOFS1 = 0;
	REG_ADCB_ADOFS2 = 0;
	REG_ADCB_ADOFS3 = 0;
	REG_ADCB_ADOFS4 = 0;
	REG_ADCB_ADOFS5 = 0;
	REG_ADCB_ADOFS6 = 0;
	REG_ADCB_ADOFS7 = 0;
	REG_ADCB_ADPOWER = 0x00D0;	
	REG_ADCB_ADLSTAT = 0xFFFF;
	REG_ADCB_ADZCSTAT = 0x00FF;
	REG_ADCB_ADSTAT = (1<<11);
	REG_ADCB_ADCTL1 = (0<<14)|(0<<13)|(0<<12)|(1<<11)|(0<<7)|(1<<0);
	REG_ADCB_ADCTL1 |= (1<<13);	
	// IRQ
	REG_ITCN_IPR9 &= (0x00FF<<0);
	REG_ITCN_IPR9 |= (0x0005<<0);
}
/* *************************************************************** 
** File End
** ************************************************************ */
