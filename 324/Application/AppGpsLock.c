#include "AppFun.h"
#include "AppVar.h"
#include "LibFunDefine.h"
#include "swGpsPrivate.h"
#include "stdlib.h"
/* ***************************************************************
**
** ��������: FunControlGpsLock
** ��������: GPS��ؿ���
**
******************************************************************/
void FunControlGpsLock(void)
{
	BOOL Step3CountStart,Step3CountStop,TimeAvailabe_Judge=0,Time_Longer;
	UINT8 VarBool1,temp_uchar,VarBool2;
	UINT32 Password_1;
	UINT32 Ulong_Temp1,Ulong_Temp2;
	UINT32 TonGpsCanError_Et;
	UINT16 Year_1,Year_2,Month_1,Month_2,Day_1,Day_2,Hour_1,Hour_2,Days,Hours;
	UINT32 code_1_H=9999,code_2_H=765432,code_1_L=8888,code_2_L=6790;
	
	//ʹ�ܳ�ʼ��
	if(GPSLock_Enable_Initial==0)
	{
		GPSLock_All_Enable = 1;	
		GPSLock_Passive_Enable = 1;
		MonthNoSignalLock_Enable = 1;
		UncoverLock_Enable = 1;
		CANSignalLostLock_Enable = 1;
		SIMCardLostLock_Enable = 1;
		
		GPSLock_Enable_Initial = 1;
		VarFlashGpsDataMasterNeedSaveFlag=1;
		VarFlashGpsDataBackupNeedSaveFlag=1;		
	}
	
	
	//GPS���������·�ʱ��д��һ��Flash
	if((VarCanGpsLockCommand_A != VarCanGpsLockCommandLast_A)||(VarCanGpsLockCommand_B != VarCanGpsLockCommandLast_B)
	||(VarCanGpsLockCommand_C != VarCanGpsLockCommandLast_C)||(VarCanGpsLockCommand_D != VarCanGpsLockCommandLast_D))	
	{
		VarFlashGpsDataMasterNeedSaveFlag=1;
		VarFlashGpsDataBackupNeedSaveFlag=1;
	}
	
	//A����
	if(	VarCanGpsLockCommand_A>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_A=TRUE;
	}
	else
	{
		VarGpsLockState_A = FALSE;//VarGpsLockWork_A
		VarGpsLockWork_A = FALSE;
	}
	VarCanGpsLockCommandLast_A = VarCanGpsLockCommand_A;
	//B����
	if(	VarCanGpsLockCommand_B>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_B=TRUE;
	}
	else
	{
		VarGpsLockState_B = FALSE;//VarGpsLockWork_B
		VarGpsLockWork_B = FALSE;
	}
	VarCanGpsLockCommandLast_B = VarCanGpsLockCommand_B;
	//C����
	if(	VarCanGpsLockCommand_C>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_C=TRUE;
	}
	else
	{
		VarGpsLockState_C = FALSE;//VarGpsLockWork_C
		VarGpsLockWork_C = FALSE;
	}
	VarCanGpsLockCommandLast_C = VarCanGpsLockCommand_C;
	//D����
	if(	VarCanGpsLockCommand_D>0 &&
		(VarCanGpsCancel==0 && VarCanGpsUrgencyState ==0)
	)
	{
		VarGpsLockState_D=TRUE;
	}
	else
	{
		VarGpsLockState_D = FALSE;//VarGpsLockWork_D
		VarGpsLockWork_D = FALSE;
	}
	VarCanGpsLockCommandLast_D = VarCanGpsLockCommand_D;
	//10���������ź��ޱ仯����Ϊcan���߹��ϣ���ʱ5���Ӻ�������
	//if(	VarCanGpsHeartBeatLast == VarCanGpsHeartBeat)	
	if(	VarCanGpsHeartBeat==0)
	{
		VarGpsCanNoBeat = 1;
	}
	else
	{
		VarGpsCanNoBeat = 0;	
	}
	VarGpsCanErrorState = LibTimerTon(9,VarGpsCanNoBeat,30000,&TonGpsCanError_Et);//30S
	if(VarGpsCanErrorState)
	{
		VarGpsCanBusError = TRUE;
	}
	else
	{
		VarGpsCanBusError = FALSE;
	}
	VarCanBusLockCommand = LibTimerTon(10,VarGpsCanBusError,30000,&VarGpsCanBusError_Et);//5min,3......	
	if((VarCanGpsCancel==0 && VarCanGpsUrgencyState==0)&&
	VarCanBusLockCommand>0
	)
	{
		
		VarCanBusLockState=1;
	}
	else
	{
		VarCanBusLockState=0;
	}
	if (VarCanGpsCancel==1 || VarCanGpsUrgencyState==1) VarGpsCanBusError = FALSE;
	
	
	//���߱�����ʱ20������
	VarCanAntennaCut = LibTimerTon(11,VarCanAntennaCutLockCommand,20000,&VarGpsAntennaCut_Et);
	if(VarCanAntennaCut>0 &&
	(VarCanGpsCancel==0 && VarCanGpsUrgencyState==0))
	{
		VarCanAntennaCutLockState=1;
	}
	else
	{
		VarCanAntennaCutLockState=0;
	}
	
	//��Ǽ�ʱ����
	if(VarCanUncoverLockCommand>0 &&
	(VarCanGpsCancel==0 && VarCanGpsUrgencyState==0))
	{
		VarCanUncoverLockState=1;
	}
	else
	{
		VarCanUncoverLockState=0;
	}
	
	TimeAvailabe_Judge= IsTimeAvailable((ClockTime_Year+2000),ClockTime_Month,ClockTime_Day,ClockTime_Hour);
	TimeAvailable_1=TimeAvailabe_Judge;
	
	//���ź�����
	if(GPSPlatformConnetState==0)//���ź�
	{	
		if (VarCan2MonthLockState==1){
			;//�������ź�����״̬�����ж�
		
		//���ź���ʱ��δ����60�죬ʱ����Ч
		}else if (TimeAvailable==1 && TimeAvailabe_Judge==1){
			Year_1 = NoSignalStart_Year+2000;//������������λ
			Month_1 = NoSignalStart_Month;
			Day_1 = NoSignalStart_Day;
			Year_2 = ClockTime_Year+2000;//������������λ
			Month_2 = ClockTime_Month;
			Day_2 = ClockTime_Day;
			Time_Longer=TimeCompare(Year_1,Month_1,Day_1,0,Year_2,Month_2,Day_2,0);
			TimeCompare_1=Time_Longer;
			if (NoSignalStart_Year==0 || NoSignalStart_Month==0 ||NoSignalStart_Day==0||Time_Longer==0){
				//���źų�ʼʱ����Чʱ�����浱ǰ�����գ��ۼ�ʱ������
				NoSignalStart_Year = ClockTime_Year;
				NoSignalStart_Month = ClockTime_Month;
				NoSignalStart_Day = ClockTime_Day;
				NoSignalTotal_Day = 0;
				//'ʱ�䱣��'
				VarFlashGpsDataMasterNeedSaveFlag=1;
				VarFlashGpsDataBackupNeedSaveFlag=1;
			}
			if (NoSignalTotal_Day==0){//�ϵ�һ��ֻ����һ�μ��ʱ�䣬�˱�����ʼ��Ϊ0
				Year_1 = NoSignalStart_Year+2000;//������������λ
				Month_1 = NoSignalStart_Month;
				Day_1 = NoSignalStart_Day;
				Year_2 = ClockTime_Year+2000;//������������λ
				Month_2 = ClockTime_Month;
				Day_2 = ClockTime_Day;
				Days = DaysBetween2Date(Year_1,Month_1,Day_1,Year_2,Month_2,Day_2);
				if (Days==0) NoSignalTotal_Day=1;
				else if(Days>60) NoSignalTotal_Day=60;
			}
			//���ź���ʱ������60��
			if (NoSignalTotal_Day>=60){	
				//'״̬����'
				if(VarCan2MonthLockState==0){
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
					VarCan2MonthLockState = 1;
				}
			}
		}
	//���źţ�����״̬�����ź�ʱ�䲻Ϊ0		
	}else {
		if(((NoSignalTotal_Day!=0)||(VarCan2MonthLockState==1))&& GPSPlatformConnetState == 1){	
			//����״̬������ۼ�ʱ������
			VarCan2MonthLockState = 0;
			NoSignalStart_Year = 0;
			NoSignalStart_Month = 0;
			NoSignalStart_Day = 0;
			NoSignalTotal_Day = 0;
			//'״̬ʱ�䱣��'
			VarFlashGpsDataMasterNeedSaveFlag=1;
			VarFlashGpsDataBackupNeedSaveFlag=1;
		} 
	}
	
	
	//����ʹ�ܿ���
	//GPSLock_All_Enable=0;
	if (GPSLock_All_Enable==0)//��ʹ��
	{
		VarGpsLockState_A = 0;
		VarGpsLockState_B = 0;
		VarGpsLockState_C = 0;
		VarGpsLockState_D = 0;
		VarGpsCanBusError = FALSE;
		VarCanBusLockState=0;
		VarCanAntennaCutLockState=0;
		VarCanUncoverLockState=0;
		VarCan2MonthLockState=0;
	}
	if(GPSLock_Passive_Enable==0)//����������ʹ��
	{
		VarGpsCanBusError = FALSE;
		VarCanBusLockState=0;
		VarCanAntennaCutLockState=0;
		VarCanUncoverLockState=0;
		VarCan2MonthLockState=0;
	}
	if(MonthNoSignalLock_Enable==0)//ä������ʹ��
	{
		VarCan2MonthLockState=0;
	}
	if(UncoverLock_Enable==0)//�������ʹ��
	{
		VarCanUncoverLockState=0;
	}
	if(CANSignalLostLock_Enable==0)//��������ʹ��
	{
		VarGpsCanBusError = FALSE;
		VarCanBusLockState=0;
	}
	if(SIMCardLostLock_Enable==0)//�ο�����ʹ��
	{
		//VarCan2MonthLockState = 0;//SIM���쳣������
	}
	
	//�����ж�
	//��ʱǰ��
	if (GPSUnLockStep==3) Step3CountStart=1;
	else Step3CountStart=0;
	Step3CountStop = LibTimerTon(5,Step3CountStart,6000,&Ulong_Temp1);
	
	//��������Ų�ͬʱ���������������ж�����
	if ((SignalNumber_115 != SignalNumber_115_Last)||((OderType_115&0x30) != (OderType_115_Last&0x30))){
		GPSUnLockStep = 0;
	}
	//�жϲ���
	switch (GPSUnLockStep){
	case 0:	
		if (OderType_115==0x11 || OderType_115==0x21 || OderType_115==0x31){
			code_1_H=VarSysVoltageMv;
			code_2_H=rand();
			code_1_L=VarAiFuelVolume;
			code_2_L=rand();
			OderType_2F1 = OderType_115;
			SignalNumber_2F1 = SignalNumber_115;
			OderType_115_Last = OderType_115;
			SignalNumber_115_Last = SignalNumber_115;
			DynamicCode_H = caculateCodeH(code_1_H,code_2_H);
			DynamicCode_L = caculateCodeL(code_1_L,code_2_L);
			GPSUnLockStep = 1;//�յ���̬�����󣬼��㶯̬�룬����������ţ����벽��1
		}
		else{//����
			DynamicCode_H = 0;
			DynamicCode_L = 0;
			break;
		}
	case 1:	
		if (OderType_115==0x12 || OderType_115==0x22 || OderType_115==0x32){
			GPSUnLockStep = 2;//�����յ���ʾ�����������ֹͣ���ͣ����벽��2
		}
		else break;	//���Ͷ�̬��
	case 2://2.���ս������룬У��������
		//����״̬����
		VarCanGpsCancelPSDoK=0;
		VarCanGpsUnlockPSDOK=0;
		VarCanGpsUrgencyPSDoK=0;
		GPSUnlockPSD_Last=GPSUnlockPSD;
		//0x12�����ź��������
		if (OderType_115==0x12){
			GPSUnLockStep = 3;
			OderType_2F1 = 0x12;
			Password_1 = swNetworklessUnlock(DynamicCode_H,DynamicCode_L,1);
			PSD =Password_1;
			if (GPSUnlockPSD==Password_1){
				VarCanGpsUnlockPSDOK=1;
				if(VarCan2MonthLockState==1){
					VarCan2MonthLockState=0;
					//���浱ǰ�����գ��ۼ�ʱ������
					if(TimeAvailable==1 && TimeAvailabe_Judge==1){
						NoSignalStart_Year = ClockTime_Year;
						NoSignalStart_Month = ClockTime_Month;
						NoSignalStart_Day = ClockTime_Day;					
					}else{
						NoSignalStart_Year = 0;
						NoSignalStart_Month = 0;
						NoSignalStart_Day = 0;			
					}
					NoSignalTotal_Day = 0;
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}
			}
			GPSPSDVerify = VarCanGpsUnlockPSDOK;
		}
		//0x22�������������ý��
		else if (OderType_115==0x22)
		{
			GPSUnLockStep = 3;
			OderType_2F1 = 0x22;
			Password_1 = swGpsPermanentCancel(DynamicCode_H,DynamicCode_L,1);
			PSD =Password_1;
			if (GPSUnlockPSD==Password_1){
				//������ȷִ��
				VarCanGpsCancelPSDoK=1;
				if(VarCanGpsCancel==0){
					VarCanGpsCancel=1;
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}
			}else if(GPSUnlockPSD==4321){
				//�ָ����룬��ʾ��ȷ
				VarCanGpsCancelPSDoK=1;
				if(VarCanGpsCancel==1){
					VarCanGpsCancel=0;
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}	
			}
			GPSPSDVerify = VarCanGpsCancelPSDoK;
		}
		//0x32���������
		else if(OderType_115==0x32){
			GPSUnLockStep = 3;
			OderType_2F1 = 0x32;
			Password_1 = swEmergentUnlock(DynamicCode_H, DynamicCode_L,1);
			PSD =Password_1;
			if (GPSUnlockPSD==Password_1){
				//������ȷִ��
				VarCanGpsUrgencyPSDoK=1;
				if(VarCanGpsUrgencyState==0){
					VarCanGpsUrgencyState=1;
					if(TimeAvailable==1 && TimeAvailabe_Judge==1){
						EmergencyStart_Year = ClockTime_Year;
						EmergencyStart_Month = ClockTime_Month;
						EmergencyStart_Day = ClockTime_Day;	
						EmergencyStart_Hour = ClockTime_Hour;	
					}else{
						EmergencyStart_Year = 0;
						EmergencyStart_Month = 0;
						EmergencyStart_Day = 0;		
						EmergencyStart_Hour = 0;
					}
					//����GPS����
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
					//����Сʱ������
					VarEngineWorkTime_Gps = VarEngineWorkTime1H;
					VarFlashEngineWorkTimeMasterNeedSaveFlag = 1;
					VarFlashEngineWorkTimeBackupNeedSaveFlag = 1;
				}
			//�ָ����룬��ʾ��ȷ
			}else if(GPSUnlockPSD==4321){
				VarCanGpsUrgencyPSDoK=1;
				if(VarCanGpsUrgencyState>0){
					VarCanGpsUrgencyState=0;
					EmergencyUnlock_Hour=0;
					EmergencyStart_Year = ClockTime_Year;
					EmergencyStart_Month = ClockTime_Month;
					EmergencyStart_Day = ClockTime_Day;	
					EmergencyStart_Hour = ClockTime_Hour;
					//����GPS����
					VarFlashGpsDataMasterNeedSaveFlag=1;
					VarFlashGpsDataBackupNeedSaveFlag=1;
				}
			}
			GPSPSDVerify = VarCanGpsUrgencyPSDoK;//����״̬��ֵ
		}else{
			GPSPSDVerify = 0;//����״̬����
			break;//��ʾ��δ���������򲻷��������ж�״̬
		}
	case 3://����������ȷ/����״̬
		//ͬһ���������յ�������󣬻ص�����2
		if ((OderType_115==OderType_2F1)&&(GPSUnlockPSD_Last!=GPSUnlockPSD)) GPSUnLockStep = 2;
		//����ͬ��������ǡ����ͬʱ�����ز���0
		else if (OderType_115!=OderType_2F1) GPSUnLockStep = 0;
		//���벽��3��ʼ��ʱ��6s����벽��4
		else if (Step3CountStop==1){
			LibTimerTon(5,0,6000,&Ulong_Temp1);//��ʱ���
			GPSUnLockStep = 4;
		}
		else break;
	case 4://�ȴ�������������˳����治��ͨѶ
		//ͬһ���������յ��������ص������жϲ���
		if ((OderType_115==OderType_2F1)&&(GPSUnlockPSD_Last!=GPSUnlockPSD)) GPSUnLockStep = 2;
		break;
	default:break;
	}

	//Gps��������ʱ��������ʱ��Ϊ48Сʱ
	//����״̬������������Чʱ��ʹ��GPS����ʱ�����48Сʱ
	if((TimeAvailable==1 && TimeAvailabe_Judge==1)&&(VarCanGpsUrgencyState>0)&&(VarGpsCanErrorState==0)){
		b_48Test=1;
		if(EmergencyUnlock_Hour==0){
			Year_1 = EmergencyStart_Year+2000;//������������λ
			Month_1 = EmergencyStart_Month;
			Day_1 = EmergencyStart_Day;
			Hour_1=EmergencyStart_Hour;
			Year_2 = ClockTime_Year+2000;//������������λ
			Month_2 = ClockTime_Month;
			Day_2 = ClockTime_Day;
			Hour_2=ClockTime_Hour;
			Time_Longer=TimeCompare(Year_1,Month_1,Day_1,Hour_1,Year_2,Month_2,Day_2,Hour_2);
			if (EmergencyStart_Year==0 || EmergencyStart_Month==0 ||EmergencyStart_Day==0||Time_Longer==0){
				EmergencyStart_Year = ClockTime_Year;
				EmergencyStart_Month = ClockTime_Month;
				EmergencyStart_Day = ClockTime_Day;	
				EmergencyStart_Hour = ClockTime_Hour;	
				//����GPS����
				VarFlashGpsDataMasterNeedSaveFlag=1;
				VarFlashGpsDataBackupNeedSaveFlag=1;
			}
			//���¸�ֵ
			Year_1 = EmergencyStart_Year+2000;//������������λ
			Month_1 = EmergencyStart_Month;
			Day_1 = EmergencyStart_Day;
			Hour_1=EmergencyStart_Hour;
			Hours=HoursBetween2Date(Year_1,Month_1,Day_1,Hour_1,Year_2,Month_2,Day_2,Hour_2);
			if (Hours==0) EmergencyUnlock_Hour=1;
			else if(Hours>48) EmergencyUnlock_Hour=48;
			else EmergencyUnlock_Hour=Hours;
		}
		if(EmergencyUnlock_Hour>=48){
			VarCanGpsUrgencyState=0;//GPS�������ȡ��
			EmergencyStart_Year = 0;
			EmergencyStart_Month = 0;
			EmergencyStart_Day = 0;		
			EmergencyStart_Hour = 0;
			//����GPS����
			VarFlashGpsDataMasterNeedSaveFlag=1;
			VarFlashGpsDataBackupNeedSaveFlag=1;
		}
	}
	//����״̬�������������޷�ʹ��GPSʱ��ʱ��ʹ�ù���Сʱ����48Сʱ
	if((VarEngineWorkTime1H>VarEngineWorkTime_Gps+48)&&(VarCanGpsUrgencyState>0))
	{
		VarCanGpsUrgencyState=0;//GPS�������ȡ��
		//����GPS����
		VarFlashGpsDataMasterNeedSaveFlag=1;
		VarFlashGpsDataBackupNeedSaveFlag=1;
	}
	
	//------------------ִ������--------------------
	if(VarCanGpsCancel==0 && VarCanGpsUrgencyState==0)//���δ����GPS����
	{
		if(VarGpsLockWork_C&&(!VarGpsLockWork_D))    //C����������������
		{
			VarGpsLockEnginePower=TRUE;
			VarGpsLockPumpPower=FALSE;
		}
		else if((!VarGpsLockWork_C)&&VarGpsLockWork_D)//D�������ù���
		{
			VarGpsLockPumpPower=TRUE;
			VarGpsLockEnginePower=FALSE;	
		}
		else if( (VarGpsLockWork_C&&VarGpsLockWork_D)//��������ת���빦��
			||VarCan2MonthLockState
			||VarCanUncoverLockState
			||VarCanBusLockState
			||VarCanAntennaCutLockState)
		{
			VarGpsLockEnginePower=TRUE;
			VarGpsLockPumpPower=TRUE;
		}
		else
		{
			VarGpsLockEnginePower=FALSE;
			VarGpsLockPumpPower=FALSE;
		}		
	}
	else
	{
		VarGpsLockEnginePower=FALSE;
		VarGpsLockPumpPower=FALSE;
	}
	//A���������ȵ�
	if( ((VarCanGpsCancel==1 || VarCanGpsUrgencyState==1)||(!VarGpsLockWork_A)) &&
		(VarSysPowerOn>0) &&
		(VarDiPilot>0))
	{
		VarDoPilot=1;
	}
	else
	{
		VarDoPilot=0;
	}
	
	//B��������������ͣ��
	if( ((VarCanGpsCancel==1 && VarCanGpsUrgencyState==1)||(!VarGpsLockWork_B))
		&&VarSysPowerOn)//B����������������������ͣ��
	{
		VarEngineStop=0;
	}
	else
	{
		VarEngineStop=1; 
	}

}

/* ***************************************************************
**
** ��������: IsLeap
** ��������: �ж�һ������Ƿ�Ϊ����
**
******************************************************************/
BOOL IsLeap(UINT16 year)
{
   return ((year % 4 ==0 && year % 100 !=0)|| year % 400 ==0) ;
}
/* ***************************************************************
**
** ��������: DayInYear
** ��������: ���ݸ��������ڣ�������ڸ���ĵڼ���
**
******************************************************************/
UINT16 DayInYear(UINT16 year, UINT16 month, UINT16 day)
{
    //int _day = 0;
	UINT16 i;
	UINT16 DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeap(year))
        DAY[1] = 29;
    for(i=0; i<month - 1; ++i)
    {
        day += DAY[i];
    }
    return day;
}
/* ***************************************************************
**
** ��������: DaysBetween2Date
** ��������: ���ݸ��������ڣ���������ڵĲ�ֵ
**
******************************************************************/
UINT16 DaysBetween2Date(UINT16 year1, UINT16 month1, UINT16 day1,UINT16 year2, UINT16 month2, UINT16 day2)
{
	UINT16 d1,d2,d3;
	UINT16 Year_Temp,Month_Temp,Day_Temp;
	UINT16 year;
	//������ͬ
	if(year1 == year2 && month1 == month2)
	{
		return (day1 > day2) ? (day1 - day2) : (day2 - day1);
      
	//�������ͬ
	}else if(year1 == year2)
	{
    	
         d1 = DayInYear(year1, month1, day1);
         d2 = DayInYear(year2, month2, day2);
         return (d1 > d2) ? (d1 - d2) : (d2 - d1);
      
     //���¶�����ͬ
     }else{
         //ȷ��year1��ݱ�year2��
         if(year1 > year2){
             //swop��������ֵ�Ľ���
        	Year_Temp = year1;
        	Month_Temp = month1;
        	Day_Temp = day1;
        	year1 = year2;
        	month1 = month2;
        	day1 = day2;
        	year2 = Year_Temp;
        	month2 = Month_Temp;
        	day2 = Day_Temp;
         }  
         if(IsLeap(year1))
			d1 = 366 - DayInYear(year1,month1, day1); //ȡ����������ڸ��껹���¶�����
         else
			d1 = 365 - DayInYear(year1,month1, day1);
         d2 = DayInYear(year2,month2,day2); //ȡ���ڵ����еĵڼ���
         d3 = 0;
         for( year= year1 + 1; year < year2; year++)
         {
			if(IsLeap(year))
				d3 += 366;
			else
				d3 += 365;
         }
         return d1 + d2 + d3;
     }
}
/* ***************************************************************
**
** ��������: HoursBetween2Date
** ��������: ���ݸ��������ڣ����Сʱ��ֵ
**
******************************************************************/
UINT16 HoursBetween2Date(UINT16 year1, UINT16 month1, UINT16 day1,UINT8 hour1, UINT16 year2, UINT16 month2, UINT16 day2, UINT8 hour2)
{
	BOOL Exchanged=0;
	UINT16 d1,d2,d3;
	UINT16 Year_Temp,Month_Temp,Day_Temp;
	UINT16 year;
	INT16 Days;
	INT32 Hours;
	//������ͬ
	if(year1 == year2 && month1 == month2)
	{
		Days = day2 - day1;
	
	//�������ͬ
	}else if(year1 == year2)
	{
		d1 = DayInYear(year1, month1, day1);
		d2 = DayInYear(year2, month2, day2);
		Days = d2 - d1;
	
	//���¶�����ͬ
	}else{
		//ȷ��year1��ݱ�year2��
		if(year1 > year2)
		{
			//swop��������ֵ�Ľ���
			Year_Temp = year1;
			Month_Temp = month1;
			Day_Temp = day1;
			year1 = year2;
			month1 = month2;
			day1 = day2;
			year2 = Year_Temp;
			month2 = Month_Temp;
			day2 = Day_Temp;
			Exchanged = 1;
		}
			
		if(IsLeap(year1))
			d1 = 366 - DayInYear(year1,month1, day1); //ȡ����������ڸ��껹���¶�����
		else
			d1 = 365 - DayInYear(year1,month1, day1);
		d2 = DayInYear(year2,month2,day2); //ȡ���ڵ����еĵڼ���
		d3 = 0;
		for( year= year1 + 1; year < year2; year++)
		{
			if(IsLeap(year))
				d3 += 366;
			else
				d3 += 365;
		}
		if(Exchanged==1)
			Days = -(d1 + d2 + d3);
		else
			Days = d1 + d2 + d3;
	}
	Hours=24*Days+hour2-hour1;
	if(Hours>65535 || Hours< -65535)
	{
		Hours=65535;
	}
	if(Hours>=0) return Hours;
	else return -Hours;
			
}
/* ***************************************************************
**
** ��������: IsTimeAvailable
** ��������: ���ݸ��������ڣ�������ڸ���ĵڼ���
**
******************************************************************/
BOOL IsTimeAvailable(UINT16 year,UINT16 month,UINT16 day,UINT8 hour)
{
	UINT16 DAY_1[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	UINT16 DAY_2[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	if(year==0 || month==0 || day==0) 	return 0 ;
	if(month>12 || hour>24)	return 0 ;
	if(IsLeap(year)){
		if(day>DAY_2[month])	return 0 ;
	}else{
		if(day>DAY_1[month])	return 0 ;
	}
	return 1 ;
}
/* ***************************************************************
**
** ��������: TimeCompare
** ��������: �����ڱȽϣ�1����2���1,2����1���0
**
******************************************************************/
BOOL TimeCompare(UINT16 year1, UINT16 month1, UINT16 day1,UINT8 hour1, UINT16 year2, UINT16 month2, UINT16 day2, UINT8 hour2)
{
	UINT16 d1,d2,d3;
	UINT16 Year_Temp,Month_Temp,Day_Temp;
	UINT16 year;
	//��������ͬ
	if(year1 == year2 && month1 == month2 && day1==day2){
		if(hour2>=hour1) return 1;
		else return 0;
	//������ͬ	
	}else if(year1 == year2 && month1 == month2){
		if(day2>=day1) return 1;
		else return 0;
	//�������ͬ
	}else if(year1 == year2)
	{	
		if(month2>=month1) return 1;
		else return 0;
	 //�����ն�����ͬ
	 }else{
		 //ȷ��year1��ݱ�year2��
		 if(year2 > year1) return 1;
		 else return 0;		 
	 }
}
