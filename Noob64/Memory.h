#pragma once

#define BYTE_MAX			255
#define HWORD_MAX			65535
#define WORD_MAX			4294967295
#define DWORD_MAX			18446744073709551615

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
//** MEMORY SEGMENTS					                                    **
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

//RDRAM
class RDRAM : public MEM_SEG
{
public:
	RDRAM();
	static const word begining = 0x00000000;
	static const word end = 0x03EFFFFF;
	static const int size = 0x800000;
	void dump(void) const;
	void dump_range(word from, word to) const;
	byte data[size];
};

// RDRAM Registers
class RDRAM_REGS : public MEM_SEG
{
public:
	RDRAM_REGS();
	static const word begining = 0x03F00000;
	static const word end = 0x03FFFFFF;
	void dump(void) const;
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

// SP Registers
class SP_REGS : public MEM_SEG
{
public:
	SP_REGS();
	static const word begining = 0x04000000;
	static const word end = 0x0400FFFF;
	void dump(void) const;
	void dump_range_dmem(word from, word to) const;
	void dump_range_imem(word from, word to) const;
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

// DP Command Registers
class DPC_REGS : public MEM_SEG
{
public:
	DPC_REGS();
	static const word begining = 0x04100000;
	static const word end = 0x041FFFFF;
	void dump(void) const;
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

// DP Span Registers
class DPS_REGS : public MEM_SEG
{
public:
	DPS_REGS();
	static const word begining = 0x04200000;
	static const word end = 0x042FFFFF;
	void dump(void) const;
	struct	{
		word tbist;
		word test_mode;
		word buftest_addr;
		word buftest_data;
		byte unused[0xFFFF0];
	} data;
};

// MIPS Interface (MI) Registers
class MI_REGS : public MEM_SEG
{
public:
	MI_REGS();
	static const word begining = 0x04300000;
	static const word end = 0x043FFFFF;
	void dump(void) const;
	struct	{
		word init_mode;
		word version;
		word intr;
		word intr_mask;
		byte unused[0xFFFF0];
	} data;
};

// Video Interface (VI) Registers
class VI_REGS : public MEM_SEG
{
public:
	VI_REGS();
	static const word begining = 0x04400000;
	static const word end = 0x044FFFFF;
	void dump(void) const;
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

// Audio Interface (AI) Registers
class AI_REGS : public MEM_SEG
{
public:
	AI_REGS();
	static const word begining = 0x04500000;
	static const word end = 0x045FFFFF;
	void dump(void) const;
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

// Peripheral Interface (PI) Registers
class PI_REGS : public MEM_SEG
{
public:
	PI_REGS();
	static const word begining = 0x04600000;
	static const word end = 0x046FFFFF;
	void dump(void) const;
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

// RDRAM Interface (RI) Registers
class RI_REGS : public MEM_SEG
{
public:
	RI_REGS();
	static const word begining = 0x04700000;
	static const word end = 0x047FFFFF;
	void dump(void) const;
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

// Serial Interface (SI) Registers
class SI_REGS : public MEM_SEG
{
public:
	SI_REGS();
	static const word begining = 0x04800000;
	static const word end = 0x048FFFFF;
	void dump(void) const;
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

// Serial Interface (SI) Registers
class PIF_ROM : public MEM_SEG
{
public:
	PIF_ROM();
	static const word begining = 0x1FC00000;
	static const word end = 0x1FC007BF;
	void dump(void) const;
	byte data[0x7C0];
};


// Serial Interface (SI) Registers
class PIF_RAM : public MEM_SEG
{
public:
	PIF_RAM();
	static const word begining = 0x1FC007C0;
	static const word end = 0x1FC007FF;
	void dump(void) const;
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
	void dma_pi_write();
	void dma_pi_read();
	void dma_si_write();
	void dma_si_read();
	void dma_sp_write();
	void dma_sp_read();
};

//****************************************************************************
//** READ					                                                **
//****************************************************************************
template <typename Type>
inline Type MEMORY::read(dword address)
{
	byte dst[sizeof(Type)];
	memcpy(dst, virtual_to_physical(address), sizeof(Type));
	return (binary_to_type<Type>(dst));
}

//****************************************************************************
//** WRITE					                                                **
//****************************************************************************
template <typename Type>
inline void MEMORY::write(Type data, dword address)
{
	//Type *dst = (Type*) virtual_to_physical(address);
	void *dst = virtual_to_physical(address);
	data = type_to_binary<Type>(data);
	memcpy(dst, &data, sizeof(Type));
	if (((address == SI_REGS::begining) && (sizeof(Type) == 8)) || (address == SI_REGS::begining + 0x4))
	{
		dma_si_write();
		getchar();
	}
	if (((address == SI_REGS::begining + 0xC) && (sizeof(Type) == 8)) || (address == SI_REGS::begining + 0x10))
	{
		dma_si_read();
		getchar();
	}
	if (((address == SP_REGS::begining + 0x40004) && (sizeof(Type) == 8)) || (address == SP_REGS::begining + 0x40008))
	{
		dma_sp_read();
		getchar();
	}
	if (((address == SP_REGS::begining + 0x40008) && (sizeof(Type) == 8)) || (address == SP_REGS::begining + 0x4000C))
	{
		dma_sp_write();
		getchar();
	}
	if (((address ==PI_REGS::begining + 0x4) && (sizeof(Type) == 8)) || (address == PI_REGS::begining + 0x8))
	{
		dma_pi_read();
		getchar();
	}
	if (((address == PI_REGS::begining + 0x8) && (sizeof(Type) == 8)) || (address == PI_REGS::begining + 0xC))
	{
		dma_pi_write();
		getchar();
	}
}

//****************************************************************************
//** CONVERTS VIRTUAL ADDRESSES TO PHYSICAL ADDRESSES                       **
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