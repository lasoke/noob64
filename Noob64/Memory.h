/*
 * Noob64 - A Nintendo 64 emulator.
 *
 * (c) Copyright 2012 Quentin Metzler and 
 * Romain Richard.
 *
 * Permission to use, copy, modify and distribute Noob64 in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Noob64 is freeware for PERSONAL USE only. Commercial users should
 * seek permission of the copyright holders first. Commercial use includes
 * chwing money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#pragma once

// Define the max of each type
#define BYTE_MAX				255
#define HWORD_MAX				65535
#define WORD_MAX				4294967295
#define DWORD_MAX				18446744073709551615

// define some useful size in the ROM
#define ROM_HEADER_SIZE			0x1000
#define ROM_BOOT_CODE_SIZE		1008

// define the virtual address of the rdram registers
#define RDRAM_CONFIG_REG		0x03F00000
#define RDRAM_DEVICE_ID_REG     0x03F00004
#define RDRAM_DELAY_REG			0x03F00008
#define RDRAM_MODE_REG			0x03F0000C
#define RDRAM_REF_INTERVAL_REG	0x03F00010
#define RDRAM_REF_ROW_REG		0x03F00014
#define RDRAM_RAS_INTERVAL_REG	0x03F00018
#define RDRAM_MIN_INTERVAL_REG	0x03F0001C
#define RDRAM_ADDR_SELECT_REG	0x03F00020
#define RDRAM_DEVICE_MANUF_REG	0x03F00024

// define the virtual address of the sp registers
#define SP_DMEM					0x04000000
#define SP_IMEM					0x04001000
#define SP_MEM_ADDR_REG			0x04040000
#define SP_DRAM_ADDR_REG        0x04040004
#define SP_RD_LEN_REG			0x04040008
#define SP_WR_LEN_REG			0x0404000C
#define SP_STATUS_REG			0x04040010
#define SP_DMA_FULL_REG			0x04040014
#define SP_DMA_BUSY_REG			0x04040018
#define SP_SEMAPHORE_REG		0x0404001C
#define SP_PC_REG				0x04080000
#define SP_IBIST_REG			0x04080004

//define the virtual address of the dpc registers
#define DPC_START_REG			0x04100000
#define DPC_END_REG				0x04100004
#define DPC_CURRENT_REG			0x04100008
#define DPC_STATUS_REG			0x0410000C
#define DPC_CLOCK_REG			0x04100010
#define DPC_BUFBUSY_REG			0x04100014
#define DPC_PIPEBUSY_REG		0x04100018
#define DPC_TMEM_REG			0x0410001C

//define the virtual address of the dps registers
#define DPS_TBIST_REG			0x04200000
#define DPS_TEST_MODE_REG		0x04200004
#define DPS_BUFTEST_ADDR_REG	0x04200008
#define DPS_BUFTEST_DATA_REG	0x0420000C

//define the virtual address of the mi registers
#define MI_INIT_MODE_REG		0x04300000
#define MI_VERSION_REG			0x04300004
#define MI_INTR_REG				0x04300008
#define MI_INTR_MASK_REG		0x0430000C

//define the virtual address of the vi registers
#define VI_STATUS_REG			0x04400000
#define VI_ORIGIN_REG			0x04400004
#define VI_WIDTH_REG			0x04400008
#define VI_INTR_REG				0x0440000C
#define VI_CURRENT_REG			0x04400010
#define VI_BURST_REG			0x04400014
#define VI_V_SYNC_REG			0x04400018
#define VI_H_SYNC_REG			0x0440001C
#define VI_LEAP_REG				0x04400020
#define VI_H_START_REG			0x04400024
#define VI_V_START_REG			0x04400028
#define VI_V_BURST_REG			0x0440002C
#define VI_X_SCALE_REG			0x04400030
#define VI_Y_SCALE_REG			0x04400034

//define the virtual address of the ai registers
#define AI_DRAM_ADDR_REG		0x04500000
#define AI_LEN_REG				0x04500004
#define AI_CONTROL_REG			0x04500008
#define AI_STATUS_REG			0x0450000C
#define AI_DACRATE_REG			0x04500010
#define AI_BITRATE_REG			0x04500014

//define the virtual address of the pi registers
#define PI_DRAM_ADDR_REG		0x04600000
#define PI_CART_ADDR_REG		0x04600004
#define PI_RD_LEN_REG			0x04600008
#define PI_WR_LEN_REG			0x0460000C
#define PI_STATUS_REG			0x04600010
#define PI_BSD_DOM1_LAT_REG		0x04600014
#define PI_BSD_DOM1_PWD_REG		0x04600018
#define PI_BSD_DOM1_PGS_REG		0x0460001C
#define PI_BSD_DOM1_RLS_REG		0x04600020
#define PI_BSD_DOM2_LAT_REG		0x04600024
#define PI_BSD_DOM2_PWD_REG		0x04600028
#define PI_BSD_DOM2_PGS_REG		0x0460002C
#define PI_BSD_DOM2_RLS_REG		0x04600030

//define the virtual address of the ri registers
#define RI_MODE_REG				0x04700000
#define RI_CONFIG_REG			0x04700004
#define RI_CURRENT_LOAD_REG		0x04700008
#define RI_SELECT_REG			0x0470000C
#define RI_REFRESH_REG			0x04700010
#define RI_LATENCY_REG			0x04700014
#define RI_RERROR_REG			0x04700018
#define RI_WERROR_REG			0x0470001C

//define the virtual address of the si registers
#define SI_DRAM_ADDR_REG		0x04800000
#define SI_PIF_ADDR_RD64B_REG	0x04800004
#define SI_PIF_ADDR_WR64B_REG	0x04800010
#define SI_STATUS_REG			0x04800018

//define the virtual address of the ROM registerss
#define INIT_BSD_DOM1_LAT_REG	0x10000000
#define INIT_BSD_DOM1_PWD_REG	0x10000001
#define INIT_BSD_DOM1_PGS_REG	0x10000002
#define INIT_BSD_DOM1_RLS_REG	0x10000003
#define CLOCK_RATE				0x10000004
#define BOOT_ADDRESS_OFFSET		0x10000008
#define RELEASE_OFFSET			0x1000000C
#define CRC1					0x10000010
#define CRC2					0x10000014
#define IMAGE_NAME				0x10000020
#define MANUFACTURER_ID			0x1000003B
#define CARTRIDGE_ID			0x1000003C
#define COUNTRY_CODE			0x1000003E

//define the virtual address of the kind of memory store
#define KSEG0					0x80000000
#define KSEG1					0xA0000000
#define KSEG2					0xC0000000
#define KSEG3					0xE0000000

//define the state in which can be the status register of si
#define	SI_STATUS_DMA_BUSY		0x0001
#define	SI_STATUS_RD_BUSY		0x0002
#define	SI_STATUS_DMA_ERROR		0x0008
#define	SI_STATUS_INTERRUPT		0x1000

//define the state in which can be the status register of pi
#define	PI_STATUS_DMA_BUSY		0x01
#define	PI_STATUS_IO_BUSY		0x02
#define	PI_STATUS_ERROR			0x04

//define the state in which can be the status register of sp
#define SP_STATUS_HALT			0x001
#define SP_STATUS_BROKE			0x002
#define SP_STATUS_DMA_BUSY		0x004
#define SP_STATUS_DMA_FULL		0x008
#define SP_STATUS_IO_FULL		0x010
#define SP_STATUS_SSTEP			0x020
#define SP_STATUS_INTR_BREAK	0x040
#define SP_STATUS_SIG0			0x080
#define SP_STATUS_SIG1			0x100
#define SP_STATUS_SIG2			0x200
#define SP_STATUS_SIG3			0x400
#define SP_STATUS_SIG4			0x800
#define SP_STATUS_SIG5	       0x1000
#define SP_STATUS_SIG6	       0x2000
#define SP_STATUS_SIG7	       0x4000

//define the what bit do what for updating the status register of sp
#define SP_CLR_HALT				0x00001
#define SP_SET_HALT				0x00002
#define SP_CLR_BROKE			0x00004
#define SP_CLR_INTR				0x00008
#define SP_SET_INTR				0x00010
#define SP_CLR_SSTEP			0x00020
#define SP_SET_SSTEP			0x00040
#define SP_CLR_INTR_BREAK		0x00080
#define SP_SET_INTR_BREAK		0x00100
#define SP_CLR_SIG0				0x00200
#define SP_SET_SIG0				0x00400
#define SP_CLR_SIG1				0x00800
#define SP_SET_SIG1				0x01000
#define SP_CLR_SIG2				0x02000
#define SP_SET_SIG2				0x04000
#define SP_CLR_SIG3				0x08000
#define SP_SET_SIG3				0x10000
#define SP_CLR_SIG4				0x20000
#define SP_SET_SIG4				0x40000	
#define SP_CLR_SIG5				0x80000
#define SP_SET_SIG5				0x100000
#define SP_CLR_SIG6				0x200000
#define SP_SET_SIG6				0x400000
#define SP_CLR_SIG7				0x800000
#define SP_SET_SIG7				0x1000000

//define the state in which can be the status register of sp
#define SP_STATUS_HALT			0x001
#define SP_STATUS_BROKE			0x002
#define SP_STATUS_DMA_BUSY		0x004
#define SP_STATUS_DMA_FULL		0x008
#define SP_STATUS_IO_FULL		0x010
#define SP_STATUS_SSTEP			0x020
#define SP_STATUS_INTR_BREAK	0x040
#define SP_STATUS_SIG0			0x080
#define SP_STATUS_SIG1			0x100
#define SP_STATUS_SIG2			0x200
#define SP_STATUS_SIG3			0x400
#define SP_STATUS_SIG4			0x800
#define SP_STATUS_SIG5	       0x1000
#define SP_STATUS_SIG6	       0x2000
#define SP_STATUS_SIG7	       0x4000

//define the what bit do what for updating the status register of dpc
#define DPC_CLR_XBUS_DMEM_DMA	0x0001
#define DPC_SET_XBUS_DMEM_DMA	0x0002
#define DPC_CLR_FREEZE			0x0004
#define DPC_SET_FREEZE			0x0008
#define DPC_CLR_FLUSH			0x0010
#define DPC_SET_FLUSH			0x0020
#define DPC_CLR_TMEM_CTR		0x0040
#define DPC_CLR_PIPE_CTR		0x0080
#define DPC_CLR_CMD_CTR			0x0100
#define DPC_CLR_CLOCK_CTR		0x0200

//define the what bit do what for updating the status register of sp
#define DPC_STATUS_XBUS_DMEM_DMA	0x001
#define DPC_STATUS_FREEZE			0x002
#define DPC_STATUS_FLUSH			0x004
#define DPC_STATUS_START_GCLK		0x008
#define DPC_STATUS_TMEM_BUSY		0x010
#define DPC_STATUS_PIPE_BUSY		0x020
#define DPC_STATUS_CMD_BUSY			0x040
#define DPC_STATUS_CBUF_READY		0x080
#define DPC_STATUS_DMA_BUSY			0x100
#define DPC_STATUS_END_VALID		0x200
#define DPC_STATUS_START_VALID		0x400

//define the what bit do what for updating the status register of mi
#define MI_CLR_INIT				0x0080
#define MI_SET_INIT				0x0100
#define MI_CLR_EBUS				0x0200
#define MI_SET_EBUS				0x0400
#define MI_CLR_DP_INTR			0x0800
#define MI_CLR_RDRAM			0x1000
#define MI_SET_RDRAM			0x2000

//define the what bit do what for updating the mode register of mi
#define MI_MODE_INIT			0x0080
#define MI_MODE_EBUS			0x0100
#define MI_MODE_RDRAM			0x0200

//define the what bit do what for updating the interrupt register of mi
#define MI_INTR_MASK_CLR_SP		0x0001
#define MI_INTR_MASK_SET_SP		0x0002
#define MI_INTR_MASK_CLR_SI		0x0004
#define MI_INTR_MASK_SET_SI		0x0008
#define MI_INTR_MASK_CLR_AI		0x0010
#define MI_INTR_MASK_SET_AI		0x0020
#define MI_INTR_MASK_CLR_VI		0x0040
#define MI_INTR_MASK_SET_VI		0x0080
#define MI_INTR_MASK_CLR_PI		0x0100
#define MI_INTR_MASK_SET_PI		0x0200
#define MI_INTR_MASK_CLR_DP		0x0400
#define MI_INTR_MASK_SET_DP		0x0800

//define the what bit do what for updating the interrupt mask register of mi
#define MI_INTR_MASK_SP			0x01
#define MI_INTR_MASK_SI			0x02
#define MI_INTR_MASK_AI			0x04
#define MI_INTR_MASK_VI			0x08
#define MI_INTR_MASK_PI			0x10
#define MI_INTR_MASK_DP			0x20

//define the what bit do what for updating the interrupt register of mi
#define MI_INTR_SP				0x01
#define MI_INTR_SI				0x02
#define MI_INTR_AI				0x04
#define MI_INTR_VI				0x08
#define MI_INTR_PI				0x10
#define MI_INTR_DP				0x20

//define the what bit do what for updating the status register of pi
#define	PI_SET_RESET			0x01
#define	PI_CLR_INTR				0x02

typedef unsigned __int8			byte;
typedef unsigned __int16		hword;
typedef unsigned __int32		word;
typedef unsigned __int64		dword;

typedef __int8					sbyte;
typedef __int16					shword;
typedef __int32					sword;
typedef __int64					sdword;

typedef float					s; // Single-Precision	Floating-Point Format:	[31:sign;30-23-exponent;22-0:fraction]
typedef double					d; // Double-Precision	Floating-Point Format:	[63:sign;62-52:exponent;51-0:fraction]
typedef long					w; // Word				Fixed-Point Format:		[31:sign;30-0:int]
typedef long long int			l; // Longword			Fixed-Point Format:		[63:sign;62-0:int]

//****************************************************************************
//** MEMORY SEGMENT															**
//****************************************************************************
class MEM_SEG
{
public:
	MEM_SEG();
	static const word begining;
	static const word end;
	const char *ptr;
	char* operator[] (const dword address) const;
};

//****************************************************************************
//** ROM																	**
//****************************************************************************

class ROM : public MEM_SEG
{
public:
	ROM(string);
	~ROM();
	static const word begining = 0x10000000;
	static const word end = 0x1FBFFFFF;

	inline word		getClock();
	inline word		getPc();
	inline word		getRelease();
	inline word		getCRC1();
	inline word		getCRC2();
	inline string	getName();
	inline word		getManufacturer();
	inline hword	getCartridge();
	inline hword	getCountry();

private:
	ifstream	file;
	char		*data;

	typedef struct {
	   byte		pi_bsd_dom1_lat;
	   byte		pi_bsd_dom1_pwd;
	   byte		pi_bsd_dom1_pgs;
	   byte		pi_bsd_dom1_rls;
	   word		clock;
	   word		pc;
	   word		release;
	   word		crc1;
	   word		crc2;
	   word		Unknown[2];
	   byte		name[20];
	   word		unknown;
	   word		manufacturer;
	   hword	cartridge;
	   hword	country;
	   word		bootcode[ROM_BOOT_CODE_SIZE];
	} ROM_HEADER;

	ROM_HEADER	*header;
};

//****************************************************************************
//** RDRAM																	**
//****************************************************************************

class RDRAM : public MEM_SEG
{
public:
	RDRAM();
	static const word begining = 0x00000000;
	static const word end = 0x03EFFFFF;
	static const int size = 0x800000;
private:
	byte data[size];
};

//****************************************************************************
//** RDRAM Registers														**
//****************************************************************************

class RDRAM_REGS : public MEM_SEG
{
public:
	RDRAM_REGS();
	static const word begining = 0x03F00000;
	static const word end = 0x03FFFFFF;

	inline word getConfig();
	inline void setConfig(word);
	inline word getDeviceId();
	inline void setDeviceId(word);
	inline word getDelay();
	inline void setDelay(word);
	inline word getMode();
	inline void setMode(word);
	inline word getRefInterval();
	inline void setRefInterval(word);
	inline word getRefRow();
	inline void setRefRow(word);
	inline word getRasInterval();
	inline void setRasInterval(word);
	inline word getMinInterval();
	inline void setMinInterval(word);
	inline word getAddrSelect();
	inline void setAddrSelect(word);
	inline word getDeviceManuf();
	inline void setDeviceManuf(word);

private:
	struct {
		word config;
		word device_id;
		word delay;
		word mode;
		word ref_interval;
		word ref_row;
		word ras_interval;
		word min_interval;
		word addr_select;
		word device_manuf;
		byte unknown[0xFFFD8];
	} data;
};

//****************************************************************************
//** SP Registers															**
//****************************************************************************

class SP_REGS : public MEM_SEG
{
public:
	SP_REGS();
	static const word begining = 0x04000000;
	static const word end = 0x040FFFFF;

	//contains the instruction of the RSP
	inline byte *getDmem();
	inline byte *getImem();

	inline word getMemAddr();
	inline void setMemAddr(word);
	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getRdLen();
	inline void setRdLen(word);
	inline word getWrLen();
	inline void setWrLen(word);
	inline word getStatus();
	inline void setStatus(word);
	inline word getDmaFull();
	inline void setDmaFull(word);
	inline word getDmaBusy();
	inline void setDmaBusy(word);
	inline word getSemaphore();
	inline void setSemaphore(word);
	inline word getPc();
	inline void setPc(word);
	inline word getIbist();
	inline void setIbist(word);
	
private:
	struct {
		byte dmem[0x1000];
		byte imem[0x1000];
		byte unused[0x3E000];
		word mem_addr;
		word dram_addr;
		word rd_len;
		word wr_len;
		word status;
		word dma_full;
		word dma_busy;
		word semaphore;
		byte unused2[0x3FFE0];
		word pc;
		word ibist;
		byte unused3[0x7FFF8];
	} data;
};

//****************************************************************************
//** DP Command Registers													**
//****************************************************************************

class DPC_REGS : public MEM_SEG
{
public:
	DPC_REGS();
	static const word begining = 0x04100000;
	static const word end = 0x041FFFFF;

	inline word getStart();
	inline void setStart(word);
	inline word getEnd();
	inline void setEnd(word);
	inline word getCurrent();
	inline void setCurrent(word);
	inline word getStatus();
	inline void setStatus(word);
	inline word getClock();
	inline void setClock(word);
	inline word getBufBusy();
	inline void setBufBusy(word);
	inline word getPipeBusy();
	inline void setPipeBusy(word);
	inline word getTmem();
	inline void setTmem(word);

private:
	struct {
		word start;
		word end;
		word current;
		word status;
		word clock;
		word bufbusy;
		word pipebusy;
		word tmem;
		byte unused[0xFFFE0];
	} data;
};

//****************************************************************************
//** DP Span Registers														**
//****************************************************************************

class DPS_REGS : public MEM_SEG
{
public:
	DPS_REGS();
	static const word begining = 0x04200000;
	static const word end = 0x042FFFFF;

	inline word getTbist();
	inline void setTbist(word);
	inline word getTestMode();
	inline void setTestMode(word);
	inline word getBufTestAddr();
	inline void setBufTestAddr(word);
	inline word getBufTestData();
	inline void setBufTestData(word);

private:
	struct	{
		word tbist;
		word test_mode;
		word buftest_addr;
		word buftest_data;
		byte unused[0xFFFF0];
	} data;
};

//****************************************************************************
//** MIPS Interface (MI) Registers											**
//****************************************************************************

class MI_REGS : public MEM_SEG
{
public:
	MI_REGS();
	static const word begining = 0x04300000;
	static const word end = 0x043FFFFF;

	inline word getInitMode();
	inline void setInitMode(word);
	inline word getVersion();
	inline void setVersion(word);
	inline word getIntr();
	inline void setIntr(word);
	inline word getIntrMask();
	inline void setIntrMask(word);

private:
	struct	{
		word init_mode;
		word version;
		word intr;
		word intr_mask;
		byte unused[0xFFFF0];
	} data;
};

//****************************************************************************
//** Video Interface (VI) Registers											**
//****************************************************************************

class VI_REGS : public MEM_SEG
{
public:
	VI_REGS();
	static const word begining = 0x04400000;
	static const word end = 0x044FFFFF;

	inline word getStatus();
	inline void setStatus(word);
	inline word getOrigin();
	inline void setOrigin(word);
	inline word getWidth();
	inline void setWidth(word);
	inline word getIntr();
	inline void setVintr(word);
	inline word getCurrent();
	inline void setCurrent(word);
	inline word getBurst();
	inline void setBurst(word);
	inline word getVsync();
	inline void setVsync(word);
	inline word getHsync();
	inline void setHsync(word);
	inline word getLeap();
	inline void setLeap(word);
	inline word getHstart();
	inline void setHstart(word);
	inline word getVstart();
	inline void setVstart(word);
	inline word getVburst();
	inline void setVburst(word);
	inline word getXscale();
	inline void setXscale(word);
	inline word getYscale();
	inline void setYscale(word);

private:
	struct	{
		word status;
		word origin;
		word width;
		word intr;
		word current;
		word burst;
		word v_sync;
		word h_sync;
		word leap;
		word h_start;
		word v_start;
		word v_burst;
		word x_scale;
		word y_scale;
		byte unused[0xFFFC8];
	} data;
};

//****************************************************************************
//** Audio Interface (AI) Registers											**
//****************************************************************************

class AI_REGS : public MEM_SEG
{
public:
	AI_REGS();
	static const word begining = 0x04500000;
	static const word end = 0x045FFFFF;

	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getLen();
	inline void setLen(word);
	inline word getControl();
	inline void setControl(word);
	inline word getStatus();
	inline void setStatus(word);
	inline word getDacrate();
	inline void setDacrate(word);
	inline word getBitrate();
	inline void setBitrate(word);

private:
	struct	{
		word dram_addr;
		word len;
		word control;
		word status;
		word dacrate;
		word bitrate;
		byte unused[0xFFFE8];
	} data;
};

//****************************************************************************
//** Peripheral Interface (PI) Registers									**
//****************************************************************************

class PI_REGS : public MEM_SEG
{
public:
	PI_REGS();
	static const word begining = 0x04600000;
	static const word end = 0x046FFFFF;

	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getCartAddr();
	inline void setCartAddr(word);
	inline word getRdLen();
	inline void setRdLen(word);
	inline word getWrLen();
	inline void setWrLen(word);
	inline word getStatus();
	inline void setStatus(word);
	inline word getBsdDom1Lat();
	inline void setBsdDom1Lat(word);
	inline word getBsdDom1Pwd();
	inline void setBsdDom1Pwd(word);
	inline word getBsdDom1Pgs();
	inline void setBsdDom1Pgs(word);
	inline word getBsdDom1Rls();
	inline void setBsdDom1Rls(word);
	inline word getBsdDom2Lat();
	inline void setBsdDom2Lat(word);
	inline word getBsdDom2Pwd();
	inline void setBsdDom2Pwd(word);
	inline word getBsdDom2Pgs();
	inline void setBsdDom2Pgs(word);
	inline word getBsdDom2Rls();
	inline void setBsdDom2Rls(word);

private:
	struct	{
		word dram_addr;
		word cart_addr;
		word rd_len;
		word wr_len;
		word status;
		word bsd_dom1_lat;
		word bsd_dom1_pwd;
		word bsd_dom1_pgs;
		word bsd_dom1_rls;
		word bsd_dom2_lat;
		word bsd_dom2_pwd;
		word bsd_dom2_pgs;
		word bsd_dom2_rls;
		byte unused[0xFFFCC];
	} data;
};

//****************************************************************************
//** RDRAM Interface (RI) Registers											**
//****************************************************************************

class RI_REGS : public MEM_SEG
{
public:
	RI_REGS();
	static const word begining = 0x04700000;
	static const word end = 0x047FFFFF;

	inline word getMode();
	inline void setMode(word);
	inline word getConfig();
	inline void setConfig(word);
	inline word getCurrentLoad();
	inline void setCurrentLoad(word);
	inline word getSelect();
	inline void setSelect(word);
	inline word getRefresh();
	inline void setRefresh(word);
	inline word getLatency();
	inline void setLatency(word);
	inline word getRerror();
	inline void setRerror(word);
	inline word getWerror();
	inline void setWerror(word);

private:
	struct	{
		word mode;
		word config;
		word current_load;
		word select;
		word refresh;
		word latency;
		word rerror;
		word werror;
		byte unused[0xFFFE0];
	} data;
};

//****************************************************************************
//** Serial Interface (SI) Registers										**
//****************************************************************************

class SI_REGS : public MEM_SEG
{
public:
	SI_REGS();
	static const word begining = 0x04800000;
	static const word end = 0x048FFFFF;

	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getPifAddrRd64b();
	inline void setPifAddrRd64b(word);
	inline word getPifAddrWr64b();
	inline void setPifAddrWr64b(word);
	inline word getStatus();
	inline void setStatus(word);

private:
	struct	{
		word dram_addr;
		word pif_addr_rd64b;
		word reserved;
		word reserved2;
		word pif_addr_wr64b;
		word reserved3;
		word status;
		byte unused[0xFFFE4];
	} data;
};

//****************************************************************************
//** PIF ROM																**
//****************************************************************************

class PIF_ROM : public MEM_SEG
{
public:
	PIF_ROM();
	static const word begining = 0x1FC00000;
	static const word end = 0x1FC007BF;
private:
	byte data[0x7C0];
};


//****************************************************************************
//** PIF RAM																**
//****************************************************************************

class PIF_RAM : public MEM_SEG
{
public:
	PIF_RAM();
	static const word begining = 0x1FC007C0;
	static const word end = 0x1FC007FF;
private:
	byte data[0x40];
};

//****************************************************************************
//** MEMORY					                                                **
//****************************************************************************

class R4300i;
class GFX;
class RSP;

class MEMORY
{
public:
	MEMORY(ROM* rom);

	ROM			&rom;
	RDRAM		&rdram;
	RDRAM_REGS	&rdram_regs;
	SP_REGS		&sp_regs;
	DPC_REGS	&dpc_regs;
	DPS_REGS	&dps_regs;
	MI_REGS		&mi_regs;
	VI_REGS		&vi_regs;
	AI_REGS		&ai_regs;
	PI_REGS		&pi_regs;
	RI_REGS		&ri_regs;
	SI_REGS		&si_regs;
	PIF_ROM		&pif_rom;
	PIF_RAM		&pif_ram;

	R4300i		*cpu;
	RSP			*rsp;
	GFX			*gfx;

	byte		SRAM[0x8000];
	word		cic_chip;
	bool		check_intr;

	inline void* virtual_to_physical(dword address);
	template <typename Type> inline Type read(dword address);
	template <typename Type> inline void write(Type data, dword address);

	void dma_pi_write();
	void dma_pi_read();
	void dma_si_write();
	void dma_si_read();
	void dma_sp_write();
	void dma_sp_read();

private:
	inline bool MEMORY::read_from_register(word *data, dword address);
	inline bool MEMORY::write_in_register(word data, dword address);
	inline void checkDMA(dword address);
};

