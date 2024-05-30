UINT32 LibVarTimer1MS=0;
UINT32 LibVarTimerB2Count=0;

UINT8 CAN0MB14Mode;	//14������1��׼֡0��չ֡
UINT32 CAN0MB14ID;	//14������ID
UINT32 CAN0MB14IDMask;//14������ID����
UINT8 LibVarCan0BufferMode[38];      // =0����ģʽ =1���ձ�׼֡ģʽ =2������չ֡ģʽ
UINT32 LibVarCan0ReceiveTargetID[38]; //����Ϊ����ģʽʱ��ID��
UINT8 LibVarCan0ReceiveFlag[38];
UINT8 LibVarCan0ReceiveData[38][8];
UINT8 LibVarCan0ReceiveLength[38];
UINT16 LibVarCan0ErrorCount=0;
UINT8 LibVarCan0NeedInit=0;
UINT16 LibVarCan0NoIntTimer1Ms=0;
UINT16 LibVarCan0InitCount=0;

UINT8 CAN1MB14Mode;	//14������1��׼֡0��չ֡
UINT32 CAN1MB14ID;	//14������ID
UINT32 CAN1MB14IDMask;//14������ID����
UINT8 LibVarCan1BufferMode[38];      // =0����ģʽ =1���ձ�׼֡ģʽ =2������չ֡ģʽ
UINT32 LibVarCan1ReceiveTargetID[38];
UINT8 LibVarCan1ReceiveFlag[38];
UINT8 LibVarCan1ReceiveData[38][8];
UINT8 LibVarCan1ReceiveLength[38];
UINT16 LibVarCan1ErrorCount=0;
UINT8 LibVarCan1NeedInit=0;
UINT16 LibVarCan1NoIntTimer1Ms=0;
UINT16 LibVarCan1InitCount=0;

UINT16 LibVarCan0IMaskInit;
UINT16 LibVarCan1IMaskInit;

UINT8 LibVarPinoutsSelect[80];   //�ܽŹ���ѡ��

UINT8 LibVar74HC595U4001=0;      // 74HC595,U4001�������
UINT8 LibVar74HC595U4002=0;      // 74HC595,U4002�������
UINT8 LibVar74HC595U4003=0;      // 74HC595,U4003�������
UINT8 LibVar74HC595U4004=0;      // 74HC595,U4004�������
UINT8 LibVar74HC595U4005=0;      // 74HC595,U4005�������

UINT8 LibVar74HC165U6004=0;      // 74HC165,U6004��������
UINT8 LibVar74HC165U6005=0;      // 74HC165,U6004��������
UINT8 LibVar74HC165U6011=0;      // 74HC165,U6011��������
UINT8 LibVar74HC165U6012=0;      // 74HC165,U6012��������

UINT8 LibVarSetValueDOL[4];      // DOL
UINT8 LibVarSetValueDOH[28];     // DOH

UINT8 LibVarSciSendData[512];      // ���ڷ������ݻ���
UINT16 LibVarSciSendDataLength=0;  // ���ڴ��������ݳ���
UINT16 LibVarSciSendDataPosi=0;    // ���ڴ���������λ��
UINT16 LibVarSciRecDataLength=0;
UINT8 LibVarSciRecData[256];
UINT16 LibVarSciRecDataNextSavePosi=0;
UINT8 LibVarSciTranEmptyTimer1MS=0;
UINT8 LibVarSciStartEchoCount=0;
UINT32 LibVarSciStartEchoLastTime1MS=0;

UINT8 LibVarPiOverFlow[4]=
{
	0,0,0,0
};                                       // PI���������־
UINT8 LibVarPiSampleSingle10MS=0;        // 
UINT16 LibVarPiSampleTimeMS[4]=
{
	500,500,500,500
};                                       // PI����ʱ��,��λms
UINT16 LibVarPiOrgData[4][100];    // PI����ԭʼֵ
UINT16 LibVarPiFrequency[4]=
{
	0,0,0,0
};                 
UINT8 LibVarPiUpdateFlag=0;      // PI���ݸ��±�־

UINT16 LibVarMcuAdcOrgData[16];    // MCU ADC����ֵ
UINT8 LibVarMcuAdcaNoIntTimer1MS=0;
UINT8 LibVarMcuAdcbNoIntTimer1MS=0;

UINT8 LibVarSpi1CommandStep=0;   // SPI1��ͨ���ɼ����� 0~11
UINT16 LibVarSpi1RecData;          // SPI1���յ�������
UINT16 LibVarPWMCurrentADC[12][100];// MCP3208���PWM����ADC����ֵ
UINT8 LibVarSpi1StoptimerMS=0;   // SPI1ֹͣ���м�ʱ
UINT8 LibVarPWMCurrentFilerNum[12]=
{
	10,10,10,10,10,10,10,10,10,10,10,10
};                                       // PWM���������˲���Ŀ

UINT8 LibVarMotorDirLast=0;

UINT32 LibVarTimer[40];
UINT8 LivVarTimeTriggerLast[40];
UINT8 LibVarTimeSignalLast[40];
UINT8 LibVarTimeEdgeStart[40];

UINT32 LibVarTonEt[32];
UINT32 LibVarTonEnable=0;
UINT32 LibVarTofEt[32];
UINT32 LibVarTofEnable=0;

UINT8 LibVarQDA1[2];
UINT8 LibVarQDB1[2];
UINT32 LibVarQD1Position=0;

UINT8 LibVarQDA0[2];
UINT8 LibVarQDB0[2];
UINT32 LibVarQD0Position=0;

/* *************************************************************** 
** File End
** ************************************************************ */
