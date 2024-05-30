#include "MC56F8367Reg.h"
#include "LibVarDefine.h"
#include "LibFunDefine.h"
/* ******************************************************
** 函数名称:LibFunMotorDriver
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibMotorDriver(UINT8 Dir)
{
	UINT8 i;
	if(LibVarPinoutsSelect[75]==0 &&
	   LibVarPinoutsSelect[76]==0 &&
	   LibVarPinoutsSelect[77]==0 &&
	   LibVarPinoutsSelect[78]==0
	)
	{
		if(Dir==1)
		{
			REG_GPIOD_DR &= ~(1<<2);
			REG_GPIOD_DR &= ~(1<<10);
			if(LibVarMotorDirLast==2)
			{
				for(i=0;i<50;i++)
				{
					i = i;
				}
			}
			REG_GPIOD_DR |= (1<<4);
			REG_GPIOD_DR |= (1<<11);
		}
		else if(Dir==2)
		{
			REG_GPIOD_DR &= ~(1<<4);
			REG_GPIOD_DR &= ~(1<<11);
			if(LibVarMotorDirLast==1)
			{
				for(i=0;i<50;i++)
				{
					i = i;
				}
			}
			REG_GPIOD_DR |= (1<<2);
			REG_GPIOD_DR |= (1<<10);			
		}
		else if(Dir==3)
		{
			REG_GPIOD_DR &= ~(1<<4);
			REG_GPIOD_DR &= ~(1<<10);
			if(LibVarMotorDirLast==1 || LibVarMotorDirLast==2)
			{
				for(i=0;i<50;i++)
				{
					i = i;
				}
			}
			REG_GPIOD_DR |= (1<<2);	
			REG_GPIOD_DR |= (1<<11);
		}
		else
		{
			REG_GPIOD_DR &= ~(1<<4);
			REG_GPIOD_DR &= ~(1<<2);
			REG_GPIOD_DR &= ~(1<<10);
			REG_GPIOD_DR &= ~(1<<11);
		}		
		LibVarMotorDirLast = Dir;
	}
}
/* *************************************************************** 
** File End
** ************************************************************ */
