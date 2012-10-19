#pragma once

#define BYTE_MAX				255
#define HWORD_MAX				65535
#define WORD_MAX				4294967295
#define DWORD_MAX				18446744073709551615

#define ROM_HEADER_SIZE			0x1000
#define ROM_BOOT_CODE_SIZE		1008

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

#define DPC_START_REG			0x04100000
#define DPC_END_REG				0x04100004
#define DPC_CURRENT_REG			0x04100008
#define DPC_STATUS_REG			0x0410000C
#define DPC_CLOCK_REG			0x04100010
#define DPC_BUFBUSY_REG			0x04100014
#define DPC_PIPEBUSY_REG		0x04100018
#define DPC_TMEM_REG			0x0410001C

#define DPS_TBIST_REG			0x04200000
#define DPS_TEST_MODE_REG		0x04200004
#define DPS_BUFTEST_ADDR_REG	0x04200008
#define DPS_BUFTEST_DATA_REG	0x0420000C

#define MI_INIT_MODE_REG		0x04300000
#define MI_VERSION_REG			0x04300004
#define MI_INTR_REG				0x04300008
#define MI_INTR_MASK_REG		0x0430000C

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

#define AI_DRAM_ADDR_REG		0x04500000
#define AI_LEN_REG				0x04500004
#define AI_CONTROL_REG			0x04500008
#define AI_STATUS_REG			0x0450000C
#define AI_DACRATE_REG			0x04500010
#define AI_BITRATE_REG			0x04500014

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

#define RI_MODE_REG				0x04700000
#define RI_CONFIG_REG			0x04700004
#define RI_CURRENT_LOAD_REG		0x04700008
#define RI_SELECT_REG			0x0470000C
#define RI_REFRESH_REG			0x04700010
#define RI_LATENCY_REG			0x04700014
#define RI_RERROR_REG			0x04700018
#define RI_WERROR_REG			0x0470001C

#define SI_DRAM_ADDR_REG		0x04800000
#define SI_PIF_ADDR_RD64B_REG	0x04800004
#define SI_PIF_ADDR_WR64B_REG	0x04800010
#define SI_STATUS_REG			0x04800018

#define PI_BSD_DOM1_LAT_REG		0x10000000                 
#define PI_BSD_DOM1_PWD_REG		0x10000001                 
#define PI_BSD_DOM1_PGS_REG		0x10000002                 
#define PI_BSD_DOM1_RLS_REG		0x10000003                 
#define CLOCK_RATE				0x10000004  
#define BOOT_ADDRESS_OFFSET		0x10000008  
#define RELEASE_OFFSET			0x1000000C  
#define CRC1					0x10000010  
#define CRC2					0x10000014  
#define IMAGE_NAME				0x10000020  
#define MANUFACTURER_ID			0x1000003B  
#define CARTRIDGE_ID			0x1000003C 
#define COUNTRY_CODE			0x1000003E  

#define KSEG0					0x80000000
#define KSEG1					0xA0000000
#define KSEG2					0xC0000000
#define KSEG3					0xE0000000

#define	SI_STATUS_DMA_BUSY		0x0001
#define	SI_STATUS_RD_BUSY		0x0002
#define	SI_STATUS_DMA_ERROR		0x0008
#define	SI_STATUS_INTERRUPT		0x1000

#define	PI_STATUS_DMA_BUSY		0x01
#define	PI_STATUS_IO_BUSY		0x02
#define	PI_STATUS_ERROR			0x04

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
	inline word getRefNow()			{ return data.ref_row; };
	inline void setRefNow(word);
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

	inline byte *getDmem()		{ return data.dmem; };
	inline byte *getImem()		{ return data.imem; };

	inline word getMemAddr()	{ return data.mem_addr; };
	inline void setMemAddr(word);
	inline word getDramAddr()	{ return data.dram_addr; };
	inline void setDramAddr(word);
	inline word getRdLen()		{ return data.rd_len; };
	inline void setRdLen(word);
	inline word getWrLen()		{ return data.wr_len; };
	inline void set(word);
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
	inline void setBuftestData(word);

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
	inline word getVintr()		{ return data.v_intr; };
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
		word v_intr;
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
		inline void setBsdDom1pwd(word);
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
		inline word getError()			{ return data.error; };
		inline void setError(word);
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
		word error;
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
	MEMORY();

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

	inline void checkDMA(dword address);
	void dma_pi_write();
	void dma_pi_read();
	void dma_si_write();
	void dma_si_read();
	void dma_sp_write();
	void dma_sp_read();

	inline void setRom(ROM *r) { rom = r; };

private:
	ROM	*rom;
};

//****************************************************************************
//** MEMORY::READ															**
//****************************************************************************
template <typename Type>
Type MEMORY::read(dword address)
{
	byte dst[sizeof(Type)];
	memcpy(dst, virtual_to_physical(address), sizeof(Type));
	return (binary_to_type<Type>(dst));
}

//****************************************************************************
//** MEMORY::WRITE															**
//****************************************************************************
template <typename Type>
inline void MEMORY::write(Type data, dword address)
{
	void *dst = virtual_to_physical(address);
	data = type_to_binary<Type>(data);
	memcpy(dst, &data, sizeof(Type));

	checkDMA(address);
}

inline void MEMORY::checkDMA(dword address)
{
	address = (word) address;
	if (address == 0x04040008) //SP_RD_LEN_REG
		dma_sp_read();
	else if (address == 0x0404000C) // SP_WR_LEN_REG
		dma_sp_write();
	else if (address == 0x04600008) // PI_RD_LEN_REG
		dma_pi_read();
	else if (address == 0x0460000C) // PI_WR_LEN_REG
		dma_pi_write();
	else if (address == 0xA4600010) // PI_STATUS
		write<word>(0x0, 0x04600010);
	else if (address == 0x04800004) // SI_PIF_ADDR_RD64B_REG
		dma_si_read();
	else if (address == 0x04800010) // SI_PIF_ADDR_WR64B_REG
		dma_si_write();
	else if (0x80000000 <= address && address <= 0x9FFFFFFF)
		return checkDMA(address - 0x80000000); // "Mirror 8 of 0x0000 0000 to 0x1FFF FFFF"
	else if (0xA0000000 <= address && address <= 0xBFFFFFFF)
		return checkDMA(address - 0xA0000000); // "Mirror A of 0x0000 0000 to 0x1FFF FFFF";
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
		return (void*) ((*rom)[address - ROM::begining]);
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