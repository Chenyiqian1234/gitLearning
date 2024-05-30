#define DefineMcuAdcVref              3000
#define DefineAiResPullUpVoltageMv    5000
#define DefineHardwareNewVersion      1
#define DefineHardwareSWE75           0

extern UINT32 LibVarTimer1MS;
extern UINT32 LibVarTimerB2Count;

extern UINT8 CAN0MB14Mode;	//14∫≈” œ‰1±Í◊º÷°0¿©’π÷°
extern UINT32 CAN0MB14ID;	//14∫≈” œ‰ID
extern UINT32 CAN0MB14IDMask;//14∫≈” œ‰ID—⁄¬Î
extern UINT8 CAN1MB14Mode;	//14∫≈” œ‰1±Í◊º÷°0¿©’π÷°
extern UINT32 CAN1MB14ID;	//14∫≈” œ‰ID
extern UINT32 CAN1MB14IDMask;//14∫≈” œ‰ID—⁄¬Î
extern UINT8 LibVarCan0BufferMode[38];
extern UINT32 LibVarCan0ReceiveTargetID[38];
extern UINT8 LibVarCan0ReceiveFlag[38];
extern UINT8 LibVarCan0ReceiveData[38][8];
extern UINT8 LibVarCan0ReceiveLength[38];
extern UINT16 LibVarCan0ErrorCount;
extern UINT8 LibVarCan0NeedInit;
extern UINT16 LibVarCan0NoIntTimer1Ms;
extern UINT16 LibVarCan0InitCount;

extern UINT8 LibVarCan1BufferMode[38];
extern UINT32 LibVarCan1ReceiveTargetID[38];
extern UINT8 LibVarCan1ReceiveFlag[38];
extern UINT8 LibVarCan1ReceiveData[38][8];
extern UINT8 LibVarCan1ReceiveLength[38];
extern UINT16 LibVarCan1ErrorCount;
extern UINT8 LibVarCan1NeedInit;
extern UINT16 LibVarCan1NoIntTimer1Ms;
extern UINT16 LibVarCan1InitCount;

extern UINT16 LibVarCan0IMaskInit;
extern UINT16 LibVarCan1IMaskInit;

extern UINT8 LibVarPinoutsSelect[80]; 

extern UINT8 LibVar74HC595U4001;
extern UINT8 LibVar74HC595U4002;
extern UINT8 LibVar74HC595U4003;
extern UINT8 LibVar74HC595U4004;
extern UINT8 LibVar74HC595U4005;
extern UINT8 LibVar74HC165U6004;
extern UINT8 LibVar74HC165U6005;
extern UINT8 LibVar74HC165U6011;
extern UINT8 LibVar74HC165U6012;

extern UINT8 LibVarSetValueDOL[4]; 
extern UINT8 LibVarSetValueDOH[28];

extern UINT8 LibVarSciSendData[512];
extern UINT16 LibVarSciSendDataLength; 
extern UINT16 LibVarSciSendDataPosi; 
extern UINT16 LibVarSciRecDataLength;
extern UINT8 LibVarSciRecData[256];
extern UINT16 LibVarSciRecDataNextSavePosi;
extern UINT8 LibVarSciTranEmptyTimer1MS;
extern UINT8 LibVarSciStartEchoCount;
extern UINT32 LibVarSciStartEchoLastTime1MS;

extern UINT8 LibVarPiOverFlow[4];
extern UINT8 LibVarPiSampleSingle10MS;
extern UINT16 LibVarPiSampleTimeMS[4];
extern UINT16 LibVarPiOrgData[4][100];
extern UINT16 LibVarPiFrequency[4];
extern UINT8 LibVarPiUpdateFlag;

extern UINT16 LibVarMcuAdcOrgData[16];
extern UINT8 LibVarMcuAdcaNoIntTimer1MS;
extern UINT8 LibVarMcuAdcbNoIntTimer1MS;

extern UINT8 LibVarSpi1CommandStep;
extern UINT16 LibVarSpi1RecData;
extern UINT16 LibVarPWMCurrentADC[12][100];
extern UINT8 LibVarSpi1StoptimerMS;
extern UINT8 LibVarPWMCurrentFilerNum[12];

extern UINT8 LibVarMotorDirLast;

extern UINT32 LibVarTimer[40];
extern UINT8 LivVarTimeTriggerLast[40];
extern UINT8 LibVarTimeSignalLast[40];
extern UINT8 LibVarTimeEdgeStart[40];

extern UINT32 LibVarTonEt[32];
extern UINT32 LibVarTonEnable;
extern UINT32 LibVarTofEt[32];
extern UINT32 LibVarTofEnable;

extern UINT8 LibVarQDA1[2];
extern UINT8 LibVarQDB1[2];
extern UINT32 LibVarQD1Position;

extern UINT8 LibVarQDA0[2];
extern UINT8 LibVarQDB0[2];
extern UINT32 LibVarQD0Position;

/* *************************************************************** 
** File End
** ************************************************************ */
