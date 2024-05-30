#include "MC56F8367Reg.h"
#include "LibFunDefine.h"

#define DefineFlashStartAddr          0x4800
#define DefineFlashLength             0x3800

#define FMCMD_ASM X:62484
#define FMCR_ASM X:62465
#define FMUSTAT_ASM X:62483
#define setReg16(RegName, val)             (RegName = (UINT16)(val))
#define clrReg16Bits(RegName, ClrMask)     (RegName &= ~(UINT16)(ClrMask))
#define BackupArrayAddr(addr) (addr & 255)
#define SectorSize(addr) (DATA_FLASH_SECTOR_SIZE)
#define ClearFlags() setReg(FMUSTAT,0x30)
#define readflash(address) (*(UINT16 *)(address))
#define writeflash(address, data) (*(UINT16 *)(address)=data)
#define SelectRegBank() setRegBitGroup(FMCR,BKSEL,DATA_REG_BANK)

static UINT8 Err;
static UINT16 BackupArray[256];

/* ******************************************************
** 函数名称:OutOfRange
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
static UINT8 OutOfRange(UINT32 addr1,UINT32 addr2)
{
	return ((addr1>addr2)||(addr1<DefineFlashStartAddr)||(addr2>=(DefineFlashStartAddr+DefineFlashLength)));
}
/* ******************************************************
** 函数名称:procflash
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
static UINT8 procflash(UINT32 address, UINT16 data, UINT16 command)
{
	UINT8 loop_count;
	UINT8  wait_en;
	UINT8 busy=0;

	loop_count = 0;
	wait_en = 1;
	busy = LibFlashBusy();
	while( busy>0 && wait_en>0 )
	{
		 LibSystemDelay1MS(1);
		 loop_count++;
		 if(loop_count > 20)
		 {
		 	 wait_en = 0;
		 }
		 busy = LibFlashBusy();
		 LibWatchDogFeed();
	}

	if (LibFlashBusy())
	{
		return 8;
	}
	REG_FM_FMUSTAT = 0x30;
	writeflash(address, data);
	REG_FM_FMCMD = command;
	REG_FM_FMUSTAT = 0x80; 
	if ((REG_FM_FMUSTAT&0x20)||(REG_FM_FMUSTAT&0x10))
	{
		return 9;
	}
	return Err;
}
/* ******************************************************
** 函数名称:BackupSector
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
static void BackupSector(UINT32 Addr)
{
	register UINT16 i;
	register UINT32 StartAddress;
	StartAddress = Addr & ~((UINT32)(256-1));
	for (i=256; i>0;) 
	{
		i--;
		BackupArray[i] = readflash((StartAddress+i));
	}
}
/* ******************************************************
** 函数名称:RestoreSector
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
static UINT8 RestoreSector(UINT32 Addr)
{
	register UINT32 i=0;
	register UINT32 StartAddress;
	StartAddress = Addr & ~((UINT32)(256-1)); /* Calculate start of the sector */
	for (i = 256; i>0;)
	{   /* For all words in the sector */
		i--;                               /* Decrease array pointer, write word to FLASH */
		Err = procflash((StartAddress+i),BackupArray[i],0x20);
		if (Err!=0)                   /* If an error uccure then exit */
		{
			return Err;
		}
		while ((REG_FM_FMUSTAT&0x80) == 0) {} /* Wait to buffer empty */
	}
	while ((REG_FM_FMUSTAT&0x40) == 0) {} /* Wait to command complete */
	for (i = 256; i>0;)
	{   /* For all words in the sector */
		i--;                               /* Decrease array pointer, write word to FLASH */
		if (readflash((StartAddress+i)) != BackupArray[i]) /* Are the written data equal to read data ? */
		{
			return 3;                   /* If no then error */
		}
	}
	return 0;                       /* OK */
}
/* ******************************************************
** 函数名称:WriteBlock
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
static UINT8 WriteBlock(UINT32 Source, UINT32 Dest, UINT32 Count)
{
  register UINT16 i, DataToWrite;
  register UINT32 s_index, Addr, LastAddr, Size;
  register UINT8 ByteFirst, ByteLast;
  register UINT8 SectorBackup;
  register UINT16 j, cycles, AddrInSec;
  register UINT32 S_index_bckup;

  Err = 0;
  j = 0;
  cycles = 0;
  Addr = (UINT32)Dest / 2;
  if ((UINT32)Dest % 2 > 0)
    ByteFirst = 1;
  else
    ByteFirst = 0;
  LastAddr = (UINT32)Dest + Count;
  if (LastAddr % 2 > 0)
    ByteLast = TRUE;
  else
    ByteLast = FALSE;
  LastAddr = (LastAddr - 1) / 2;
  Size = (LastAddr - Addr) + 1;
  if (OutOfRange(Addr,LastAddr))       /* Is the address out of range? */
    return(2);                 /* If yes then exit */
  //SelectRegBank();                     /* Select Data_Flash register bank */
  (UINT16)(REG_FM_FMCR&0x03|1);
  SectorBackup = 0;                /* Initialize sector backup flag */
  s_index = 0;
  for (i=0; i<Size; i++) {             /* For all given data */
    AddrInSec = (UINT16)((Addr+i)&((UINT32)(256-1))); /* Calculate relative address in a sector */
    if ((AddrInSec==0)||(i==0)) {      /* Is the actual address the first or is it a border of a sector? */
      cycles = (UINT16)((Size - i < (256 - AddrInSec)) ? (Size - i) : (256 - AddrInSec)); /* How many address places have to be tested in the actual sector? */
      while ((REG_FM_FMUSTAT&0x40) == 0) {} /* Wait to command complete */
      S_index_bckup = s_index;
      for (j=0; j<cycles;j++) {        /* For all memory locations which have to be tested in the actual sector */
        if ((i + j == 0) && (ByteFirst))
          DataToWrite = (readflash(Addr) & 0x00ff) + (((UINT16)((UINT8 *)(Source))[s_index++]) << 8);
        else if ((i + j == Size - 1) && (ByteLast))
          DataToWrite = (readflash(Addr + i + j) & 0xff00) + ((UINT8 *)(Source))[s_index];
        else {
          DataToWrite = ((UINT8 *)Source)[s_index] + ((UINT16)((UINT8 *)(Source))[s_index + 1] << 8);
          s_index += 2;
        }
        if (~(readflash(Addr+i+j))&(DataToWrite)) { /* Is the sector erasure necessary? */
           BackupSector(Addr+i);       /* Backup the sector */
           SectorBackup=1;          /* Set backup sector flag */
          Err = procflash((Addr+i),0,0x40); /* Erase the sector */
          if (Err != 0) {         /* If an error occured then exit */
            return Err;
          }
          break;                       /* The sector is backuped and erased. Now end test of the sector */
        }
      }
      s_index = S_index_bckup;
      j = 0;                           /* Initialize sector memory location index */
    }
      if ((i == 0) && (ByteFirst)) {
        if (SectorBackup)
          DataToWrite = BackupArray[AddrInSec];
        else {
          while ((REG_FM_FMUSTAT&0x40) == 0) {} /* Wait to command complete */
          DataToWrite = readflash(Addr + i);
        }
        DataToWrite = (DataToWrite & 0x00ff) + (((UINT16)((UINT8 *)(Source))[s_index++]) << 8);
      }
      else if ((i == Size - 1) && (ByteLast)) {
        if (SectorBackup)
          DataToWrite = BackupArray[AddrInSec];
        else {
          while ((REG_FM_FMUSTAT&0x40) == 0) {} /* Wait to command complete */
          DataToWrite = readflash(Addr + i);
        }
        DataToWrite = (DataToWrite & 0xff00) + ((UINT8 *)(Source))[s_index];
      }
      else {
        DataToWrite = ((UINT8 *)Source)[s_index] + ((UINT16)((UINT8 *)(Source))[s_index + 1] << 8);
        s_index += 2;
      }
    if (SectorBackup)                  /* If the sector is backuped, write new data to buffer */
      BackupArray[AddrInSec] = DataToWrite;
    else {                             /* If no, write data directly to FLASH */
      while ((REG_FM_FMUSTAT&0x40) == 0) {} /* Wait to command complete */
      if (readflash(Addr+i)!=DataToWrite) /* Is a programming of the FLASH necessary? */
        Err = procflash((Addr+i), DataToWrite, 0x20); /* If yes program new data to FLASH */
      if (Err != 0) {             /* If an error occured then exit */
        return Err;
      }
    }
    j++;                               /* Increment the sector index */
    if ((j==cycles)&&(SectorBackup)) { /* Is the actual sector memory location the last and is the sector backuped? */
      while ((REG_FM_FMUSTAT&0x80) == 0) {} /* Wait to buffer empty */
      Err = RestoreSector(Addr+i);     /* Restore actual sector */
      SectorBackup = 0;            /* Clear sector backup flag */
    }
    if (Err!=0) {                 /* If an error occured then exit */
      return Err;
    }
  }
  while ((REG_FM_FMUSTAT&0x40) == 0) {} /* Wait to command complete */
  i = 0;
  s_index = 0;
  if ((Err == 0) && (ByteFirst)) {
    i++;
    if ((readflash(Addr) >> 8) != ((UINT8*)Source)[s_index++])
      Err = 3;
  }
  if (Err == 0) {
    for (; i < Size - ByteLast; i++) { /* Check all given data were written good */
      if (readflash(Addr+i) != ((((UINT8*)Source)[s_index]) + ((UINT16)((UINT8*)Source)[s_index + 1] << 8))) {
        s_index += 2;
        Err = 3;
        break;
      }
      else {
        s_index += 2;
      }
    }
  }
  if ((Err == 0) && (ByteLast)) {
    if ((UINT8)(readflash(Addr+i)) != ((UINT8*)Source)[s_index])
      Err = 3;
  }
  return Err;
}
/* ******************************************************
** 函数名称:LibFlashSetWord
** 功能描述:总共有0x3C00个WORD空间，地址范围为0~0x3BFF
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibFlashSetWord(UINT32 Addr,UINT16 Data)
{
	UINT8 ERR;
	if( Addr >= DefineFlashLength )
	{
		return FALSE;
	}
	Addr += DefineFlashStartAddr;
	LibFlashSetGlobalProtection(0);
	ERR = WriteBlock((UINT32)((UINT8 *)&Data), Addr*2, sizeof(Data));
	LibFlashSetGlobalProtection(1);
	return !ERR;
}
/* ******************************************************
** 函数名称:LibFlashSetBlock
** 功能描述:总共有0x3C00个WORD空间，地址范围为0~0x3BFF，共分为60个page
**          例如第一个page地址范围为0~0x00FF
**          使用block写入时操作空间范围必须在一个page内
**          跨page无法正确写入
**          例如试图从地址0x00F0至0x0105写入22个WORD是错误的
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibFlashSetBlock(UINT32 Addr,UINT16 *Data,UINT32 Count)
{
	UINT8 ERR;
	if( Addr >= DefineFlashLength || Count >= DefineFlashLength )
	{
		return FALSE;
	}
	Addr += DefineFlashStartAddr;
	if (OutOfRange(Addr, Addr+Count-1))
	{
		return FALSE;
	}
	LibFlashSetGlobalProtection(0);  
	ERR = WriteBlock((UINT32)((UINT8 *)Data), Addr*2, Count*2);
	LibFlashSetGlobalProtection(1);
	return !ERR;
}
/* ******************************************************
** 函数名称:LibFlashGetWord
** 功能描述:总共有0x3C00个WORD空间，地址范围为0~0x3BFF
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibFlashGetWord(UINT32 Addr,UINT16 *Data)
{
	if( Addr >= DefineFlashLength )
	{
		return FALSE;
	}
	Addr += DefineFlashStartAddr;
	*Data = readflash(Addr);
	return TRUE;
}
/* ******************************************************
** 函数名称:LibFlashGetBlock
** 功能描述:总共有0x3800个WORD空间，地址范围为0~0x3BFF
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibFlashGetBlock(UINT32 Addr,UINT16 *Data,UINT32 Count)
{
	UINT8 ERR=0;
	UINT32 i;

	if( Addr >= DefineFlashLength || Count >= DefineFlashLength )
	{
		return FALSE;
	}
	Addr += DefineFlashStartAddr;
	
	if (OutOfRange(Addr, Addr+Count-1))
	{
		ERR = 2;
		return !ERR;
	}
	for(i=0;i<Count;i++)
	{
		*(Data+i) = readflash(Addr+i);
	}
	return !ERR;
}
/* ******************************************************
** 函数名称:LibFlashSetGlobalProtection
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibFlashSetGlobalProtection(UINT8 ProtectAll)
{
	UINT8 ERR=0;
	register UINT16 data;
	if (ProtectAll)
	{
		data=0xffff;
	}
	else
	{
		data=0;
	}
	(REG_FM_FMCR = (UINT16)((REG_FM_FMCR & ~0x03) | ((1) << 0))); 
	REG_FM_FMPROT=data; 
	if(data != REG_FM_FMPROT)
	{
		ERR = 3;
		return !ERR;
	}
	return !ERR;
}
/* ******************************************************
** 函数名称:LibFlashBusy
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
UINT8 LibFlashBusy()
{
	UINT8 busy;
	busy = ((UINT8)((REG_FM_FMUSTAT&0x40) ? (REG_FM_FMCR^=3, ((REG_FM_FMUSTAT&0x40) ? (REG_FM_FMCR^=3, 0) : (REG_FM_FMCR^=3, 1))) : (1)));
	return busy;
}
/* ******************************************************
** 函数名称:LibFlashInit
** 功能描述:
** 传入参数:
** 返回数据:
** *************************************************** */
void LibFlashInit(void)
{
  clrReg16Bits(REG_FM_FMCR, 256U);     
  LibFlashSetGlobalProtection(1);        
}
/* *************************************************************** 
** File End
** ************************************************************ */
