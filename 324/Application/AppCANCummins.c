#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppVar.h"
/**************************************************************
**函数名：FunCanReceiveCumminsData()
**功能描述：接收康明斯发动机ECU的数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanReceiveCumminsData(void)
{
   FunCanReceiveISUZUData();
}
/**************************************************************
**函数名：FunCanSendEngineDataPack()
**功能描述：组合发送至Cummins发动机ECU的数据
**传入参数：无
**输出参数：无
**************************************************************/
void FunCanSendCumminsDataPack(void)
{
  //ID=0x0C000003,发动机转速控制
/***********************************************************************  
	VarSendDataID_0x0C000003[0]=9;
	VarSendDataID_0x0C000003[1]=(UINT8)(VarCanEngineLevelSpeed*8);
	VarSendDataID_0x0C000003[2]=(UINT8)((VarCanEngineLevelSpeed*8)>>8);
	VarSendDataID_0x0C000003[3]=255;
	VarSendDataID_0x0C000003[4]=255;
	VarSendDataID_0x0C000003[5]=255;
	VarSendDataID_0x0C000003[6]=255;
	VarSendDataID_0x0C000003[7]=255;
	
	
	
*****************************************************************************/
	  //ID=0x0CF00330,发动机开度控制
	VarSendDataID_0x0CF00330[0]=255;
  //VarSendDataID_0x0CF00330[1]=(UINT8)(((VarCanEngineLevelSpeed-590)/16.2)/0.4);//将转速换算成开度控制(*16.2=(2210-590)/100 *)
    VarSendDataID_0x0CF00330[1]=(UINT8)(((VarCanEngineLevelSpeed-590)/16.3)/0.4);//将转速换算成开度控制(*16.4=(2226-590)/100 *)

//	VarSendDataID_0x0CF00330[1]=(UINT8)(((VarCanEngineLevelSpeed-740)/15.8)/0.4);//将转速换算成开度控制(*15.8=(2322-740)/100 *)
	VarSendDataID_0x0CF00330[2]=255;
	VarSendDataID_0x0CF00330[3]=255;
	VarSendDataID_0x0CF00330[4]=255;
	VarSendDataID_0x0CF00330[5]=255;
	VarSendDataID_0x0CF00330[6]=255;
	VarSendDataID_0x0CF00330[7]=255;
	

	
	
		//ID=0x0CFDCB30,发动机调速率控制
	VarSendDataID_0x18FDCB30[0]=255;
	VarSendDataID_0x18FDCB30[1]=00;
	VarSendDataID_0x18FDCB30[2]=00; 		
	VarSendDataID_0x18FDCB30[3]=255;
	VarSendDataID_0x18FDCB30[4]=255;
	VarSendDataID_0x18FDCB30[5]=255;
	VarSendDataID_0x18FDCB30[6]=255;
	VarSendDataID_0x18FDCB30[7]=255;
	
	
		//ID=0x18EA0028,油耗请求
	/*
	VarSendDataID_0x18EA0028[0]=179;
	VarSendDataID_0x18EA0028[1]=254;
	VarSendDataID_0x18EA0028[2]=00; 		
	VarSendDataID_0x18EA0028[3]=00;
	VarSendDataID_0x18EA0028[4]=00;
	VarSendDataID_0x18EA0028[5]=00;
	VarSendDataID_0x18EA0028[6]=00;
	VarSendDataID_0x18EA0028[7]=00;
	*/
	
}
/**************************************************************
**函数名：FunCumminsFaultSPNCodeGet()
**功能描述：康明斯发动机的故障代码提取
**传入参数：无
**输出参数：无
**************************************************************/
void FunCumminsFaultSPNCodeGet(void)
{
	FunISUZUFaultSPNCodeGet();//故障代码提取方式与五十铃相同
}
/**************************************************************
**函数名：FunCumminsFaultCodeDiagnose()
**功能描述：康明斯发动机的故障代码判断
**传入参数：无
**输出参数：无
**************************************************************/
void FunCumminsFaultCodeDiagnose(void)
{
	UINT8 i;
	for(i=0;i<8;i++)
	{
		VarSendDataID1A2[i]=0;
	}
	//根据SPN确认康明斯发动机故障位置
	for(i=0;i<VarIszuFaultSPNNumber;i++)
	{
		switch(VarIsuzuSPN[i])
		{
			case 22:VarSendDataID1A2[0] |= 1<<0;break;
			case 52:VarSendDataID1A2[0] |= 1<<1;break;
		//	case 91:VarSendDataID1A2[0] |= 1<<2;break;//屏蔽此报警
			case 94:VarSendDataID1A2[0] |= 1<<3;break;
			case 95:VarSendDataID1A2[0] |= 1<<4;break;
		//	case 97:VarSendDataID1A2[0] |= 1<<5;break;//油水分离器报警
			case 100:VarSendDataID1A2[0] |= 1<<6;break;
			case 102:VarSendDataID1A2[0] |= 1<<7;break;
			
			case 103:VarSendDataID1A2[1] |= 1<<0;break;
			case 105:VarSendDataID1A2[1] |= 1<<1;break;
			case 108:VarSendDataID1A2[1] |= 1<<2;break;
			case 109:VarSendDataID1A2[1] |= 1<<3;break;
			case 110:VarSendDataID1A2[1] |= 1<<4;break;
			case 111:VarSendDataID1A2[1] |= 1<<5;break;
			case 157:VarSendDataID1A2[1] |= 1<<6;break;
			case 167:VarSendDataID1A2[1] |= 1<<7;break;
			
			case 171:VarSendDataID1A2[2] |= 1<<0;break;
			case 174:VarSendDataID1A2[2] |= 1<<1;break;
			case 175:VarSendDataID1A2[2] |= 1<<2;break;
			case 190:VarSendDataID1A2[2] |= 1<<3;break;
			case 191:VarSendDataID1A2[2] |= 1<<4;break;
			case 412:VarSendDataID1A2[2] |= 1<<5;break;
			case 441:VarSendDataID1A2[2] |= 1<<6;break;
			case 558:VarSendDataID1A2[2] |= 1<<7;break;
			
			case 629:VarSendDataID1A2[3] |= 1<<0;break;
			case 633:VarSendDataID1A2[3] |= 1<<1;break;
			case 639:VarSendDataID1A2[3] |= 1<<2;break;
			case 640:VarSendDataID1A2[3] |= 1<<3;break;
			case 647:VarSendDataID1A2[3] |= 1<<4;break;
			case 651:VarSendDataID1A2[3] |= 1<<5;break;
			case 652:VarSendDataID1A2[3] |= 1<<6;break;
			case 653:VarSendDataID1A2[3] |= 1<<7;break;
			
			case 654:VarSendDataID1A2[4] |= 1<<0;break;
			case 655:VarSendDataID1A2[4] |= 1<<1;break;
			case 656:VarSendDataID1A2[4] |= 1<<2;break;
			case 677:VarSendDataID1A2[4] |= 1<<3;break;
			case 702:VarSendDataID1A2[4] |= 1<<4;break;
			case 723:VarSendDataID1A2[4] |= 1<<5;break;
			case 729:VarSendDataID1A2[4] |= 1<<6;break;
			case 730:VarSendDataID1A2[4] |= 1<<7;break;
			
			case 974:VarSendDataID1A2[5] |= 1<<0;break;
			case 1072:VarSendDataID1A2[5] |= 1<<1;break;
			case 1073:VarSendDataID1A2[5] |= 1<<2;break;
			case 1075:VarSendDataID1A2[5] |= 1<<3;break;
			case 1112:VarSendDataID1A2[5] |= 1<<4;break;
			case 1172:VarSendDataID1A2[5] |= 1<<5;break;
			case 1209:VarSendDataID1A2[5] |= 1<<6;break;
			case 1484:VarSendDataID1A2[5] |= 1<<7;break;
						
			case 1800:VarSendDataID1A2[6] |= 1<<0;break;
			case 2623:VarSendDataID1A2[6] |= 1<<1;break;
			case 2802:VarSendDataID1A2[6] |= 1<<2;break;
			case 2981:VarSendDataID1A2[6] |= 1<<3;break;
			case 3509:VarSendDataID1A2[6] |= 1<<4;break;
			case 3510:VarSendDataID1A2[6] |= 1<<5;break;
			case 520199:VarSendDataID1A2[6] |= 1<<6;break;
		}
	}
}
