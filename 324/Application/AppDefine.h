#ifndef _DefineVar
	#define _DefineVar
	
	#define UINT8   unsigned char
	#define UINT16  unsigned int
	#define UINT32  unsigned long
	#define INT8    signed char
	#define INT16   signed int
	#define INT32   signed long
	#define BOOL    unsigned char
	#define TRUE    1
	#define FALSE   0
	#define FLOAT32 float
	#define FLOAT64 double
	
#endif

#define DefExcavatorEngineType 2   //����������Ϊ���緢����
#define DefineHardwareVersion 23   //ɽ�ӿ�����2����1��IO�˿�����
#define DefineSoftVersion 238      //����汾��

#define VarSysParaDataSort_ID 0x0A01
#define VarGpsParaDataSort_ID 0x0A02
#define VarEngineWorkTimeDataSort_ID 0x0A03
#define VarEngineWorkTimeDataIndexSort_ID 0x0A04
#define VarEngineWorkTimeHourMainSort_ID 0x0A05
#define VarFlashEngineTimeMasterAdrDefault 0x1000	//����ʱ�����洢����Ĭ����ʼ��ַ
#define VarFlashEngineTimeMasterAdrMax 0x13F0		//����ʱ�����洢��������ŵ�ַ
#define VarFlashEngineTimeBackupAdrDefault 0x1400
#define VarFlashEngineTimeBackupAdrMax 0x17F0
#define VarFlashEngineTimeMasterAdrIndexDef 0x1800	//����ʱ������洢��ʼ��ַ�Ĵ�ŵ�ַ
#define VarFlashEngineTimeBackupAdrIndexDef 0x1C00  //����ʱ��ı��ݴ洢��ʼ��ַ�Ĵ�ŵ�ַ
#define VarFlashHourMainAdrDef 0x2000

#define VarFuelLowAlarmLimit 5
#define VarWaterHighAlarmLimit 102



//�ھ�ģʽ�µĵ�����ת��*****************
//���ʵ���,470S
#define DefineValveCurrentSet0 0
#define DefineValveCurrentSet1 0
#define DefineValveCurrentSet2 0//120
#define DefineValveCurrentSet3 450//240//120//240
#define DefineValveCurrentSet4 520//350//240//380
#define DefineValveCurrentSet5 650//550//650//450
#define DefineValveCurrentSet6 650//580//550//420
#define DefineValveCurrentSet7 650//600//580//600//500
#define DefineValveCurrentSet8 650//620//620//650//500
#define DefineValveCurrentSet9 620//650//620//650//620//650//500
#define DefineValveCurrentSet10 650//620//650//620//650//500

//�궨��Ŀ��ת��
#define DefineEngineSpeedSet0 900//1050
#define DefineEngineSpeedSet1 1150
#define DefineEngineSpeedSet2 1250
#define DefineEngineSpeedSet3 1350//1400
#define DefineEngineSpeedSet4 1400
#define DefineEngineSpeedSet5 1500//1560 //1550
#define DefineEngineSpeedSet6 1530//1600
#define DefineEngineSpeedSet7 1560//1650
#define DefineEngineSpeedSet8 1580//1570//1680//1700
#define DefineEngineSpeedSet9 1700//1580//1800//1850
#define DefineEngineSpeedSet10 1700//1850//1900


//����ɢ�ȷ��ȵ������趨ÿ��������ʹÿ����λ�µķ���ת����߲�����������ת�٣�ǰ���������ת������ȴ�㹻��ʹ���¡�ˮ�²������涨ֵ��
#define DefineFANCurrentSet0 450//370
#define DefineFANCurrentSet1 450//350
#define DefineFANCurrentSet2 450//340
#define DefineFANCurrentSet3 430//320
#define DefineFANCurrentSet4 400//300
#define DefineFANCurrentSet5 380//280
#define DefineFANCurrentSet6 370//280
#define DefineFANCurrentSet7 360//270
#define DefineFANCurrentSet8 355//260
#define DefineFANCurrentSet9 350//250
#define DefineFANCurrentSet10 350// 250
