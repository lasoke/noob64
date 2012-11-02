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
 * charging money for Noob64 or software derived from Noob64.
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
	virtual void dump(void) const = 0;
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
	void dump(void) const;

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
	void dump(void) const;
	void dump_range(word from, word to) const;
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
	void dump(void) const;

	inline word getConfig()			{ return data.config; };
	inline void setConfig(word);
	inline word getDeviceId()		{ return data.device_id; };
	inline void setDeviceId(word);
	inline word getDelay()			{ return data.delay; };
	inline void setDelay(word);
	inline word getMode()			{ return data.mode; };
	inline void setMode(word);
	inline word getRefInterval()	{ return data.ref_interval; };
	inline void setRefInterval(word);
	inline word getRefRow()			{ return data.ref_row; };
	inline void setRefRow(word);
	inline word getRasInterval()	{ return data.ras_interval; };
	inline void setRasInterval(word);
	inline word getMinInterval()	{ return data.min_interval; };
	inline void setMinInterval(word);
	inline word getAddrSelect()		{ return data.addr_select; };
	inline void setAddrSelect(word);
	inline word getDeviceManuf()	{ return data.device_manuf; };
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
	void dump(void) const;
	void dump_range_dmem(word from, word to) const;
	void dump_range_imem(word from, word to) const;

	//contains the instruction of the RSP
	inline byte *getDmem()		{ return data.dmem; };
	inline byte *getImem()		{ return data.imem; };

	inline word getMemAddr()	{ return data.mem_addr; };
	inline void setMemAddr(word);
	inline word getDramAddr()	{ return data.dram_addr; };
	inline void setDramAddr(word);
	inline word getRdLen()		{ return data.rd_len; };
	inline void setRdLen(word);
	inline word getWrLen()		{ return data.wr_len; };
	inline void setWrLen(word);
	inline word getStatus()		{ return data.status; };
	inline void setStatus(word);
	inline word getDmaFull()	{ return data.dma_full; };
	inline void setDmaFull(word);
	inline word getDmaBusy()	{ return data.dma_busy; };
	inline void setDmaBusy(word);
	inline word getSemaphore()	{ return data.semaphore; };
	inline void setSemaphore(word);
	inline word getPc()			{ return data.pc; };
	inline void setPc(word);
	inline word getIbist()		{ return data.ibist; };
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
	void dump(void) const;

	inline word getStart()		{ return data.start; };
	inline void setStart(word);
	inline word getEnd()		{ return data.end; };
	inline void setEnd(word);
	inline word getCurrent()	{ return data.current; };
	inline void setCurrent(word);
	inline word getStatus()		{ return data.status; };
	inline void setStatus(word);
	inline word getClock()		{ return data.clock; };
	inline void setClock(word);
	inline word getBufBusy()	{ return data.bufbusy; };
	inline void setBufBusy(word);
	inline word getPipeBusy()	{ return data.pipebusy; };
	inline void setPipeBusy(word);
	inline word getTmem()		{ return data.tmem; };
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
	void dump(void) const;

	inline word getTbist()			{ return data.tbist; };
	inline void setTbist(word);
	inline word getTestMode()		{ return data.test_mode; };
	inline void setTestMode(word);
	inline word getBufTestAddr()	{ return data.buftest_addr; };
	inline void setBufTestAddr(word);
	inline word getBufTestData()	{ return data.buftest_data; };
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
	void dump(void) const;

	inline word getInitMode()	{ return data.init_mode; };
	inline void setInitMode(word);
	inline word getVersion()	{ return data.version; };
	inline void setVersion(word);
	inline word getIntr()		{ return data.intr; };
	inline void setIntr(word);
	inline word getIntrMask()	{ return data.intr_mask; };
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
	void dump(void) const;

	inline word getStatus()		{ return data.status; };
	inline void setStatus(word);
	inline word getOrigin()		{ return data.origin; };
	inline void setOrigin(word);
	inline word getWidth()		{ return data.width; };
	inline void setWidth(word);
	inline word getIntr()		{ return data.intr; };
	inline void setVintr(word);
	inline word getCurrent()	{ return data.current; };
	inline void setCurrent(word);
	inline word getBurst()		{ return data.burst; };
	inline void setBurst(word);
	inline word getVsync()		{ return data.v_sync; };
	inline void setVsync(word);
	inline word getHsync()		{ return data.h_sync; };
	inline void setHsync(word);
	inline word getLeap()		{ return data.leap; };
	inline void setLeap(word);
	inline word getHstart()		{ return data.h_start; };
	inline void setHstart(word);
	inline word getVstart()		{ return data.v_start; };
	inline void setVstart(word);
	inline word getVburst()		{ return data.v_burst; };
	inline void setVburst(word);
	inline word getXscale()		{ return data.x_scale; };
	inline void setXscale(word);
	inline word getYscale()		{ return data.y_scale; };
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
	void dump(void) const;

	inline word getDramAddr()	{ return data.dram_addr; };
	inline void setDramAddr(word);
	inline word getLen()		{ return data.len; };
	inline void setLen(word);
	inline word getControl()	{ return data.control; };
	inline void setControl(word);
	inline word getStatus()		{ return data.status; };
	inline void setStatus(word);
	inline word getDacrate()	{ return data.dacrate; };
	inline void setDacrate(word);
	inline word getBitrate()	{ return data.bitrate; };
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
	void dump(void) const;

		inline word getDramAddr()	{ return data.dram_addr; };
		inline void setDramAddr(word);
		inline word getCartAddr()	{ return data.cart_addr; };
		inline void setCartAddr(word);
		inline word getRdLen()		{ return data.rd_len; };
		inline void setRdLen(word);
		inline word getWrLen()		{ return data.wr_len; };
		inline void setWrLen(word);
		inline word getStatus()		{ return data.status; };
		inline void setStatus(word);
		inline word getBsdDom1Lat()	{ return data.bsd_dom1_lat; };
		inline void setBsdDom1Lat(word);
		inline word getBsdDom1Pwd()	{ return data.bsd_dom1_pwd; };
		inline void setBsdDom1Pwd(word);
		inline word getBsdDom1Pgs()	{ return data.bsd_dom1_pgs; };
		inline void setBsdDom1Pgs(word);
		inline word getBsdDom1Rls()	{ return data.bsd_dom1_rls; };
		inline void setBsdDom1Rls(word);
		inline word getBsdDom2Lat()	{ return data.bsd_dom2_lat; };
		inline void setBsdDom2Lat(word);
		inline word getBsdDom2Pwd()	{ return data.bsd_dom2_pwd; };
		inline void setBsdDom2Pwd(word);
		inline word getBsdDom2Pgs()	{ return data.bsd_dom2_pgs; };
		inline void setBsdDom2Pgs(word);
		inline word getBsdDom2Rls()	{ return data.bsd_dom2_rls; };
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
	void dump(void) const;

		inline word getMode()			{ return data.mode; };
		inline void setMode(word);
		inline word getConfig()			{ return data.config; };
		inline void setConfig(word);
		inline word getCurrentLoad()	{ return data.current_load; };
		inline void setCurrentLoad(word);
		inline word getSelect()			{ return data.select; };
		inline void setSelect(word);
		inline word getRefresh()		{ return data.refresh; };
		inline void setRefresh(word);
		inline word getLatency()		{ return data.latency; };
		inline void setLatency(word);
		inline word getRerror()			{ return data.rerror; };
		inline void setRerror(word);
		inline word getWerror()			{ return data.werror; };
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
	void dump(void) const;

	inline word getDramAddr()		{ return data.dram_addr; };
	inline void setDramAddr(word);
	inline word getPifAddrRd64b()	{ return data.pif_addr_rd64b; };
	inline void setPifAddrRd64b(word);
	inline word getPifAddrWr64b()	{ return data.pif_addr_wr64b; };
	inline void setPifAddrWr64b(word);
	inline word getStatus()			{ return data.status; };
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
//** Serial Interface (SI) Registers										**
//****************************************************************************

class PIF_ROM : public MEM_SEG
{
public:
	PIF_ROM();
	static const word begining = 0x1FC00000;
	static const word end = 0x1FC007BF;
	void dump(void) const;

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
	void dump(void) const;

private:
	byte data[0x40];
};

//****************************************************************************
//** MEMORY					                                                **
//****************************************************************************

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

//****************************************************************************
//** MEMORY::READ															**
//****************************************************************************
template <typename Type>
Type MEMORY::read(dword address)
{
	Type res;
	if (typeid(Type) == typeid(word) && read_from_register((word *) &res, address))
		return res;
	byte dst[sizeof(Type)];
	memcpy(dst, virtual_to_physical(address), sizeof(Type));
	res = binary_to_type<Type>(dst);
	return res;
}

// Get the value contains in the registes
inline bool MEMORY::read_from_register(word *data, dword address)
{
	address &= 0x0FFFFFFF;
	if (address == RDRAM_CONFIG_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_DEVICE_ID_REG)
		*data = rdram_regs.getDeviceId();
	else if (address == RDRAM_DELAY_REG)
		*data = rdram_regs.getDelay();
	else if (address == RDRAM_MODE_REG)
		*data = rdram_regs.getMode();
	else if (address == RDRAM_REF_INTERVAL_REG)
		*data = rdram_regs.getRefInterval();
	else if (address == RDRAM_REF_ROW_REG)
		*data = rdram_regs.getRefRow();
	else if (address == RDRAM_RAS_INTERVAL_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_MIN_INTERVAL_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_ADDR_SELECT_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_DEVICE_MANUF_REG)
		*data = rdram_regs.getConfig();

	else if (address == SP_MEM_ADDR_REG)
		*data = sp_regs.getMemAddr();
	else if (address == SP_DRAM_ADDR_REG)
		*data = sp_regs.getDramAddr();
	else if (address == SP_RD_LEN_REG)
		*data = sp_regs.getRdLen();
	else if (address == SP_WR_LEN_REG)
		*data = sp_regs.getWrLen();
	else if (address == SP_STATUS_REG)
		*data = sp_regs.getStatus();
	else if (address == SP_DMA_FULL_REG)
		*data = sp_regs.getDmaFull();
	else if (address == SP_DMA_BUSY_REG)
		*data = sp_regs.getDmaBusy();
	else if (address == SP_SEMAPHORE_REG)
		*data = sp_regs.getSemaphore();
	else if (address == SP_PC_REG)
		*data = sp_regs.getPc();
	else if (address == SP_IBIST_REG)
		*data = sp_regs.getIbist();

	else if (address == DPC_START_REG)
		*data = dpc_regs.getStart();
	else if (address == DPC_END_REG)
		*data = dpc_regs.getEnd();
	else if (address == DPC_CURRENT_REG)
		*data = dpc_regs.getCurrent();
	else if (address == DPC_STATUS_REG)
		*data = dpc_regs.getStatus();
	else if (address == DPC_CLOCK_REG)
		*data = dpc_regs.getClock();
	else if (address == DPC_BUFBUSY_REG)
		*data = dpc_regs.getBufBusy();
	else if (address == DPC_PIPEBUSY_REG)
		*data = dpc_regs.getPipeBusy();
	else if (address == DPC_TMEM_REG)
		*data = dpc_regs.getTmem();

	else if (address == DPS_TBIST_REG)
		*data = dps_regs.getTbist();
	else if (address == DPS_TEST_MODE_REG)
		*data = dps_regs.getTestMode();
	else if (address == DPS_BUFTEST_ADDR_REG)
		*data = dps_regs.getBufTestAddr();
	else if (address == DPS_BUFTEST_DATA_REG)
		*data = dps_regs.getBufTestData();

	else if (address == MI_INIT_MODE_REG)
		*data = mi_regs.getInitMode();
	else if (address == MI_VERSION_REG)
		*data = mi_regs.getVersion();
	else if (address == MI_INTR_REG)
		*data = mi_regs.getIntr();
	else if (address == MI_INTR_MASK_REG)
		*data = mi_regs.getIntrMask();

	else if (address == VI_STATUS_REG)
		*data = vi_regs.getStatus();
	else if (address == VI_ORIGIN_REG)
		*data = vi_regs.getOrigin();
	else if (address == VI_WIDTH_REG)
		*data = vi_regs.getWidth();
	else if (address == VI_INTR_REG)
		*data = vi_regs.getIntr();
	else if (address == VI_CURRENT_REG)
	{
		*data = vi_regs.getCurrent();
		//UpdateCurrentHalfLine();
	}
	else if (address == VI_BURST_REG)
		*data = vi_regs.getBurst();
	else if (address == VI_V_SYNC_REG)
		*data = vi_regs.getVsync();
	else if (address == VI_H_SYNC_REG)
		*data = vi_regs.getHsync();
	else if (address == VI_LEAP_REG)
		*data = vi_regs.getLeap();
	else if (address == VI_H_START_REG)
		*data = vi_regs.getHstart();
	else if (address == VI_V_START_REG)
		*data = vi_regs.getVstart();
	else if (address == VI_V_BURST_REG)
		*data = vi_regs.getVburst();
	else if (address == VI_X_SCALE_REG)
		*data = vi_regs.getXscale();
	else if (address == VI_Y_SCALE_REG)
		*data = vi_regs.getYscale();

	else if (address == AI_DRAM_ADDR_REG)
		*data = ai_regs.getDramAddr();
	else if (address == AI_LEN_REG)
	{
		*data = ai_regs.getLen();
		//res = AiReadLength();
	}
	else if (address == AI_CONTROL_REG)
		*data = ai_regs.getControl();
	else if (address == AI_STATUS_REG)
		*data = ai_regs.getStatus();
	else if (address == AI_DACRATE_REG)
		*data = ai_regs.getDacrate();
	else if (address == AI_BITRATE_REG)
		*data = ai_regs.getBitrate();

	else if (address == PI_DRAM_ADDR_REG)
		*data = pi_regs.getDramAddr();
	else if (address == PI_CART_ADDR_REG)
		*data = pi_regs.getCartAddr();
	else if (address == PI_RD_LEN_REG)
		*data = pi_regs.getRdLen();
	else if (address == PI_WR_LEN_REG)
		*data = pi_regs.getWrLen();
	else if (address == PI_STATUS_REG)
		*data = pi_regs.getStatus();
	else if (address == PI_BSD_DOM1_LAT_REG)
		*data = pi_regs.getBsdDom1Lat();
	else if (address == PI_BSD_DOM1_PWD_REG)
		*data = pi_regs.getBsdDom1Pwd();
	else if (address == PI_BSD_DOM1_PGS_REG)
		*data = pi_regs.getBsdDom1Pgs();
	else if (address == PI_BSD_DOM1_RLS_REG)
		*data = pi_regs.getBsdDom1Rls();
	else if (address == PI_BSD_DOM2_LAT_REG)
		*data = pi_regs.getBsdDom2Lat();
	else if (address == PI_BSD_DOM2_PWD_REG)
		*data = pi_regs.getBsdDom2Pwd();
	else if (address == PI_BSD_DOM2_PGS_REG)
		*data = pi_regs.getBsdDom2Pgs();
	else if (address == PI_BSD_DOM2_RLS_REG)
		*data = pi_regs.getBsdDom2Rls();

	else if (address == RI_MODE_REG)
		*data = ri_regs.getMode();
	else if (address == RI_CONFIG_REG)
		*data = ri_regs.getConfig();
	else if (address == RI_CURRENT_LOAD_REG)
		*data = ri_regs.getCurrentLoad();
	else if (address == RI_SELECT_REG)
		*data = ri_regs.getSelect();
	else if (address == RI_REFRESH_REG)
		*data = ri_regs.getRefresh();
	else if (address == RI_LATENCY_REG)
		*data = ri_regs.getLatency();
	else if (address == RI_RERROR_REG)
		*data = ri_regs.getRerror();
	else if (address == RI_WERROR_REG)
		*data = ri_regs.getWerror();

	else if (address == SI_DRAM_ADDR_REG)
		*data = si_regs.getDramAddr();
	else if (address == SI_PIF_ADDR_RD64B_REG)
		*data = si_regs.getPifAddrRd64b();
	else if (address == SI_PIF_ADDR_WR64B_REG)
		*data = si_regs.getPifAddrWr64b();
	else if (address == SI_STATUS_REG)
		*data = si_regs.getStatus();
	else
		return false;
	return true;
}

//****************************************************************************
//** MEMORY::WRITE															**
//****************************************************************************
template <typename Type>
inline void MEMORY::write(Type data, dword address)
{
	if (typeid(Type) == typeid(word) && write_in_register((word) data, address))
		return;

	void *dst = virtual_to_physical(address);
	data = type_to_binary<Type>(data);
	memcpy(dst, &data, sizeof(Type));
}

// Set the value of the registers
inline bool MEMORY::write_in_register(word data, dword address)
{
	address &= 0x0FFFFFFF;
	if (address == RDRAM_CONFIG_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_DEVICE_ID_REG)
		rdram_regs.setDeviceId(data);
	else if (address == RDRAM_DELAY_REG)
		rdram_regs.setDelay(data);
	else if (address == RDRAM_MODE_REG)
		rdram_regs.setMode(data);
	else if (address == RDRAM_REF_INTERVAL_REG)
		rdram_regs.setRefInterval(data);
	else if (address == RDRAM_REF_ROW_REG)
		rdram_regs.setRefRow(data);
	else if (address == RDRAM_RAS_INTERVAL_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_MIN_INTERVAL_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_ADDR_SELECT_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_DEVICE_MANUF_REG)
		rdram_regs.setConfig(data);

	else if (address == SP_MEM_ADDR_REG)
		sp_regs.setMemAddr(data);
	else if (address == SP_DRAM_ADDR_REG)
		sp_regs.setDramAddr(data);
	else if (address == SP_RD_LEN_REG)
	{
		sp_regs.setRdLen(data);
		dma_sp_read();	
		sp_regs.setDmaBusy(0);
		sp_regs.setStatus(sp_regs.getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_WR_LEN_REG)
	{
		sp_regs.setWrLen(data);
		dma_sp_write();
		sp_regs.setDmaBusy(0);
		sp_regs.setStatus(sp_regs.getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_STATUS_REG)
	{
		sp_regs.setStatus(data);
		if (data & SP_SET_SIG0) 
		{
			mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_SP);
			check_intr = true;
		}
		if (data & SP_CLR_INTR)
		{ 
			mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_SP);
			//	RunRsp();
			check_intr = true;
		}
		else
			;//	RunRsp();
	}
	else if (address == SP_DMA_FULL_REG)
		sp_regs.setDmaFull(data);
	else if (address == SP_DMA_BUSY_REG)
		sp_regs.setDmaBusy(data);
	else if (address == SP_SEMAPHORE_REG)
		sp_regs.setSemaphore(data);
	else if (address == SP_PC_REG)
		sp_regs.setPc(data);
	else if (address == SP_IBIST_REG)
		sp_regs.setIbist(data);

	else if (address == DPC_START_REG)
		dpc_regs.setStart(data);
	else if (address == DPC_END_REG)
		dpc_regs.setEnd(data);
	else if (address == DPC_CURRENT_REG)
		dpc_regs.setCurrent(data);
	else if (address == DPC_STATUS_REG)
		dpc_regs.setStatus(data);
	else if (address == DPC_CLOCK_REG)
		dpc_regs.setClock(data);
	else if (address == DPC_BUFBUSY_REG)
		dpc_regs.setBufBusy(data);
	else if (address == DPC_PIPEBUSY_REG)
		dpc_regs.setPipeBusy(data);
	else if (address == DPC_TMEM_REG)
		dpc_regs.setTmem(data);

	else if (address == DPS_TBIST_REG)
		dps_regs.setTbist(data);
	else if (address == DPS_TEST_MODE_REG)
		dps_regs.setTestMode(data);
	else if (address == DPS_BUFTEST_ADDR_REG)
		dps_regs.setBufTestAddr(data);
	else if (address == DPS_BUFTEST_DATA_REG)
		dps_regs.setBufTestData(data);

	else if (address == MI_INIT_MODE_REG)
		mi_regs.setInitMode(data);
	else if (address == MI_VERSION_REG)
		mi_regs.setVersion(data);
	else if (address == MI_INTR_REG)
		mi_regs.setIntr(data);
	else if (address == MI_INTR_MASK_REG)
		mi_regs.setIntrMask(data);

	else if (address == VI_STATUS_REG)
		vi_regs.setStatus(data);
	else if (address == VI_ORIGIN_REG)
		vi_regs.setOrigin(data);
	else if (address == VI_WIDTH_REG)
		vi_regs.setWidth(data);
	else if (address == VI_INTR_REG)
	{
		vi_regs.setVintr(data);
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_VI);
		check_intr = true;
	}
	else if (address == VI_CURRENT_REG)
		vi_regs.setCurrent(data);
	else if (address == VI_BURST_REG)
		vi_regs.setBurst(data);
	else if (address == VI_V_SYNC_REG)
		vi_regs.setVsync(data);
	else if (address == VI_H_SYNC_REG)
		vi_regs.setHsync(data);
	else if (address == VI_LEAP_REG)
		vi_regs.setLeap(data);
	else if (address == VI_H_START_REG)
		vi_regs.setHstart(data);
	else if (address == VI_V_START_REG)
		vi_regs.setVstart(data);
	else if (address == VI_V_BURST_REG)
		vi_regs.setVburst(data);
	else if (address == VI_X_SCALE_REG)
		vi_regs.setXscale(data);
	else if (address == VI_Y_SCALE_REG)
		vi_regs.setYscale(data);

	else if (address == AI_DRAM_ADDR_REG)
		ai_regs.setDramAddr(data);
	else if (address == AI_LEN_REG)
		ai_regs.setLen(data);
	else if (address == AI_CONTROL_REG)
		ai_regs.setControl(data);
	else if (address == AI_STATUS_REG)
	{
		ai_regs.setStatus(data);
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_AI);
		check_intr = true;
	}
	else if (address == AI_DACRATE_REG)
		ai_regs.setDacrate(data);
	else if (address == AI_BITRATE_REG)
		ai_regs.setBitrate(data);

	else if (address == PI_DRAM_ADDR_REG)
		pi_regs.setDramAddr(data);
	else if (address == PI_CART_ADDR_REG)
		pi_regs.setCartAddr(data);
	else if (address == PI_RD_LEN_REG)
	{
		pi_regs.setRdLen(data);
		dma_pi_read();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_PI);
		pi_regs.setStatus(pi_regs.getStatus() & ~PI_STATUS_DMA_BUSY);
		check_intr = true;
	}
	else if (address == PI_WR_LEN_REG)
	{
		pi_regs.setWrLen(data);
		dma_pi_write();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_PI);
		pi_regs.setStatus(pi_regs.getStatus() & ~PI_STATUS_DMA_BUSY);
		check_intr = true;
	}
	else if (address == PI_STATUS_REG)
	{
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_PI);
		check_intr = true;
	}
	else if (address == PI_BSD_DOM1_LAT_REG)
		pi_regs.setBsdDom1Lat(data);
	else if (address == PI_BSD_DOM1_PWD_REG)
		pi_regs.setBsdDom1Pwd(data);
	else if (address == PI_BSD_DOM1_PGS_REG)
		pi_regs.setBsdDom1Pgs(data);
	else if (address == PI_BSD_DOM1_RLS_REG)
		pi_regs.setBsdDom1Rls(data);
	else if (address == PI_BSD_DOM2_LAT_REG)
		pi_regs.setBsdDom2Lat(data);
	else if (address == PI_BSD_DOM2_PWD_REG)
		pi_regs.setBsdDom2Pwd(data);
	else if (address == PI_BSD_DOM2_PGS_REG)
		pi_regs.setBsdDom2Pgs(data);
	else if (address == PI_BSD_DOM2_RLS_REG)
		pi_regs.setBsdDom2Rls(data);

	else if (address == RI_MODE_REG)
		ri_regs.setMode(data);
	else if (address == RI_CONFIG_REG)
		ri_regs.setConfig(data);
	else if (address == RI_CURRENT_LOAD_REG)
		ri_regs.setCurrentLoad(data);
	else if (address == RI_SELECT_REG)
		ri_regs.setSelect(data);
	else if (address == RI_REFRESH_REG)
		ri_regs.setRefresh(data);
	else if (address == RI_LATENCY_REG)
		ri_regs.setLatency(data);
	else if (address == RI_RERROR_REG)
		ri_regs.setRerror(data);
	else if (address == RI_WERROR_REG)
		ri_regs.setWerror(data);

	else if (address == SI_DRAM_ADDR_REG)
		si_regs.setDramAddr(data);
	else if (address == SI_PIF_ADDR_RD64B_REG)
	{
		si_regs.setPifAddrRd64b(data);
		dma_si_read();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_SI);
		si_regs.setStatus(si_regs.getStatus() | SI_STATUS_INTERRUPT);
		check_intr = true;
	}
	else if (address == SI_PIF_ADDR_WR64B_REG)
	{
		si_regs.setPifAddrWr64b(data);
		dma_si_write();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_SI);
		si_regs.setStatus(si_regs.getStatus() | SI_STATUS_INTERRUPT);
		check_intr = true;
	}
	else if (address == SI_STATUS_REG)
	{
		si_regs.setStatus(data);
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_SI);
		check_intr = true;
	}
	else
		return false;
	return true;
}

//****************************************************************************
//** MEMORY::VIRTUAL TO PHYSICAL											**
//****************************************************************************
inline void* MEMORY::virtual_to_physical(dword address)
{
	address = (word) address;
	if (RDRAM::begining <= address && address <= RDRAM::end)
		return (void*) (rdram[address- RDRAM::begining]);
	else if (RDRAM_REGS::begining <= address && address <= RDRAM_REGS::end)
		return (void*) (rdram_regs[address - RDRAM_REGS::begining]);
	else if (SP_REGS::begining <= address && address <= SP_REGS::end)
		return (void*) (sp_regs[address - SP_REGS::begining]);
	else if (DPC_REGS::begining <= address && address <= DPC_REGS::end)
		return (void*) (dpc_regs[address - DPC_REGS::begining]);
	else if (DPS_REGS::begining <= address && address <= DPS_REGS::end)
		return (void*) (dps_regs[address - DPS_REGS::begining]);
	else if (MI_REGS::begining <= address && address <= MI_REGS::end)
		return (void*) (mi_regs[address - MI_REGS::begining]);
	else if (VI_REGS::begining <= address && address <= VI_REGS::end)
		return (void*) (vi_regs[address - VI_REGS::begining]);
	else if (AI_REGS::begining <= address && address <= AI_REGS::end)
		return (void*) (ai_regs[address - AI_REGS::begining]);
	else if (PI_REGS::begining <= address && address <= PI_REGS::end)
		return (void*) (pi_regs[address - PI_REGS::begining]);
	else if (RI_REGS::begining <= address && address <= RI_REGS::end)
		return (void*) (ri_regs[address - RI_REGS::begining]);
	else if (SI_REGS::begining <= address && address <= SI_REGS::end)
		return (void*) (si_regs[address - SI_REGS::begining]);
	else if (ROM::begining <= address && address <= ROM::end)
		return (void*) (rom[address - ROM::begining]);
	else if (PIF_ROM::begining <= address && address <= PIF_ROM::end)
		return (void*) (pif_rom[address - PIF_ROM::begining]);
	else if (PIF_RAM::begining <= address && address <= PIF_RAM::end)
		return (void*) (pif_ram[address - PIF_RAM::begining]);
	else if (0x80000000 <= address && address <= 0x9FFFFFFF) // Mirror 8 of 0x0000 0000 to 0x1FFF FFFF
		return (virtual_to_physical(address - 0x80000000));
	else if (0xA0000000 <= address && address <= 0xBFFFFFFF) // Mirror A of 0x0000 0000 to 0x1FFF FFFF
		return (virtual_to_physical(address - 0xA0000000));
	else
		cerr << endl << "ERROR: Address 0x" << hex << address << " not handled" << endl;
	return 0;
}

bool is_address_defined(dword address);

//****************************************************************************
//** SET METHODS					                                        **
//****************************************************************************

inline void RDRAM_REGS::setConfig(word arg)
{
	data.config = arg;
}
inline void RDRAM_REGS::setDeviceId(word arg)
{
	data.device_id = arg;
}
inline void RDRAM_REGS::setDelay(word arg)
{
	data.delay = arg;
}
inline void RDRAM_REGS::setMode(word arg)
{
	data.mode = arg;
}
inline void RDRAM_REGS::setRefInterval(word arg)
{
	data.ref_interval = arg;
}
inline void RDRAM_REGS::setRefRow(word arg)
{
	data.ref_row = arg;
}
inline void RDRAM_REGS::setRasInterval(word arg)
{
	data.ras_interval = arg;
}
inline void RDRAM_REGS::setMinInterval(word arg)
{
	data.min_interval = arg;
}
inline void RDRAM_REGS::setAddrSelect(word arg)
{
	data.addr_select = arg;
}
inline void RDRAM_REGS::setDeviceManuf(word arg)
{
	data.device_manuf = arg;
}

inline void SP_REGS::setMemAddr(word arg)
{
	data.mem_addr = arg;
}
inline void SP_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
inline void SP_REGS::setRdLen(word arg)
{
	data.rd_len = arg;
}
inline void SP_REGS::setWrLen(word arg)
{
	data.wr_len = arg;
}
inline void SP_REGS::setStatus(word arg)
{
	if (arg & SP_CLR_HALT)
		data.status &= ~SP_STATUS_HALT;
	if (arg & SP_CLR_BROKE)
		data.status &= ~SP_STATUS_BROKE;
	if (arg & SP_CLR_SSTEP)
		data.status &= ~SP_STATUS_SSTEP;
	if (arg & SP_CLR_INTR_BREAK)
		data.status &= ~SP_STATUS_INTR_BREAK;
	if (arg & SP_CLR_SIG0)
		data.status &= ~SP_STATUS_SIG0;
	if (arg & SP_CLR_SIG1)
		data.status &= ~SP_STATUS_SIG1;
	if (arg & SP_CLR_SIG2)
		data.status &= ~SP_STATUS_SIG2;
	if (arg & SP_CLR_SIG3)
		data.status &= ~SP_STATUS_SIG3;
	if (arg & SP_CLR_SIG4)
		data.status &= ~SP_STATUS_SIG4;
	if (arg & SP_CLR_SIG5)
		data.status &= ~SP_STATUS_SIG5;
	if (arg & SP_CLR_SIG6)
		data.status &= ~SP_STATUS_SIG6;
	if (arg & SP_CLR_SIG7)
		data.status &= ~SP_STATUS_SIG7;

	if (arg & SP_SET_HALT)
		data.status |= SP_STATUS_HALT;
	if (arg & SP_SET_SSTEP)
		data.status |= SP_STATUS_SSTEP;
	if (arg & SP_SET_INTR_BREAK)
		data.status |= SP_STATUS_INTR_BREAK;
	if (arg & SP_SET_SIG0)
		data.status |= SP_STATUS_SIG0;
	if (arg & SP_SET_SIG1)
		data.status |= SP_STATUS_SIG1;
	if (arg & SP_SET_SIG2)
		data.status |= SP_STATUS_SIG2;
	if (arg & SP_SET_SIG3)
		data.status |= SP_STATUS_SIG3;
	if (arg & SP_SET_SIG4)
		data.status |= SP_STATUS_SIG4;
	if (arg & SP_SET_SIG5)
		data.status |= SP_STATUS_SIG5;
	if (arg & SP_SET_SIG6)
		data.status |= SP_STATUS_SIG6;
	if (arg & SP_SET_SIG7)
		data.status |= SP_STATUS_SIG7;
}
inline void SP_REGS::setDmaFull(word arg)
{
	data.dma_full = arg;
}
inline void SP_REGS::setDmaBusy(word arg)
{
	data.dma_busy = arg;
}
inline void SP_REGS::setSemaphore(word arg)
{
	data.semaphore = 0;
}
inline void SP_REGS::setPc(word arg)
{
	data.pc = arg & 0xFFC;
}
inline void SP_REGS::setIbist(word arg)
{
	data.ibist = arg;
}

inline void DPC_REGS::setStart(word arg)
{
	data.start = arg;
}
inline void DPC_REGS::setEnd(word arg)
{
	data.end = arg;
}
inline void DPC_REGS::setCurrent(word arg)
{
	data.current = arg;
}
inline void DPC_REGS::setStatus(word arg)
{
	data.status = arg;
}
inline void DPC_REGS::setClock(word arg)
{
	data.clock = arg;
}
inline void DPC_REGS::setBufBusy(word arg)
{
	data.bufbusy = arg;
}
inline void DPC_REGS::setPipeBusy(word arg)
{
	data.pipebusy = arg;
}
inline void DPC_REGS::setTmem(word arg)
{
	data.tmem = arg;
}

inline void DPS_REGS::setTbist(word arg)
{
	data.tbist = arg;
}
inline void DPS_REGS::setTestMode(word arg)
{
	data.test_mode = arg;
}
inline void DPS_REGS::setBufTestAddr(word arg)
{
	data.buftest_addr = arg;
}
inline void DPS_REGS::setBufTestData(word arg)
{
	data.buftest_data = arg;
}

inline void MI_REGS::setInitMode(word arg)
{
	if (arg & MI_CLR_INIT)
		data.init_mode &= ~MI_MODE_INIT;
	if (arg & MI_CLR_EBUS)
		data.init_mode &= ~MI_MODE_EBUS;
	if (arg & MI_CLR_RDRAM)
		data.init_mode &= ~MI_MODE_RDRAM;

	if (arg & MI_SET_INIT)
		data.init_mode |= MI_MODE_INIT;
	if (arg & MI_SET_EBUS)
		data.init_mode |= MI_MODE_EBUS;
	if (arg & MI_SET_RDRAM)
		data.init_mode |= MI_MODE_RDRAM;

	if (arg & MI_CLR_DP_INTR)
		data.intr &= ~MI_INTR_DP;
}
inline void MI_REGS::setVersion(word arg)
{
	data.version = arg;
}
inline void MI_REGS::setIntr(word arg)
{
	data.intr = arg;
}
inline void MI_REGS::setIntrMask(word arg)
{
	if (arg & MI_INTR_MASK_CLR_SP )
		data.intr_mask &= ~MI_INTR_MASK_SP;
	if (arg & MI_INTR_MASK_CLR_SI )
		data.intr_mask &= ~MI_INTR_MASK_SI;
	if (arg & MI_INTR_MASK_CLR_AI )
		data.intr_mask &= ~MI_INTR_MASK_AI;
	if (arg & MI_INTR_MASK_CLR_VI )
		data.intr_mask &= ~MI_INTR_MASK_VI;
	if (arg & MI_INTR_MASK_CLR_PI )
		data.intr_mask &= ~MI_INTR_MASK_PI;
	if (arg & MI_INTR_MASK_CLR_DP )
		data.intr_mask &= ~MI_INTR_MASK_DP;

	if (arg & MI_INTR_MASK_SET_SP )
		data.intr_mask |= MI_INTR_MASK_SP;
	if (arg & MI_INTR_MASK_SET_SI )
		data.intr_mask |= MI_INTR_MASK_SI;
	if (arg & MI_INTR_MASK_SET_AI )
		data.intr_mask |= MI_INTR_MASK_AI;
	if (arg & MI_INTR_MASK_SET_VI )
		data.intr_mask |= MI_INTR_MASK_VI;
	if (arg & MI_INTR_MASK_SET_PI )
		data.intr_mask |= MI_INTR_MASK_PI;
	if (arg & MI_INTR_MASK_SET_DP )
		data.intr_mask |= MI_INTR_MASK_DP;
}

inline void VI_REGS::setStatus(word arg)
{
	data.status = arg;
	//ViStatusChanged
}
inline void VI_REGS::setOrigin(word arg)
{
	data.origin = arg;
}
inline void VI_REGS::setWidth(word arg)
{
	data.width = arg;
	//ViWidthChanged
}
inline void VI_REGS::setVintr(word arg)
{
}
inline void VI_REGS::setCurrent(word arg)
{
	data.current = arg;
}
inline void VI_REGS::setBurst(word arg)
{
	data.burst = arg;
}
inline void VI_REGS::setVsync(word arg)
{
	data.v_sync = arg;
}
inline void VI_REGS::setHsync(word arg)
{
	data.h_sync = arg;
}
inline void VI_REGS::setLeap(word arg)
{
	data.leap = arg;
}
inline void VI_REGS::setHstart(word arg)
{
	data.h_start = arg;
}
inline void VI_REGS::setVstart(word arg)
{
	data.v_start = arg;
}
inline void VI_REGS::setVburst(word arg)
{
	data.v_burst = arg;
}
inline void VI_REGS::setXscale(word arg)
{
	data.x_scale = arg;
}
inline void VI_REGS::setYscale(word arg)
{
	data.y_scale = arg;
}

inline void AI_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
inline void AI_REGS::setLen(word arg)
{
	data.len = arg;
	//AiLenChanged
}
inline void AI_REGS::setControl(word arg)
{
	data.control = arg & 0x1;
}
inline void AI_REGS::setStatus(word arg)
{
}
inline void AI_REGS::setDacrate(word arg)
{
	data.dacrate = arg;
}
inline void AI_REGS::setBitrate(word arg)
{
	data.bitrate = arg;
}

inline void PI_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
inline void PI_REGS::setCartAddr(word arg)
{
	data.cart_addr = arg;
}
inline void PI_REGS::setRdLen(word arg)
{
	data.rd_len = arg;
}
inline void PI_REGS::setWrLen(word arg)
{
	data.wr_len = arg;
}
inline void PI_REGS::setStatus(word arg)
{
	data.status = arg;
}
inline void PI_REGS::setBsdDom1Lat(word arg)
{
	data.bsd_dom1_lat = arg;
}
inline void PI_REGS::setBsdDom1Pwd(word arg)
{
	data.bsd_dom1_pwd = arg;
}
inline void PI_REGS::setBsdDom1Pgs(word arg)
{
	data.bsd_dom1_pgs = arg;
}
inline void PI_REGS::setBsdDom1Rls(word arg)
{
	data.bsd_dom1_rls = arg;
}
inline void PI_REGS::setBsdDom2Lat(word arg)
{
	data.bsd_dom2_lat = arg;
}
inline void PI_REGS::setBsdDom2Pwd(word arg)
{
	data.bsd_dom2_pwd = arg;
}
inline void PI_REGS::setBsdDom2Pgs(word arg)
{
	data.bsd_dom2_pgs = arg;
}
inline void PI_REGS::setBsdDom2Rls(word arg)
{
	data.bsd_dom2_rls = arg;
}

inline void RI_REGS::setMode(word arg)
{
	data.mode = arg;
}
inline void RI_REGS::setConfig(word arg)
{
	data.config = arg;
}
inline void RI_REGS::setCurrentLoad(word arg)
{
	data.current_load = arg;
}
inline void RI_REGS::setSelect(word arg)
{
	data.select = arg;
}
inline void RI_REGS::setRefresh(word arg)
{
	data.refresh = arg;
}
inline void RI_REGS::setLatency(word arg)
{
	data.latency = arg;
}
inline void RI_REGS::setRerror(word arg)
{
	data.rerror = arg;
}
inline void RI_REGS::setWerror(word arg)
{
	data.werror = arg;
}

inline void SI_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
inline void SI_REGS::setPifAddrRd64b(word arg)
{
	data.pif_addr_rd64b = arg;
}
inline void SI_REGS::setPifAddrWr64b(word arg)
{
	data.pif_addr_wr64b = arg;
}
inline void SI_REGS::setStatus(word arg)
{
}
