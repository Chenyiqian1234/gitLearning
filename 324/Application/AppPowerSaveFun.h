#include "AppDefine.h"
//SWE330LC������Ŀ��Ӻ���
void FunPowerSaveControl(void);
void FunBoomTonClear();
UINT8 FunEnergySavingModeCheck();
void FunBoomEnergySavingMode_0(void);
void FunBoomEnergySavingMode_1(void);   
void FunBoomEnergySavingMode_2(void);  
void FunBoomEnergySavingMode_3(void);   
void FunBoomEnergySavingMode_4(void);   
void FunBoomEnergySavingMode_5(void); 
void FunBoomEnergySavingMode_6(void);   
void FunBoomEnergySavingMode_7(void);   
void FunBoomEnergySavingMode_8(void);  
void FunBoomEnergySavingMode_9(void); 
void FunBoomEnergySavingMode_10(void);
void FunBoomEnergySavingMode_12(void);
void FunPwmCompute(void);  //DT1��DT2 PWM ����
void FunRatatorPowerSave(void);
//ѹ���������źŴ���
UINT16 FunPressureCompute2(UINT16 VarAiCurrent);
UINT16 FunPressureCompute3(UINT16 VarAiCurrent);

void FunDefCurrentValue(void);

UINT8 FunXiKongEndJudge(void);
void FunPowerSaveIO(void);
void FunPowerSaveAiSample(void);//Ai����
void FunPowerSaveDoSet(void);   //��Do
void FunPowerSavePwmOutput(void);
void FunPowerSaveDiSample(void);
void FunChargeMaxPreCal(void);
void FunClearPIDparams(PIDparams *Params);
INT32 FunPID(INT32 MeasPoint,INT32 SetPoint,PIDparams *Params,INT32 Error,UINT32 Interval,BOOL Enable);
void FunUartSendPowerSaveDate(void);
void FunPowerSaveSpeedControl(void);//����ģʽ�·�����ת�ٿ���
void FunPowerSavePumpCurrentControl(void);//����ģʽ�±ù��ʿ���
void FunPowerSaveFault(void);//���������ϱ���
