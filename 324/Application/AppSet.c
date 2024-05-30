#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
/**************************************************************
**��������Fun_Set_Loop()
**�����������궨���ű��������λ�¶�Ӧ��ת��ֵ
**�����������
**�����������
**************************************************************/
void FunDialSpeedSet(void)
{
	UINT8 VarAccDialPosiSetSort;
	//���ű�����Сֵ�����ֵ�궨
	if((VarCanAccDialPosiMinSet==1)&&(VarCanAccDialPosiMaxSet==0))
	{
		VarAccDialPosiSetSort=1;//�궨��Сֵ
	}
	else if((VarCanAccDialPosiMinSet==0)&&(VarCanAccDialPosiMaxSet==1))
	{
		VarAccDialPosiSetSort=2;//�궨���ֵ
	}
	else
	{
		VarAccDialPosiSetSort=0;
	}
	VarCanAccDialSetCommand=VarAccDialPosiSetSort;
	if(VarAccDialPosiSetSort>0)
	{
		FunDialSet(VarAccDialPosiSetSort);	
	}
	VarDialSetSortLast=VarAccDialPosiSetSort;
	VarCanAccDialSetCommandLast=VarCanAccDialSetCommand;
	//ȡ��ʻԱ�趨��λ, �����Χ0-9
	VarDialGrade = FunDialGradeCal(VarAccDialPosiMin,VarAccDialPosiMax);//VarAccDialPosiMax
}
 /**************************************************************
**��������Fun_Set_Acc_Dial_Max()
**�����������궨���ű��̵����λ����С��λ
**���������Set_Sort�� ==1���궨��С��λ./==2���궨���λ
**�����������
**************************************************************/
void FunDialSet(UINT8 Set_Sort)
{
	//�ޱ궨����򲻽��б궨
	if(VarCanAccDialSetCommand==0)
	{
		VarAccDialPosiSetting=0;
	}
	//�����ش������б궨���ҵ�ǰ���ڷǱ궨״̬���ϵ�ʱ�䳬��5S
	if(	(VarCanAccDialSetCommand>0)&&
		(VarCanAccDialSetCommandLast==0)&&
		(VarAccDialPosiSetting==0)&&
    	(LibTimerGet1S()-5>0 ))
	{
		VarAccDialPosiSetting=1;
	}
	//��������ģʽ��
	if(VarAccDialPosiSetting==1)
	{
		if(Set_Sort==1)
		{
			VarAccDialPosiMin=VarAccDialPosiNow;
		}
		else if(Set_Sort==2)
		{
			VarAccDialPosiMax=VarAccDialPosiNow;
		}
		VarFlashSysDateMasterNeedSaveFlag = 1;//������Ҫ����
		VarFlashSysDateBackupNeedSaveFlag = 1;
		VarAccDialPosiSetting=0;//�궨���
		VarDialSetSortLast=Set_Sort;
		VarAccDialPosiSetTimeLast=LibTimerGet1S();
	}
}
/**************************************************************
**��������Fun_Dial_Grade_Cal()
**�����������궨���ű��̵ĵ�λ
**���������Dial_Limit_1�����ű��̵�һ��ֵ��Dial_Limit_2�����ű��̵�ʮ��ֵ��
**�����������ǰ��λֵ
**************************************************************/
UINT8 FunDialGradeCal(UINT16 Dial_Limit_1,UINT16 Dial_Limit_2)
{
	UINT8 Dial_Grade_Now;
	UINT16 Dial_Grade_Band;
	if(LibAbsUint16(VarAccDialPosiNow,VarAccDialPosiLast)<15)
	return(VarDialGrade);
	VarAccDialPosiLast=VarAccDialPosiNow;
	
	if(Dial_Limit_1<Dial_Limit_2)
	{
		Dial_Grade_Band=(UINT16)( (Dial_Limit_2-Dial_Limit_1)/18 );
		if(VarAccDialPosiNow<(Dial_Limit_1+Dial_Grade_Band))
		{
			Dial_Grade_Now=1;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+3*Dial_Grade_Band))
		{
			Dial_Grade_Now=2;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+5*Dial_Grade_Band))
		{
			Dial_Grade_Now=3;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+7*Dial_Grade_Band))
		{
			Dial_Grade_Now=4;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+9*Dial_Grade_Band))
		{
			Dial_Grade_Now=5;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+11*Dial_Grade_Band))
		{
			Dial_Grade_Now=6;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+13*Dial_Grade_Band))
		{
			Dial_Grade_Now=7;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+15*Dial_Grade_Band))
		{
			Dial_Grade_Now=8;
		}
		else if(VarAccDialPosiNow<(Dial_Limit_1+17*Dial_Grade_Band))
		{
			Dial_Grade_Now=9;
		}
		else 
		{
			Dial_Grade_Now=10;
		}
	}
	else 
	{
		Dial_Grade_Band=(UINT16)( (Dial_Limit_1-Dial_Limit_2)/18);
		if(VarAccDialPosiNow>(Dial_Limit_1-Dial_Grade_Band))
		{
			Dial_Grade_Now=1;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-3*Dial_Grade_Band))
		{
			Dial_Grade_Now=2;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-5*Dial_Grade_Band))
		{
			Dial_Grade_Now=3;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-7*Dial_Grade_Band))
		{
			Dial_Grade_Now=4;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-9*Dial_Grade_Band))
		{
			Dial_Grade_Now=5;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-11*Dial_Grade_Band))
		{
			Dial_Grade_Now=6;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-13*Dial_Grade_Band))
		{
			Dial_Grade_Now=7;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-15*Dial_Grade_Band))
		{
			Dial_Grade_Now=8;
		}
		else if(VarAccDialPosiNow>(Dial_Limit_1-17*Dial_Grade_Band))
		{
			Dial_Grade_Now=9;
		}
		else 
		{
			Dial_Grade_Now=10;
		}
	}	
	return(Dial_Grade_Now);
}
