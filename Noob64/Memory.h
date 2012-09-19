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

//RDRAM is the class which contains the memory of the emulator
//and every relatives functions
class RDRAM
{
public:
	RDRAM();
	~RDRAM();

	template <typename Type>
	Type read(dword address);

	template <typename Type>
	void write(Type data, dword address);

	static const int size = 0x800000;

	word config_reg;
	word device_id_reg;
	word delay_reg;
	word mode_reg;
	word ref_interval_reg;
	word ref_row_reg;
	word ras_interval_reg;
	word min_interval_reg;
	word addr_select_reg;
	word device_manuf_reg;

	void debug(void);
	void debug(bool registers, word start, word end);

private:
	template <typename Type>
	void print_word(dword address);

	byte rdram[size];
};

//print the word of the type Type contains at the address given
//in the parameter to the console
template <typename Type>
inline void RDRAM::print_word(dword address)
{
	int remainder;
	if (remainder = address % 4)
	{
		read<word>(address - remainder);
		if (sizeof(Type) > (4 - remainder))
		{
			read<word>(address + (4 - remainder));
		}
	}
	else
	{
		read<word>(address);
	}
}

//Read and return a data of the type Type contains at the address given in argument
template <typename Type>
inline Type RDRAM::read(dword address)
{
	Type data = *((Type *)(rdram + address));
#if defined DEBUG
		char addr[8];
		_itoa_s((int) address, addr, 8, 16);
		cout << " *READING* address : " << format_number(string(8 - strlen(addr), '0') + addr, ' ', 2) << " data : ";
		char mem[64];
		_itoa_s((int) data, mem, 64, 2);
		cout << format_number(string(sizeof(Type) * 8 - strlen(mem), '0') + mem, ' ', 4);
#endif // DEBUG
	return data;
}

//Write a data of the type Type into the RAM at the address given in argument
template <typename Type>
inline void RDRAM::write(Type data, dword address)
{
	*((Type *)(rdram + address)) = data;
#if defined DEBUG
		cout << " *WRITING* " << data << " @ " << address << " : ";
		print_word<Type>(address);
#endif // DEBUG
}

/*

class SP
{
private:
	byte dmem[4000];
	byte imem[4000];

	word mem_addr_reg;
	word dram_addr_reg;
	word rd_len_reg;
	word wr_len_reg;
	word status_reg;
	word dma_full_reg;
	word dma_busy_reg;
	word semaphore_reg;
	word pc_reg;
	word ibist_reg;
};

class DPC
{
private:
   word start_reg;
   word end_reg;
   word current_reg;
   word status_reg;
   word clock_reg;
   word bufbusy_reg;
   word pipebusy_reg;
   word tmem_reg;
};

class DPS
{
private:
   word tbist_reg;
   word test_mode_reg;
   word buftest_addr_reg;
   word buftest_data_reg;
};

class MI
{
private:
   word init_mode_reg;
   word version_reg;
   word intr_reg;
   word intr_mask_reg;
};

class VI
{
private:
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
   //word delay_reg;
};

class AI
{
private:
   word dram_addr_reg;
   word len_reg;
   word control_reg;
   word status_reg;
   word dacrate_reg;
   word bitrate_reg;
   word next_delay_reg;
   word next_len_reg;
   word current_delay_reg;
   word current_len_reg;
};

class PI
{
private:
   word dram_addr_reg;
   word cart_addr_reg;
   word rd_len_reg;
   word wr_len_reg;
   word read_status_reg;
   word bsd_dom1_lat_reg;
   word bsd_dom1_pwd_reg;
   word bsd_dom1_pgs_reg;
   word bsd_dom1_rls_reg;
   word bsd_dom2_lat_reg;
   word bsd_dom2_pwd_reg;
   word bsd_dom2_pgs_reg;
   word bsd_dom2_rls_reg;
};

class RI
{
private:
   word mode_reg;
   word config_reg;
   word current_load_reg;
   word select_reg;
   word refresh_reg;
   word latency_reg;
   word error_reg;
   word werror_reg;
};

class SI
{
private:
   word dram_addr_reg;
   word pif_addr_rd64b_reg;
   word pif_addr_wr64b_reg;
   word status_reg;
};


/*
  00000000-03EFFFFF   RDRAM Memory
  03F00000-03FFFFFF   RDRAM Registers

  04000000-040FFFFF   SP Registers
  04100000-041FFFFF   DP Command Registers
  04200000-042FFFFF   DP Span Registers
  04300000-043FFFFF   MIPS Interface (MI) Registers
  04400000-044FFFFF   Video Interface (VI) Registers
  04500000-045FFFFF   Audio Interface (AI) Registers
  04600000-046FFFFF   Peripheral Interface (PI) Registers
  04700000-047FFFFF   RDRAM Interface (RI) Registers
  04800000-048FFFFF   Serial Interface (SI) Registers
  04900000-04FFFFFF   Unused
  05000000-05FFFFFF   Cartridge Domain 2 Address 1
  06000000-07FFFFFF   Cartridge Domain 1 Address 1
  08000000-0FFFFFFF   Cartridge Domain 2 Address 2
  10000000-1FBFFFFF   Cartridge Domain 1 Address 2
  1FC00000-1FC007BF   PIF Boot ROM
  1FC007C0-1FC007FF   PIF RAM
  1FC00800-1FCFFFFF   Reserved
  1FD00000-7FFFFFFF   Cartridge Domain 1 Address 3
  80000000-FFFFFFFF   External SysAD Device
  */