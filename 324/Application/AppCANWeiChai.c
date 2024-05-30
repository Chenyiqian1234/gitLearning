#include "AppFun.h"
#include "LibFunDefine.h"
#include "AppVar.h"
/**************************************************************
**��������FunCanReceiveWeiChaiData()
**��������������Ϋ�񷢶���ECU������
**�����������
**�����������
**************************************************************/
void FunCanReceiveWeiChaiData(void)
{
	FunCanReceiveISUZUData();
}
/**************************************************************
**��������FunCanSendWeiChaiDataPack()
**������������Ϸ�����Ϋ�񷢶���ECU������
**�����������
**�����������
**************************************************************/
void FunCanSendWeiChaiDataPack(void)
{
	//ID=0x0C0000E4,ת�ٿ���
	VarSendDataID_0x0C000003[0]=253;
	VarSendDataID_0x0C000003[1]=(UINT8)(VarCanEngineLevelSpeed*8);
	VarSendDataID_0x0C000003[2]=(UINT8)((VarCanEngineLevelSpeed*8)>>8);
	VarSendDataID_0x0C000003[3]=255;
	VarSendDataID_0x0C000003[4]=255;
	VarSendDataID_0x0C000003[5]=255;
	VarSendDataID_0x0C000003[6]=255;
	VarSendDataID_0x0C000003[7]=255;
}
/**************************************************************
**��������FunWeiChaiFaultSPNCodeGet()
**����������Ϋ�񷢶����Ĺ��ϴ�����ȡ
**�����������
**�����������
**************************************************************/
void FunWeiChaiFaultSPNCodeGet(void)
{
	UINT8 i=0,k=0;
	/**********�������ϴ��룬���ϴ������ȡ��ʽ����ʮ�塢����˹��ͬ***********/
	if(VarIsuzuFaultCodeSingle>0)
	{
		VarIsuzuSPN[0]=VarRecDataID_0x18ECFF00[2]+(UINT16)VarRecDataID_0x18ECFF00[3]*256+(UINT32)((VarRecDataID_0x18ECFF00[4]&0xE0)>>5)*65536;
		VarIsuzuFMI[0]=(UINT8)(VarRecDataID_0x18ECFF00[4]&0x1F);
		VarUartFaultCode=(UINT8)(VarIsuzuSPN[0]);
		VarIszuFaultSPNNumber=1;
	}
	/**********�������ϴ���,���ϴ������ȡ��ʽ����ʮ�塢����˹��ͬ***********/
	else if(VarIsuzuFaultCodeMany>0)
	{
		//�����еĹ��ϴ��붼�����ά�����У���ά����ĵ�i�б�ʾ��i��ѭ��NO.
		for(i=0;i<8;i++)
		{
			VarIsuzuFault[VarRecDataID_0x18EBFF00[0]][i]=VarRecDataID_0x18EBFF00[i];
			//��ȡ��ǰ���ϴ���ѭ��NO.��
			if(VarIsuzuCodeNumber<VarRecDataID_0x18EBFF00[0])
			{
				VarIsuzuCodeNumber=VarRecDataID_0x18EBFF00[0];
			}
		}
		//������ϴ����е�SPN
		for(i=1;i<VarIsuzuCodeNumber+1;i++)
		{
			switch(i%4)
			{
				case 0:
					VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][4]&0x1F);
					VarIsuzuSPN[k++] =VarIsuzuFault[i][2]+(UINT16)VarIsuzuFault[i][3]*256+(UINT32)((VarIsuzuFault[i][4]&0xE0)>>5)*65536;
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					break;
				case 1:
				    VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][5]&0x1F);
					VarIsuzuSPN[k++] = VarIsuzuFault[i][3]+(UINT16)VarIsuzuFault[i][4]*256+(UINT32)((VarIsuzuFault[i][5]&0xE0)>>5)*65536;
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					if(i!=1)//����NO.1�������������ϴ���
					{
						VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][1]&0x1F);
						VarIsuzuSPN[k++] = VarIsuzuFault[i-1][6]+(UINT16)VarIsuzuFault[i-1][7]*256+(UINT32)((VarIsuzuFault[i][1]&0xE0)>>5)*65536;
						VarIszuFaultSPNNumber = (UINT8)(k-1);
					}
					break;
				case 2:
				    VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][6]&0x1F);
					VarIsuzuSPN[k++] =VarIsuzuFault[i][4]+(UINT16)VarIsuzuFault[i][5]*256+(UINT32)((VarIsuzuFault[i][6]&0xE0)>>5)*65536;
					VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][2]&0x1F);
					VarIsuzuSPN[k++] = VarIsuzuFault[i-1][7]+(UINT16)VarIsuzuFault[i][1]*256+(UINT32)((VarIsuzuFault[i][2]&0xE0)>>5)*65536;
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					break;
				case 3:
				    VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][3]&0x1F);
					VarIsuzuSPN[k++] =VarIsuzuFault[i][1]+VarIsuzuFault[i][2]*256+(UINT32)((VarIsuzuFault[i][3]&0xE0)>>5)*65536;
					VarIsuzuFMI[k] = (UINT8)(VarIsuzuFault[i][7]&0x1F);
					VarIsuzuSPN[k++] =VarIsuzuFault[i][5]+VarIsuzuFault[i][6]*256+(UINT32)((VarIsuzuFault[i][7]&0xE0)>>5)*65536;
					VarIszuFaultSPNNumber = (UINT8)(k-1);
					break;
				default:break;
			}
		}
		VarEngineFaultCode2 = (UINT16)VarIsuzuSPN[1];
		VarEngineFaultCode3 = (UINT16)VarIsuzuSPN[2];
		VarEngineFaultCode4 = (UINT16)VarIsuzuSPN[3];
		VarEngineFaultCode5 = (UINT16)VarIsuzuSPN[4];
		VarEngineFaultCode6 = (UINT16)VarIsuzuSPN[5];
	}

}
/**************************************************************
**��������FunWeiChaiFaultCodeDiagnose()
**����������Ϋ�񷢶����Ĺ��ϴ����ж�
**�����������
**�����������
**************************************************************/
void FunWeiChaiFaultCodeDiagnose(void)
{
	UINT8 i=0;	
	for(i=0;i<8;i++)
	{
		VarSendDataID1A1[i]=0;
	}
	//����SPNȷ�Ϲ���λ��
	for(i=0;i<VarIszuFaultSPNNumber;i++)
	{
		switch(VarIsuzuSPN[i])
		{
			case 29:VarSendDataID1A1[0] |= 1<<0;;break;
			case 84:VarSendDataID1A1[0] |= 1<<1;break;
			case 91:VarSendDataID1A1[0] |= 1<<2;break;
			case 97:VarSendDataID1A1[0] |= 1<<3;break;
			case 98:VarSendDataID1A1[0] |= 1<<4;break;
			case 100:VarSendDataID1A1[0] |= 1<<5;break;
			case 102:VarSendDataID1A1[0] |= 1<<6;break;
			case 105:VarSendDataID1A1[0] |= 1<<7;break;
			
			case 108:VarSendDataID1A1[1] |= 1<<0;break;
			case 110:VarSendDataID1A1[1] |= 1<<1;break;
			case 157:VarSendDataID1A1[1] |= 1<<2;break;
			case 158:VarSendDataID1A1[1] |= 1<<3;break;
			case 168:VarSendDataID1A1[1] |= 1<<4;break;
			case 171:VarSendDataID1A1[1] |= 1<<5;break;
			case 175:VarSendDataID1A1[1] |= 1<<6;break;
			case 190:VarSendDataID1A1[1] |= 1<<7;break;
			
			case 533:VarSendDataID1A1[2] |= 1<<0;break;
			case 596:VarSendDataID1A1[2] |= 1<<1;break;
			case 597:VarSendDataID1A1[2] |= 1<<2;break;
			case 598:VarSendDataID1A1[2] |= 1<<3;break;
			case 624:VarSendDataID1A1[2] |= 1<<4;break;
			case 636:VarSendDataID1A1[2] |= 1<<5;break;
			case 639:VarSendDataID1A1[2] |= 1<<6;break;
			case 645:VarSendDataID1A1[2] |= 1<<7;break;
			
			case 651:VarSendDataID1A1[3] |= 1<<0;break;
			case 652:VarSendDataID1A1[3] |= 1<<1;break;
			case 653:VarSendDataID1A1[3] |= 1<<2;break;
			case 654:VarSendDataID1A1[3] |= 1<<3;break;
			case 655:VarSendDataID1A1[3] |= 1<<4;break;
			case 656:VarSendDataID1A1[3] |= 1<<5;break;
			case 677:VarSendDataID1A1[3] |= 1<<6;break;
			case 729:VarSendDataID1A1[3] |= 1<<7;break;
			
			case 970:VarSendDataID1A1[4] |= 1<<0;break;
			case 1041:VarSendDataID1A1[4] |= 1<<1;break;
			case 1074:VarSendDataID1A1[4] |= 1<<2;break;
			case 1079:VarSendDataID1A1[4] |= 1<<3;break;
			case 1080:VarSendDataID1A1[4] |= 1<<4;break;
			case 1081:VarSendDataID1A1[4] |= 1<<5;break;
			case 1108:VarSendDataID1A1[4] |= 1<<6;break;
			case 1231:VarSendDataID1A1[4] |= 1<<7;break;
			
			case 1235:VarSendDataID1A1[5] |= 1<<0;break;
			case 1322:VarSendDataID1A1[5] |= 1<<1;break;
			case 1323:VarSendDataID1A1[5] |= 1<<2;break;
			case 1324:VarSendDataID1A1[5] |= 1<<3;break;
			case 1325:VarSendDataID1A1[5] |= 1<<4;break;
			case 1326:VarSendDataID1A1[5] |= 1<<5;break;
			case 1327:VarSendDataID1A1[5] |= 1<<6;break;
			case 1328:VarSendDataID1A1[5] |= 1<<7;break;
			
			case 1351:VarSendDataID1A1[6] |= 1<<0;break;
			case 1485:VarSendDataID1A1[6] |= 1<<1;break;
			case 1624:VarSendDataID1A1[6] |= 1<<2;break;
			case 1639:VarSendDataID1A1[6] |= 1<<3;break;
			case 2634:VarSendDataID1A1[6] |= 1<<4;break;
			default:break;
		}
	}
}