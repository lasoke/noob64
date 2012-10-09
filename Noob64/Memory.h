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
	const void *ptr;
	virtual void dump(void) const = 0;
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
private:
	byte rdram[size];
};

// RDRAM Registers
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

// SP Registers
class SP_REGS : public MEM_SEG
{
public:
	SP_REGS();
	static const word begining = 0x04000000;
	static const word end = 0x0400FFFF;
	void dump(void) const;
private:
	struct {
		byte dmem[0x1000];
		byte imem[0x1000];
		byte unused[0x3E000];
		word mem_addr_reg;
		word dram_addr_reg;
		word rd_len_reg;
		word wr_len_reg;
		word status_reg;
		word dma_full_reg;
		word dma_busy_reg;
		word semaphore_reg;
		byte unused2[0x3FFE0];
		word pc_reg;
		word ibist_reg;
		byte unused3[0x7FFF8];
	} data;
};

class DPC_REGS : public MEM_SEG
{
public:
	DPC_REGS();
	static const word begining = 0x04100000;
	static const word end = 0x041FFFFF;
	void dump(void) const;
private:
	struct
	{
		word start_reg;
		word end_reg;
		word current_reg;
		word status_reg;
		word clock_reg;
		word bufbusy_reg;
		word pipebusy_reg;
		word tmem_reg;
		byte unused[0xFFFE0];
	} data;
};

class DPS_REGS : MEM_SEG
{
public:
	DPS_REGS();
	static const word begining = 0x04200000;
	static const word end = 0x042FFFFF;
	void dump(void) const;
private:
	struct
	{
		word tbist_reg;
		word test_mode_reg;
		word buftest_addr_reg;
		word buftest_data_reg;
		byte unused[0xFFFF0];
	} data;
};

class MI_REGS : MEM_SEG
{
public:
	MI_REGS();
	static const word begining = 0x04300000;
	static const word end = 0x043FFFFF;
	void dump(void) const;
private:
	struct
	{
		word init_mode_reg;
		word version_reg;
		word intr_reg;
		word intr_mask_reg;
		byte unused[0xFFFF0];
	} data;
};

class VI_REGS : MEM_SEG
{
public:
	VI_REGS();
	static const word begining = 0x04400000;
	static const word end = 0x044FFFFF;
	void dump(void) const;
private:
	struct
	{
		word status_reg;
		word origin_reg;
		word width_reg;
		word v_intr_reg;
		word current_reg;
		word burst_reg;
		word v_sync_reg;
		word h_sync_reg;
		word leap_reg;
		word h_start_reg;
		word v_start_reg;
		word v_burst_reg;
		word x_scale_reg;
		word y_scale_reg;
		byte unused[0xFFFC8];
	} data;
};

class AI_REGS : MEM_SEG
{
public:
	AI_REGS();
	static const word begining = 0x04500000;
	static const word end = 0x045FFFFF;
	void dump(void) const;
private:
	struct
	{
		word dram_addr_reg;
		word len_reg;
		word control_reg;
		word status_reg;
		word dacrate_reg;
		word bitrate_reg;
		byte unused[0xFFFE8];
	} data;
};

class PI_REGS : MEM_SEG
{
public:
	PI_REGS();
	static const word begining = 0x04600000;
	static const word end = 0x046FFFFF;
	void dump(void) const;
private:
	struct
	{
		word dram_addr_reg;
		word cart_addr_reg;
		word rd_len_reg;
		word wr_len_reg;
		word status_reg;
		word bsd_dom1_lat_reg;
		word bsd_dom1_pwd_reg;
		word bsd_dom1_pgs_reg;
		word bsd_dom1_rls_reg;
		word bsd_dom2_lat_reg;
		word bsd_dom2_pwd_reg;
		word bsd_dom2_pgs_reg;
		word bsd_dom2_rls_reg;
		byte unused[0xFFFCC];
	} data;
};

// RDRAM Interface (RI) Registers
class RI_REGS : MEM_SEG
{
public:
	RI_REGS();
	static const word begining = 0x04700000;
	static const word end = 0x047FFFFF;
	void dump(void) const;
private:
	struct
	{
		word mode_reg;
		word config_reg;
		word current_load_reg;
		word select_reg;
		word refresh_reg;
		word latency_reg;
		word error_reg;
		word werror_reg;
		byte unused[0xFFFE0];
	} data;
};	// 0x047FFFFF

class SI_REGS : MEM_SEG
{
public:
	SI_REGS();
	static const word begining = 0x04800000;
	static const word end = 0x048FFFFF;
	void dump(void) const;
private:
	struct
	{
		word dram_addr_reg;
		word pif_addr_rd64b_reg;
		word reserved;
		word reserved2;
		word pif_addr_wr64b_reg;
		word reserved3;
		word status_reg;
		byte unused[0xFFFE4];
	} data;
};

//****************************************************************************
//** MEMORY					                                                **
//****************************************************************************
class MEMORY
{
public:
	MEMORY();

	RDRAM* rdram;
	RDRAM_REGS* rdram_regs;
	SP_REGS* sp_regs;
	DPC_REGS* dpc_regs;
	DPS_REGS* dps_regs;
	MI_REGS* mi_regs;
	VI_REGS* vi_regs;
	AI_REGS* ai_regs;
	PI_REGS* pi_regs;
	RI_REGS* ri_regs;
	SI_REGS* si_regs;
	// TODO: declare the other segments

	inline void* virtual_to_physical(dword address);
	template <typename Type> inline Type read(dword address);
	template <typename Type> inline void write(Type data, dword address);
};

//****************************************************************************
//** READ					                                                **
//****************************************************************************
template <typename Type>
inline Type MEMORY::read(dword address)
{
	Type dst[1];
	memcpy(dst, virtual_to_physical(address), sizeof(Type));
	return dst[0];
}

//****************************************************************************
//** WRITE					                                                **
//****************************************************************************
template <typename Type>
inline void MEMORY::write(Type data, dword address)
{
	Type *dst = (Type*) virtual_to_physical(address);
	*dst = data;
	//memcpy(dst, &data, sizeof(Type));
}

//****************************************************************************
//** CONVERTS VIRTUAL ADDRESSES TO PHYSICAL ADDRESSES                       **
//****************************************************************************
inline void* MEMORY::virtual_to_physical(dword address)
{
	if (RDRAM::begining <= address && address <= RDRAM::end)
	{
		//cout << "[RRDRAM]";
		return (void*) ((char*) rdram->ptr + address - RDRAM::begining);
	}
	else if (RDRAM_REGS::begining <= address && address <= RDRAM_REGS::end)
	{
		//cout << "[RRDRAM_REGS]";
		return (void*) ((char*) rdram_regs->ptr + address - RDRAM_REGS::begining);
	}
	else
		cout << "ERROR: Address not handled (yet)" << endl;
	return 0;
}