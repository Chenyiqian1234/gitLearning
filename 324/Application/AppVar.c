#include "AppDefine.h"
UINT32 VarSysControlSerialID;//���������
UINT8 VarCMCommunicationVersion=0;//ͨѶЭ��汾��
UINT8 VarExcavatorMonitorType;//��ʾ������
//DI
UINT8 VarDiAirFilterAlarm;	//���˱���Di������Ч
UINT8 VarDiPreheat;			//Ԥ��Di������Ч��    **δ��
UINT8 VarDiTravelHighSpeed;	//���߸���Di������Ч��**δ��
UINT8 VarDiPilot;			//�ȵ�����Di������Ч
UINT8 VarDiLowSpeedEnable;	//������ѹDi������Ч��**δ��
UINT8 VarSysPowerOn;		//�ϵ�Di������Ч
UINT8 VarDiCharge;			//��籨��Di,����õ�
UINT8 VarDiPressureSwitch;  //����ѹ����ֵ����
//AI
UINT16 VarAiFuelVolume;		//�������裬0.1R
UINT16 VarAiEngineDial;		//���̷���,mV
UINT16 VarAiPump1Pressure;	//��1����������,uA
UINT16 VarAiPump2Pressure;	//��2����������,uA
UINT16 VarAiPilotSwitch;	//�ȵ�ѹ������,DIH pin50
UINT16 VarAiAirFilter;		//���˵���,0.1R
//Do
UINT8 VarDoSecondPressure;	//������ѹ�����ŷ�
UINT8 VarDoTravelHighSpeed;	//���߸��������ŷ�
UINT8 VarDoBatteryRelay;	//ϵͳ��Դ�̵���
UINT8 VarDoPilot;			//�ȵ������ŷ�
UINT8 VarDoEngineStopRelay;	//Ϩ������ŷ�
UINT8 VarDoValveBreakPilot=0; //����Һѹ��
UINT8 VarDoValvePressRegulate=0;//����ѹ�����Ʒ�
//CAN
UINT8 VarSendDataID181[8];
UINT8 VarSendDataID281[8];
UINT8 VarSendDataID381[8];
UINT8 VarSendDataID481[8];
UINT8 VarSendDataID182[8];
UINT8 VarSendDataID282[8];
UINT8 VarSendDataID382[8];
//UINT8 VarSendDataID383[8];
//UINT8 VarSendDataID384[8];
//���ܲ���
UINT8 VarSendDataID236[8];
UINT8 VarSendDataID237[8];
UINT8 VarSendDataID238[8];
UINT8 VarSendDataID239[8];

UINT8 VarSendDataID187[8];
UINT8 VarSendDataID287[8];
UINT8 VarRecDataID116[8];  //���ܲ���
UINT8 VarRecDataID285[8];

UINT8 VarRecDataID385[8];
UINT8 VarRecDataID485[8];
UINT8 VarRecDataID585[8];
UINT8 VarRecDataID188[8];
UINT8 VarSendDataID387[8];
UINT8 VarSendDataID487[8];
UINT8 VarRecDataID666[8];
UINT8 VarSendDataID1A0[8];
UINT8 VarSendDataID1A1[8];
UINT8 VarSendDataID1A2[8];
UINT8 VarCanSendDataStep=0;
UINT8 VarCanSendDataGpsStep=0;
UINT8 VarCanGpsCancelCommand;	//GPSȡ����������
UINT8 VarCanGpsCancelPSDoK;		//Gpsȡ������Դ���ֵ��1-��ȷ;0-����
UINT8 VarCanHighlandMode=0;     //0-��ͨģʽ��8-��ԭģʽ
//H Bridge
UINT8 VarAccMotorMoveDir=0;		//���ŵ���˶�����,0-ͣ;1-��;2-��;3-ɲ
//System
UINT16 VarSysVoltageMv=0;		//ϵͳ��ѹ��mV
UINT16 VarSysVoltFilterLast=0;

//NEW
UINT8 VarCanEngineOilPreAlarm=0;
UINT8 VarCanEngineDialPosi=0;
INT8 VarCanEngineTorque=0;
UINT16 VarCanEngineSpeed=0;
UINT16 VarCanEngineTargetSpeed=0;
UINT8 VarCanEngineWaterTemp=0;
UINT16 VarCanEngineOilPressure=0;
UINT16 VarCanEngineOilFlowRate=0;
UINT16 VarCanEngineAtmosPressrue=0;
INT16 VarCanEngineAirInTemp=0;
UINT16 VarCanEngineBoostPressrue=0;
INT16 VarCanEngineBoostTemp=0;
UINT16 VarCanEngineFuelWastageAll=0;
UINT8 VarCanSendEngineStep=0;
UINT8 VarRecDataID_0CF00300[8];
UINT8 VarRecDataID_0CF00400[8];
UINT8 VarRecDataID_18FEDF00[8];
UINT8 VarRecDataID_0x18FEEE00[8];
UINT8 VarRecDataID_0x18FEEF00[8];
UINT8 VarRecDataID_0x18FEF200[8];
UINT8 VarRecDataID_0x18FEF500[8];
UINT8 VarRecDataID_0x18FEF600[8];
UINT8 VarRecDataID_0x18FEF900[8];
UINT8 VarRecDataID_0x1CEBFF00[8];
UINT8 VarRecDataID_0x1CECFF00[8];
UINT8 VarRecDataID_0x18FECA00[8];
UINT8 VarSendDataID_0x0C0000E4[8];
UINT8 VarSendDataID_0x18FEE4E4[8];
UINT8 VarSendDataID_0x0C000003[8];
UINT8 VarSendDataID_0x18EA0021[8];
UINT8 VarSendDataID_0x18EA00F2[8];
UINT8 VarRecDataID_0x18ECFF00[8];//Ϋ�񷢶��������ϴ���
UINT8 VarRecDataID_0x18EBFF00[8];//Ϋ�񷢶�������ϴ���
UINT8 VarRecDataID_0x18FEE900[8];//��ʮ���ͺ�����
UINT8 VarRecDataID_0x18FEB100[8];//��ʮ��Сʱ������
UINT8 VarSendDataID0x18EA00FA[8];//��ʮ��Сʱ����������ָ��
UINT16 VarEngineAverageFuelYouHao;//ƽ���ͺ�
UINT8 VarEngineNeedStopFlag=0;//����ѹ����ͣ��
//***************Control***********************
UINT8 VarDiLowSpeedEnableLast=0;
UINT16 VarEngineLevelSpeed[11];
UINT16 VarCanEngineLevelSpeed;
UINT8 VarButtonLowSpeedEnable=0;
UINT8 VarSetAccMotorCommand=0;		//��ʼ�궨����
UINT16 VarSetAccMotorMoveDoneTime1Ms=0;
UINT16 VarSetAccMotorMoveCount=0;	//����˶�����
UINT16 VarEngineTorque;
UINT16 VarAccMotorPosi[100]=
{
	0
};//�����ʷλ��
UINT16 VarEngineSpeed[100]=
{
	0
};//��������ʷת��ֵ
UINT16 VarAccMotorPosiNow=0;		//���λ�÷�����mv
UINT16 VarAccDialPosiNow=0;			//����λ�÷���,mV
UINT16 VarAccDialPosiLast=0;		//ǰһ�������ڱ���λ��ֵ
UINT8 VarDialGrade=1;				//���̵�λֵ
UINT16 VarAccMotorPosiTarget=2000;	//���Ŀ��λ��
UINT16 VarAccMotorPosiSet[11];		//ת�ٱ궨�еõ��λ�ã�11��
UINT16 VarAccMotorMoveTime1Ms=0;	//����˶�ʱ��
UINT16 VarAccMotorStopTime1Ms=0;	//���ֹͣʱ��
UINT8 VarAccMotorMoveState=0;		//����˶�״̬:1-�����˶���;0-�����˶�����
UINT32 VarAccMotorTimerLast=0;		//��һ�������ڵ�ϵͳʱ�䣬���Լ����������ʱ�䣬�����������˶�ʣ��ʱ��
UINT16 VarAccMotorPosiTargetLast=0;	//�ϳ�����Ŀ��λ�ã����ڵ�λ�仯���жϼ�ת�ٱ궨
UINT8 VarAccMotorStopJiggle=0;		//ֹͣ΢����־λ��1-�����趨΢������,ֹͣ�˶�;0-δ�����趨΢������
UINT8 VarEngineSpeedSetGradeTargetLast=0;//�ϳ������ڱ궨Ŀ�굵λ������ͬһ��λ�궨ʱ��ļ���
UINT8 VarTargetGradeSetState=0;			//����λ�궨״̬��1-�ڱ궨ͬһת�ٵ�λ;0-�궨��ת�ٵ�λ�����仯
UINT16 VarAccMotorMoveTimeExtra=0;		//����˶���������ʱ�䣬�ڱ궨�е��������ʱ���ӵ��˶�ʱ��

UINT16 VarCanAccMotorPosiMaxLimit=4200;		//���ŵ�����λ������ֵ
UINT16 VarCanAccMotorPosiMinLimit=1300;		//���ŵ����Сλ������ֵ

UINT8 VarCanAccDialSetCommand=0;		//���ű��̱궨���������ʾ��
UINT8 VarAccDialPosiSetting=0;			//���̱궨״̬��1-�궨��
UINT32 VarAccDialPosiSetTimeLast=0;		//�����ϴα궨ʱ��
UINT8 VarCanAccDialSetCommandLast=0;	//�ϳ������ڱ��̱궨����
UINT8 VarDialSetSortLast=0;				//�ϴα��̱궨����
UINT16 VarAccDialPosiMax=0;				//���̱궨���ֵ
UINT16 VarAccDialPosiMin=0;				//���̱궨��Сֵ
UINT8 VarCanEngineSpeedSet=0;			//ת�ٱ궨���������ʾ��
UINT8 VarCanEngineSpeedSetLast=0;		//�ϳ���ת�ٱ궨���������ʾ������������Ϊ�궨��ʼ����
UINT8 VarEngineSpeedSetCommand=0;		//ת�ٱ궨��ʼ����
UINT8 VarEngineSpeedSetState=0;			//ת�ٱ궨״̬��1-�궨��
UINT8 VarEngineSpeedSetGradeTarget=0;	//ת��Ŀ��궨��λ
UINT16 VarEngineSpeedSet[11]=
{
	1000,1200,1350,1600,1800,1890,1980,2080,2150,2200,2250
};										//����λ�趨�ı궨ת��
UINT8 VarSetAutoMotorPosiOk=0;			//�궨��������,1-�궨����
UINT16 VarEngineSpeedNow=0;				//��������ǰת��
UINT16 VarEngineSpeedTarget=0;			//������Ŀ��ת�٣�����ת�ٱ궨
UINT8 VanEngineTimeSetPSDSendFlag=0;		//����������Сʱ�������뷢�����������ʾ��
UINT8 VanEngineTimeSetPSDoKFlag=0;		//����������Сʱ��������Դ�����1-������ȷ��0-�������
//CAN
UINT8 VarCanAccDialPosiMinSet=0;		//������С��λ�궨���������ʾ��
UINT8 VarCanAccDialPosiMaxSet=0;		//�������λ�궨���������ʾ��
UINT8 VarMoveTimes=0;					//���΢������

//AIת��Ϊ��������ر�������
UINT8 VarFuelComputeNum=1;				//�����������ƽ���Ļ���
UINT16 VarFuelCompute[100]=
{
	0
};										//����������ʷֵ
UINT8 VarFuelVolume=40;					//ȼ������δ�˲�
UINT8 VarFuelLackAlarm=0;				//ȼ�͵ͱ���
UINT8 VarFuelSensorError=0;				//ȼ����λ����������
UINT8 VarWaterComputeNum=0;				//ˮ�¼������ƽ���Ļ���
UINT16 VarWaterCompute[100]=
{
	0
};										//ˮ�²�����ʷֵ
UINT8 VarWaterTemp=0;					//ˮ���¶�ֵ��δ�˲�
UINT8 VarCanWaterHihgAlarm=0;			//ˮ�¸߱���
UINT8 VarWaterTempSensorError=0;		//ˮ�´���������
UINT8 VarP1PressureSensorEorror=0;		//��1ѹ������������
UINT16 VarP1PressureArray[20]=
{
	0
};										//��1ѹ�������˲�����
UINT16 VarP1Pressure=0;					//��1ѹ����δ�˲�����λbar
UINT8 VarP2PressureSensorEorror=0;		//��2����������
UINT8 VarPiPressureSensorEorror=0;      //�ȵ���ѹ������������
UINT16 VarPiPressureArray[20]=
{
	0
};
UINT16 VarP2PressureArray[20]=
{
	0
};
UINT16 VarP2Pressure=0;					//��2ѹ����δ�˲�����λbar
//UINT16 VarPiPressure=0;                 //�ȵ���ѹ����δ�˲�����λbar
UINT16 VarSysAveragePress=0;			//ϵͳƽ��ѹ������λbar
UINT16 VarP2PressureFilter=0;			//��2ѹ�������˲�����λbar
UINT16 VarP1PressureFilter=0;			//��1ѹ�������˲�����λbar	
UINT16 VarPiPressureFilter=0;			//�ȵ�ѹ�������˲�����λbar
UINT8 VarDialSensorError=0;				//���ű��̷�������
UINT8 VarAccMotorSensorError=0;			//�����������
UINT8 VarFuelVolumeFilter=0;			//ȼ�����������˲�
UINT16 VarValveErrorTime1S=0;			//��ŷ������ۻ�ʱ�䣬S
UINT8 VarEngineSpeedSensorError=0;		//ת�ٴ���������
UINT8 VarEngineWorkErrorTime1S=0;       //����ѹ�����ۻ�ʱ�䣬������������ʼ��ʱ
//*******
BOOL VarCanAutoIdleEnable = TRUE;		//�Զ�����ʹ��
UINT16 VarCanP1PressureIdleLimit=50;	//�Զ����ٿ���ѹ��
UINT16 VarCanP2PressureIdleLimit=50;	//�Զ����ٿ���ѹ��
BOOL VarstartIdle = TRUE;				//�Զ����ٿ�ʼ��־����TURE-�����Զ�����
UINT8 VarIdleState=0;					//����״̬��1-������
BOOL VarCurrentIdleDelay = FALSE;		//�ñ�����������ʱ������TURE-Ӧ��ʱ����ʱ������Ϊ0
UINT32 VarIdleTimer=0;					//�Զ�����״̬�жϼ�ʱ��
//****
BOOL VarCanHighSpeedTravel=FALSE;		//���߸���ʹ�ܣ�������ʾ����TURE-���߸���ʹ��
//***
UINT8 VarCanSysHSLBKRMode=2;			 //����ģʽ�л���H-S-L-B-K-R
UINT8 VarHydHammerFlow=0;                //Һѹ������ֵ
UINT8 VarHydSicissorsFlow=0;             //Һѹ������ֵ
UINT8 VarHydRamFlow=0;                   //Һѹ������ֵ
UINT16 VarProValveCurrentTarget=0;       //Һѹ���߷�Ŀ�����ֵ
UINT8 VarPumpPowerParameter[8];          //Һѹ�ù��ʵ�
//****
UINT8 VarSpeedLevel=0;					//������ת�ٵ�λ
BOOL VarEngineStartState;				//��������ʼ�ϵ�״̬���ϵ�ǰ5s-TURE
BOOL VarEngineWarmState=FALSE;			//������ů��״̬��TURE-ů����
BOOL VarEngineCoolState=FALSE;			//���������״̬��TURE-�����
BOOL VarSysSleepCommand=FALSE;			//ϵͳ��������
BOOL VarEngineWarmDone = FALSE;			//������ů��ִ�У���;��ʹ��������һ��������ֻů��һ��
UINT32 VarEngineWarmStartTime=0;		//������ů��ʱ����Ƽ�ʱ��
UINT16 VarValveCurrent[11];				//����λ���趨�ıù��������
UINT16 VarValveCurrentTarget=0;			//ʵ�ʹ����еı�ʵ��Ŀ�����
UINT32 TempCurrentTarget=0;				//��Ŀ����������м����������ѹ��ֵ�趨
UINT16 CurrentOffset=0;					//��Ŀ����������м����������ת�ٱ仯����
UINT8 VarCurrentLevel=0;				//�õ�����λ
UINT16 VarValvePwRatio=0;				//�����������У�PWM�ߵ�ƽ��
UINT16 VarValveCurrentNow=0;			//Һѹ�õ�ŷ���ǰ����
UINT16 VarAssValveCurrentNow=0;          //�����������ڵ�ŷ���ǰ����
UINT8 VarValveRatioKp=0;				//������PID�����е�Kp����
UINT8 VarValveRatioKi=0;				//������PID�����е�Ki����
UINT8 VarValveRatioKd=0;				//������PID�����е�Kd����
INT32 x[3]=
{
	0
};										//������PID�����еñ�����΢�֣�������
float D_Output=0;						//������PID����õ���PWM�ߵ�ƽ��
float D_Last=0;							//����ʽPID���õ��������Ƴ�����δ��
INT32 PID_Error_1=0;					//Ŀ�������ʵ�ʵ����ƵĲ�
INT16 PID_Error_2=0;					//ƫ����ۼ�
UINT8 VarValveError=0;					//��ŷ�����			
UINT8 VarCanEngineTimeSetFlag;			//����������ʱ����������ͱ�־��
UINT8 VarCanEngineTimeSetPSDoK=0;		//����������ʱ����������Դ��жϣ�1-������ȷ��0-�������
UINT32 VarCanEngineTimeSetPSD;			//����������ʱ����������
UINT16 VarCanEngineTimeSetHour;			//���õķ���������ʱ��
UINT8 VarExcavatorEngineType=0;          //���緢����:0-����˹��1-��ʮ�壬2-Ϋ��
//****************GPS������ز���***********************
UINT8 VarGpsLockState_A=0;			//Gps��A����״̬
UINT8 VarCanGpsLockCommand_A=0;		//GPS��A��������
UINT8 VarCanGpsCancel=0;			//GPS����ȡ�����1-ȡ������
BOOL VarGpsLockWork_A=FALSE;		//GPS��A������ִ�������жϱ�����ʹ�ھ����A������ȵ��´�������ִ������
UINT8 VarGpslockState_B=0;			//Gps��B����״̬
UINT8 VarCanGpsLockCommand_B=0;		//GPS��B��������
BOOL VarGpsLockWork_B=FALSE;		//GPS��B������ִ�������жϱ�����ʹ�ھ����A������ȵ��´�������ִ������
UINT8 VarGpslockState_C=0;			//Gps��C����״̬
UINT8 VarCanGpsLockCommand_C=0;		//GPS��C��������
BOOL VarGpsLockWork_C=FALSE;		//GPS��C������ִ�������жϱ�����ʹ�ھ����A������ȵ��´�������ִ������
UINT8 VarGpslockState_D=0;			//Gps��D����״̬
UINT8 VarCanGpsLockCommand_D=0;		//GPS��D��������
UINT8 VarGpsLockWork_D=0;			//GPS��D������ִ�������жϱ�����ʹ�ھ����A������ȵ��´�������ִ������
UINT8 VarCanGpsHeartBeatLast=0;		//�ϳ�������GPS����״̬
UINT8 VarCanGpsHeartBeat=0;			//����������GPS����״̬
UINT8 VarGpsCanNoBeat=0;			//GPS10s������
UINT8 VarGpsCanErrorState=0;		//CAN���߹���״̬�ж���
BOOL VarGpsCanBusError=FALSE;		//GPS��CAN���߹���,10S��ͨѶ
UINT8 VarCanBusLockCommand=0;		//GPS���������ͨѶ��������
UINT8 VarCanBusLockState=0;			//CANͨѶ��������״̬
UINT8 VarCan2MonthLockCommand=0;	//GPS2�����ź���������
UINT8 VarCan2MonthLockState=0;		//GPS2�����ź�����״̬
UINT8 VarCanAntennaCut=0;			//GPS���߼����ж���
UINT8 VarCanAntennaCutLockState=0;	//GPS���߼�������״̬
UINT8 VarCanAntennaCutLockCommand=0;//GPS���߼�����������
UINT8 VarCanUncoverLockCommand=0;	//GPS�Ҹ���������
UINT8 VarCanUncoverLockState;		//GPS�Ҹ�����״̬
BOOL VarGpsLockEnginePower;			//GPS����������������
BOOL VarGpsLockPumpPower;			//GPS������Һѹ�ù���
UINT8 VarGpsSIMCardError;           //GPS�豸��SIM������
UINT8 VarCanSendGps1F1[8];
UINT8 VarCanSendGps1F2[8];
UINT8 VarCanSendGps1F3[8];
UINT8 VarCanSendGps1F4[8];
UINT8 VarCanSendGps1F5[8];
UINT8 VarCanSendGps1F6[8];
UINT8 VarCanSendGps1F7[8];
UINT8 VarCanSendGps1FC[8];
UINT8 VarCanSendGps1FD[8];
UINT32 VarCanGpsUnlockPSD;			//GPS2��������������
UINT8 VarCanSendGpsStep;			//���ڷ���CAN���ݵ�GPS
UINT8 VarCanGpsRx1EF[8];
UINT8 VarCanGpsRx1FB[8];
UINT8 VarCanGpsRx1EE[8];
UINT8 VarCanGpsTemper;				//GPS�¶�
UINT32 VarGpsAntennaCut_Et=0;		//���߼�������ʱ��
UINT32 VarGpsCanBusError_Et=0;		//CAN�����ѹ���ʱ��
UINT8 VarCanGpsSendUnlockPSDFlag=0;	//����Gps���������־��
BOOL VarCan2MonthLockCancel=0;		//GPS2������ȡ��
//******************FLASH********************
UINT8 VarFlashSysDateMasterNeedSaveFlag = 0;//���洢��ϵͳ������Ҫ�����־λ
UINT8 VarFlashSysDateBackupNeedSaveFlag = 0;//���ݴ洢��ϵͳ������Ҫ�����־λ
UINT16 VarSysDataMasterCheckFlag;			//���洢��ϵͳ��������У�����ݣ�����һ�μ�1
UINT16 VarSysDataBackupCheckFlag;			//���ݴ洢��ϵͳ��������У�����ݣ�����һ�μ�1
UINT8 VarFlashGpsDataMasterNeedSaveFlag=0;	//���洢��GPS������Ҫ�����־λ
UINT8 VarFlashGpsDataBackupNeedSaveFlag=0;	//���ݴ洢��GPS������Ҫ�����־λ
UINT16 VarGpsDataMasterCheckFlag;			//���洢��GPS��������У�����ݣ�����һ�μ�1
UINT16 VarGpsDataBackupCheckFlag;			//���ݴ洢��GPS��������У�����ݣ�����һ�μ�1
UINT32 VarCanGpsCacelPSD=0;					//Gpsȡ������
UINT32 VarCanGpsUrgencyPSD=0;				//Gps������������
UINT8 VarCanGpsUrgencyCommand=0;			//Gps������������
UINT8 VarCanGpsUrgencyPSDoK=0;				//Gps�������������жϣ�1-������ȷ��0-�������
UINT8 VarCanGpsUrgencyState;				//GPS��������״̬��1-����������
//*******����Сʱ��*******
UINT16 VarEngineWorkTime1S;					//����������ʱ��Second
UINT32 VarEngineWorkTime1H;					//����������ʱ��Hour
UINT32 VarEngineWorkTime_Gps;				//Gps��������ʱ����������Сʱ
UINT16 VarEngineWorkTime1M;					//����������ʱ��Min					
UINT8 VarFlashEngineWorkTimeMasterNeedSaveFlag;//���洢������������ʱ�������Ҫ�����־λ
UINT8 VarFlashEngineWorkTimeBackupNeedSaveFlag;//���ݴ洢������������ʱ�������Ҫ�����־λ
UINT8 VarEngineStarted;							//��������������1-��������0-������
UINT16 VarEngineTimeMasterCheckFlag;			//���洢������������ʱ���������У�����ݣ�����һ�μ�1
UINT16 VarEngineTimeBackupCheckFlag;			//���ݴ洢������������ʱ���������У�����ݣ�����һ�μ�1
UINT16 VarFlashEngineTimeMasterAdr;				//����������Сʱ�������洢��ַ
UINT8 VarFlashEngineWorkTimeMasterNeedSaveFlagIndex;//����������Сʱ�������洢����ַ�ı��豣���־��
UINT16 VarFlashEngineTimeBackupAdr;					//����������Сʱ���汸�ݴ洢��ַ
UINT8 VarFlashEngineWorkTimeBackupNeedSaveFlagIndex;//����������Сʱ���汸�ݴ洢����ַ�ı��豣���־��
UINT16 VarEngineTimeMasterCheckFlagIndex;			//���洢������������ʱ���ַ��������У�����ݣ�����һ�μ�1
UINT16 VarEngineTimeBackupCheckFlagIndex;			//���ݴ洢������������ʱ���ַ��������У�����ݣ�����һ�μ�1
UINT8 VarFlashHourNeedSaveMainFlag=0;					//���洢������������ʱ���豣���־��
UINT16 VarFlashHourMainAdrCheckFlag=0;				//���ݴ洢������������ʱ���豣���־��
//********8
UINT8 VarCanMonitorNeedBellAlarm;					//��ʾ�������ź�
UINT16 VarCanExcavatorType;							//�ھ���ͺ�
UINT16 VarCanExcavatorId;							//�ھ������
UINT8 VarCanAlarmNoVoiceFlag;						//����
UINT32 VarMonitorPassword;							//��ʾ����̬����





UINT16 VarPbPressure;
UINT16 VarPbPressureArray[20];

//*******************���緢�������ϴ������****************************
UINT8 VarCanEngineNoDataFlag=0;
UINT8 VarCanEcmNoDataFlag=0;
UINT8 VarIsuzuFaultCodeSingle = 0;
UINT8 VarIsuzuFaultCodeMany = 0;
UINT32 VarIsuzuSPN[100]=
{
	0
};
UINT8 VarIsuzuFMI[100]=
{
	0
};
UINT16 VarIsuzuCodeNumber=0;
UINT8 VarIsuzuFault[100][8]=
{
	0
};
UINT8 VarIszuFaultSPNNumber=0;
UINT8 VarCanInFuelFilterAlarm=0;
UINT8 VarCanInOilPreLowAlarm=0;
UINT8 VarCanInPreBoostAlarm=0;
UINT8 VarCanInFuelTemAlarm=0;
UINT8 VarCanInWaterTempAlarm=0;
UINT8 VarCanInStopUrgency=0;
UINT8 VarCanInFeicheAlarm=0;
UINT8 VarCanInPreheat=0;

//Uart
//����ͨѶ��ر���
UINT8 VarUartDataSendFlag=0;
UINT8 LibSciReadData[100];
//**********8test************
UINT16 VarUartFaultCode;
UINT16 VarEngineFaultCode2;
UINT16 VarEngineFaultCode3;
UINT16 VarEngineFaultCode4;
UINT16 VarEngineFaultCode5;
UINT16 VarEngineFaultCode6;

UINT16 VarP1PressureFilterHistory[6]=
{
	0,0,0,0,0,0
};
BOOL  VarP1PressureUpFlag=FALSE;

UINT16 VarP2PressureFilterHistory[6]=
{
	0,0,0,0,0,0
};
BOOL  VarP2PressureUpFlag=FALSE;

UINT32 VarCANIsuzuTime[3]={0,0,0};



UINT8 VarPAccumAirSensorError=0;
UINT8 VarValveDT1Error=0;
UINT8 VarValveDT2Error=0;
UINT16 VarPAccumAirPressureBar=0;


UINT8 VarSendDataID_0x0CF00330[8];
UINT8 VarSendDataID_0x18FDCB30[8];

UINT16 TempPressBigger;

UINT16 VarLoadMiddleStateTimer10Ms;
UINT16 VarLoadHeavyStateTimer10Ms;
UINT16 VarTempCureentTargetValue;
UINT16 VarSpeedLowTimer10Ms;
float VarTempCurrentTarget2;
float VarCurrentAddValue;
UINT8 VarCurrentReduceValue;


UINT8 VarDiFastReversingSw;
UINT8 VarHydraulicOilComputeNum=0;		//Һѹ���¼������ƽ���Ļ���
UINT8 VarHydraulicOilTemp=0;			//Һѹ���²�����ʷֵ
UINT16 VarHydraulicOilCompute[100]=
{
	0
};
UINT8 VarHydraulicOilTempFilter=0;
UINT8 VarHydraulicOilHighAlarmLimit=0;
UINT8 VarHydraulicOilHihgAlarm=0;
UINT8 VarHydraulicOilTempSensorError=0;

UINT8 VarDoHydraulicCoolingPositiveValve;
UINT8 VarDoHydraulicCoolingReverseValve;

UINT16 VarAiHydraulicTemp;     //Һѹ���� ���裬0.1R
UINT16 VarProHydraulicFANValveCurrentTarget;

UINT16 VarHydraulicCoolingPumpValveCurrent;//Һѹ��ȴ�õ�ǰ����

UINT8 VarHydraulicFanBool=0;
UINT8 VarCanAccHydraulicCoolingFWD;
UINT16 VarFANCurrent[11]; 

UINT8 VarDiStop=0;
UINT8 VarDoBuzzerAlarm=0;
UINT8    VarDoAirFilterPump;
UINT8     VarDoFuelFilterPump;
UINT8    VarAirFilterPump_Enable;
UINT8    VarFuelFilterPump_Enable;

 //PIDparams StructPwmDT1;
 //PIDparams StructPwmDT2;
 PIDparams StructPwmDT3;
 PIDparams StructPwmDT4;
 PIDparams StructPwmDT5;
// UINT16 VarDt1PwRatio;
// UINT16 VarDt2PwRatio;
 UINT16 VarDt3PwRatio;
 UINT16 VarDt4PwRatio;
 UINT16 VarDt5PwRatio;
 
 UINT8 VarCanSysHSLMode;			 
 UINT8 VarCanSysBKRMode;
 UINT8 VarSendDataID_0x18EA0028[8];
 UINT8 VarRecDataID_0x18FEB300[8];
 
 UINT16 VarLoadFreeStateTimer10Ms;
 UINT16 VarLowEngineAirPressureBar=145;
 UINT8 VarLowEnginePressureFlag=0;
 UINT32 VarEngineFuelYouHao;
 UINT32 VarEngineSpeedWorkTome;
 UINT16 VarResCompensation;
 UINT8 VarMode1ChangeFlag=0;


 UINT8 VarCanPumpMode=0;//H+ģʽ��������ת��Ϊ�õĶת��
 UINT8 VarCanEngineMode=0;//Eģʽ��������ת��Ϊ�������Ķת��
 UINT8 VarValveCurrentTargetoffset;
 UINT16 VarHydraulicOilTempCount; //Һѹ�͸���ʱ�����

 FLOAT32 VarEngineFuelYouHaoInt;
 FLOAT32 VarEngineSpeedWorkTomeInt;
 UINT32 VarEngineSpeedWorkTomeEnd;
 UINT16 VarEngineSpeedWorkTomeTime;
 UINT32 VarEngineFuelYouHaoEnd;
 UINT32 VarYouHaoInit = 41065;//40804
 UINT32 VarWorkTimeInt = 11278;//11215
 FLOAT64 VarTemp1;
 FLOAT32 VarSub1;
 UINT16 VarEngineInstantFuelYouHao;//������˲ʱ�ͺ�
 FLOAT32 VarEngineSpeedWorkTome1;
 FLOAT32 VarEngineFuelYouHao1;
 FLOAT32 VarEngineFuelYouHaoTemp;
 FLOAT32 VarEngineSpeedWorkTomeTemp;
 
 
 UINT8 VarSendDataID200[8];
 UINT8 VarSendDataID201[8];
 UINT8 VarSendDataID203[8];
 UINT8 VarSendDataID209[8];
 UINT8 VarSendDataID20A[8];
 UINT8 VarSendDataID20C[8];
 UINT8 VarSendDataID20D[8];
 UINT8 VarSendDataID20E[8];
 UINT8 VarSendDataID20F[8];
 UINT8 VarSendDataID210[8];
 UINT8 VarSendDataID211[8];
 UINT8 VarSendDataID212[8];
 UINT8 VarSendDataID215[8];
 UINT8 VarSendDataID216[8];
 UINT8 VarSendDataID217[8];
 UINT8 VarSendDataID218[8];
 UINT8 VarSendDataID220[8];
 UINT8 VarSendDataID221[8];
 UINT8 VarSendDataID222[8];
 UINT8 VarSendDataID224[8];
 UINT8 VarSendDataID227[8];
 UINT8 VarSendDataID22F[8];
 UINT8 VarSendDataID231[8];
 UINT8 VarSendDataID233[8];
 UINT8 VarSendDataID21E[8];
 UINT8 VarSendDataID216[8];
 UINT8 VarSendDataID218[8];
 UINT8 VarSendDataID2E1[8];
 UINT8 VarSendDataID2F0[8];
 UINT8 VarSendDataID2F1[8];
 
 //����������GPS
 UINT8 VarRecDataID300[8];
 UINT8 VarRecDataID303[8];
 UINT8 VarRecDataID321[8];
 UINT8 VarRecDataID322[8];
 UINT8 VarRecDataID323[8];
 
 //������������ʾ��
 UINT8 VarRecDataID101[8];
 UINT8 VarRecDataID102[8];
 UINT8 VarRecDataID106[8];
 UINT8 VarRecDataID107[8];
 UINT8 VarRecDataID110[8];
 UINT8 VarRecDataID111[8];
 UINT8 VarRecDataID112[8];
 UINT8 VarRecDataID115[8];
 
 UINT16 GPSStateByte;	//
 UINT8 SimCardLostAlarm;	//�ο�����
 BOOL GPSPlatformConnetState;	//GPS��ƽ̨����״̬��0-�쳣��1-����
 BOOL GPSPlatformConnetState_Last=0;
 
 UINT8 VarAutoIdleSpeedGrade=1;
 UINT8 VarManualIdleSpeedGrade=1;
 UINT8 EscapeModeButton;
 BOOL b_115=0;
 BOOL PumpPowerParaSend;		//�ù��ʷ��ͱ�־λ
 UINT16 SignalNumber_115;//0x115��Ϣ���
 UINT8 OderType_115=0;//�������ͣ�x1:��̬����x2:���뷢�ͣ�1x:���źţ�2x:���ý�����3x:��������
 UINT32 GPSUnlockPSD=0;
 UINT16 SignalNumber_2E1;//0x2E1��Ϣ���
 UINT8 GPSLock_All_Enable=1;		//������ʹ��,1-���ã�0-ͣ��
 UINT8 GPSLock_Passive_Enable=1;	//����������ʹ��,1-���ã�0-ͣ��
 UINT8 MonthNoSignalLock_Enable=1;	//ä������ʹ��,1-���ã�0-ͣ��
 UINT8 UncoverLock_Enable=1;		//�������ʹ��,1-���ã�0-ͣ��
 UINT8 CANSignalLostLock_Enable=1;	//��������ʹ��,1-���ã�0-ͣ��
 UINT8 SIMCardLostLock_Enable=1;	//�ο�����ʹ��,1-���ã�0-ͣ��
 
 UINT16 VarAftertreatmentDOCIntakeTemp;//����β���¶�(DOCǰ)
 UINT16 VarAftertreatmentDOCOutletTemp;//����β���¶�(DOC��)
 UINT8 VarIntakeManifoldTemp; //����������¶�
 UINT8 VarInterCoolInletTemp; //����������¶�
 UINT16 VarCommonRailPressure; //����ѹ��
 UINT16 VarAftertreatmentDPFDifferentialPressure;//DPFβ��ѹ��UINT8 
 UINT8 VarDPFRegenerationStatus;//DPF����״̬
 UINT8 VarDPFTripStatus;
 UINT8 VarDPFPMAccumulationStatus;//DPF PM�ѻ�״̬
 UINT16 VarDPFModeL;//DPFģʽ
 UINT8 VarModeSelectionError;
 UINT8 VarDoManualRegenrationLoad; //�ֶ������������ص�ŷ�
 UINT8 VarManualRegenerationButton;		// 11-�ֶ���������
 UINT8 VarRegenerationInhibitButton; 	// 12-������ֹ
 BOOL VarCanGpsUnlockPSDOK;	//GPS2��������������״̬
 UINT16 VarBKRFlowNowCurrent=0;//�����������ڵ�ŷ���ǰ����
 UINT8 VarGpsLockState_B=0;			//Gps��B����״̬
 UINT8 VarGpsLockState_C=0;			//Gps��C����״̬
 UINT8 VarGpsLockState_D=0;			//Gps��D����״̬
 UINT8 GPSUnLockStep=0;
 UINT16 SignalNumber_2F1;//0x2F1��Ϣ���
 UINT32 DynamicCode_H=0;
 UINT32 DynamicCode_L=0;
 UINT8 OderType_2F1=0;//�������ͣ�x1:��̬����x2:���뷢�ͣ�1x:���źţ�2x:���ý�����3x:��������
 UINT8 GPSPSDVerify; 
 
 /****GPSLock***/
 BOOL TimeAvailable_1=0;
 UINT8 TimeAvailable;	//ʱ����Чλ
 UINT8 NoSignalStart_Year=0;	//���źſ�ʼʱ�䣬��
 UINT8 NoSignalStart_Month=0;//���źſ�ʼʱ�䣬��
 UINT8 NoSignalStart_Day=0;	//���źſ�ʼʱ�䣬��
 UINT8 NoSignalTotal_Day=0;	//���ź���ʱ�䣬��
 UINT8 EmergencyStart_Year=0;//����������ʼʱ�䣬��
 UINT8 EmergencyStart_Month=0;//����������ʼʱ�䣬��
 UINT8 EmergencyStart_Day=0;	//����������ʼʱ�䣬��
 UINT8 EmergencyStart_Hour=0;//����������ʼʱ�䣬ʱ
 UINT8 EmergencyUnlock_Hour=0;//����������ʱ��
 
 UINT8 VarRecDataID_0x18FFF900[8];
 UINT8 VarRecDataID0x18FEB100[8];
 UINT8 VarRecDataID0x18FEE900[8];
 UINT8 VarRecDataID_0x18FED900[8];
 UINT8 VarAutoRegenerationLamp=0;//�Զ�������(�̵Ƴ���)
 UINT8 VarRecDataID_0x18FFF800[8];
 UINT8 VarManualRegenerationLamp=0;//�ֶ�������:1-�ȵƳ���;2-�ȵ�����;3-�ȵƿ���;
 UINT8 VarDoManualRegenrationLoadEnabled; //�ֶ������������ص�ŷ�ʹ��
 UINT8 VarRecDataID_0x18FF0300[8];
 UINT8 GPSLock_Enable_Initial;
 UINT16 BreakHammerFrequencyTimes;
 UINT8 VarCanGpsLockCommandLast_A=0;	
 UINT8 VarCanGpsLockCommandLast_B=0;
 UINT8 VarCanGpsLockCommandLast_C=0;	
 UINT8 VarCanGpsLockCommandLast_D=0;
 UINT8 ClockTime_Year;	//ʱ��ʱ�䣬��
 UINT8 ClockTime_Month;	//ʱ��ʱ�䣬��
 UINT8 ClockTime_Day;	//ʱ��ʱ�䣬��
 UINT8 ClockTime_Hour;	//ʱ��ʱ�䣬ʱ
 BOOL TimeCompare_1=0;
 UINT16 OderType_115_Last=0;
 UINT16 SignalNumber_115_Last=0;
 UINT32 GPSUnlockPSD_Last=0;
 UINT32 PSD=0;
 BOOL b_48Test=0;
 UINT8 VarEngineStop=0;//������ͣ���ź�(����B)
 UINT8 flag=0;
 
