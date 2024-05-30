#include "AppVar.h"
#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppPowerSaveFun.h"
#include "AppPowerSaveVar.h"

/* *************************************************************** 
** AppInit
** ************************************************************ */
void AppInit(void)
{
	//��Ŷ���
	//AI
	LibPinoutsSelect(4,0); //���ű��̣�AI_V
	LibPinoutsSelect(7,3); //ȼ �� ����AI_R
	LibPinoutsSelect(21,2);//��1 ѹ����AI_C
	LibPinoutsSelect(10,2);//��2 ѹ����AI_C
	LibPinoutsSelect(11,2);//��������ѹ��AI_C
	LibPinoutsSelect(23,2);//����Сǻѹ����������AI_C13
	LibPinoutsSelect(8,2);//��������ѹ����AI_C4
	LibPinoutsSelect(9,2);//�����½�ѹ����AI_C5
	LibPinoutsSelect(20,2);//����Сǻѹ����������AI_11
	LibPinoutsSelect(16,2);//���۴�ǻѹ����������AI_C8
	LibPinoutsSelect(17,2);//���˴�ǻѹ����AI_C5
	LibPinoutsSelect(6,2);//������ǻ��AI_C5
	LibPinoutsSelect(19,2);//������ѹ����AI_C5
	
	
	LibPinoutsSelect(5,3); //Һѹ���£�AI_R
	//DI
	LibPinoutsSelect(26,0);//�ϵ��źţ�DI_H
	LibPinoutsSelect(14,0);//����ѹ����DI_H
	LibPinoutsSelect(51,0);//�ȵ����أ�DI_H
	LibPinoutsSelect(13,0);//һ�����٣�DI_H
	LibPinoutsSelect(24,0);//���˱�����DI_L
	LibPinoutsSelect(50,0);//���߿���ѹ�����أ�DI_H
	
	LibPinoutsSelect(52,0);//��ͣ�źţ�DI_H
	
	LibPinoutsSelect(33,1);//�������գ�DI_H
	LibPinoutsSelect(34,1);//������ڣ�DI_H
	LibPinoutsSelect(61,1);//�������գ�DI_H
	LibPinoutsSelect(62,1);//�������
	
	
	
	//DO
	LibPinoutsSelect(48,0);//������ѹ��DOH
	LibPinoutsSelect(31,0);//HUIZHUANFA��DOH
	LibPinoutsSelect(46,0);//���߸��٣�DO_H
	LibPinoutsSelect(42,0);//��Դ�̵�����DO_H(����)
	LibPinoutsSelect(35,0);//�ȵ��жϣ�DO_H
	LibPinoutsSelect(34,0);//����Һѹ����1��DO_H
	
	LibPinoutsSelect(32,0);// DO_H
	LibPinoutsSelect(37,0);//������������DO_H
	
    LibPinoutsSelect(41,0);// DO_L
    LibPinoutsSelect(45,0);//DO_H
    LibPinoutsSelect(67,1);//DO_H DT8
    LibPinoutsSelect(70,1);//DO_H
    LibPinoutsSelect(71,1);//DO_H
    LibPinoutsSelect(36,0);//DO_H
    LibPinoutsSelect(38,1);//DO_H
    LibPinoutsSelect(40,1);//DO_H
    LibPinoutsSelect(44,0);//DO_H
    LibPinoutsSelect(72,1);//DO_H
    LibPinoutsSelect(31,0);//DO_H DT5
    
	//PWM
	LibPinoutsSelect(66,0);			//��ű�����,PWM3,��1
	LibPinoutsSelect(80,0);			//��ű�����,PWM11,��1
	LibPinoutsSelect(39,0);			//��ű�����,PWM1,��0 �ܽ����ù���0
//	LibPinoutsSelect(67,0);			//��ű�����,PWM4,��0 pwm8ȥ��
	LibPwmInit(0,300);				//��һ�飬���Ϊ0�ĵ�ű�����Ƶ������300HZ	
	LibPwmInit(1,300);				//�ڶ��飬���Ϊ1�ĵ�ű�����Ƶ������300HZ
	LibSetPwmCurrentFilter(3,20);	//���õ��������˲�����Ŀ20
	LibSetPwmCurrentFilter(1,20);	//���õ��������˲�����Ŀ20
	
	
	//CAN
	LibCan0Init(250);				//CAN0������������Ϊ250KHZ
	LibCan1Init(250);				//CAN1������������Ϊ250KHZ
	/*
	//CAN0 311��312
	LibCan0SetRecMode(0,1,0x18FFF800);	//CAN0,buffer0����,J1939-71,������Ť��
	LibCan0SetRecMode(1,1,0x0CF00400);	//CAN0,buffer1����,J1939-71
	LibCan0SetRecMode(2,1,0x18FFF900);	//CAN0,buffer2����,J1939-71
	LibCan0SetRecMode(3,1,0x18FEEE00);	//CAN0,buffer3����,J1939-71
	LibCan0SetRecMode(4,1,0x18FEEF00);	//CAN0,buffer4����,J1939-71
	LibCan0SetRecMode(5,1,0x18FEB100);	//CAN0,buffer5����,���շ���������ʱ��
	LibCan0SetRecMode(6,1,0x18FEF500);	//CAN0,buffer6����,J1939-71
	LibCan0SetRecMode(7,1,0x18FEF600);	//CAN0,buffer7����,J1939-71
	LibCan0SetRecMode(8,1,0x18FEE900);//CAN0,buffer8����,���շ������������ͺ�
//	LibCan0SetRecMode(9,1,0x18FFE200);  //CAN0,buffer9����,J1939-73
	LibCan0SetRecMode(9,1,0x18FED900); //CAN0,buffer10����,J1939-71
	LibCan0SetRecMode(10,1,0x18FF0300); //CAN0,buffer11����,J1939-71
	//ͨ��11���������������ݼ�¼�� �˶�
	//ͨ��12����������������
	//ͨ��13��������ת������
	//ͨ��14�����������ݷ�����GPS
	LibCan0SetRecMaskId(0, 0x101, 0x5C8);//CAN0��������buffer15-38Ϊ��׼֡
	//����GPS���� CAN0 311��312
	LibCan0SetRecMode(23,0,0x300); //CAN0,buffer23����ID0x300
	LibCan0SetRecMode(24,0,0x321); //CAN0,buffer24����ID0x321
	LibCan0SetRecMode(25,0,0x322); //CAN0,buffer25����ID0x322
	LibCan0SetRecMode(26,0,0x323); //CAN0,buffer26����ID0x323

	//ͨ��11�����������ݷ�������ʾ�� CAN1 327��328 ID200-ID2F1
	//ͨ��12�����������ݷ�������ʾ�� ���۴�Сǻѹ�� ������Сǻѹ��
	//ͨ��13�����������ݷ�������ʾ�� ���˴�Сǻѹ��
	//CAN1������ʾ������
	LibCan1SetRecMode(3,0,0x101); //CAN1������ʾ������ 327��328
	LibCan1SetRecMode(4,0,0x102); //CAN1����ID0x102
	LibCan1SetRecMode(5,0,0x106); //CAN1����ID0x106
	LibCan1SetRecMode(6,0,0x107); //CAN1����ID0x107
	LibCan1SetRecMode(7,0,0x110); //CAN1����ID0x110
	LibCan1SetRecMode(8,0,0x111); //CAN1����ID0x111
	LibCan1SetRecMode(9,0,0x112); //CAN1����ID0x112
	LibCan1SetRecMode(10,0,0x115); //CAN1����ID0x115
	
	/*
	//CAN1***********�ɲ���****************  
	LibCan1SetRecMode(0,0,0x18B);	//CAN1,buffer1����,ID0x18B   ������� ���Բ���
	LibCan1SetRecMode(1,0,0x18C);	//CAN1,buffer1����,ID0x18C   ��ֹ���������� ������ť ������
	LibCan1SetRecMode(2,0,0x09B);	//CAN1,buffer1����,ID0x09B   ������� �����ź�
*/
	
	//CAN0
	LibCan0SetRecMode(0,1,0x18FFF800);	//CAN0,buffer0����,J1939-71,������Ť��
	LibCan0SetRecMode(1,1,0x0CF00400);	//CAN0,buffer1����,J1939-71
	LibCan0SetRecMode(2,1,0x18FFF900);	//CAN0,buffer2����,J1939-71
	LibCan0SetRecMode(3,1,0x18FEEE00);	//CAN0,buffer3����,J1939-71
	LibCan0SetRecMode(4,1,0x18FEEF00);	//CAN0,buffer4����,J1939-71
	LibCan0SetRecMode(5,1,0x18FEB100);	//CAN0,buffer5����,���շ���������ʱ��
	LibCan0SetRecMode(6,1,0x18FEF500);	//CAN0,buffer6����,J1939-71
	LibCan0SetRecMode(7,1,0x18FEF600);	//CAN0,buffer7����,J1939-71
	LibCan0SetRecMode(8,1,0x18FEE900);//CAN0,buffer8����,���շ������������ͺ�
	//LibCan0SetRecMode(9,1,0x1CEBFF00);	//CAN0,buffer9����,J1939-73,��ʮ�塢����˹�����ID
	LibCan0SetRecMode(9,1,0x18FED900); //CAN0,buffer10����,J1939-71
	LibCan0SetRecMode(10,1,0x18FF0300); //CAN0,buffer11����,J1939-71
	//LibCan0SetRecMode(11,1,0x18FEF200); //CAN0,buffer11����,J1939-71
	//LibCan0SetRecMode(11,1,0x18FECA00);	//CAN0,buffer11����,J1939-73,��ʮ�塢����˹������ID
	//LibCan0SetRecMode(11,0,0x101); //CAN0,buffer11����ID0x101
	//ͨ��11���������������ݼ�¼�� �˶�
	//ͨ��12����������������
	//ͨ��13��������ת������
	//ͨ��14�����������ݷ�������ʾ����GPS(����������ת����������������ʾ��)
	LibCan0SetRecMaskId(0, 0x101, 0x100);//CAN0��������buffer15-38Ϊ��׼֡
//	LibCan0SetRecMode(15,0,0x101); //CAN0,buffer15����ID0x101
	LibCan0SetRecMode(16,0,0x102); //CAN0,buffer16����ID0x102
	LibCan0SetRecMode(17,0,0x106); //CAN0,buffer17����ID0x106
	LibCan0SetRecMode(18,0,0x107); //CAN0,buffer18����ID0x107
	LibCan0SetRecMode(19,0,0x116); //CAN0,buffer19����ID0x110
	LibCan0SetRecMode(20,0,0x111); //CAN0,buffer20����ID0x111
	LibCan0SetRecMode(21,0,0x112); //CAN0,buffer21����ID0x112
	LibCan0SetRecMode(22,0,0x115); //CAN0,buffer22����ID0x115
	LibCan0SetRecMode(23,0,0x300); //CAN0,buffer23����ID0x300
	LibCan0SetRecMode(24,0,0x321); //CAN0,buffer24����ID0x321
	LibCan0SetRecMode(25,0,0x322); //CAN0,buffer25����ID0x322
	LibCan0SetRecMode(26,0,0x323); //CAN0,buffer26����ID0x323
	LibCan0SetRecMode(27,0,0x101); //CAN0,buffer27����ID0x101
	//ͨ��33-37,��������511-516�����ݼ�¼��

	
	//+5V���
	LibSystem5vOutput(1);	//+5V���ʹ��
	LibSystem12vOutput(0);	//+12V����ر�
	//�жϽ�ֹ
	LibIrqaDisable();
	LibIrqbDisable();
	//Flash��ʼ��
	FunFlashInit();
	
	VarSysVoltFilterLast = LibGetSystemVoltage();
	
	FunClearPIDparams(&StructPwmDT8);
	VarRestarForEnginerFlag=1;//���ܲ����ж�ϵͳ����
}
/* *************************************************************** 
** File End
** ************************************************************ */
