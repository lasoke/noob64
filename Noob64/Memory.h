#pragma once

#define BYTE_MAX			255
#define HWORD_MAX			65535
#define WORD_MAX			4294967295
#define DWORD_MAX			18446744073709551615

#define ROM_HEADER_SIZE		0x1000
#define ROM_BOOT_CODE_SIZE	1008

typedef unsigned __int8		byte;
typedef unsigned __int16	hword;
typedef unsigned __int32	word;
typedef unsigned __int64	dword;

typedef __int8				sbyte;
typedef __int16				shword;
typedef __int32				sword;
typedef __int64				sdword;

typedef float				s; // Single-Precision	Floating-Point Format:	[31:sign;30-23-exponent;22-0:fraction]
typedef double				d; // Double-Precision	Floating-Point Format:	[63:sign;62-52:exponent;51-0:fraction]
typedef long				w; // Word				Fixed-Point Format:		[31:sign;30-0:int]
typedef long long int		l; // Longword			Fixed-Point Format:		[63:sign;62-0:int]

//****************************************************************************
//** MEMORY SEGMENT															**
//****************************************************************************
class MEM_SEG
{
public:
	MEM_SEG();
	static const word begining;
	static const word end;
	//static bool contains(word address) { return begining <= address && address <= end; };
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
	ROM(void);
	ROM(char* filename);
	static const word begining = 0x10000000;
	static const word end = 0x1FBFFFFF;
	void dump(void) const;

	word getClock();
	word getPc();
	word getRelease();
	word getCRC1();
	word getCRC2();
	string getName();
	word getManufacturer();
	hword getCartridge();
	hword getCountry();

private:
	struct { // ROM Header
	   byte		PI_BSD_DOM1_LAT_REG;
	   byte		PI_BSD_DOM1_PWD_REG;
	   byte		PI_BSD_DOM1_PGS_REG;
	   byte		PI_BSD_DOM1_RLS_REG;
	   word		clock;
	   word		pc;
	   word		release;
	   word		CRC1;
	   word		CRC2;
	   word		Unknown[2];
	   byte		name[20];
	   word		unknown;
	   word		manufacturer;
	   hword	cartridge;
	   hword	country;
	   word		bootcode[ROM_BOOT_CODE_SIZE];
	} header;
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
	inline word getDramAddr()	{ return data.dram_addr; };
	inline word getRdLen()		{ return data.rd_len; };
	inline word getWrLen()		{ return data.wr_len; };
	inline word getStatus()		{ return data.status; };
	inline word getDmaFull()	{ return data.dma_full; };
	inline word getDmaBusy()	{ return data.dma_busy; };
	inline word getSemaphore()	{ return data.semaphore; };
	inline word getPc()			{ return data.pc; };
	inline word getIbist()		{ return data.ibist; };
	
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
	inline word getEnd()		{ return data.end; };
	inline word getCurrent()	{ return data.current; };
	inline word getStatus()		{ return data.status; };
	inline word getClock()		{ return data.clock; };
	inline word getBufBusy()	{ return data.bufbusy; };
	inline word getPipeBusy()	{ return data.pipebusy; };
	inline word getTmem()		{ return data.tmem; };

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
	inline word getTestMode()		{ return data.test_mode; };
	inline word getBufTestAddr()	{ return data.buftest_addr; };
	inline word getBufTestData()	{ return data.buftest_data; };

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
	inline word getVersion()	{ return data.version; };
	inline word getIntr()		{ return data.intr; };
	inline word getIntrMask()	{ return data.intr_mask; };

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
	inline word getOrigin()		{ return data.origin; };
	inline word getWidth()		{ return data.width; };
	inline word getVintr()		{ return data.v_intr; };
	inline word getCurrent()	{ return data.current; };
	inline word getBurst()		{ return data.burst; };
	inline word getVsync()		{ return data.v_sync; };
	inline word getHsync()		{ return data.h_sync; };
	inline word getLeap()		{ return data.leap; };
	inline word getHstart()		{ return data.h_start; };
	inline word getVstart()		{ return data.v_start; };
	inline word getVburst()		{ return data.v_burst; };
	inline word getXscale()		{ return data.x_scale; };
	inline word getYscale()		{ return data.y_scale; };

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
	inline word getLen()		{ return data.len; };
	inline word getControl()	{ return data.control; };
	inline word getStatus()		{ return data.status; };
	inline word getDacrate()	{ return data.dacrate; };
	inline word getBitrate()	{ return data.bitrate; };

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
		inline word getCartAddr()	{ return data.cart_addr; };
		inline word getRdLen()		{ return data.rd_len; };
		inline word getWrLen()		{ return data.wr_len; };
		inline word getStatus()		{ return data.status; };
		inline word getBsdDom1Lat()	{ return data.bsd_dom1_lat; };
		inline word getBsdDom1Pwd()	{ return data.bsd_dom1_pwd; };
		inline word getBsdDom1Pgs()	{ return data.bsd_dom1_pgs; };
		inline word getBsdDom1Rls()	{ return data.bsd_dom1_rls; };
		inline word getBsdDom2Lat()	{ return data.bsd_dom2_lat; };
		inline word getBsdDom2Pwd()	{ return data.bsd_dom2_pwd; };
		inline word getBsdDom2Pgs()	{ return data.bsd_dom2_pgs; };
		inline word getBsdDom2Rls()	{ return data.bsd_dom2_rls; };

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
		inline word getConfig()			{ return data.config; };
		inline word getCurrentLoad()	{ return data.current_load; };
		inline word getSelect()			{ return data.select; };
		inline word getRefresh()		{ return data.refresh; };
		inline word getLatency()		{ return data.latency; };
		inline word getError()			{ return data.error; };
		inline word getWerror()			{ return data.werror; };

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
	inline word getPifAddrRd64b()	{ return data.pif_addr_rd64b; };
	inline word getPifAddrWr64b()	{ return data.pif_addr_wr64b; };
	inline word getStatus()			{ return data.status; };

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
	word		CIC_Chip;

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
	if (address == 0x04040008) //SP_RD_LEN_REG
	{
		// SP read DMA length
		dma_sp_read();

	}
	else if (address == 0x0404000C) // SP_WR_LEN_REG
	{
		// SP write DMA length
		dma_sp_write();

	}
	else if (address == 0x04600008) // PI_RD_LEN_REG
	{
		// PI read length
		dma_pi_read();

	}
	else if (address == 0x0460000C) // PI_WR_LEN_REG
	{
		// PI write length
		dma_pi_write();
	}
	else if (address == 0x04800004) // SI_PIF_ADDR_RD64B_REG
	{
		// SI address read 64B
		dma_si_read();
	}
	else if (address == 0x04800010) // SI_PIF_ADDR_WR64B_REG
	{
		// SI address write 64B
		dma_si_write();
	}
}

//****************************************************************************
//** MEMORY::VIRTUAL TO PHYSICAL											**
//****************************************************************************
inline void* MEMORY::virtual_to_physical(dword address)
{
	address = (word) address;
	if (RDRAM::begining <= address && address <= RDRAM::end)
	{
		// cout << "[RRDRAM]";
		return (void*) (rdram[address- RDRAM::begining]);
	}
	else if (RDRAM_REGS::begining <= address && address <= RDRAM_REGS::end)
	{
		// cout << "[RRDRAM_REGS]";
		return (void*) (rdram_regs[address - RDRAM_REGS::begining]);
	}
	else if (SP_REGS::begining <= address && address <= SP_REGS::end)
	{
		// cout << "[SP_REGS]";
		return (void*) (sp_regs[address - SP_REGS::begining]);
	}
	else if (DPC_REGS::begining <= address && address <= DPC_REGS::end)
	{
		// cout << "[DPC_REGS]";
		return (void*) (dpc_regs[address - DPC_REGS::begining]);
	}
	else if (DPS_REGS::begining <= address && address <= DPS_REGS::end)
	{
		// cout << "[DPS_REGS]";
		return (void*) (dps_regs[address - DPS_REGS::begining]);
	}
	else if (MI_REGS::begining <= address && address <= MI_REGS::end)
	{
		// cout << "[MI_REGS]";
		return (void*) (mi_regs[address - MI_REGS::begining]);
	}
	else if (VI_REGS::begining <= address && address <= VI_REGS::end)
	{
		// cout << "[VI_REGS]";
		return (void*) (vi_regs[address - VI_REGS::begining]);
	}
	else if (AI_REGS::begining <= address && address <= AI_REGS::end)
	{
		// cout << "[AI_REGS]";
		return (void*) (ai_regs[address - AI_REGS::begining]);
	}
	else if (PI_REGS::begining <= address && address <= PI_REGS::end)
	{
		// cout << "[PI_REGS]";
		return (void*) (pi_regs[address - PI_REGS::begining]);
	}
	else if (RI_REGS::begining <= address && address <= RI_REGS::end)
	{
		// cout << "[RI_REGS]";
		return (void*) (ri_regs[address - RI_REGS::begining]);
	}
	else if (SI_REGS::begining <= address && address <= SI_REGS::end)
	{
		// cout << "[SI_REGS]";
		return (void*) (si_regs[address - SI_REGS::begining]);
	}
	else if (ROM::begining <= address && address <= ROM::end)
	{
		// cout << "[ROM]";
		return (void*) ((*rom)[address - ROM::begining]);
	}
	else if (0x80000000 <= address && address <= 0x9FFFFFFF)
	{
		// cout << "Mirror 8 of 0x0000 0000 to 0x1FFF FFFF";
		return (virtual_to_physical(address - 0x80000000));
	}
	else if (0xA0000000 <= address && address <= 0xBFFFFFFF)
	{
		// cout << "Mirror A of 0x0000 0000 to 0x1FFF FFFF";
		return (virtual_to_physical(address - 0xA0000000));
	}
	else
		cout << endl << "ERROR: Address 0x" << hex << address << " not handled" << endl;
	return 0;
}

