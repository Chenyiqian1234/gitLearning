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
	//针脚定义
	//AI
	LibPinoutsSelect(4,0); //油门表盘，AI_V
	LibPinoutsSelect(7,3); //燃 油 量，AI_R
	LibPinoutsSelect(21,2);//泵1 压力，AI_C
	LibPinoutsSelect(10,2);//泵2 压力，AI_C
	LibPinoutsSelect(11,2);//蓄能器气压，AI_C
	LibPinoutsSelect(23,2);//斗杆小腔压力传感器，AI_C13
	LibPinoutsSelect(8,2);//动臂上升压力，AI_C4
	LibPinoutsSelect(9,2);//动臂下降压力，AI_C5
	LibPinoutsSelect(20,2);//动臂小腔压力传感器，AI_11
	LibPinoutsSelect(16,2);//动臂大腔压力传感器，AI_C8
	LibPinoutsSelect(17,2);//斗杆大腔压力，AI_C5
	LibPinoutsSelect(6,2);//铲斗大腔，AI_C5
	LibPinoutsSelect(19,2);//蓄能器压力，AI_C5
	
	
	LibPinoutsSelect(5,3); //液压油温，AI_R
	//DI
	LibPinoutsSelect(26,0);//上电信号，DI_H
	LibPinoutsSelect(14,0);//行走压力，DI_H
	LibPinoutsSelect(51,0);//先导开关，DI_H
	LibPinoutsSelect(13,0);//一键怠速，DI_H
	LibPinoutsSelect(24,0);//空滤报警，DI_L
	LibPinoutsSelect(50,0);//辅具控制压力开关，DI_H
	
	LibPinoutsSelect(52,0);//急停信号，DI_H
	
	LibPinoutsSelect(33,1);//斗杆内收，DI_H
	LibPinoutsSelect(34,1);//斗杆外摆，DI_H
	LibPinoutsSelect(61,1);//铲斗内收，DI_H
	LibPinoutsSelect(62,1);//铲斗外摆
	
	
	
	//DO
	LibPinoutsSelect(48,0);//二次增压，DOH
	LibPinoutsSelect(31,0);//HUIZHUANFA，DOH
	LibPinoutsSelect(46,0);//行走高速，DO_H
	LibPinoutsSelect(42,0);//电源继电器，DO_H(常电)
	LibPinoutsSelect(35,0);//先导切断，DO_H
	LibPinoutsSelect(34,0);//辅具液压锤阀1，DO_H
	
	LibPinoutsSelect(32,0);// DO_H
	LibPinoutsSelect(37,0);//蜂鸣器报警，DO_H
	
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
	LibPinoutsSelect(66,0);			//电磁比例阀,PWM3,组1
	LibPinoutsSelect(80,0);			//电磁比例阀,PWM11,组1
	LibPinoutsSelect(39,0);			//电磁比例阀,PWM1,组0 管脚设置功能0
//	LibPinoutsSelect(67,0);			//电磁比例阀,PWM4,组0 pwm8去掉
	LibPwmInit(0,300);				//第一组，组号为0的电磁比例阀频率设置300HZ	
	LibPwmInit(1,300);				//第二组，组号为1的电磁比例阀频率设置300HZ
	LibSetPwmCurrentFilter(3,20);	//设置电流采样滤波点数目20
	LibSetPwmCurrentFilter(1,20);	//设置电流采样滤波点数目20
	
	
	//CAN
	LibCan0Init(250);				//CAN0，波特率设置为250KHZ
	LibCan1Init(250);				//CAN1，波特率设置为250KHZ
	/*
	//CAN0 311、312
	LibCan0SetRecMode(0,1,0x18FFF800);	//CAN0,buffer0接受,J1939-71,发动机扭矩
	LibCan0SetRecMode(1,1,0x0CF00400);	//CAN0,buffer1接受,J1939-71
	LibCan0SetRecMode(2,1,0x18FFF900);	//CAN0,buffer2接受,J1939-71
	LibCan0SetRecMode(3,1,0x18FEEE00);	//CAN0,buffer3接受,J1939-71
	LibCan0SetRecMode(4,1,0x18FEEF00);	//CAN0,buffer4接受,J1939-71
	LibCan0SetRecMode(5,1,0x18FEB100);	//CAN0,buffer5接受,接收发动机工作时间
	LibCan0SetRecMode(6,1,0x18FEF500);	//CAN0,buffer6接受,J1939-71
	LibCan0SetRecMode(7,1,0x18FEF600);	//CAN0,buffer7接受,J1939-71
	LibCan0SetRecMode(8,1,0x18FEE900);//CAN0,buffer8接受,接收发动机工作总油耗
//	LibCan0SetRecMode(9,1,0x18FFE200);  //CAN0,buffer9接受,J1939-73
	LibCan0SetRecMode(9,1,0x18FED900); //CAN0,buffer10接受,J1939-71
	LibCan0SetRecMode(10,1,0x18FF0300); //CAN0,buffer11接受,J1939-71
	//通道11，发送数据至数据记录仪 核对
	//通道12，发动机数据请求
	//通道13，发动机转速请求
	//通道14，控制器数据发送至GPS
	LibCan0SetRecMaskId(0, 0x101, 0x5C8);//CAN0掩码设置buffer15-38为标准帧
	//接收GPS数据 CAN0 311、312
	LibCan0SetRecMode(23,0,0x300); //CAN0,buffer23接受ID0x300
	LibCan0SetRecMode(24,0,0x321); //CAN0,buffer24接受ID0x321
	LibCan0SetRecMode(25,0,0x322); //CAN0,buffer25接受ID0x322
	LibCan0SetRecMode(26,0,0x323); //CAN0,buffer26接受ID0x323

	//通道11，控制器数据发送至显示屏 CAN1 327、328 ID200-ID2F1
	//通道12，控制器数据发送至显示屏 动臂大、小腔压力 铲斗大小腔压力
	//通道13，控制器数据发送至显示屏 斗杆大、小腔压力
	//CAN1接收显示屏数据
	LibCan1SetRecMode(3,0,0x101); //CAN1接收显示屏数据 327、328
	LibCan1SetRecMode(4,0,0x102); //CAN1接受ID0x102
	LibCan1SetRecMode(5,0,0x106); //CAN1接受ID0x106
	LibCan1SetRecMode(6,0,0x107); //CAN1接受ID0x107
	LibCan1SetRecMode(7,0,0x110); //CAN1接受ID0x110
	LibCan1SetRecMode(8,0,0x111); //CAN1接受ID0x111
	LibCan1SetRecMode(9,0,0x112); //CAN1接受ID0x112
	LibCan1SetRecMode(10,0,0x115); //CAN1接受ID0x115
	
	/*
	//CAN1***********可不用****************  
	LibCan1SetRecMode(0,0,0x18B);	//CAN1,buffer1接受,ID0x18B   总线面板 可以不用
	LibCan1SetRecMode(1,0,0x18C);	//CAN1,buffer1接受,ID0x18C   禁止再生和再生 油门旋钮 总线型
	LibCan1SetRecMode(2,0,0x09B);	//CAN1,buffer1接受,ID0x09B   总线面板 心跳信号
*/
	
	//CAN0
	LibCan0SetRecMode(0,1,0x18FFF800);	//CAN0,buffer0接受,J1939-71,发动机扭矩
	LibCan0SetRecMode(1,1,0x0CF00400);	//CAN0,buffer1接受,J1939-71
	LibCan0SetRecMode(2,1,0x18FFF900);	//CAN0,buffer2接受,J1939-71
	LibCan0SetRecMode(3,1,0x18FEEE00);	//CAN0,buffer3接受,J1939-71
	LibCan0SetRecMode(4,1,0x18FEEF00);	//CAN0,buffer4接受,J1939-71
	LibCan0SetRecMode(5,1,0x18FEB100);	//CAN0,buffer5接受,接收发动机工作时间
	LibCan0SetRecMode(6,1,0x18FEF500);	//CAN0,buffer6接受,J1939-71
	LibCan0SetRecMode(7,1,0x18FEF600);	//CAN0,buffer7接受,J1939-71
	LibCan0SetRecMode(8,1,0x18FEE900);//CAN0,buffer8接受,接收发动机工作总油耗
	//LibCan0SetRecMode(9,1,0x1CEBFF00);	//CAN0,buffer9接受,J1939-73,五十铃、康明斯多故障ID
	LibCan0SetRecMode(9,1,0x18FED900); //CAN0,buffer10接受,J1939-71
	LibCan0SetRecMode(10,1,0x18FF0300); //CAN0,buffer11接受,J1939-71
	//LibCan0SetRecMode(11,1,0x18FEF200); //CAN0,buffer11接受,J1939-71
	//LibCan0SetRecMode(11,1,0x18FECA00);	//CAN0,buffer11接受,J1939-73,五十铃、康明斯单故障ID
	//LibCan0SetRecMode(11,0,0x101); //CAN0,buffer11接受ID0x101
	//通道11，发送数据至数据记录仪 核对
	//通道12，发动机数据请求
	//通道13，发动机转速请求
	//通道14，控制器数据发送至显示屏、GPS(控制器不再转发发动机数据至显示屏)
	LibCan0SetRecMaskId(0, 0x101, 0x100);//CAN0掩码设置buffer15-38为标准帧
//	LibCan0SetRecMode(15,0,0x101); //CAN0,buffer15接受ID0x101
	LibCan0SetRecMode(16,0,0x102); //CAN0,buffer16接受ID0x102
	LibCan0SetRecMode(17,0,0x106); //CAN0,buffer17接受ID0x106
	LibCan0SetRecMode(18,0,0x107); //CAN0,buffer18接受ID0x107
	LibCan0SetRecMode(19,0,0x116); //CAN0,buffer19接受ID0x110
	LibCan0SetRecMode(20,0,0x111); //CAN0,buffer20接受ID0x111
	LibCan0SetRecMode(21,0,0x112); //CAN0,buffer21接受ID0x112
	LibCan0SetRecMode(22,0,0x115); //CAN0,buffer22接受ID0x115
	LibCan0SetRecMode(23,0,0x300); //CAN0,buffer23接受ID0x300
	LibCan0SetRecMode(24,0,0x321); //CAN0,buffer24接受ID0x321
	LibCan0SetRecMode(25,0,0x322); //CAN0,buffer25接受ID0x322
	LibCan0SetRecMode(26,0,0x323); //CAN0,buffer26接受ID0x323
	LibCan0SetRecMode(27,0,0x101); //CAN0,buffer27接受ID0x101
	//通道33-37,发送数据511-516到数据记录仪

	
	//+5V输出
	LibSystem5vOutput(1);	//+5V输出使能
	LibSystem12vOutput(0);	//+12V输出关闭
	//中断禁止
	LibIrqaDisable();
	LibIrqbDisable();
	//Flash初始化
	FunFlashInit();
	
	VarSysVoltFilterLast = LibGetSystemVoltage();
	
	FunClearPIDparams(&StructPwmDT8);
	VarRestarForEnginerFlag=1;//节能部分判断系统重启
}
/* *************************************************************** 
** File End
** ************************************************************ */
